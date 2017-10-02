//Link para setear timers
//https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
//
//TIMER 1 ES USADO POR ANALOGWRITE!!!
//

// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Arduino.h"
 
// include the library code:
#include <LiquidCrystal.h>
#define ButtonPin A2 




// these constants won't change.  But you can change the size of
// your LCD using them:
const int numRows = 2;
const int numCols = 16;

volatile int minuto;
volatile int segundo;
volatile int centesima;
volatile int tiempo;
volatile int estado;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  //INICIALIZACION DE VARIABLES
  tiempo=0;
  estado=1;
  minuto=0;
  segundo=0;
  centesima=0;
  //INICIALIZACION SHIELD LCD1602
  lcd.begin(numCols,numRows);  
  analogWrite(10, 100); //Controla intensidad backlight
  lcd.setCursor(0, 0);
  lcd.print("Cronometro: ");
  lcd.setCursor(0, 1); 
 
    // INICIALIZACION TIMER 2 --------------------------------------------------------------------------------------
    cli();             // deshabilita interrupciones globales
    TCCR2A = 0;        // setea el registro TCCR1A en 0
    TCCR2B = 0;

    //setea el registro comparador para decidir cuando contar.toma 1 ciclo resetear el time entonces es 25000 - 1
    OCR2A=155;
   
    //modo CTC
     TCCR2A |= (1 << WGM21);

    //interrupcion por comparacion
    TIMSK2 |= (1 << OCIE2A);
      
    // Setea CS10 y CS12 para un preescalado de 1024
    TCCR2B |= (1 << CS21);
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS22);

    //INICIALIZACION INTERRUPT PIN A2 --------------------------------------------------------------------------------
    PCMSK1 |= (1 << PCINT10);  // en mask1 que le preste atencion al pin 10
    PCICR  |= (1 << PCIE1);   //que le preste atencion al mask1
    
    // habilita interrupciones globales
    sei();

}

void loop() {
  // put your main code here, to run repeatedly:
  //analogWrite(10, 75); //Controla intensidad backlight
  lcd.setCursor(0, 1);      //line=1, x=0
  int tiempo=minuto*10000+segundo*100+centesima;
  lcd.print(minuto);
  lcd.print(":");
  lcd.print(segundo);
  lcd.print(":");
  lcd.print(centesima);

  //SOLO PARA TESTING SIN EL DISPLAY
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
  Serial.print(":");
  Serial.println(centesima);
  //Serial.print(estado);
  if(estado==1){
  lcd.setCursor(0, 1);
  lcd.print(minuto);
  lcd.print(":");
  lcd.print(segundo);
  lcd.print(":");
  lcd.print(centesima);
  lcd.print("       ");
  }
}

ISR(TIMER2_COMPA_vect)
{
  /*
   * ESTADO 2 --> CUENTA
   * ESTADO 1 --> RESETEA
   * ESTADO 0 --> SOLO MUESTRA VALOR ACTUAL
   */
  if(estado==2){
    centesima++;
    if(centesima==100){
     segundo++;
     centesima=0;
    }
    if(segundo==60){
     minuto++;
     segundo=0;
   } 
  }
  if(estado==1){
    minuto=0;
    segundo=0;
    centesima=0;}
}

ISR (PCINT1_vect)
{
    //SOLO INCREMENTO EN EL FLANCO ASCENDENTE
    if((PINC & (1 << PINC2)))
    {   
     estado=(estado+1)%3;
     }
 }



