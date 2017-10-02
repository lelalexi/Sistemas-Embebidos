#include <avr/interrupt.h> 
#include "Arduino.h"
#include <LiquidCrystal.h>

#define LDRPin A1

// these constants won't change.  But you can change the size of
// your LCD using them:
const int numRows = 2;
const int numCols = 16;
float R1;

int tabla[2][9]={{92,41,24,16,10,7,5,3,1},{0,1,3,6,10,15,35,80,100}};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 lcd.begin(numCols,numRows);
  analogWrite(10, 100); //Controla intensidad backlight
   lcd.setCursor(0, 0);      //line=1, x=0
   lcd.print("R en LUX:");
   
}

void loop() {
  // put your main code here, to run repeatedly:
  int valorLeido=analogRead(LDRPin);
  float voltaje=(5/1023.0)*valorLeido;
  R1=((5.0-voltaje)*10.0)/voltaje;
  convertir(R1);
  //lcd.setCursor(0, 0);      //line=1, x=0
  //lcd.print(R1);
}

void convertir(float resistencia){
  int termine=0;
  int i=0;
   while((!termine)&&(i<9)){
    if(tabla[0][i]<=resistencia)
        termine=1;
     else i++;      
   }
  float resultado=0.0;
   if(i==0)
       resultado=tabla[1][0];
    else { if(i==9)
              resultado=tabla[1][8];
           else {
                int anterior=tabla[0][i];
                int luxanterior=tabla[1][i];
                int siguiente=tabla[0][i-1];
                int luxsiguiente=tabla[1][i-1];   
                resultado=map(resistencia*100,anterior*100,siguiente*100,luxanterior*100,luxsiguiente*100);
                resultado=resultado/100;
           }
    }
    
  
   lcd.setCursor(0, 1);      //line=1, x=0
   lcd.print(resultado);
   //Serial.print("R en LUX: ");
   Serial.println(resistencia);
}
