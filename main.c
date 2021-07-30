#include "pic18f4520.h"
#include "config.h"
#include "atraso.h"
#include "lcd.h"
#include "adc.h"
#include "i2c.h"
#include "pwm.h"
#include "bits.h"

void itoa(unsigned int val, char* str );
void itoa1(unsigned int val1, char* str1 );

void main() {

    unsigned char tmp, umid,temp;
    unsigned char tensao;
    char str[6],grau = 223;
    char str1[6];

    ADCON1 = 0x06;
    TRISA = 0xC3;
    TRISB = 0xF0;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    lcd_init();
    adc_init();
    pwmInit();

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Ligar o circuito");
    lcd_cmd(L_L2);
    lcd_str("pressionando RB5");
    while (PORTBbits.RB5);
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Sensor1 = ");
    lcd_cmd(L_L2);
    lcd_str("Sensor2 = ");
    
    for (;;) {
        umid = (adc_amostra(2)*10) / 204;
        tmp = (adc_amostra(0)*10) / 204;
        lcd_cmd(L_L1 + 9 );
        itoa(tmp, str);
        itoa1(umid, str1);
        tensao = str[3];
        umid = str1[3];
        
             if(tensao <= 50 && tensao >= 49) pwmSet1(32);
             if(tensao <= 52 && tensao > 50)  pwmSet1(64);
             if(tensao <= 53 && tensao > 52)  pwmSet1(92);
             if(tensao == 48) pwmSet1(0);
             if(umid <= 50 && umid >= 49) 
             {    
                BitSet(PORTB,2);
                BitSet(PORTB,3);
                BitClr(PORTB,1);
             }
             if(umid <= 52 && umid > 50)
             {  
                BitClr(PORTB,2);
                BitSet(PORTB,3);
                BitClr(PORTB,1);
             }
             if(umid <= 53 && umid > 52)
             {  
                BitClr(PORTB,1);
                BitClr(PORTB,3);
                BitClr(PORTB,2);
             }
             if(umid == 48)
             { 
                 BitSet(PORTB,3);
                 BitSet(PORTB,2);
                 BitSet(PORTB,1);   
             }
        lcd_dat(str[3]);
        lcd_dat('V');
        lcd_dat(' ');
        lcd_dat(str[3]);
        lcd_dat(str[4]);
        lcd_dat(grau);
        lcd_dat('C');
        lcd_cmd(L_L2 + 9 );
        lcd_dat(str1[3]);
        lcd_dat('V');
        atraso_ms(10);
}
}
void itoa(unsigned int val, char* str )
{
  str[0]=(val/10000)+0x30;  
  str[1]=((val%10000)/1000)+0x30;  
  str[2]=((val%1000)/100)+0x30;  
  str[3]=((val%100)/10)+0x30;
  str[4]=(val%10)+0x30;
  str[5]=0;
}
void itoa1(unsigned int val1, char* str1 )
{
  str1[0]=(val1/10000)+0x30;  
  str1[1]=((val1%10000)/1000)+0x30;  
  str1[2]=((val1%1000)/100)+0x30;  
  str1[3]=((val1%100)/10)+0x30;
  str1[4]=(val1%10)+0x30;
  str1[5]=0;
}