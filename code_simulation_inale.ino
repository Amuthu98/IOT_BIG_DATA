#include <LiquidCrystal.h>
#define buzzer 13 //the pin of the active buzzer
#define capteur A0
#define photo A3
#define moteur 7
#define LED 10
#define Interrupteur 8
#define Appuye digitalRead(Interrupteur)==1
float VoltOffset = 0.5;
LiquidCrystal lcd(12,11,5,4,3,2);
void setup() {
Serial.begin(9600);
lcd.begin(16,2);
pinMode(buzzer,OUTPUT);
pinMode(moteur,OUTPUT);
pinMode(LED,OUTPUT);
pinMode(Interrupteur,INPUT_PULLUP);
digitalWrite(LED,LOW);

  

}
void loop() {
  if(Appuye) {
    while(Appuye) {
    	digitalWrite(LED,HIGH);
        lcd.setCursor(0,0);
		lcd.print("Appel d'Urgence");
		lcd.setCursor(2,1);
		lcd.print("En cours...");
    }
  digitalWrite(LED,LOW);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  }
  int i;
  int light = analogRead(photo);
  int valcapt = analogRead(capteur);
  float voltage = valcapt*5.0/1024.0;
  float temperature = (voltage-VoltOffset)*100;
  Serial.print("Température = ");
  Serial.print(temperature);
  Serial.println("C°");
  Serial.print("Luminosité (en lux): ");
  Serial.print(light);
  Serial.println(" lux");
  delay(1000);
  if (temperature > 26){
    while(temperature >= 26) {
      digitalWrite(moteur,HIGH);
      valcapt = analogRead(capteur);
  	  voltage = valcapt*5.0/1024.0;
      temperature = (voltage-VoltOffset)*100;
      if(temperature < 26) {
        digitalWrite(moteur,LOW);  
        break;
      }
    }
  }
 if(light >= 500) {
    while(light >= 500) {
      for(i=0;i<100;i++) {
        light = analogRead(photo);
        if(light < 500) {
          digitalWrite(buzzer,LOW);
          break;
        }
    
        digitalWrite(buzzer,HIGH);
    	delay(1);//wait for 1ms
    	digitalWrite(buzzer,LOW);
    	delay(1);//wait for 1ms
      }
    //output another frequency
     for(i=0;i<100;i++) {
        light = analogRead(photo);
        if(light < 500) {
          digitalWrite(buzzer,LOW);
          break;
        }
        digitalWrite(buzzer,HIGH);
        delay(2);//wait for 2ms
        digitalWrite(buzzer,LOW);
        delay(2);//wait for 2ms
     } 
    }

 }
valcapt = analogRead(capteur);
voltage = valcapt*5.0/1024.0;
temperature = (voltage-VoltOffset)*100;
}