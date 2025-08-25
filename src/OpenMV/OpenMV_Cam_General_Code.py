import sensor, time
from machine import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
#---Flips sensor data because it is upside down---
sensor.set_vflip(True)
sensor.set_hmirror(True)

sensor.skip_frames(time=2000)
uart1 = UART(1, baudrate=9600) #Starts Uart Communication in pin "P4" and "P5"

clock = time.clock()
img_width = sensor.width()
img_height = sensor.height()

#---Finds brightness in middle to detect wall---
def Find_MiddleBrightness(img):
    #---Defining a rectangle roi for middle---
    rect_x = int(img_width * 0.3)
    rect_y = int(img_height * 0.35)
    rect_w = int(img_width * 0.4)
    rect_h = int(img_height * 0.3)
    middle_roi = (rect_x, rect_y, rect_w, rect_h)

    #---Gets the average brightness of the pixels in roi---
    stats = img.get_statistics(roi=middle_roi)
    brightness = stats.mean()
    return brightness


#---Detects Orange Line to determine the direction---
def Find_Orange_Line(img):
    orange_threshold = (40, 51, -115, 68, 16, 29) #Color threshold used for orange

    #---Defines a rectangle roi for the floor---
    rect_x = int(0)
    rect_y = int(img_height * 0.3)
    rect_w = int(img_width)
    rect_h = int(img_height)
    lines_roi = (rect_x, rect_y, rect_w, rect_h)

    #---Finds similar colored pixel blocks---
    orange_blobs = img.find_blobs([orange_threshold], roi=lines_roi, area_threshold=3000)
    for blob in orange_blobs:
        img.draw_rectangle(blob.rect(),color=(0, 255, 0))
        return True #Returns True if sees an orange blob
    return False #Returns False if it doesn't see an orange blob


#---Detects Blue Line to determine the direction---
def Find_Blue_Line(img):
    blue_threshold = (35, 8, -128, 16, -128, -6) #Color threshold used for blue

    #---Defines a rectangle roi for the floor---
    rect_x = int(0)
    rect_y = int(img_height * 0.3)
    rect_w = int(img_width)
    rect_h = int(img_height)
    lines_roi = (rect_x, rect_y, rect_w, rect_h)
    img.draw_rectangle(lines_roi,color=(255, 0, 0))

    #---Finds similar colored pixel blocks---
    blue_blobs = img.find_blobs([blue_threshold], roi=lines_roi, area_threshold=3000)
    for blob in blue_blobs:
        img.draw_rectangle(blob.rect(),color=(0, 255, 0))
        print(blob.area())
        return True #Returns True if sees a blue blob

    return False #Returns False if it doesn't see a blue blob


#---Detects Red Rectangles (used for object tracking or direction)---
def Find_Red_Rect(img):
    red_threshold = (9, 72, 57, 22, -12, 57) #Color threshold used for red
    blobs_red = img.find_blobs([red_threshold], area_threshold=1000)

    rect = None
    center = None
    error = None
    area = None
    returnSTR = ""

    #---Draws cross at image center---
    img_center_x = img.width() // 2
    img_center_y = img.height() // 2
    img.draw_cross(img_center_x, img_center_y, color=(255, 0, 0))

    #---Finds blobs that match red threshold---
    for a in blobs_red:
        img.draw_rectangle(a.rect())
        x, y, w, h = a.rect()
        img.draw_cross(x + w // 2, y + h // 2)

        #---Check shape (elongation close to rectangle)---
        if a.elongation() < 1.2:
            area = a.area()
            rect = a.rect()
            x, y, w, h = rect
            center = (x + w // 2, y + h // 2)
            error = center[0] - img_center_x
            returnSTR = returnSTR + str([area, error])+"?"

    return returnSTR


#---Detects Green Rectangles (used for object tracking or direction)---
def Find_Green_Rect(img):
    green_threshold = (0, 52, -35, -15, -55, 17) #Color threshold used for green
    blobs_green = img.find_blobs([green_threshold], area_threshold=1000)

    rect = None
    center = None
    returnSTR = ""
    error = 0
    area = 0

    #---Draws cross at image center---
    img_center_x = img.width() // 2
    img_center_y = img.height() // 2
    img.draw_cross(img_center_x, img_center_y, color=(255, 0, 0))

    #---Finds blobs that match green threshold---
    for a in blobs_green:
        img.draw_rectangle(a.rect())
        x, y, w, h = a.rect()
        img.draw_cross(x + w // 2, y + h // 2)

        #---Check shape (elongation close to rectangle)---
        if a.elongation() < 1.2:
            area = a.area()
            rect = a.rect()
            x, y, w, h = rect
            center = (x + w // 2, y + h // 2)
            error = center[0] - img_center_x
            returnSTR = returnSTR + str([area, error])+"?"

    return returnSTR


#---Main Loop---
while True:
    clock.tick()  #Updates the FPS clock
    img = sensor.snapshot()  #Takes a picture from the camera

    #---Reads 1 byte from UART to decide which function to run---
    a = uart1.read(1)

    if a == b'1':
        #---Detects Green Rectangle and sends area + error via UART---
        uart1.write("<" + str(Find_Green_Rect(img)) + "*")
    elif a == b'2':
        #---Detects Red Rectangle and sends area + error via UART---
        uart1.write("<" + str(Find_Red_Rect(img)) + "*")
    elif a == b'3':
        #---Measures brightness in the middle ROI and sends value via UART---
        uart1.write("<" + str(Find_MiddleBrightness(img)) + "*")
    elif a == b'4':
        #---Detects Orange Line and sends True/False via UART---
        uart1.write("<" + str(Find_Orange_Line(img)) + "*")
    elif a == b'5':
        #---Detects Blue Line and sends True/False via UART---
        uart1.write("<" + str(Find_Blue_Line(img)) + "*")

    #---Debugging: print the received UART command and FPS---
    print(a)
    print(clock.fps())
    time.sleep(0.01)  #Small delay for stability
