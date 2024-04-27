//rfid uart0_driver//
#include<LPC21xx.h>
#include"header.h"
void uart0_init(unsigned int baud)
{
 int a[]={15,60,30,0,15};
 unsigned int result=0;
 unsigned pclk=0;
 pclk=a[VPBDIV]*1000000;
 result=pclk/(16*baud);
 PINSEL0|=0x5;
 U0LCR=0x83;
 U0DLL=result&0xff;
 U0DLM=(result>>8)&0xff;
 U0LCR=0x03;
 } 

 #define THRE ((U0LSR>>5)&1)
 void uart0_tx(unsigned char data)
 {
  U0THR=data;
  while(THRE==0);
 }

 #define RDR (U0LSR&1)
 unsigned char uart0_rx(void)
 {
  while(RDR==0);
  return U0RBR;
 }

 void uart0_tx_string(char *ptr)
 {
  while(*ptr)
  {
   U0THR=*ptr;
   while(THRE==0);
   ptr++;
  }
}

void uart0_rx_string(char *arr,int max_bytes)
{
 int i;
 for(i=0;i<max_bytes;i++)
 {
   while(RDR==0);
   arr[i]=U0RBR;
   uart0_tx(arr[i]);
   if(arr[i]=='\r')
   break;
   }
   //if(i==12)
   arr[i]='\0';
}

void uart0_tx_int(int num)
{
 char a[10];
 int i;
 if(num=='0')
 {
  uart0_tx('0');
  return;
 }
 if(num<0)
 {
   uart0_tx('-');
   num=-num;
  }
  i=0;
  while(num!=0)
  {
    a[i]=num%10;
	num=num/10;
	i++;
  }
  for(--i;i>=0;i--)
  {
   uart0_tx(a[i]+48);
  }
}
