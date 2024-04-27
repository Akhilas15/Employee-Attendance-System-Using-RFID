//uart0_interrupt//
#include<LPC21xx.h>
//#define RDR (U0LSR&1)
extern int j;
//extern int t;
//extern char empl[13];
//extern int flag;
//extern int c;
extern char temp[100];
int i=0;
void uart0_handler(void)__irq
{
  int t=U0IIR;
 if(t&4)//masking//
  {
    temp[i++]=U0RBR;
    // lcd_cmd(0xc0);
	// lcd_data('b');
    //	c++;
   }
  
   /*empl[j]=U0RBR;
   if(j==12){
   	empl[j]=0;
	flag=1;
	j=0;
   }*/			  
   	
   VICVectAddr=0;
}

void config_VIC(void)
{
VICIntSelect=0;
VICVectCntl0=6|(1<<5);
VICVectAddr0=(int)uart0_handler;
VICIntEnable|=1<<6;
}
void en_uart0_intr(void)
{
U0IER=3;
}
