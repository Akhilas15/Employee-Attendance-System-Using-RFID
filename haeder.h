//header.h//
#include<LPC21xx.h>
//typedef unsigned char u8;
//typedef signed char s8;
//typedef signed int s32;
//typedef unsigned int u32;
extern void delay_sec(unsigned int sec);
extern void delay_ms(unsigned int ms);

extern void uart0_init(unsigned int baud);

extern void uart0_tx(unsigned char data);

extern	unsigned char uart0_rx(void);

extern 	void uart0_tx_string(char *ptr);
extern 	void uart0_rx_string(char *ptr,int max_bytes);


extern void lcd_data(unsigned char data);

extern 	void lcd_cmd(unsigned char cmd);


extern void lcd_init(void);

extern void lcd_string(char *ptr);

extern void i2c_init(void);

extern void i2c_byte_write_frame(unsigned char sa,unsigned char mr,unsigned char data);

extern unsigned char i2c_byte_read_frame(unsigned char sa,unsigned char mr);

extern void config_VIC(void);

extern void en_uart0_intr(void);
