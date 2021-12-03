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

  // NeoPixel Ring related:
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
int NeoPixelPin = 6;
int NUMPIXELS = 16;
Adafruit_NeoPixel pixels(NUMPIXELS, NeoPixelPin, NEO_GRB + NEO_KHZ800);

  // Servo related:
#include <Servo.h>
int servoPin = 3;
Servo myServo;
float angle;

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

  // NeoPixel Ring related:
  pinMode(NeoPixelPin, OUTPUT);
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

    // Servo related:
myServo.attach(servoPin);
pinMode(servoPin, OUTPUT);

  Serial.begin(9600);
}

  // NeoPixel Ring function:
void showGreen(float percentage) {
    float multiplier = percentage / 100;
    int lightsToTurnOn = NUMPIXELS * multiplier;
    // GREN LEDS
    for(int i=0; i<lightsToTurnOn; i++) { 
        pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    }
    // RED LEDS
    for(int i=lightsToTurnOn; i<NUMPIXELS; i++) { 
        pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    }
    // for too much water
    if (multiplier >= 1){
          for(int i=0; i<lightsToTurnOn; i++) { 
        pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    }
    }
    pixels.show(); 
}
  // Servo function:
void leafPosition(float percentage) {
    float AngleMultiplier = percentage / 100;
    int currentLeafAngle = 180. * AngleMultiplier;
    myServo.write(currentLeafAngle);
    }

    
void loop() {
   //Soil moisture sensor related:
  SensorValue = analogRead(SoilSensorPin);
  Percent = (100./500.)*SensorValue;
  showGreen(Percent);
  delay(dt);
  leafPosition(Percent);

    // LCD expressions:
  if (Percent >= 90. ){
    lcd.setCursor(0,0);
    lcd.println("Too much (^_^;)         ");
  }   else if (Percent >= 40. && Percent < 90.){
    lcd.setCursor(0,0);
    lcd.println("All good (^_^)           ");
  }   else if (Percent >= 20. && Percent < 40.){
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
    lcd.setCursor(0,1);
    lcd.println("(^_-)                   ");
    delay(LCDdelay);
    lcd.clear();
  }
}
