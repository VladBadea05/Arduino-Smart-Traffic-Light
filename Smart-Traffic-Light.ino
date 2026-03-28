#include <LiquidCrystal.h>

#define LedG 10
#define LedY 8
#define LedR 7
const int Mic = A5;

const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


enum TrafficState {
  StateR,
  StateG,
  StateY,
  EmergencyState
};


TrafficState StartState = StateR;

unsigned long timer = 0; 
unsigned long sum = 0;
unsigned long media = 0;

void setup() {
  pinMode(LedG, OUTPUT);
  pinMode(LedY, OUTPUT);
  pinMode(LedR, OUTPUT);
  lcd.begin(16, 2);

  Serial.begin(9600);
  lcd.print("Semafor pornit!");
  delay(2000); 
  lcd.clear(); 
}

void loop() {
  switch(StartState) {
    case StateR:
      digitalWrite(LedR, LOW);
      digitalWrite(LedG, HIGH);
      digitalWrite(LedY, HIGH);
      
      lcd.clear();
      sum = 0;
      lcd.print("ROSU!");
      for(int i = 0; i < 10; i++) {
         sum += analogRead(Mic);
      }
      media = sum / 10;
      
      if(media >= 800) {
        lcd.clear();
        lcd.print("Autospeciala!");
        StartState = EmergencyState;
      } else if(millis() - timer >= 2000) { 
        StartState = StateG;
        timer = millis();
      }
      break;
      
    case StateG:
      digitalWrite(LedR, HIGH);
      digitalWrite(LedG, LOW);
      digitalWrite(LedY, HIGH);
      
      lcd.clear(); 
      sum = 0;
      lcd.print("VERDE!");
      for(int i = 0; i < 10; i++) {
         sum += analogRead(Mic);
      }
      media = sum / 10;

      if(media >= 800) {
        lcd.clear();
        lcd.print("Autospeciala!");
        lcd.clear();
        StartState = EmergencyState;
      } else if(millis() - timer >= 1500) {
        StartState = StateY;
        timer = millis();
      }
      break;
      
    case StateY:
      digitalWrite(LedR, HIGH);
      digitalWrite(LedG, HIGH);
      digitalWrite(LedY, LOW);
      
      lcd.clear(); 
      sum = 0;
      lcd.print("GALBEN!");

      for(int i = 0; i < 10; i++) {
         sum += analogRead(Mic);
      }
      media = sum / 10;
      
      if(media >= 800) {
        lcd.clear();
        lcd.print("Autospeciala!");
        lcd.clear();
        StartState = EmergencyState;
      } else if(millis() - timer >= 1000) {
        StartState = StateR;
        timer = millis();
      }
      break;
      
    case EmergencyState:
      lcd.clear();
      while(analogRead(Mic) > 900) {
        lcd.print("ATENTIE!");
        if(timer % 2 == 0) {
          delay(50);
          digitalWrite(LedR, LOW);
        } else {
          delay(50);
          digitalWrite(LedR, HIGH);
        }
        lcd.clear();
      }
      delay(100);
      StartState = StateY;
      timer = millis();
      break;
  }
}