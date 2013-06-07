//*********************************************************************
//led2.cpp: This program reads the logic value of a pushbutton switch
//connected to expansion header P8, pin 5 (GPIO1_2 designated as gpio34).
//If the switch is logic high (1) an LED connected to expansion header
//P8, pin3 (GPIO1_6 designated as gpio38) is illuminated.
//*********************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//define file handles for gpio38 (P8, pin 3, GPIO1_6)
FILE *ofp_gpmc_ad6, *ofp_export_38, *ofp_gpio38_value, *ofp_gpio38_direction;

//define file handles for gpio34 (P8, pin 5, GPIO1_2)
FILE *ofp_gpmc_ad2, *ofp_export_34, *ifp_gpio34_value, *ofp_gpio34_direction;

//define pin variables for gpio38
int mux_mode_38 = 0x0007, pin_number_38 = 38, logic_status_38 = 1;
char* pin_direction_38 = output;

//define pin variables for gpio34
int mux_mode_34 = 0x003f, pin_number_34 = 34, logic_status_34;
char* pin_direction_34 = input;

//gpio38 mux setting
ofp_gpmc_ad6 = fopen("/sys/kernel/debug/omap_mux/gpmc_ad6", "w");
if(ofp_gpmc_ad6 == NULL) {printf("Unable to open gpmc_ad6.\n");}
fseek(ofp_gpmc_ad6, 0, SEEK_SET);
fprintf(ofp_gpmc_ad6, "0x%02x", mux_mode_38);
fflush(ofp_gpmc_ad6);

//gpio34 mux setting
ofp_gpmc_ad2 = fopen("/sys/kernel/debug/omap_mux/gpmc_ad2", "w");
if(ofp_gpmc_ad2 == NULL) {printf("Unable to open gpmc_ad2.\n");}
fseek(ofp_gpmc_ad2, 0, SEEK_SET);
fprintf(ofp_gpmc_ad2, "0x%02x", mux_mode_34);
fflush(ofp_gpmc_ad2);

//create direction and value file for gpio38
ofp_export_38 = fopen("/sys/class/gpio/export", "w");
if(ofp_export_38 == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export_38, 0, SEEK_SET);
fprintf(ofp_export_38, "%d", pin_number_38);
fflush(ofp_export_38);

//create direction and value file for gpio34
ofp_export_34 = fopen("/sys/class/gpio/export", "w");
if(ofp_export_34 == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export_34, 0, SEEK_SET);
fprintf(ofp_export_34, "%d", pin_number_34);
fflush(ofp_export_34);

//configure gpio38 direction
ofp_gpio38_direction = fopen("/sys/class/gpio/gpio38/direction", "w");
if(ofp_gpio38_direction == NULL) {printf("Unable to open gpio38_direction.\n");}
fseek(ofp_gpio38_direction, 0, SEEK_SET);
fprintf(ofp_gpio38_direction, "%s",  pin_direction_38);
fflush(ofp_gpio38_direction);

//configure gpio34 direction
ofp_gpio34_direction = fopen("/sys/class/gpio/gpio34/direction", "w");
if(ofp_gpio34_direction == NULL) {printf("Unable to open gpio34_direction.\n");}
fseek(ofp_gpio34_direction, 0, SEEK_SET);
fprintf(ofp_gpio34_direction, "%s",  pin_direction_34);
fflush(ofp_gpio34_direction);

//configure gpio38 value \--- initially set logic high
ofp_gpio38_value = fopen("/sys/class/gpio/gpio38/value", "w");
if(ofp_gpio38_value == NULL) {printf("Unable to open gpio38_value.\n");}
fseek(ofp_gpio38_value, 0, SEEK_SET);
fprintf(ofp_gpio38_value, "%d", logic_status_38);
fflush(ofp_gpio38_value);

while(1)
  {
  //configure gpio34 value and read the gpio34 pin  
  ifp_gpio34_value = fopen("/sys/class/gpio/gpio34/value", "r");
  if(ifp_gpio34_value == NULL) {printf("Unable to open gpio34_value.\n");}
  fseek(ifp_gpio34_value, 0, SEEK_SET);
  fscanf(ifp_gpio34_value, "%d", &logic_status_34);
  fclose(ifp_gpio34_value);
  printf("%d", logic_status_34);
  if(logic_status_34 == 1) 
    {	   
    //set gpio38 logic high
    fseek(ofp_gpio38_value, 0, SEEK_SET);
    logic_status_38 = 1;
    fprintf(ofp_gpio38_value, "%d", logic_status_38);
    fflush(ofp_gpio38_value);
    printf("High\n");
    }
  else
    {	   
    //set gpio38 logic low
    fseek(ofp_gpio38_value, 0, SEEK_SET);
    logic_status_38 = 0;
    fprintf(ofp_gpio38_value, "%d", logic_status_38);
    fflush(ofp_gpio38_value);
    printf("Low\n");
    }
  }

//close files
fclose(ofp_gpmc_ad6);
fclose(ofp_export_38);
fclose(ofp_gpio38_direction);
fclose(ofp_gpio38_value);

fclose(ofp_gpmc_ad2);
fclose(ofp_export_34);
fclose(ofp_gpio34_direction);
fclose(ifp_gpio34_value);

return 1;
}
//*********************************************************************

