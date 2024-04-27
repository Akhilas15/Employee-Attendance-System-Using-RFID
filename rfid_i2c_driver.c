//rfid_i2c_driver//
#include<LPC21xx.h>
#include"header.h"
#define SI ((I2CONSET>>3)&1)
void i2c_init(void)
{
 PINSEL0|=0x50;
 I2SCLH=75;
 I2SCLL=75;
 I2CONSET=(1<<6);
}
void i2c_byte_write_frame(unsigned char  sa,unsigned char mr,unsigned char data)
{
  I2CONSET=(1<<5);
  I2CONCLR=(1<<3);

  while(SI==0);

  I2CONCLR=(1<<5);

  /*if(I2STAT!=0x08)
  {
    uart0_tx_string("Err:start condi\r\n");
   goto exit;
  }
	*/
    I2DAT=sa;
    I2CONCLR=(1<<3);
    while(SI==0);

  /*if(I2STAT==0x20)
  {
    uart0_tx_string("Err:slave addr\r\n");
   goto exit;
  }
  	*/
  I2DAT=mr;
  I2CONCLR=(1<<3);
  while(SI==0);
   
/*if(I2STAT==0x30)
 {
    uart0_tx_string("Err:memory addr\r\n");
    goto exit;
 }
  */
  I2DAT=data;
  I2CONCLR=(1<<3);
  while(SI==0);

 /*if(I2STAT==0x30)
 {
   uart0_tx_string("Err:data\r\n");
	    //goto exit;
 }
   */
//  exit:
   I2CONSET=(1<<4);
   I2CONCLR=(1<<3);
 }
 unsigned char i2c_byte_read_frame(unsigned char sa,unsigned char mr)
 {
   unsigned char temp=0;
   I2CONSET=(1<<5);
   I2CONCLR=(1<<3);

   while(SI==0);
   I2CONCLR=(1<<5);

  /* if(I2STAT!=0x8)
   {
    uart0_tx_string("Err:start dindition\r\n");
	goto exit;
   }
	*/
   I2DAT=sa;
   I2CONCLR=(1<<3);
    while(SI==0);

  /* if(I2STAT==0x20)
   {
    uart0_tx_string("Err:sa+w\r\n");
	goto exit;
	}
	*/
   I2DAT=mr;
   I2CONCLR=(1<<3);
   while(SI==0);

  /* if(I2STAT==0x30)
   {
    uart0_tx_string("Err:mry add\r\n");
	goto exit;
   }
	*/
   I2CONSET=(1<<5);
   I2CONCLR=(1<<3);
   while(SI==0);
   I2CONCLR=(1<<5);

	/*if(I2STAT!=0x10)
	{
	 uart0_tx_string("Err:restart condin\r\n");
	 goto exit;
	 }
	  */
   I2DAT=sa|1;
   I2CONCLR=(1<<3);
   while(SI==0);

   /*if(I2STAT==0x48)
   {
    uart0_tx_string("Err:sa+r\r\n");
	goto exit;
	}
	 */
   I2CONCLR=(1<<3);
   while(SI==0);
   temp=I2DAT;
	// exit:
   I2CONSET=(1<<4);
   I2CONCLR=(1<<3);
    return temp;
}
