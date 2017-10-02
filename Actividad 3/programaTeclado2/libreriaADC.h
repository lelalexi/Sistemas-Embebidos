
#ifndef libreriaADC
#define libreriaADC

  typedef struct miestructura{
  int canal;
  void (*callback)();
  int analogValue;
  }miestruct;
  
  int adc_init(struct miestructura *cfg);
  void adc_loop();



#endif

