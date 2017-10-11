#include  "msp430_version.h"
#include "osc.h"
#define MAX 1500
int n=1;
int i;
void (*fp)(void);//

void toggle_port(void){
  P2OUT^=0xFF;
  for(i=0;i<MAX;i++);
}

void inicio(void){
    P2OUT=0xF0;
}

void shift_port(void)
{
 // if (P2OUT==0xF0){
    while ((P2OUT & 0x01)!=0x01){
           P2OUT = P2OUT >> 1; 
           for(i=0;i<MAX;i++);
          }
    while ((P2OUT & 0x80)!=0x80){
           P2OUT = P2OUT << 1;
          for(i=0;i<MAX;i++) ;
    }
 // }
}

void main(void)
{
        P2DIR = 0xFF;
        fp=inicio;
       	P1DIR = 0x00;
        P1IE |= BIT0;
        P1IES |= 0X01;
        P1IFG |= 0X00;
        osc_init_xt2();
	WDTCTL = WDTPW + WDTHOLD;
	//TACCTL0 = CCIE;			// TACCR0 habilita interrupción del timer
	//TTACCR0 = 500;
	//TACTL = TASSEL_2 + MC_1; 
        	// 
        //P2DIR = 0xFF;
        //fp=inicio;
       	//P1DIR = 0x00;
        //P1IE |= BIT0;
        //P1IES |= 0X01;
        //P1IFG |= 0X00;
        
        _BIS_SR(GIE); 	// modo bajo consumo e interrupciones
        while(1){
            fp();
        }
}

// Timer A0 rutina de servicio de interrupción
#pragma vector = PORT1_VECTOR
__interrupt void PORT1(void)
{

if (n%2)
        {
            fp=shift_port;
        }
        else
        {
            fp=toggle_port;
}
        n=n+1;
            P1IFG=0x00;
}

