package com.howthe.flux
//imports necessary to build the framework
import android.Manifest
import android.annotation.SuppressLint
import android.app.PendingIntent
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.content.pm.PackageManager
import android.hardware.usb.UsbDevice
import android.hardware.usb.UsbManager
import android.os.Bundle
import android.util.Log
import android.view.WindowManager
import android.widget.Button
import android.widget.SeekBar
import android.widget.TextView
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import org.opencv.android.CameraBridgeViewBase
import org.opencv.android.OpenCVLoader
import org.opencv.core.CvType
import org.opencv.core.Mat
import org.opencv.core.MatOfPoint
import org.opencv.core.Point
import org.opencv.core.Rect
import org.opencv.core.Scalar
import com.hoho.android.usbserial.driver.UsbSerialPort
import com.hoho.android.usbserial.driver.UsbSerialProber
import org.opencv.core.Core
import org.opencv.imgproc.Imgproc
import org.opencv.core.Size
import android.graphics.Bitmap
import android.os.Environment
import org.opencv.android.Utils
import android.content.ContentValues
import android.provider.MediaStore
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
//definition of main class,  which handles all logic
class MainActivity : AppCompatActivity(), CameraBridgeViewBase.CvCameraViewListener2 {
    //declaration of variables
    private var brightnessThreshold = 150.0

    private var isPreviewActive = false
    private var isOpenCvInitialized = false
    private val cameraPermissionRequestCode = 100
    //initialisation of the camera and USB port
    private lateinit var openCvCameraView: CameraBridgeViewBase
    private lateinit var buttonTogglePreview: Button
    private lateinit var usbManager: UsbManager
    private var serialPort: UsbSerialPort? = null
    private val lowerBlue  = Scalar(100.0, 100.0,  30.0)
    private val upperBlue  = Scalar(160.0, 255.0, 160.0)
    private val lowerBlack = Scalar(  0.0,   0.0, brightnessThreshold)
    private val upperBlack = Scalar(170.0, 255.0, 255.0)
    //variables for limitin fps to 15
    private val frameInterval = 1000L / 15L
    @Volatile private var lastProcessTime = 0L
    @Volatile private var busy            = false
    //USB companion definition
    companion object {
        private const val ACTION_USB_PERMISSION = "com.example.myapplication.USB_PERMISSION"
    }
    //creating the object that handles USB transmissions
    private val usbReceiver = object : BroadcastReceiver() {
        override fun onReceive(context: Context, intent: Intent) {
            if (intent.action == ACTION_USB_PERMISSION &&
                intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)
            ) {
                val device = intent.getParcelableExtra<UsbDevice>(UsbManager.EXTRA_DEVICE)
                if (device != null) {
                    connectToDevice(device)
                }
            }
        }
    }

    //declaration of the function that starts on launch and initializes variables
    @SuppressLint("ClickableViewAccessibility", "SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        //defining UI elements
        buttonTogglePreview = findViewById(R.id.buttonTogglePreview)
        openCvCameraView = findViewById(R.id.cameraView)
        usbManager = getSystemService(USB_SERVICE) as UsbManager
        val thresholdSeek = findViewById<SeekBar>(R.id.thresholdSeek)
        thresholdSeek.progress = brightnessThreshold.toInt()
        findViewById<TextView>(R.id.thresholdValue)?.text = "Threshold: ${thresholdSeek.progress}"

        //hooking up UI elements with functions
        thresholdSeek.onChange {
            brightnessThreshold = it.toDouble()
            findViewById<TextView>(R.id.thresholdValue)?.text = "Threshold: $it"
        }

        findViewById<Button>(R.id.btnUsbConnect).setOnClickListener {
            requestPermissionAndConnect()
        }

        buttonTogglePreview.setOnClickListener {
            requestPermissionAndConnect()
            if (isPreviewActive) {
                openCvCameraView.disableView()
            } else {
                openCvCameraView.setCameraPermissionGranted()
                openCvCameraView.enableView()
            }
            updateControls()
        }

        //initialising OpenCV
        isOpenCvInitialized = OpenCVLoader.initLocal()
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA)
            != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.CAMERA),
                cameraPermissionRequestCode
            )
            Core.setUseOptimized(true)
            Core.setNumThreads(Runtime.getRuntime().availableProcessors())
        }
        openCvCameraView.setCvCameraViewListener(this)
        openCvCameraView.setCameraIndex(2)
        openCvCameraView.setMaxFrameSize(700, 500)

        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        Core.setUseOptimized(true)
        Core.setNumThreads(Runtime.getRuntime().availableProcessors())

        updateControls()
    }
    
    //function to request and establish USB connection
    private fun requestPermissionAndConnect() {
        Log.d("USB", "requestPermissionAndConnect called")
        val drivers = UsbSerialProber.getDefaultProber().findAllDrivers(usbManager)
        if (drivers.isEmpty()) {
            return
        }

        val device = drivers[0].device

        if (usbManager.hasPermission(device)) {
            connectToDevice(device)
            return
        }

        val permissionIntent = PendingIntent.getBroadcast(
            this, 0, Intent(ACTION_USB_PERMISSION), PendingIntent.FLAG_IMMUTABLE
        )

        try {
            unregisterReceiver(usbReceiver)
        } catch (_: Exception) {
        }

        val filter = IntentFilter(ACTION_USB_PERMISSION)
        registerReceiver(usbReceiver, filter, RECEIVER_NOT_EXPORTED)

        Log.d("USB", "Requesting permission…")
        if (usbManager.hasPermission(device)) {
            connectToDevice(device)
        } else {
            usbManager.requestPermission(device, permissionIntent)
        }

    }

    //function do execute the USB connection
    private fun connectToDevice(device: UsbDevice) {
        val connection = usbManager.openDevice(device)
        if (connection == null) {
            return
        }

        val driver = UsbSerialProber.getDefaultProber().probeDevice(device)
        if (driver == null || driver.ports.isEmpty()) {
            return
        }

        val port = driver.ports[0]
        try {
            //initialisation of the serial port
            port.open(connection)
            port.setParameters(9600, 8, UsbSerialPort.STOPBITS_1, UsbSerialPort.PARITY_NONE)
            serialPort = port
            Toast.makeText(this, "USB Connected", Toast.LENGTH_SHORT).show()
        } catch (e: Exception) {
            Log.e("USB", "Failed to open port", e)
        }
    }

    //function for sending data packages to the EVN via USB
    private fun send(marker: Char, x: Int, y: Int) {
        val port = serialPort ?: return
        val x = x.coerceIn(0, 255)
        val y = y.coerceIn(0, 255)
        try {
            val data = byteArrayOf(
                marker.code.toByte(),
                x.toByte(),
                y.toByte()
            )
            port.write(data, 10)
        } catch (e: Exception) {
            Log.e("BT-SEND", "Write failed", e)
        }
    }

    //function to update UI elements
    private fun updateControls() {
        if (!isOpenCvInitialized) {
            buttonTogglePreview.isEnabled = false
        } else {
            buttonTogglePreview.isEnabled = true
            buttonTogglePreview.text =
                if (isPreviewActive) "Stop Processing" else "Start Processing"
        }
    }

    //initialisation of the function that starts when the camera recieves its first frame
    override fun onCameraViewStarted(width: Int, height: Int) {
        isPreviewActive = true
        updateControls()
        //pre-initialisation of image mats for performance
        rgbaMat         = Mat()
        rgbMat          = Mat()
        rgbCopy         = Mat()
        hsv1            = Mat()
        hsv2            = Mat()
        blueMask        = Mat()
        blueWhiteMask   = Mat()
        blackMask       = Mat()
        inverted        = Mat()
        holes           = Mat()
        filledBlackMask = Mat()
        cleanedMask     = Mat()
        frameMat        = Mat()
        floodMask1      = Mat()
        mask            = Mat()
        contourMask     = Mat()
        hierarchy       = Mat()
        contours        = mutableListOf()
        kernel          = Imgproc.getStructuringElement(
            Imgproc.MORPH_RECT, Size(5.0, 5.0)
        )
        lastFrame       = Mat()
    }
    
    //function to terminate camera view
    override fun onCameraViewStopped() {
        isPreviewActive = false
        updateControls()
    }

    //optional function to save images during the processing for documentation and debugging
    private fun saveMatAsJpeg(mat: Mat) {
        val bmp = Bitmap.createBitmap(mat.cols(), mat.rows(), Bitmap.Config.ARGB_8888)
        Utils.matToBitmap(mat, bmp)

        val filename = "IMG_${System.currentTimeMillis()}.jpg"
        val values = ContentValues().apply {
            put(MediaStore.Images.Media.DISPLAY_NAME, filename)
            put(MediaStore.Images.Media.MIME_TYPE, "image/jpeg")
            put(MediaStore.Images.Media.RELATIVE_PATH, Environment.DIRECTORY_PICTURES + "/FLUX")
        }
        val uri = contentResolver.insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values)
        uri?.let {
            contentResolver.openOutputStream(it)?.use { out ->
                bmp.compress(Bitmap.CompressFormat.JPEG, 100, out)
            }
        } ?: run {
        }

    }
    //first decleration of image mats. lateinit variables dont initialize until called
    private lateinit var rgbaMat:         Mat
    private lateinit var rgbMat:          Mat
    private lateinit var rgbCopy:         Mat
    private lateinit var hsv1:            Mat
    private lateinit var hsv2:            Mat
    private lateinit var blueMask:        Mat
    private lateinit var blueWhiteMask:   Mat
    private lateinit var blackMask:       Mat
    private lateinit var inverted:        Mat
    private lateinit var holes:           Mat
    private lateinit var filledBlackMask: Mat
    private lateinit var cleanedMask:     Mat
    private lateinit var frameMat:        Mat
    private lateinit var floodMask1:      Mat
    private lateinit var mask:            Mat
    private lateinit var contourMask:     Mat
    private lateinit var hierarchy:       Mat
    private lateinit var contours:        MutableList<MatOfPoint>
    private lateinit var kernel:          Mat
    private lateinit var lastFrame:       Mat

    //debugging configurations
    var hasSaved=false
    var findDir=true
    //main loop function that runs on every frame
    override fun onCameraFrame(inputFrame: CameraBridgeViewBase.CvCameraViewFrame?): Mat {
        //intake and formatting of frame
        inputFrame!!.rgba().copyTo(rgbaMat)
        //fps limit to 15fps
        val now = System.currentTimeMillis()
        if (!busy && now - lastProcessTime >= frameInterval) {
            busy = true
            lastProcessTime = now
            GlobalScope.launch(Dispatchers.Default) {
                //image processes
                Imgproc.cvtColor(rgbaMat, rgbMat, Imgproc.COLOR_RGBA2RGB)//conversion from rgba to rgb
                rgbMat.copyTo(rgbCopy)
                if (hasSaved) saveMatAsJpeg(rgbMat)
                Imgproc.cvtColor(rgbMat, hsv1, Imgproc.COLOR_RGB2HSV)
                if (findDir) findTurnDirection(hsv1)//if requested, finds the direction of the mat
                Core.inRange(hsv1, lowerBlue, upperBlue, blueMask)
                Imgproc.cvtColor(blueMask, blueWhiteMask, Imgproc.COLOR_GRAY2BGR)
                blueWhiteMask.setTo(Scalar(255.0, 255.0, 255.0), blueMask)
                Core.bitwise_or(rgbMat, blueWhiteMask, rgbMat)//turning blue pixels to white to not mistake the blu line as a wall
                if (hasSaved) saveMatAsJpeg(rgbMat)

                Imgproc.cvtColor(rgbMat, hsv2, Imgproc.COLOR_RGB2HSV)
                Core.inRange(hsv2, lowerBlack, upperBlack, blackMask)
                Core.bitwise_not(blackMask, inverted)//differentiating the white game mat from the bordering black walls
                if (hasSaved) saveMatAsJpeg(blackMask)

                floodMask1.create(inverted.rows() + 2, inverted.cols() + 2, CvType.CV_8UC1)
                floodMask1.setTo(Scalar(0.0))
                Imgproc.floodFill(inverted, floodMask1, Point(0.0, 0.0), Scalar(255.0))//flood filling the centre area to white
                if (hasSaved) saveMatAsJpeg(inverted)

                Core.bitwise_not(inverted, holes)
                Core.bitwise_or(blackMask, holes, filledBlackMask)//logic to combine masks

                Imgproc.morphologyEx(//simplifying edges and removing artifacts
                    filledBlackMask, cleanedMask,
                    Imgproc.MORPH_CLOSE, kernel
                )
                Imgproc.morphologyEx(
                    cleanedMask, cleanedMask,
                    Imgproc.MORPH_OPEN, kernel
                )
                if (hasSaved) saveMatAsJpeg(cleanedMask)

                cleanedMask.copyTo(frameMat)
                mask.create(frameMat.rows() + 2, frameMat.cols() + 2, CvType.CV_8UC1)
                mask.setTo(Scalar(0.0))
                val seed = Point(frameMat.cols() / 2.0, frameMat.rows() - 1.0)
                Imgproc.floodFill(
                    frameMat, mask, seed,
                    Scalar(255.0), Rect(),
                    Scalar(0.0), Scalar(0.0),
                    Imgproc.FLOODFILL_MASK_ONLY or 8
                )//another flood fill to get the filtered version of the game mat
                Imgproc.cvtColor(frameMat, frameMat, Imgproc.COLOR_GRAY2RGB)
                if (hasSaved) saveMatAsJpeg(frameMat)

                val filledRegion = mask.submat(1, mask.rows() - 1, 1, mask.cols() - 1)//draw the contours of the filled centre
                contours.clear()
                hierarchy.create(1, 1, CvType.CV_8UC4)
                Imgproc.findContours(
                    filledRegion, contours, hierarchy,
                    Imgproc.RETR_CCOMP,
                    Imgproc.CHAIN_APPROX_SIMPLE
                )

                for (i in contours.indices) {//filter the contours to eliminate the outer border
                    val h = hierarchy.get(0, i)
                    if (h[3].toInt() != -1) {
                        Imgproc.drawContours(
                            frameMat, contours, i,
                            Scalar(255.0, 255.0, 0.0), 2
                        )
                    }
                }

                if (hasSaved) {
                    saveMatAsJpeg(frameMat)
                }

                val bottomX = frameMat.cols() / 2
                val bottomY = frameMat.rows() - 1
                for (i in contours.indices) {//perform logic for each identified area inside the game mat to find traffic signs
                    val h = hierarchy.get(0, i)
                    if (h[3].toInt() == -1) continue

                    val cnt = contours[i]
                    if (Imgproc.contourArea(cnt) < 400.0) continue

                    contourMask.create(rgbCopy.size(), CvType.CV_8UC1)//cross-check areas with the colored version of the frame
                    contourMask.setTo(Scalar(0.0))
                    Imgproc.drawContours(
                        contourMask, listOf(cnt), -1,
                        Scalar(255.0), Imgproc.FILLED
                    )

                    val mc = Core.mean(rgbCopy, contourMask).`val`//differentiate the color of the traffic sign
                    val r = mc[0]; val g = mc[1]; val b = mc[2]

                    val (label, dotColor) = when {
                        r > (g + b)/2 + 10 -> 'R' to Scalar(255.0, 0.0, 0.0)
                        g > (r + b)/2 + 10 -> 'G' to Scalar(0.0, 255.0, 0.0)
                        else               -> continue
                    }

                    val M = Imgproc.moments(cnt)//find the centre of the traffic sign
                    val cx = (M.m10 / M.m00).toInt()
                    val cy = (M.m01 / M.m00).toInt()
                    val dx = cx - bottomX
                    val dy = bottomY - cy
                    send(label, dx/2, dy/2)

                    Imgproc.circle(//draw lines and circles for the visualisation of the traffic signs
                        frameMat,
                        Point(cx.toDouble(), cy.toDouble()), 5,
                        dotColor, 1
                    )
                    Imgproc.circle(
                        frameMat,
                        Point(cx.toDouble(), cy.toDouble()), 2,
                        dotColor, -1
                    )
                    Imgproc.line(
                        frameMat,
                        Point(cx.toDouble(), cy.toDouble()),
                        Point(cx.toDouble(), bottomY.toDouble()),
                        dotColor, 1
                    )
                    Imgproc.line(
                        frameMat,
                        Point(cx.toDouble(), bottomY.toDouble()),
                        Point(bottomX.toDouble(), bottomY.toDouble()),
                        dotColor, 1
                    )
                }
                if (hasSaved) {
                    saveMatAsJpeg(frameMat)
                    hasSaved=false
                }
                frameMat.copyTo(lastFrame)
                busy = false
            }
        }

        return if (!lastFrame.empty()) lastFrame else inputFrame.rgba()//return frame so it gets displayed on the screen
    }

    //function that closes USB when the program is closed
    override fun onDestroy() {
        super.onDestroy()
        serialPort?.close()
        try {
            unregisterReceiver(usbReceiver)
        } catch (_: Exception) {
        }
    }

    //function that acivates when the activity is reopened
    override fun onResume() {
        super.onResume()
        val thresholdSeek = findViewById<SeekBar>(R.id.thresholdSeek)
        thresholdSeek.progress = brightnessThreshold.toInt()
        findViewById<TextView>(R.id.thresholdValue).text = "Threshold: ${thresholdSeek.progress}"
    }

    override fun onPause() {//empty pause fubction because it is required
        super.onPause()
    }

    //function that starts a flood fill from the middle and searches its edges to detect the turn direction
    fun findTurnDirection(hsv1: Mat) {
        val vChannel = Mat()
        Core.extractChannel(hsv1, vChannel, 2)
        val floorMask = Mat()
        Imgproc.threshold(vChannel, floorMask, brightnessThreshold, 255.0, Imgproc.THRESH_BINARY)

        val floodMask = Mat(floorMask.rows() + 2, floorMask.cols() + 2, CvType.CV_8UC1, Scalar(0.0))//flood the middle
        val seed = Point(floorMask.cols() / 2.0, floorMask.rows() - 1.0)
        Imgproc.floodFill(floorMask, floodMask, seed, Scalar(255.0), null, Scalar(0.0), Scalar(0.0), Imgproc.FLOODFILL_MASK_ONLY)

        val floodArea = floodMask.submat(1, floodMask.rows() - 1, 1, floodMask.cols() - 1)

        val blueMask = Mat()//create masks for orange and blue
        val orangeMask = Mat()
        Core.inRange(hsv1, Scalar(100.0, 100.0, 50.0), Scalar(130.0, 255.0, 255.0), blueMask)
        Core.inRange(hsv1, Scalar(10.0, 100.0, 100.0), Scalar(25.0, 255.0, 255.0), orangeMask)

        var lowestBlueY = -1
        var lowestOrangeY = -1

        fun processColor(mask: Mat, floodArea: Mat, update: (Int) -> Unit) {//took at the places where the filled middle has an edge to the blue/orange mask
            val contours = mutableListOf<MatOfPoint>()
            Imgproc.findContours(mask, contours, Mat(), Imgproc.RETR_EXTERNAL, Imgproc.CHAIN_APPROX_SIMPLE)
            for (cnt in contours) {
                if (Imgproc.contourArea(cnt) < 50) continue
                val colorMask = Mat.zeros(mask.size(), CvType.CV_8UC1)
                Imgproc.drawContours(colorMask, listOf(cnt), -1, Scalar(255.0), -1)

                val intersection = Mat()
                Core.bitwise_and(colorMask, floodArea, intersection)

                if (Core.countNonZero(intersection) > 0) {//count number of intersecting pixels to determine the color
                    for (pt in cnt.toArray()) {
                        update(pt.y.toInt())
                    }
                }
            }
        }

        processColor(blueMask, floodArea) { y -> if (y > lowestBlueY) lowestBlueY = y }
        processColor(orangeMask, floodArea) { y -> if (y > lowestOrangeY) lowestOrangeY = y }

        when {
            lowestBlueY > lowestOrangeY ->send('B', 0, 0)//sends the found color data to the EVN via USB
            lowestOrangeY > lowestBlueY ->send('O', 0, 0)
        }
        findDir=false
    }

    private fun SeekBar.onChange(block: (Int) -> Unit) {//handles changes on the seekbar UI element
        this.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(sb: SeekBar?, value: Int, fromUser: Boolean) {
                if (fromUser) block(value)
            }

            override fun onStartTrackingTouch(sb: SeekBar?) {}
            override fun onStopTrackingTouch(sb: SeekBar?) {}
        })
    }
}
