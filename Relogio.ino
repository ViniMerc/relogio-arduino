#include <ioconfig.h>

#define set_bit(Y,bit_x) (Y!=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))

#define ENTRADA INPUT
#define SAIDA OUTPUT
#define ENTRADA_PULLUP INPUT_PULLUP
#define LIGA HIGH
#define DESLIGA LOW

int segundos= 0;
int minutos= 0;
int horas= 0;
char auxOVF = 0x00;

int D1 = 9, D2 = 10, D3 = 11, D4 = 12, D5= 13, D6= 14;
int segDisplay[7] = {2,3,4,5,6,7,8};
int numero [10][7] = {
      {0,0,0,0,0,0,1},
      {1,0,0,1,1,1,1},
      {0,0,1,0,0,1,0},
      {0,0,0,0,1,1,0},
      {1,0,0,1,1,0,0},
      {0,1,0,0,1,0,0},
      {0,1,0,0,0,0,0},
      {0,0,0,1,1,1,1},
      {0,0,0,0,0,0,0},
      {0,0,0,0,1,0,0}  
    };

ISR(TIMER2_OVF_vect){  //Interrupção Timer2. A cada 10ms*100 Interrupções = 1s
  TCNT2 = 0x64;
  auxOVF++;
  if(auxOVF == 0x64){
    auxOVF = 0x00;
    segundos++;
  }
}

void atualizaDisplay(int pino,int num){
  escreveDigital(pino,LIGA);
  for(int i=0;i<=6;i++){
    escreveDigital(segDisplay[i],!numero[num][i]);
  }
  delay(10);
  escreveDigital(pino,DESLIGA);
}

void setup (){
  modoPino(16,ENTRADA);  
  modoPino(17,ENTRADA);  
  for(int i = 0; i <= 6; i++){
    modoPino(segDisplay[i],SAIDA);
  }
  modoPino(D1,SAIDA);
  modoPino(D2,SAIDA);
  modoPino(D3,SAIDA);
  modoPino(D4,SAIDA);
  modoPino(D5,SAIDA);
  modoPino(D6,SAIDA);
 
  TCCR2A = 0x00;    //Registradores do Timer
  TCCR2B = 0x07;    
  TCNT2  = 0x64;    
  TIMSK2 = 0x01;    
}

void relogio() {
  if (segundos > 59){
    segundos = 0x00;
    minutos++;
    if(minutos >59){
      minutos = 0x00;
      horas++;
      if(horas > 23){
        horas = 0x00;
      }
    }
  }
}

void ajuste(){
  if (leDigital(17)==LIGA){
    delay(150);
    minutos++;
    if (minutos > 59) {
      minutos = 0x00;
    }
  }
  if (leDigital(16)==LIGA){
    delay(150);
    horas++;
    if(horas > 23){
      horas = 0x00;
    }
  }
}

void mostraHora(){
  if (segundos <= 9){
  atualizaDisplay(13,segundos);
  atualizaDisplay(14,round(segundos/10));
  }
  if (segundos > 9){
  atualizaDisplay(13,(segundos%10));  
  atualizaDisplay(14,round(segundos/10));
  }
  
  if (minutos <= 9){
  atualizaDisplay(12,minutos);
  atualizaDisplay(11,round(minutos/10));
  }
  if (minutos > 9){
  atualizaDisplay(12,(minutos%10));  
  atualizaDisplay(11,round(minutos/10));
  }
  
  if (horas <= 9){
  atualizaDisplay(10,horas);
  atualizaDisplay(9,round(horas/10));
  }
  if (horas > 9){
  atualizaDisplay(10,(horas%10));
  atualizaDisplay(9,round(horas/10));
  }
}

void loop() {
  relogio();
  mostraHora();
  ajuste();
}
