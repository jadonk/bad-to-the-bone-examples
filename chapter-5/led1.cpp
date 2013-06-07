//*******************************************************************
//led1.cpp: illuminates an LED connected to expansion header P8, pin3
//(GPIO1_6 designated as gpio38)
//*******************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define  output "out"     
#define  input  "in"

int  main (void)
{
//define file handles
FILE *ofp_gpmc_ad6, *ofp_export, *ofp_gpio38_value, *ofp_gpio38_direction;

//define pin variables
int mux_mode = 0x007, pin_number = 38, logic_status = 1;
char* pin_direction = output;

//configure the mux mode
ofp_gpmc_ad6 = fopen("/sys/kernel/debug/omap_mux/gpmc_ad6", "w");
if(ofp_gpmc_ad6 == NULL) {printf("Unable to open gpmc_ad6.\n");}
fseek(ofp_gpmc_ad6, 0, SEEK_SET);
fprintf(ofp_gpmc_ad6, "0x%02x", mux_mode);
fflush(ofp_gpmc_ad6);

//establish a direction and value file within export for gpio38
ofp_export = fopen("/sys/class/gpio/export", "w");
if(ofp_export == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export, 0, SEEK_SET);
fprintf(ofp_export, "%d", pin_number);
fflush(ofp_export);

//configure gpio38 for writing
ofp_gpio38_direction = fopen("/sys/class/gpio/gpio38/direction", "w");
if(ofp_gpio38_direction == NULL) {printf("Unable to open gpio38_direction.\n");}
fseek(ofp_gpio38_direction, 0, SEEK_SET);
fprintf(ofp_gpio38_direction, "%s",  pin_direction);
fflush(ofp_gpio38_direction);

//write a logic 1 to gpio38 to illuminate the LED
ofp_gpio38_value = fopen("/sys/class/gpio/gpio38/value", "w");
if(ofp_gpio38_value == NULL) {printf("Unable to open gpio38_value.\n");}
fseek(ofp_gpio38_value, 0, SEEK_SET);
fprintf(ofp_gpio38_value, "%d", logic_status);
fflush(ofp_gpio38_value);

//close all files
fclose(ofp_gpmc_ad6);
fclose(ofp_export);
fclose(ofp_gpio38_direction);
fclose(ofp_gpio38_value);
return 1;
}	
//********************************************************************

