
#include <EVN.h>

#define IMU_I2C_PORT     1

EVNAlpha board;
EVNIMUSensor imu(IMU_I2C_PORT);
float gyroBias = 0.0f;         
unsigned long lastTime = 0;
void calibrateGyroBias(uint16_t duration_ms = 200) {
  unsigned long t0 = millis();
  uint16_t n = 0;
  double sum = 0.0;
  while (millis() - t0 < duration_ms) {
    float gz = imu.readGyroZ(); 
    sum += gz;
    n++;
    delay(4);
  }
  if (n > 0) gyroBias = (float)(sum / n);
}

float yaw = 0.00f;
float updateYaw() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0f;
  lastTime = now;
  float gz = imu.readGyroZ();      
  gz -= gyroBias;                   
  yaw += gz * dt;                     
  return yaw;
}
void setup()
{
  board.begin(); 
  Serial.begin(9600);
  imu.begin();
  imu.setGyroRange(IMU_GYRO_DPS_1000);
  calibrateGyroBias(2000);
  lastTime = millis();
}

void loop(){
  Serial.println(updateYaw());
}