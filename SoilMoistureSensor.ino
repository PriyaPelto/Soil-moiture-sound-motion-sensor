  // Soil moisture sensor related:
int SoilSensorPin = A0;
int SensorValue = 0;
float Percent = 0;

  // Sound sensor related:
int SoundSensorPin = A1;
unsigned long lastEvent = 0;
int SoundSensorData = 0;


  // MotionDetection sensor related:
int MotionSensorPin = A2;
int MotionValue = 0;

// LCD monitor related:
#include <LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int LCDdelay = 2000;  
  
  // Overall related:
int dt = 250;

void setup() {

  // Soil moisture sensor related:
  pinMode(SoilSensorPin, OUTPUT);
  
  // Sound sensor related:
  pinMode(SoundSensorPin, INPUT);
  
  // MotionDetection sensor related:
  pinMode(MotionSensorPin, INPUT);
  
  // LCD monitor related:
  lcd.begin(16,2);
  
  Serial.begin(9600);
}

void loop() {

   //Soil moisture sensor related:
  SensorValue = analogRead(SoilSensorPin);
  Percent = (100./650.)*SensorValue;
  Serial.println(Percent);
  Serial.println(SensorValue);
  //Serial.print("%");
  //delay(dt);
  
  if (Percent >= 90. ){
    lcd.setCursor(0,0);
    lcd.println("Too much (^_^;)         ");
  } else if (Percent >= 40. && Percent < 90.){
    lcd.setCursor(0,0);
    lcd.println("All good (^_^)           ");
  } else if (Percent >= 20. && Percent < 40.){
    lcd.setCursor(0,0);
    lcd.println("Water me.. (=_=)          ");
  } else if (Percent >= 0. && Percent < 20.){
    lcd.setCursor(0,0);
    lcd.println("Water!!! (>_<)           ");
  }
  
  // Sound sensor related:
  SoundSensorData = digitalRead(SoundSensorPin);
  
  // MotionDetection sensor related:
  MotionValue = digitalRead(MotionSensorPin);
    
  if (SoundSensorData == LOW){
      Serial.println("How's it ");
      if (millis() - lastEvent > 25){
      Serial.println("How's it going?");
      lcd.setCursor(0,1);
      lcd.println(" (*^0^*)            ");
      delay(LCDdelay);
      lcd.clear();
    }
    lastEvent = millis();
  }
  else if (MotionValue == HIGH){
    Serial.println("Glad you are here.");
    lcd.setCursor(0,1);
    lcd.println("(^_-)                   ");
    delay(LCDdelay);
    lcd.clear();
  }
}
