#include <main.h>

double valueADC;

void setup() {
   /*
   lcd_init();
   lcd_clear();
   lcd_gotoxy(1, 1);
   printf(lcd_putc, "Hello");
   
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(SENSOR_PIN);
   set_adc_channel(1); */
   
   output_bit(PUMP, ON);
   set_tris_c(0xFE);
   
   delay_ms(20);
}

void main() {
   setup();
   
   while(1) {
   /*   valueADC = read_adc();
      calculatePID(valueADC);
      lcd_gotoxy(2, 1);
      printf(lcd_putc, "Level: ");
      lcd_gotoxy(2, 8);
      printf(lcd_putc, valueADC); */
      
      output_high(PIN_C1);
      delay_ms(500);
      output_low(PIN_C1);
      delay_ms(500);
   }
}
