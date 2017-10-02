
#ifndef interfazDriver
#define interfazDriver


  void key_down_callback(void (*handler)(),int tecla);
  void key_up_callback(void (*handler)(),int tecla);
  //no te olvides de estas juli!!!!!!!!!!!!
  void teclado_init();
  void teclado_loop();

#endif

