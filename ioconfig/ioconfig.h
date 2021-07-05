#include <Arduino.h>

#ifndef IOCONFIG_h
#define IOCONFIG_h

void modoPino(int pino, int estado);
void escreveDigital(int pino, int escrita);
void adc_init();
int leituraAnalogica(int porta);
bool leDigital(int pino);

#endif
