#include "ioconfig.h"
#include <Arduino.h>

#define set_bit(Y,bit_x) (Y!=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))

#define ENTRADA INPUT
#define SAIDA OUTPUT
#define ENTRADA_PULLUP INPUT_PULLUP
#define LIGA HIGH
#define DESLIGA LOW

void modoPino(int pino, int estado){
  if(pino>=0&&pino<=7){
    if(estado==ENTRADA){
      DDRD = DDRD & ~(0b00000001<<pino);
    }
    else if(estado==SAIDA){
      DDRD = DDRD | (0b00000001<<pino);
    }
  }
  if(pino>=8&&pino<=13){
    if(estado==ENTRADA){
      DDRB = DDRB & ~(0b00000001<<pino-8);
    }
    else if(estado==SAIDA){
      DDRB = DDRB | (0b00000001<<pino-8);
    }
  }
  if(pino>=14&&pino<=19){
    if(estado==ENTRADA){
      DDRC = DDRC & ~(0b00000001<<pino-14);
    }
    else if(estado==SAIDA){
      DDRC = DDRC | (0b00000001<<pino-14);
    }
  }
}

void escreveDigital(int pino, int escrita){
  if(pino>=0&&pino<=7){
    if(escrita==LIGA){
      PORTD = PORTD | (0b00000001<<pino);
    }
    else if(escrita==DESLIGA){
      PORTD = PORTD & ~(000000001<<pino);
    }
  }
  if(pino>=8&&pino<=13){
    if(escrita==LIGA){
      PORTB = PORTB | (0b00000001<<pino-8);
    }
    else if(escrita==DESLIGA){
      PORTB = PORTB & ~(000000001<<pino-8);
    }
  }
  if(pino>=14&&pino<=19){
    if(escrita==LIGA){
      PORTC = PORTC | (0b00000001<<pino-14);
    }
    else if(escrita==DESLIGA){
      PORTC = PORTC & ~(000000001<<pino-14);
    }
  }
}

bool leDigital(int pino){
  if(pino>=0&&pino<=7){
    bool estadoPino;
    estadoPino = (PIND & (0b00000001 << pino));
    return (estadoPino);
  }
  if(pino>=8&&pino<=13){
    bool estadoPino;
    estadoPino = (PINB & (0b00000001 << pino-8));
    return (estadoPino);
  }
  if(pino>=14&&pino<=19){
    bool estadoPino;
    estadoPino = (PINC & (0b00000001 << pino-14));
    return (estadoPino);
  }
}

void adc_init()
{
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<ADPS0);
  ADCSRA &= ~(1<<ADATE);
  ADCSRA |= ADEN;
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<ADLAR);
} 

int leituraAnalogica(int porta)
{
  int adcValue;
  int bToChannel = porta & 0x07;
  ADMUX |= bToChannel;  
  ADCSRA |= (1<<ADSC);
  while(bit_is_clear(ADCSRA, ADIF));
  adcValue = (ADCH<<8)|ADCL;
  return(adcValue);
}
