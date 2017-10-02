#include <avr/interrupt.h>
#include "interfazDriver.h"
#include "libreriaADC.h"
#include <avr/io.h>
#include "Arduino.h" //o stdlib.h


void (* funcKeyUp[9])();
void (* funcKeyDown[9])();
struct miestructura adcEstr;

volatile uint8_t portchistory=0xFF;
volatile uint8_t changebits=0xFF;
volatile int presionado;
volatile int botonSoltado;
volatile int botonpresionado;
volatile int hubointerrupcion;

int teclapresionada;

static int valor;


void call(){
  valor=adcEstr.analogValue;
}



void teclado_init() {
  Serial.begin(9600);
  delay(40);
  
  presionado=0;
  botonSoltado=0;
  botonpresionado=0;
  hubointerrupcion=0;

   teclapresionada=-1;
   
  pinMode(A0,INPUT); //Botonera del Shiel LCD

  //adcEstr=malloc(sizeof(struct miestructura));
  adcEstr.canal=0;
  adcEstr.callback=call;
  adc_init(&adcEstr);
  

cli();
  //seteo pines A2,A3,A4,A5 como entrada
  DDRC &= ~(1 << DDC2);
  DDRC &= ~(1 << DDC3);
  DDRC &= ~(1 << DDC4);
  DDRC &= ~(1 << DDC5);

  //EICRA |= (1<<ISC01); // trigger el vector interrupcion en el flanco descendente ( falling)
  
   PORTC |=(1<<PORTC2);
   PORTC |=(1<<PORTC3);
   PORTC |=(1<<PORTC4);
   PORTC |=(1<<PORTC5);
   

   PCMSK1 |= (1 << PCINT10);  // en mask1 que le preste atencion al pin 10
   PCMSK1 |= (1 << PCINT11);  // en mask1 que le preste atencion al pin 11
   PCMSK1 |= (1 << PCINT12);  // en mask1 que le preste atencion al pin 12
   PCMSK1 |= (1 << PCINT13);  // en mask1 que le preste atencion al pin 13
   PCICR  |= (1 << PCIE1);   //que le preste atencion al mask1

    sei();
}

void teclado_loop() {
  if(hubointerrupcion==1){
    if(presionado){
        
         funcKeyUp[botonpresionado]();
    }
     else   {funcKeyDown[botonSoltado]();
              
     }
    hubointerrupcion=0;
    //adc_loop();
  }
  else{
    adc_loop();
    if( valor<=30){
           teclapresionada=3;         
           funcKeyUp[teclapresionada]();
    }    
     else{ 
          if( valor<=150){
           teclapresionada=0;
           funcKeyUp[teclapresionada]();
           }
           else{
               if( valor<=360){
                 teclapresionada=1;
                 funcKeyUp[teclapresionada]();
                }
                else{
                     if( valor<=535){
                         teclapresionada=2;
                         funcKeyUp[teclapresionada]();
                      }
                      else{
                           if( valor<=760){
                              teclapresionada=4;
                              funcKeyUp[teclapresionada]();
                           }
                            else{
                                if((1023)&&(teclapresionada>=0)){
                                   funcKeyDown[teclapresionada]();
                                   teclapresionada=-1;
                                }
                            }
                      }
                }
           }
           
           
     }
  }
 }


 void key_down_callback(void (*handler)(),int tecla)
 {
  funcKeyDown[tecla]=handler;
 }
 void key_up_callback(void (*handler)(),int tecla)
 {
  funcKeyUp[tecla]=handler;
 }

ISR (PCINT1_vect)
{
  hubointerrupcion=1;
 changebits=PINC ^ portchistory;
 portchistory=PINC;

 if(changebits &(1<<PINC2)){
    if((PINC & (1 << PINC2))){//low to high
      presionado=1;
      botonpresionado=5;

    }
      else{//high to low
    
         botonSoltado=5;
         presionado=0;
      }
 }
 if(changebits &(1<<PINC3)){
   if((PINC & (1 << PINC3)) ){
      presionado=1;
      botonpresionado=6;
   }
      else
     {
      botonSoltado=6;
      presionado=0;
      }
 }
 if(changebits &(1<<PINC4)){
  if((PINC & (1 << PINC4))){
      presionado=1;
      botonpresionado=7;
  }
  else{
      botonSoltado=7;
      presionado=0;
      }
 }
 if(changebits &(1<<PINC5)){
  if((PINC & (1 << PINC5))){
      presionado=1;
      botonpresionado=8;
  }
      else
     {
      botonSoltado=8;
      presionado=0;
      }
 }      
}      
