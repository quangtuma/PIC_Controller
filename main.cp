#line 1 "C:/Users/QUANG TU PC/Desktop/PIC Project/PIC_Controller/main.c"
#line 1 "c:/users/quang tu pc/desktop/pic project/pic_controller/main.h"
#line 1 "c:/users/quang tu pc/desktop/pic project/pic_controller/lcd_i2c.c"





byte lcd_total_rows = 4;
byte lcd_total_columns =20 ;
#line 23 "c:/users/quang tu pc/desktop/pic project/pic_controller/lcd_i2c.c"
int8 new_row_request=1, BACKLIGHT_LED= 0b00001000 ;

void lcd_backlight_led(byte bl)
{
 If (bl) BACKLIGHT_LED= 0b00001000 ; else BACKLIGHT_LED= 0 ;
}

void i2c_send_nibble(byte data, byte type)
{
 switch (type)
 {
 case 0 :
 i2c_write( data<<4  | BACKLIGHT_LED);
 delay_cycles(1);
 i2c_write( data<<4  |  0b00000100  | BACKLIGHT_LED );
 delay_us(2);
 i2c_write( data<<4  &  ~   0b00000100  | BACKLIGHT_LED);
 break;

 case 1 :
 i2c_write( data<<4  |  0b00000001  | BACKLIGHT_LED);
 delay_cycles(1);
 i2c_write( data<<4  |  0b00000001  |  0b00000100  | BACKLIGHT_LED );
 delay_us(2);
 i2c_write( data<<4  |  0b00000001  | BACKLIGHT_LED);
 break;
 }
}

void lcd_send_byte(byte data, byte type)
 {
 i2c_start();
 i2c_write( 0x4E );
 i2c_send_nibble(data >> 4 , type);
 i2c_send_nibble(data & 0xf , type);
 i2c_stop();
 }

void lcd_clear()
{
 lcd_send_byte(0x01,0);
 delay_ms(2);
 new_row_request=1;
}

void lcd_init()
{
 byte i;
 byte CONST lcd_type=2;
 byte CONST LCD_INIT_STRING[4] = {0x20 | (lcd_type << 2), 0xc, 1, 6};

 BACKLIGHT_LED= 0b00001000 ;



 disable_interrupts(GLOBAL);
 delay_ms(50);

 i2c_start();
 i2c_write( 0x4E );
 i2c_send_nibble(0x00,0);
 delay_ms(15);

 for (i=1;i<=3;++i)
 {
 i2c_send_nibble(0x03,0);
 delay_ms(5);
 }
 i2c_send_nibble(0x02,0);
 delay_ms(5);
 i2c_stop();

 for (i=0;i<=3;++i) {
 lcd_send_byte(LCD_INIT_STRING[i],0);
 delay_ms(5);
 }
 lcd_clear();
 enable_interrupts(GLOBAL);
}

void lcd_gotoxy( byte x, byte y)
{
byte row,column,row_addr,lcd_address;


 if (y>lcd_total_rows) row=lcd_total_rows; else row=y;

 switch(row)
 {
 case 1: row_addr= 0x00 ; break;
 case 2: row_addr= 0x40 ; break;
 case 3: row_addr= 0x14 ; break;
 case 4: row_addr= 0x54 ; break;
 default: row_addr= 0x00 ; break;
 }

 if (x>lcd_total_columns) column=lcd_total_columns; else column=x;
 lcd_address=(row_addr+(column-1));
 lcd_send_byte(0x80|lcd_address,0);
}


void lcd_putc(char in_data)
{

 switch(in_data)
 {

 case '\f': lcd_clear(); break;

 case '\n':
 new_row_request++;
 if (new_row_request>lcd_total_rows) new_row_request=1;
 lcd_gotoxy(1, new_row_request);

 break;

 case '\b': lcd_send_byte(0x10,0); break;

 default: lcd_send_byte(in_data,1); break;

 }
}
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/string.h"





void * memchr(void *p, char n, unsigned int v);
int memcmp(void *s1, void *s2, int n);
void * memcpy(void * d1, void * s1, int n);
void * memmove(void * to, void * from, int n);
void * memset(void * p1, char character, int n);
char * strcat(char * to, char * from);
char * strchr(char * ptr, char chr);
int strcmp(char * s1, char * s2);
char * strcpy(char * to, char * from);
int strlen(char * s);
char * strncat(char * to, char * from, int size);
char * strncpy(char * to, char * from, int size);
int strspn(char * str1, char * str2);
char strcspn(char * s1, char * s2);
int strncmp(char * s1, char * s2, char len);
char * strpbrk(char * s1, char * s2);
char * strrchr(char *ptr, char chr);
char * strstr(char * s1, char * s2);
char * strtok(char * s1, char * s2);
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/math.h"





double fabs(double d);
double floor(double x);
double ceil(double x);
double frexp(double value, int * eptr);
double ldexp(double value, int newexp);
double modf(double val, double * iptr);
double sqrt(double x);
double atan(double f);
double asin(double x);
double acos(double x);
double atan2(double y,double x);
double sin(double f);
double cos(double f);
double tan(double x);
double exp(double x);
double log(double x);
double log10(double x);
double pow(double x, double y);
double sinh(double x);
double cosh(double x);
double tanh(double x);
#line 3 "C:/Users/QUANG TU PC/Desktop/PIC Project/PIC_Controller/main.c"
void main() {

}
