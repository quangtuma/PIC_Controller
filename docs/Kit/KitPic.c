// viet bang CCS 5.025

#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)

#define LCD_ENABLE_PIN PIN_D2
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>

volatile int16 increment = 1, pwm1 = 0;
volatile unsigned int16 buttonClicks = 0;

//ngat ngoai
#INT_EXT
void EXT_isr(void) {
	buttonClicks++;
}

//ngat Timer1
#int_TIMER1
void  TIMER1_isr(void)
{ 
	set_timer1(65036); //200us
   	
	//dao chieu tang PWM LED
	if(pwm1 >= 1023 - 1)
		increment = -1;
	if(pwm1 <= 1)
		increment = 1;
		   	
	pwm1 += increment;
	   	
	set_pwm1_duty(pwm1);
	set_pwm2_duty(1023 - pwm1);
} 

void main() {
	setup_adc_ports(AN0);
	setup_adc(ADC_CLOCK_INTERNAL);
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	setup_timer_2(T2_DIV_BY_16,255,1);      //819 us overflow, 819 us interrupt

	setup_ccp1(CCP_PWM);
	setup_ccp2(CCP_PWM);

	//Bat cac ngat
	enable_interrupts(INT_TIMER1); 
	enable_interrupts(INT_EXT);
	enable_interrupts(GLOBAL);

	lcd_init();
	lcd_putc("\fdientuspider.com");
   	
	delay_ms(1000);

	while(TRUE){
		delay_ms(200);
	   	
		int16 adc = read_adc();
		float vol = (float)adc * 5.0 / 65536.0;
		// cam bien nhiet do LM35, 10mV / do C
		float temperatureC = vol * 100;
		   	
		//update lcd
		printf(lcd_putc, "\fint:%ld T:%0.1f*C", (long)buttonClicks, temperatureC);
		lcd_gotoxy(11,2);
		printf(lcd_putc, "%0.2fV", vol);
		lcd_gotoxy(1,2);
		printf(lcd_putc, "ADC:%lu", (unsigned long)adc);
	}
}
