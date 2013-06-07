//*********************************************************************
//led2.cpp: This program reads the logic value of a pushbutton switch
//connected to expansion header P8, pin 7 (GPIO2_2 designated as gpio66).
//If the switch is logic high (1) an LED connected to expansion header
//P8, pin13 (GPIO1_12 designated as gpio44) is illuminated.
//*********************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//define file handles for gpio44 (P8, pin 13, GPIO1_12)
FILE *ofp_export_44, *ofp_gpio44_value, *ofp_gpio44_direction;

//define file handles for gpio66 (P8, pin 7, GPIO2_2)
FILE *ofp_export_66, *ifp_gpio66_value, *ofp_gpio66_direction;

//define pin variables for gpio44
int pin_number_44 = 44, logic_status_44 = 1;
char* pin_direction_44 = output;

//define pin variables for gpio66
int pin_number_66 = 66, logic_status_66;
char* pin_direction_66 = input;

//create direction and value file for gpio44
ofp_export_44 = fopen("/sys/class/gpio/export", "w");
if(ofp_export_44 == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export_44, 0, SEEK_SET);
fprintf(ofp_export_44, "%d", pin_number_44);
fflush(ofp_export_44);

//create direction and value file for gpio66
ofp_export_66 = fopen("/sys/class/gpio/export", "w");
if(ofp_export_66 == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export_66, 0, SEEK_SET);
fprintf(ofp_export_66, "%d", pin_number_66);
fflush(ofp_export_66);

//configure gpio44 direction
ofp_gpio44_direction = fopen("/sys/class/gpio/gpio44/direction", "w");
if(ofp_gpio44_direction == NULL) {printf("Unable to open gpio44_direction.\n");}
fseek(ofp_gpio44_direction, 0, SEEK_SET);
fprintf(ofp_gpio44_direction, "%s",  pin_direction_44);
fflush(ofp_gpio44_direction);

//configure gpio66 direction
ofp_gpio66_direction = fopen("/sys/class/gpio/gpio66/direction", "w");
if(ofp_gpio66_direction == NULL) {printf("Unable to open gpio66_direction.\n");}
fseek(ofp_gpio66_direction, 0, SEEK_SET);
fprintf(ofp_gpio66_direction, "%s",  pin_direction_66);
fflush(ofp_gpio66_direction);

//configure gpio44 value \--- initially set logic high
ofp_gpio44_value = fopen("/sys/class/gpio/gpio44/value", "w");
if(ofp_gpio44_value == NULL) {printf("Unable to open gpio44_value.\n");}
fseek(ofp_gpio44_value, 0, SEEK_SET);
fprintf(ofp_gpio44_value, "%d", logic_status_44);
fflush(ofp_gpio44_value);

while(1)
  {
  //configure gpio66 value and read the gpio66 pin  
  ifp_gpio66_value = fopen("/sys/class/gpio/gpio66/value", "r");
  if(ifp_gpio66_value == NULL) {printf("Unable to open gpio66_value.\n");}
  fseek(ifp_gpio66_value, 0, SEEK_SET);
  fscanf(ifp_gpio66_value, "%d", &logic_status_66);
  fclose(ifp_gpio66_value);
  printf("%d", logic_status_66);
  if(logic_status_66 == 1) 
    {	   
    //set gpio44 logic high
    fseek(ofp_gpio44_value, 0, SEEK_SET);
    logic_status_44 = 1;
    fprintf(ofp_gpio44_value, "%d", logic_status_44);
    fflush(ofp_gpio44_value);
    printf("High\n");
    }
  else
    {	   
    //set gpio44 logic low
    fseek(ofp_gpio44_value, 0, SEEK_SET);
    logic_status_44 = 0;
    fprintf(ofp_gpio44_value, "%d", logic_status_44);
    fflush(ofp_gpio44_value);
    printf("Low\n");
    }
  }

//close files
fclose(ofp_export_44);
fclose(ofp_gpio44_direction);
fclose(ofp_gpio44_value);

fclose(ofp_export_66);
fclose(ofp_gpio66_direction);
fclose(ifp_gpio66_value);

return 1;
}
//*********************************************************************

