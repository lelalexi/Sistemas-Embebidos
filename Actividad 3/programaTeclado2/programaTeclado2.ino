#include <LiquidCrystal.h>
#include "interfazDriver.h"

// these constants won't change.  But you can change the size of
// your LCD using them:
const int numRows = 2;
const int numCols = 16;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void TeclaUpUp(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla UP pulsada");
}
void TeclaUpDown(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla UP soltada");
}
void TeclaDownUp(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla DOWN pulsada");
}
void TeclaDownDown(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla DOWN soltada");
}
void TeclaRightUp(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla RIGHT pulsada");
}
void TeclaRightDown(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla RIGHT soltada");
}
void TeclaLeftUp(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla LEFT pulsada");
}
void TeclaLeftDown(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla LEFT soltada");
}
void TeclaSelectUp(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla SELECT pulsada");
}
void TeclaSelectDown(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Tecla SELECT soltada");
}
void BotonA2Up(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A2 pulsado");
}
void BotonA2Down(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A2 soltado");
}

void BotonA3Up(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A3 pulsado");
}
void BotonA3Down(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A3 soltado");
}

void BotonA4Up(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A4 pulsado");
}
void BotonA4Down(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A4 soltado");
}
void BotonA5Up(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A5 pulsado");
}
void BotonA5Down(){
  lcd.setCursor(0, 1);      //line=1, x=0
  lcd.print("Boton A5 soltado");
}

void setup() {
  delay(30);
//seteamos valores del lcd
   lcd.begin(numCols,numRows);
  analogWrite(10, 100); //Controla intensidad backlight
  lcd.setCursor(0,0);
  lcd.print("Labo 2");

 key_up_callback(&TeclaUpUp,0);
 key_down_callback(&TeclaUpDown,0);

 key_up_callback(&TeclaDownUp,1);
 key_down_callback(&TeclaDownDown,1);

 key_up_callback(&TeclaLeftUp,2);
 key_down_callback(&TeclaLeftDown,2);

 key_up_callback(&TeclaRightUp,3);
 key_down_callback(&TeclaRightDown,3);

 key_up_callback(&TeclaSelectUp,4);
 key_down_callback(&TeclaSelectDown,4);
 
 key_up_callback(&BotonA2Up,5);
 key_down_callback(&BotonA2Down,5);

 key_up_callback(&BotonA3Up,6);
 key_down_callback(&BotonA3Down,6);
 
 key_up_callback(&BotonA4Up,7);
 key_down_callback(&BotonA4Down,7);
 
 key_up_callback(&BotonA5Up,8);
 key_down_callback(&BotonA5Down,8);

 teclado_init();
}

void loop() {
  
teclado_loop();
}


