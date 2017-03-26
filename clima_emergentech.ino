
#include <LiquidCrystal.h>

#define echoPin 10
#define trigPin 11
#define tempPin 13
LiquidCrystal lcd(5,4,3,2,1,0);
int maximumRange = 9;
int minimumRange = 4;
long duration, distance;
double voltage,reading,degreesC,degreesF;
int timing = 0;
int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = 8; // key
int scroll = 0;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT_PULLUP);
}

void loop() {
    int x, y, z;
  x = analogRead (JoyStick_X);
  y = analogRead (JoyStick_Y);
  z = digitalRead (JoyStick_Z);

  if(y > 0 || y < 0){
    scroll++;
  while(z < 0){
    lcd.print("Notify Me:");
    lcd.setCursor(0,1);
    lcd.print(scroll + " Hour");
    while (x > 0 && scroll < 7 || scroll > 1){
      scroll++;
            lcd.clear();
          lcd.print("Notify Me:");
    lcd.setCursor(0,1);
    lcd.print(scroll + " Hour");
    break;
    }
    while (x < 0 && scroll < 7 || scroll > 1){
      scroll--;
      lcd.clear();
    lcd.print("Notify Me:");
    lcd.setCursor(0,1);
    lcd.print(scroll + " Hour");
    break;
    }
    if (scroll > 6){
      scroll = 1;
    }
    if (scroll < 0){
      scroll = 6;
    }
    if (z<0){
      // insert datastoring method here
      scroll = 0;
      break;
    }
    }
  }
  reading = analogRead(tempPin);
  float voltage = reading;
  voltage /= 1024.0;
  degreesC = (voltage)*100;
  degreesF = (degreesC * (9.0/5.0) + 32.0);
  String d = String(degreesF);
  while (degreesF >=40 && timing <= 1)
  {
    lcd.print("WARNING:"); lcd.setCursor(0,1);
    lcd.print("TEMP ABOVE 40 F");
    delay(1000);
    lcd.clear();
    int tar = x;
    int tay = y;
    break;
    delay(500);
    timing+=20;
  }
  lcd.print("Temp: "+d+" F");
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  //lcd.print(millis() / 1000);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance =  duration/58.2;
  String c = String(distance);
  if (distance < minimumRange){
    lcd.print("Status: Closed");
    delay(1000);
  }   
  if (distance > minimumRange){
      lcd.print("Status: Open");
      delay(1000);
    }
  lcd.clear();
  timing--;
//  lcd.clear();
//  lcd.setCursor(0,1);
//  lcd.print("s");
//  delay(500);
//  lcd.clear();
//  lcd.setCursor(0,1);
//  lcd.print("ys");
//  delay(500);
}
