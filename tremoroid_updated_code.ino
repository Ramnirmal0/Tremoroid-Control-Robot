/*Licened by : pineapplem3.com | Compiled and Programmed by : Nirmal Ram*/


#include<Wire.h>
#include <Servo.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
Servo myservo1;  // any name can be choosen in case of " myservo"
Servo myservo2;  // any name can be choosen in case of " myservo"

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  myservo1.attach(13);
  myservo2.attach(12);
  pinMode(2, OUTPUT);

}

void servoup()
{
  myservo1.write(900);
  myservo2.write(900);
  digitalWrite(2, HIGH);
  Serial.println("calibrating the system..");
  delay(500);

}

void servodown()
{
  myservo1.write(200);
  myservo2.write(200);
  digitalWrite(2, LOW);
  Serial.println("Calibrating the system");
  delay(500);

}
void loop() {
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

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ);

  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(1000);

  //for (int i = -1744 , j =-399  , z = 70 ; i > -1696 , j < -248 , z < 362 ; i++ , j++ , z++)
  //{
  if ( GyX == -1744 or GyY == -403 or GyZ == 320)
  {
    servoup();
    return 0;
  }
  else
  {
    int t=0;
    while (t<2)
    {
      servoup();
      servodown();
      t++;

    }
  }
}
