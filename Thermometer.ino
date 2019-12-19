#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

boolean lightMe;
int defC = 20;
int upstate = 0; 
int downstate = 0; 
int ledPin = 2;
float Celsius=0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define ONE_WIRE_BUS 10

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin (9600); 
  lcd.begin(16, 2); 
  lcd.clear(); 
  pinMode(ledPin, OUTPUT);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();   
  Celsius=sensors.getTempCByIndex(0);  
  int x;
  x = analogRead (0);  
  if (x > 60 && x < 200) {
    upstate = LOW;
    downstate = HIGH;    
  }
  else if(x > 200 && x < 400) {
    upstate = HIGH;
    downstate = LOW;    
  }
  else{
    upstate = HIGH;
    downstate = HIGH;    
  }

  if (upstate == LOW) {   
    defC = defC + 1;
  }
  if (downstate == LOW) {
    defC = defC - 1; 
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp ");  
  lcd.print (Celsius);  
  lcd.print((char)223);
  lcd.print ("C");
  delay(255);  
  lcd.setCursor (0, 1);
  lcd.print ("Targ ");  
  lcd.print (defC);
  lcd.print((char)223);
  lcd.print ("C");
    
  lightUp(Celsius, defC);
  
  if (lightMe == true) {
    digitalWrite(ledPin, HIGH);
  } else if (lightMe == false) {
    digitalWrite(ledPin, LOW);
  }
}

boolean lightUp(float act, int desC) { 
  if (act < desC) {
    lightMe = true;
  } else { //otherwise
    lightMe = false;
  }
  return lightMe;
}
