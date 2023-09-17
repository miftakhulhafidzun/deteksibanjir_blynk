#define BLYNK_TEMPLATE_ID "TMPL6hbwAzvGl"
#define BLYNK_TEMPLATE_NAME "Distance"
#define BLYNK_AUTH_TOKEN "bsLoNvabhNzEqp_R2x_SXtmJQ2aARmtK"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
const int triggerPin = D6;
const int echoPin = D7;

void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, "POCO F4", "1234lima");  // Ganti dengan SSID dan password WiFi Anda

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Jarak : ");
  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(1000);
}

void loop() {
  Blynk.run();
  
  long duration, distance;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  lcd.setCursor(8, 0);
  lcd.print("     ");
  lcd.setCursor(8, 0);
  lcd.print(distance);
  lcd.print(" cm");  
  
  lcd.setCursor(8, 1);
  lcd.print("        ");
  lcd.setCursor(8, 1);
  if (distance > 20) {
    lcd.print("Jauh");
    Blynk.virtualWrite(V7, "Jauh");
    Blynk.setProperty(V1, "color", "#00FF00");  
    Blynk.virtualWrite(V1, 1); 
  } else if (distance >= 10 && distance <= 20) {
    lcd.print("Sedang");
    Blynk.virtualWrite(V7, "Sedang");
    Blynk.setProperty(V1, "color", "#FFFF00");  
    Blynk.virtualWrite(V1, 1); 
  } else {
    lcd.print("Dekat");
    Blynk.virtualWrite(V7, "Dekat");  
    Blynk.setProperty(V1, "color", "#FF0000");
    Blynk.virtualWrite(V1, 1);
  }

  
  Blynk.virtualWrite(V10, distance); // Mengirim data jarak ke widget V1 di Blynk
  
  delay(3000);
}
