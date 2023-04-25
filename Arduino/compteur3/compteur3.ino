#include <HCSR04.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);



const int trigPin = 2;
const int echoPin = 3;

UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
void setup() {
lcd.init();
Serial.begin(9600);
}
void loop() {
lcd.backlight();
lcd.clear();
Serial.println(distanceSensor.measureDistanceCm());
lcd.print("distance = ");
lcd.setCursor(0,1); 
lcd.print(distanceSensor.measureDistanceCm()+1);
lcd.print(" cm");
delay(500);
}
