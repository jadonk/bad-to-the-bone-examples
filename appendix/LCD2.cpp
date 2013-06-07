//******************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define  output "out"
#define  input  "in"

//function prototypes
void configure_LCD_interface(void);
void LCD_putcommand(unsigned char);
void LCD_putchar(unsigned char);
void LCD_print(unsigned int, char *string);
void delay_us(int);
void LCD_init(void);

//LCD_RS: bone.P8_29 LCD Register Set (RS) control: GPIO2_23: pin-87
FILE *ofp_lcd_hsync, *export_87, *gpio87_value, *gpio87_direction;
int mux_mode_87 = 0x8007, pin_number_87 = 87, logic_status_87 = 1;
char* pin_direction_87 = output;

//LCD_E:   bone.P8_28: LCD Enable En (E): GPIO2_24: pin-88
FILE *ofp_lcd_pclk, *export_88, *gpio88_value, *gpio88_direction;
int mux_mode_88 = 0x8007, pin_number_88 = 88, logic_status_88 = 1;
char* pin_direction_88 = output;
  
//LCD_DB0: bone.P8_45: LCD Data line DB0: GPIO2_6: pin-70
FILE *ofp_lcd_data0, *export_70, *gpio70_value, *gpio70_direction;
int mux_mode_70 = 0x8007, pin_number_70 = 70, logic_status_70 = 1;
char* pin_direction_70 = output;

//LCD_DB1: bone.P8_46: LCD Data line DB1: GPIO2_7: pin-71
FILE *ofp_lcd_data1, *export_71, *gpio71_value, *gpio71_direction;
int mux_mode_71 = 0x8007, pin_number_71 = 71, logic_status_71 = 1;
char* pin_direction_71 = output;

//LCD_DB2: bone.P8_43: LCD Data line DB2: GPIO2_8: pin-72
FILE *ofp_lcd_data2, *export_72, *gpio72_value, *gpio72_direction;
int mux_mode_72 = 0x8007, pin_number_72 = 72, logic_status_72 = 1;
char* pin_direction_72 = output;

//LCD_DB3: bone.P8_44: LCD Data line DB3: GPIO2_9: pin-73
FILE *ofp_lcd_data3, *export_73, *gpio73_value, *gpio73_direction;
int mux_mode_73 = 0x8007, pin_number_73 = 73, logic_status_73 = 1;
char* pin_direction_73 = output;

//LCD_DB4: bone.P8_41: LCD Data line DB4: GPIO2_10: pin-74
FILE *ofp_lcd_data4, *export_74, *gpio74_value, *gpio74_direction;
int mux_mode_74 = 0x8007, pin_number_74 = 74, logic_status_74 = 1;
char* pin_direction_74 = output;

//LCD_DB5: bone.P8_42: LCD Data line DB5: GPIO2_11: pin-75
FILE *ofp_lcd_data5, *export_75, *gpio75_value, *gpio75_direction;
int mux_mode_75 = 0x8007, pin_number_75 = 75, logic_status_75 = 1;
char* pin_direction_75 = output;

//LCD_DB6: bone.P8_39: LCD Data line DB6: GPIO2_12: pin-76
FILE *ofp_lcd_data6, *export_76, *gpio76_value, *gpio76_direction;
int mux_mode_76 = 0x8007, pin_number_76 = 76, logic_status_76 = 1;
char* pin_direction_76 = output;

//LCD_DB7: bone.P8_40: LCD Data line DB0: GPIO2_13: pin-77
FILE *ofp_lcd_data7, *export_77, *gpio77_value, *gpio77_direction;
int mux_mode_77 = 0x8007, pin_number_77 = 77, logic_status_77 = 1;
char* pin_direction_77 = output;


int main(void)
{	
configure_LCD_interface();
printf("Configure LCD \n");
LCD_init();  //call LCD initialize
printf("LCD initialize \n");

while(1)
 {
  LCD_print(1, "G");
  printf("G\n");
  delay_us(100);
  //LCD_print(2, "Bonescript");
  //printf("Bonescript\n");
  delay_us(100);
  }
return 1;
}

//******************************************************************
//void configure_LCD_interface(void)
//******************************************************************

void configure_LCD_interface(void)
{

//gpio87 mux setting
ofp_lcd_hsync = fopen("/sys/kernel/debug/omap_mux/lcd_hsync", "w");
if(ofp_lcd_hsync == NULL) {printf("Unable to open lcd_hsync.\n");}
fseek(ofp_lcd_hsync, 0, SEEK_SET);
fprintf(ofp_lcd_hsync, "0x%02x", mux_mode_87);
fflush(ofp_lcd_hsync);

//create direction and value file for gpio87
export_87 = fopen("/sys/class/gpio/export", "w");
if(export_87 == NULL) {printf("Unable to open export.\n");}
fseek(export_87, 0, SEEK_SET);
fprintf(export_87, "%d", pin_number_87);
fflush(export_87);

//configure gpio87 direction
gpio87_direction = fopen("/sys/class/gpio/gpio87/direction", "w");
if(gpio87_direction == NULL) {printf("Unable to open gpio87_direction.\n");}
fseek(gpio87_direction, 0, SEEK_SET);
fprintf(gpio87_direction, "%s",  pin_direction_87);
fflush(gpio87_direction);


//LCD_E
//gpio88 mux setting
ofp_lcd_pclk = fopen("/sys/kernel/debug/omap_mux/lcd_pclk", "w");
if(ofp_lcd_pclk == NULL) {printf("Unable to open lcd_pclk.\n");}
fseek(ofp_lcd_pclk, 0, SEEK_SET);
fprintf(ofp_lcd_pclk, "0x%02x", mux_mode_88);
fflush(ofp_lcd_pclk);

//create direction and value file for gpio88
export_88 = fopen("/sys/class/gpio/export", "w");
if(export_88 == NULL) {printf("Unable to open export.\n");}
fseek(export_88, 0, SEEK_SET);
fprintf(export_88, "%d", pin_number_88);
fflush(export_88);

//configure gpio88 direction
gpio88_direction = fopen("/sys/class/gpio/gpio88/direction", "w");
if(gpio88_direction == NULL) {printf("Unable to open gpio88_direction.\n");}
fseek(gpio88_direction, 0, SEEK_SET);
fprintf(gpio88_direction, "%s",  pin_direction_88);
fflush(gpio88_direction);


//LCD_DB0
//gpio70 mux setting
ofp_lcd_data0 = fopen("/sys/kernel/debug/omap_mux/lcd_data0", "w");
if(ofp_lcd_data0 == NULL) {printf("Unable to open lcd_data0.\n");}
fseek(ofp_lcd_data0, 0, SEEK_SET);
fprintf(ofp_lcd_data0, "0x%02x", mux_mode_70);
fflush(ofp_lcd_data0);

//create direction and value file for gpio70
export_70 = fopen("/sys/class/gpio/export", "w");
if(export_70 == NULL) {printf("Unable to open export.\n");}
fseek(export_70, 0, SEEK_SET);
fprintf(export_70, "%d", pin_number_70);
fflush(export_70);

//configure gpio70 direction
gpio70_direction = fopen("/sys/class/gpio/gpio70/direction", "w");
if(gpio70_direction == NULL) {printf("Unable to open gpio70_direction.\n");}
fseek(gpio70_direction, 0, SEEK_SET);
fprintf(gpio70_direction, "%s",  pin_direction_70);
fflush(gpio70_direction);


//LCD_DB1
//gpio71 mux setting
ofp_lcd_data1 = fopen("/sys/kernel/debug/omap_mux/lcd_data1", "w");
if(ofp_lcd_data1 == NULL) {printf("Unable to open lcd_data1.\n");}
fseek(ofp_lcd_data1, 0, SEEK_SET);
fprintf(ofp_lcd_data1, "0x%02x", mux_mode_71);
fflush(ofp_lcd_data1);

//create direction and value file for gpio71
export_71 = fopen("/sys/class/gpio/export", "w");
if(export_71 == NULL) {printf("Unable to open export.\n");}
fseek(export_71, 0, SEEK_SET);
fprintf(export_71, "%d", pin_number_71);
fflush(export_71);

//configure gpio71 direction
gpio71_direction = fopen("/sys/class/gpio/gpio71/direction", "w");
if(gpio71_direction == NULL) {printf("Unable to open gpio71_direction.\n");}
fseek(gpio71_direction, 0, SEEK_SET);
fprintf(gpio71_direction, "%s",  pin_direction_71);
fflush(gpio71_direction);


//LCD_DB2
//gpio72 mux setting
ofp_lcd_data2 = fopen("/sys/kernel/debug/omap_mux/lcd_data2", "w");
if(ofp_lcd_data2 == NULL) {printf("Unable to open lcd_data2.\n");}
fseek(ofp_lcd_data2, 0, SEEK_SET);
fprintf(ofp_lcd_data2, "0x%02x", mux_mode_72);
fflush(ofp_lcd_data2);

//create direction and value file for gpio72
export_72 = fopen("/sys/class/gpio/export", "w");
if(export_72 == NULL) {printf("Unable to open export.\n");}
fseek(export_72, 0, SEEK_SET);
fprintf(export_72, "%d", pin_number_72);
fflush(export_72);

//configure gpio72 direction
gpio72_direction = fopen("/sys/class/gpio/gpio72/direction", "w");
if(gpio72_direction == NULL) {printf("Unable to open gpio72_direction.\n");}
fseek(gpio72_direction, 0, SEEK_SET);
fprintf(gpio72_direction, "%s",  pin_direction_72);
fflush(gpio72_direction);


//LCD_DB3
//gpio73 mux setting
ofp_lcd_data3 = fopen("/sys/kernel/debug/omap_mux/lcd_data3", "w");
if(ofp_lcd_data3 == NULL) {printf("Unable to open lcd_data3.\n");}
fseek(ofp_lcd_data3, 0, SEEK_SET);
fprintf(ofp_lcd_data3, "0x%02x", mux_mode_73);
fflush(ofp_lcd_data3);

//create direction and value file for gpio73
export_73 = fopen("/sys/class/gpio/export", "w");
if(export_73 == NULL) {printf("Unable to open export.\n");}
fseek(export_73, 0, SEEK_SET);
fprintf(export_73, "%d", pin_number_73);
fflush(export_73);

//configure gpio73 direction
gpio73_direction = fopen("/sys/class/gpio/gpio73/direction", "w");
if(gpio73_direction == NULL) {printf("Unable to open gpio73_direction.\n");}
fseek(gpio73_direction, 0, SEEK_SET);
fprintf(gpio73_direction, "%s",  pin_direction_73);
fflush(gpio73_direction);


//LCD_DB4
//gpio74 mux setting
ofp_lcd_data4 = fopen("/sys/kernel/debug/omap_mux/lcd_data4", "w");
if(ofp_lcd_data4 == NULL) {printf("Unable to open lcd_data4.\n");}
fseek(ofp_lcd_data4, 0, SEEK_SET);
fprintf(ofp_lcd_data4, "0x%02x", mux_mode_74);
fflush(ofp_lcd_data4);

//create direction and value file for gpio74
export_74 = fopen("/sys/class/gpio/export", "w");
if(export_74 == NULL) {printf("Unable to open export.\n");}
fseek(export_74, 0, SEEK_SET);
fprintf(export_74, "%d", pin_number_74);
fflush(export_74);

//configure gpio74 direction
gpio74_direction = fopen("/sys/class/gpio/gpio74/direction", "w");
if(gpio74_direction == NULL) {printf("Unable to open gpio74_direction.\n");}
fseek(gpio74_direction, 0, SEEK_SET);
fprintf(gpio74_direction, "%s",  pin_direction_74);
fflush(gpio74_direction);


//LCD_DB5
//gpio75 mux setting
ofp_lcd_data5 = fopen("/sys/kernel/debug/omap_mux/lcd_data5", "w");
if(ofp_lcd_data5 == NULL) {printf("Unable to open lcd_data5.\n");}
fseek(ofp_lcd_data5, 0, SEEK_SET);
fprintf(ofp_lcd_data5, "0x%02x", mux_mode_75);
fflush(ofp_lcd_data5);

//create direction and value file for gpio75
export_75 = fopen("/sys/class/gpio/export", "w");
if(export_75 == NULL) {printf("Unable to open export.\n");}
fseek(export_75, 0, SEEK_SET);
fprintf(export_75, "%d", pin_number_75);
fflush(export_75);

//configure gpio75 direction
gpio75_direction = fopen("/sys/class/gpio/gpio75/direction", "w");
if(gpio75_direction == NULL) {printf("Unable to open gpio75_direction.\n");}
fseek(gpio75_direction, 0, SEEK_SET);
fprintf(gpio75_direction, "%s",  pin_direction_75);
fflush(gpio75_direction);


//LCD_DB6
//gpio76 mux setting
ofp_lcd_data6 = fopen("/sys/kernel/debug/omap_mux/lcd_data6", "w");
if(ofp_lcd_data6 == NULL) {printf("Unable to open lcd_data6.\n");}
fseek(ofp_lcd_data6, 0, SEEK_SET);
fprintf(ofp_lcd_data6, "0x%02x", mux_mode_76);
fflush(ofp_lcd_data6);

//create direction and value file for gpio76
export_76 = fopen("/sys/class/gpio/export", "w");
if(export_76 == NULL) {printf("Unable to open export.\n");}
fseek(export_76, 0, SEEK_SET);
fprintf(export_76, "%d", pin_number_76);
fflush(export_76);

//configure gpio76 direction
gpio76_direction = fopen("/sys/class/gpio/gpio76/direction", "w");
if(gpio76_direction == NULL) {printf("Unable to open gpio76_direction.\n");}
fseek(gpio76_direction, 0, SEEK_SET);
fprintf(gpio76_direction, "%s",  pin_direction_76);
fflush(gpio76_direction);


//LCD_DB7
//gpio77 mux setting
ofp_lcd_data7 = fopen("/sys/kernel/debug/omap_mux/lcd_data7", "w");
if(ofp_lcd_data7 == NULL) {printf("Unable to open lcd_data7.\n");}
fseek(ofp_lcd_data7, 0, SEEK_SET);
fprintf(ofp_lcd_data7, "0x%02x", mux_mode_77);
fflush(ofp_lcd_data7);

//create direction and value file for gpio77
export_77 = fopen("/sys/class/gpio/export", "w");
if(export_77 == NULL) {printf("Unable to open export.\n");}
fseek(export_77, 0, SEEK_SET);
fprintf(export_77, "%d", pin_number_77);
fflush(export_77);

//configure gpio77 direction
gpio77_direction = fopen("/sys/class/gpio/gpio77/direction", "w");
if(gpio77_direction == NULL) {printf("Unable to open gpio77_direction.\n");}
fseek(gpio77_direction, 0, SEEK_SET);
fprintf(gpio77_direction, "%s",  pin_direction_77);
fflush(gpio77_direction);
}

//******************************************************************
//LCD_init
//******************************************************************

void LCD_init(void)
{
delay_us(15000);                   //wait 15 ms
LCD_putcommand(0x30);              //set for 8-bit operation
delay_us(5000);                    //delay 5 ms
LCD_putcommand(0x30);              //set for 8-bit operation
delay_us(100);                     //delay 100 us
LCD_putcommand(0x30);              //set for 8-bit operation
LCD_putcommand(0x38);              //function set
LCD_putcommand(0x80);              //display off
LCD_putcommand(0x01);              //display clear
LCD_putcommand(0x06);              //entry mode set
}

//******************************************************************
//LCD_putcommand
//******************************************************************

void LCD_putcommand(unsigned char cmd)
{
//parse command variable into individual bits for output
//to LCD

//configure DB7 value
gpio77_value = fopen("/sys/class/gpio/gpio77/value", "w");
if(gpio77_value == NULL) {printf("Unable to open gpio77_value.\n");}
fseek(gpio77_value, 0, SEEK_SET);
if((cmd & 0x0080)== 0x0080)
  {
  printf("CmDB7:1");
  logic_status_77 = 1; 
  fprintf(gpio77_value, "%d", logic_status_77);
  }
else
  {
  printf(" CmDB7:0");
  logic_status_77 = 0;
  fprintf(gpio77_value, "%d", logic_status_77);
  }
fflush(gpio77_value);


//configure DB6 value
gpio76_value = fopen("/sys/class/gpio/gpio76/value", "w");
if(gpio76_value == NULL) {printf("Unable to open gpio76_value.\n");}
fseek(gpio76_value, 0, SEEK_SET);
if((cmd & 0x0040)== 0x0040)
  {
  printf(" CmDB6:1");
  logic_status_76 = 1; 
  fprintf(gpio76_value, "%d", logic_status_76);
  }
else
  {
  printf(" CmDB6:0");
  logic_status_76 = 0;
  fprintf(gpio76_value, "%d", logic_status_76);
  }
fflush(gpio76_value);


//configure DB5 value
gpio75_value = fopen("/sys/class/gpio/gpio75/value", "w");
if(gpio75_value == NULL) {printf("Unable to open gpio75_value.\n");}
fseek(gpio75_value, 0, SEEK_SET);
if((cmd & 0x0020)== 0x0020)
  {
  printf(" CmDB5:1");
  logic_status_75 = 1; 
  fprintf(gpio75_value, "%d", logic_status_75);
  }
else
  {
  printf(" CmDB5:0");
  logic_status_75 = 0;
  fprintf(gpio75_value, "%d", logic_status_75);
  }
fflush(gpio75_value);


//configure DB4 value
gpio74_value = fopen("/sys/class/gpio/gpio74/value", "w");
if(gpio74_value == NULL) {printf("Unable to open gpio74_value.\n");}
fseek(gpio74_value, 0, SEEK_SET);
if((cmd & 0x0010)== 0x0010)
  {
  printf(" CmDB4:1");
  logic_status_74 = 1; 
  fprintf(gpio74_value, "%d", logic_status_74);
  }
else
  {
  printf(" CmDB4:0");
  logic_status_74 = 0;
  fprintf(gpio74_value, "%d", logic_status_74);
  }
fflush(gpio74_value);


//configure DB3 value
gpio73_value = fopen("/sys/class/gpio/gpio73/value", "w");
if(gpio73_value == NULL) {printf("Unable to open gpio73_value.\n");}
fseek(gpio73_value, 0, SEEK_SET);
if((cmd & 0x0008)== 0x0008)
  {
  printf(" CmDB3:1");
  logic_status_73 = 1; 
  fprintf(gpio73_value, "%d", logic_status_73);
  }
else
  {
  printf(" CmDB3:0");
  logic_status_73 = 0;
  fprintf(gpio73_value, "%d", logic_status_73);
  }
fflush(gpio73_value);


//configure DB2 value
gpio72_value = fopen("/sys/class/gpio/gpio72/value", "w");
if(gpio72_value == NULL) {printf("Unable to open gpio72_value.\n");}
fseek(gpio72_value, 0, SEEK_SET);
if((cmd & 0x0004)== 0x0004)
  {
  printf(" CmDB2:1");
  logic_status_72 = 1; 
  fprintf(gpio72_value, "%d", logic_status_72);
  }
else
  {
  printf(" CmDB2:0");
  logic_status_72 = 0;
  fprintf(gpio72_value, "%d", logic_status_72);
  }
fflush(gpio72_value);


//configure DB1 value
gpio71_value = fopen("/sys/class/gpio/gpio71/value", "w");
if(gpio71_value == NULL) {printf("Unable to open gpio71_value.\n");}
fseek(gpio71_value, 0, SEEK_SET);
if((cmd & 0x0002)== 0x0002)
  {
  printf(" CmDB1:1");
  logic_status_71 = 1; 
  fprintf(gpio71_value, "%d", logic_status_71);
  }
else
  {
  printf(" CmDB1:0");
  logic_status_71 = 0;
  fprintf(gpio77_value, "%d", logic_status_71);
  }
fflush(gpio71_value);


//configure DB0 value
gpio70_value = fopen("/sys/class/gpio/gpio70/value", "w");
if(gpio70_value == NULL) {printf("Unable to open gpio70_value.\n");}
fseek(gpio70_value, 0, SEEK_SET);
if((cmd & 0x0001)== 0x0001)
  {
  printf(" CmDB0:1\n");
  logic_status_70 = 1; 
  fprintf(gpio70_value, "%d", logic_status_70);
  }
else
  {
  printf(" CmDB0:0\n");
  logic_status_70 = 0;
  fprintf(gpio70_value, "%d", logic_status_70);
  }
fflush(gpio70_value);

//LCD Register Set (RS) to logic zero for command input
logic_status_87 = 0;
gpio87_value = fopen("/sys/class/gpio/gpio87/value", "w");
if(gpio87_value == NULL) {printf("Unable to open gpio87_value.\n");}
fseek(gpio87_value, 0, SEEK_SET);
fprintf(gpio87_value, "%d", logic_status_87);
fflush(gpio87_value);


//LCD Enable (E) pin high
logic_status_88 = 1;
gpio88_value = fopen("/sys/class/gpio/gpio88/value", "w");
if(gpio88_value == NULL) {printf("Unable to open gpio88_value.\n");}
fseek(gpio88_value, 0, SEEK_SET);
fprintf(gpio88_value, "%d", logic_status_88);
fflush(gpio88_value);

//delay
delay_us(2);

//LCD Enable (E) pin low
logic_status_88 = 0;
gpio88_value = fopen("/sys/class/gpio/gpio88/value", "w");
if(gpio88_value == NULL) {printf("Unable to open gpio88_value.\n");}
fseek(gpio88_value, 0, SEEK_SET);
fprintf(gpio88_value, "%d", logic_status_88);
fflush(gpio88_value);

//delay
delay_us(100);
}

//******************************************************************
//LCD_putchar
//******************************************************************

void LCD_putchar(unsigned char chr)
{
//parse character variable into individual bits for output
//to LCD

printf("Data: %c:%d", chr, chr);
chr = (int)(chr);

//configure DB7 value
gpio77_value = fopen("/sys/class/gpio/gpio77/value", "w");
if(gpio77_value == NULL) {printf("Unable to open gpio77_value.\n");}
fseek(gpio77_value, 0, SEEK_SET);
if((chr & 0x0080)== 0x0080)
  {
  printf(" DB7:1");
  logic_status_77 = 1; 
  fprintf(gpio77_value, "%d", logic_status_77);
  }
else
  {
  printf(" DB7:0");	  
  logic_status_77 = 0;
  fprintf(gpio77_value, "%d", logic_status_77);
  }
fflush(gpio77_value);


//configure DB6 value
gpio76_value = fopen("/sys/class/gpio/gpio76/value", "w");
if(gpio76_value == NULL) {printf("Unable to open gpio76_value.\n");}
fseek(gpio76_value, 0, SEEK_SET);
if((chr & 0x0040)== 0x0040)
  {
  printf(" DB6:1");
  logic_status_76 = 1; 
  fprintf(gpio76_value, "%d", logic_status_76);
  }
else
  {
  printf(" DB6:0");
  logic_status_76 = 0;
  fprintf(gpio76_value, "%d", logic_status_76);
  }
fflush(gpio76_value);


//configure DB5 value
gpio75_value = fopen("/sys/class/gpio/gpio75/value", "w");
if(gpio75_value == NULL) {printf("Unable to open gpio75_value.\n");}
fseek(gpio75_value, 0, SEEK_SET);
if((chr & 0x0020)== 0x0020)
  {
  printf(" DB5:1");
  logic_status_75 = 1; 
  fprintf(gpio75_value, "%d", logic_status_75);
  }
else
  {
  printf(" DB5:0");
  logic_status_75 = 0;
  fprintf(gpio75_value, "%d", logic_status_75);
  }
fflush(gpio75_value);


//configure DB4 value
gpio74_value = fopen("/sys/class/gpio/gpio74/value", "w");
if(gpio74_value == NULL) {printf("Unable to open gpio74_value.\n");}
fseek(gpio74_value, 0, SEEK_SET);
if((chr & 0x0010)== 0x0010)
  {
  printf(" DB4:1");
  logic_status_74 = 1; 
  fprintf(gpio74_value, "%d", logic_status_74);
  }
else
  {
  printf(" DB4:0");
  logic_status_74 = 0;
  fprintf(gpio74_value, "%d", logic_status_74);
  }
fflush(gpio74_value);


//configure DB3 value
gpio73_value = fopen("/sys/class/gpio/gpio73/value", "w");
if(gpio73_value == NULL) {printf("Unable to open gpio73_value.\n");}
fseek(gpio73_value, 0, SEEK_SET);
if((chr & 0x0008)== 0x0008)
  {
  printf(" DB3:1");
  logic_status_73 = 1; 
  fprintf(gpio73_value, "%d", logic_status_73);
  }
else
  {
  printf(" DB3:0");
  logic_status_73 = 0;
  fprintf(gpio73_value, "%d", logic_status_73);
  }
fflush(gpio73_value);


//configure DB2 value
gpio72_value = fopen("/sys/class/gpio/gpio72/value", "w");
if(gpio72_value == NULL) {printf("Unable to open gpio72_value.\n");}
fseek(gpio72_value, 0, SEEK_SET);
if((chr & 0x0004)== 0x0004)
  {
  printf(" DB2:1");
  logic_status_72 = 1; 
  fprintf(gpio72_value, "%d", logic_status_72);
  }
else
  {
  printf(" DB2:0");
  logic_status_72 = 0;
  fprintf(gpio72_value, "%d", logic_status_72);
  }
fflush(gpio72_value);


//configure DB1 value
gpio71_value = fopen("/sys/class/gpio/gpio71/value", "w");
if(gpio71_value == NULL) {printf("Unable to open gpio71_value.\n");}
fseek(gpio71_value, 0, SEEK_SET);
if((chr & 0x0002)== 0x0002)
  {
  printf(" DB1:1");
  logic_status_71 = 1; 
  fprintf(gpio71_value, "%d", logic_status_71);
  }
else
  {
  printf(" DB1:0");
  logic_status_71 = 0;
  fprintf(gpio77_value, "%d", logic_status_71);
  }
fflush(gpio71_value);

//configure DB0 value
gpio70_value = fopen("/sys/class/gpio/gpio70/value", "w");
if(gpio70_value == NULL) {printf("Unable to open gpio70_value.\n");}
fseek(gpio70_value, 0, SEEK_SET);
if((chr & 0x0001)== 0x0001)
  {
  printf(" DB0:1\n");
  logic_status_70 = 1; 
  fprintf(gpio70_value, "%d", logic_status_70);
  }
else
  {
  printf(" DB0:0\n");
  logic_status_70 = 0;
  fprintf(gpio70_value, "%d", logic_status_70);
  }
fflush(gpio70_value);

//LCD Register Set (RS) to logic one for character input
logic_status_87 = 1;
gpio87_value = fopen("/sys/class/gpio/gpio87/value", "w");
if(gpio87_value == NULL) {printf("Unable to open gpio87_value.\n");}
fseek(gpio87_value, 0, SEEK_SET);
fprintf(gpio87_value, "%d", logic_status_87);
fflush(gpio87_value);


//LCD Enable (E) pin high
logic_status_88 = 1;
gpio88_value = fopen("/sys/class/gpio/gpio88/value", "w");
if(gpio88_value == NULL) {printf("Unable to open gpio88_value.\n");}
fseek(gpio88_value, 0, SEEK_SET);
fprintf(gpio88_value, "%d", logic_status_88);
fflush(gpio88_value);

//delay
delay_us(2);

//LCD Enable (E) pin low
logic_status_88 = 0;
gpio88_value = fopen("/sys/class/gpio/gpio88/value", "w");
if(gpio88_value == NULL) {printf("Unable to open gpio88_value.\n");}
fseek(gpio88_value, 0, SEEK_SET);
fprintf(gpio88_value, "%d", logic_status_88);
fflush(gpio88_value);

//delay
delay_us(2);

}

//******************************************************************
//******************************************************************
void LCD_print(unsigned int line, char *msg)
{
int i = 0;

if(line == 1)
  {
  LCD_putcommand(0x80);          //print to LCD line 1
  }
else
  {
  LCD_putcommand(0xc0);          //print to LCD line 2
  }

while(*(msg) != '\0')
  {
  LCD_putchar(*msg);
  //printf("Data: %c\n\n", *msg);
  msg++;
  }
}

//******************************************************************

void delay_us(int desired_delay_us)
{
struct timeval  tv_start;  //start time hack
struct timeval  tv_now;    //current time hack
int elapsed_time_us;

gettimeofday(&tv_start, NULL);
elapsed_time_us = 0;

while(elapsed_time_us <  desired_delay_us)
  {
  gettimeofday(&tv_now, NULL);
  if(tv_now.tv_usec >= tv_start.tv_usec)
    elapsed_time_us = tv_now.tv_usec - tv_start.tv_usec;
  else
    elapsed_time_us = (1000000 - tv_start.tv_usec) + tv_now.tv_usec;
  //printf("start: %ld \n", tv_start.tv_usec);
  //printf("now: %ld \n", tv_now.tv_usec);
  //printf("desired: %d \n", desired_delay_ms);
  //printf("elapsed: %d \n\n", elapsed_time_ms);
  }
}

//******************************************************************



