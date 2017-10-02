#include "libreriaADC.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "arduino.h"

volatile int readFlag;
volatile int analogVal;
volatile miestruct* me;

int adc_init(miestruct *cfg){ 
  me=cfg;
  //seteo el voltaje de referencia como Vcc
  ADMUX|= (1<<REFS0);
  //depende el canal, habilita los bits correspondientes, freerunning
  ADMUX |= me->canal;
  if(((me->canal)<1)||((me->canal)>6))
      return 0;
      
  //enable bit ADEN
  ADCSRA |=  (1<<ADEN);

//setea el prescaler 16Mhz/128=125KHz. para q este entre 0 y 50, se le pone el prescaler de 128.
  ADCSRA |=  (1<<ADPS0);
  ADCSRA |=  (1<<ADPS1);
  ADCSRA |=  (1<<ADPS2);

//habilita la interrupcion de ADC
 ADCSRA |= (1<<ADIE);
 // ADCSRA = 0B00001000;

//habilita interrupciones globales
  sei();

  readFlag=0;
  
 //inicia la conversion
  ADCSRA|=(1<<ADSC);

  return 1;
}

void adc_loop(){
  if(readFlag==1){
      readFlag=0;
      me->analogValue=analogVal;
  //callback muestra la conversion una vez que termina exitosamente la misma
      me->callback();
  }
}


//interrupcion de ADC (cuando ya tiene el valor se activa adc_vect,obtiene el valor del conversor)
ISR(ADC_vect){
  readFlag=1;
  analogVal=ADCL|(ADCH<<8);
//inicia la conversion nuevamente, despues de actualizar el valor de analogVal
   ADCSRA|=(1<<ADSC);
}
