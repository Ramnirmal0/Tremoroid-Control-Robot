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
  myservo1.write(179);
  myservo2.write(179);
  digitalWrite(2, HIGH);
  delay(3000);

}

void servodown()
{
  myservo1.write(0);
  myservo2.write(0);
  digitalWrite(2, LOW);
  delay(3000);

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

  for (int i = -800 , j = 700 ; i < -10000 , j < 1900 ; i-- , j++)
  {
    if ( GyX == i || GyY == i || GyZ == j)
    {
      servoup();
    }
    else
    {
      servodown();
    }
  }
}
