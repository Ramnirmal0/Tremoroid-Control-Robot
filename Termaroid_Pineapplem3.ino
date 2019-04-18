/*Licenced code from https://pineapplem3.com
  Compiled and debugging : Nirmal Ram
  Project id= PM30004 Project title : Tremoroid Control System Project Year: 2019
  Copyrighted by pineapplem3 Robotics Inc.
  Open Source Code | Free to use | Published in Github : http://github.com/Ramnirmal0/
*/


#include<Wire.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int range, temp;

void setup() {
  servo1.attach(4);
  servo2.attach(3);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void s1up()
{
  servo1.write(0);
  Serial.println("Servo1 up....\n\n");
}
void s1down()
{
  servo1.write(40);
  Serial.println("Servo1 down...\n\n");
}
void s1idle()
{
  servo1.write(20);
  Serial.println("Servo1 idle...\n\n");
}
void s2idle()
{
  servo2.write(20);
  Serial.println("Servo2 idle...\n\n");
}
void s2left()
{
  servo2.write(0);
  Serial.println("Servo2 left...\n\n");
}
void s2right()
{
  servo2.write(40);
  Serial.println("Servo2 right...\n\n");
}
void check(int x)
{
  if (x >= 20000 and x <= 40000)
  {
    s2left();
  }
  if (x <= -20000 and x >= -40000)
  {
    s2right();
  }
  if (x >= 1200 and x >= -600)
  {
    s2idle();
  }
}

void loop() {
  if (Serial.available())
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 12, true);
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();

    /*Serial.print("Accelerometer Readings: ");
      Serial.print("X = "); Serial.print(AcX);Serial.print("\n\n");
      Serial.print(" | Y = "); Serial.print(AcY);Serial.print("\n\n");
      Serial.print(" | Z = "); Serial.println(AcZ); Serial.print("\n\n");*/

    Serial.print("Gyroscope Readings ");
    /*Serial.print("X = "); Serial.print(GyX); Serial.print("\n\n");
      Serial.print(" | Y = "); Serial.print(GyY);Serial.print("\n\n");*/
    Serial.print(" | Z = "); Serial.println(GyZ); Serial.print("\n\n");
    /*Serial.println(" ");
      delay(1000);*/
    range = GyZ;
    if (range <= -2000 and range >= -9000)
    {
      temp = range;
      s1up();
      check(temp);
    }
    if (range >= 2500 and range < 12000)
    {
      temp = range;
      s1down();
      check(temp);
    }
    if (range >= 1200 and range >= -600)
    {
      temp = range;
      s1idle();
      s2idle();
      check(temp);
    }
  }
}
