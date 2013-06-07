//**************************************************************
//adc1.cpp: the analog value on AIN0 (P9, pin 39) provided by 
//a LM34 temperature sensor is read continuously until 
//[Control][C] is used to stop the program.
//
//Before the AIN values show up, you must perform:
//  echo cape-bone-iio > /sys/devices/bone_capemgr.*/slots
//
//Notes:
// * The ".11" after helper can change between software revs
// * The scale of values is now 0-1800 (mV) instead of 0-4095
// * The AINx indexes now match the hardware documentation
//   instead of being off by 1
//**************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//define file handles
FILE *ifp_ain0;
float ain0_value;

ifp_ain0 = fopen("/sys/module/bone_iio_helper/drivers/platform:bone-iio-helper/helper.11/AIN0", "r");
if (ifp_ain0 == NULL) {printf("Unable to AIN0.\n");}

while(1)
  {
  fseek(ifp_ain0, 0, SEEK_SET);
  fscanf(ifp_ain0, "%f", &ain0_value);
  printf("%f\n", ain0_value); 
  }

fclose(ifp_ain0);
return 1;
}	
//**************************************************************

