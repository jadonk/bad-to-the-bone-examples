//*******************************************************************
//dagu.cpp
//
//Before the right interfaces show up, you must have performed:
//  echo cape-bone-iio > /sys/devices/bone_capemgr.*/slots
//  echo am335x_pwm > /sys/devices/bone_capemgr.*/slots
//  echo bone_pwm_P9_14 > /sys/devices/bone_capemgr.*/slots
//  echo bone_pwm_P9_16 > /sys/devices/bone_capemgr.*/slots
//
//Note:
// * The .11 in helper.11 is likely to change
// * The .12 and .15 in the PWM entries are likely to change
// * The .2 in ocp might change
//*******************************************************************
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//wall detection threshold
double threshold = 1100.0;               //experimentally determined       

//configure adc channels
//define file handles for adc related files
FILE *ifp_ain0, *ifp_ain1, *ifp_ain2;
float ain0_value, ain1_value, ain2_value;

//open adc related files for access to ain0, 1 and 2
ifp_ain0 = fopen("/sys/module/bone_iio_helper/drivers/platform:bone-iio-helper/helper.11/AIN0", "r");
if (ifp_ain0 == NULL) {printf("Unable to ain0.\n");}

ifp_ain1 = fopen("/sys/module/bone_iio_helper/drivers/platform:bone-iio-helper/helper.11/AIN1", "r");
if (ifp_ain1 == NULL) {printf("Unable to ain1.\n");}

ifp_ain2 = fopen("/sys/module/bone_iio_helper/drivers/platform:bone-iio-helper/helper.11/AIN2", "r");
if (ifp_ain2 == NULL) {printf("Unable to ain2.\n");}

//configure pwm channels 0 and 1
//define file handles for channel 0 – EHRPWM1A (P9, pin 14)
//designated as ehrpwm.1:0
FILE *pwm_period0, *pwm_duty0;
FILE *pwm_polarity0, *pwm_run0;

//define pin variables for channel 0 
int period0 = 500000, duty0 = 250000;
int polarity0 = 1, run0 = 1;

pwm_period0 = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/period", "w");
if(pwm_period0 == NULL) {printf("Unable to open pwm 0 period.\n");}
fseek(pwm_period0, 0, SEEK_SET);
fprintf(pwm_period0, "%d", period0);
fflush(pwm_period0);

pwm_duty0 = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/duty", "w");
if(pwm_duty0 == NULL) {printf("Unable to open pwm 0 duty cycle.\n");}
fseek(pwm_duty0, 0, SEEK_SET);
fprintf(pwm_duty0, "%d", duty0);
fflush(pwm_duty0);

pwm_polarity0 = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/polarity", "w");
if(pwm_polarity0 == NULL) {printf("Unable to open pwm 0 polarity.\n");}
fseek(pwm_polarity0, 0, SEEK_SET);
fprintf(pwm_polarity0, "%d", polarity0);
fflush(pwm_polarity0);

pwm_run0 = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/run", "w");
if(pwm_run0 == NULL) {printf("Unable to open pwm 0 run.\n");}

//define file handles for channel 1 – EHRPWM1B (P9, pin 16)
//designated as ehrpwm.1:1
FILE *pwm_period1, *pwm_duty1;
FILE *pwm_polarity1, *pwm_run1;

//define pin variables for channel 1
int period1 = 500000, duty1 = 250000;
int polarity1 = 1, run1 = 1;

pwm_period1 = fopen("/sys/devices/ocp.2/pwm_test_P9_16.15/period", "w");
if(pwm_period1 == NULL) {printf("Unable to open pwm 1 period.\n");}
fseek(pwm_period1, 0, SEEK_SET);
fprintf(pwm_period1, "%d", period1);
fflush(pwm_period1);

pwm_duty1 = fopen("/sys/devices/ocp.2/pwm_test_P9_16.15/duty", "w");
if(pwm_duty1 == NULL) {printf("Unable to open pwm 1 duty cycle.\n");}
fseek(pwm_duty1, 0, SEEK_SET);
fprintf(pwm_duty1, "%d", duty1);
fflush(pwm_duty1);

pwm_polarity1 = fopen("/sys/devices/ocp.2/pwm_test_P9_16.15/polarity", "w");
if(pwm_polarity1 == NULL) {printf("Unable to open pwm 1 polarity.\n");}
fseek(pwm_polarity1, 0, SEEK_SET);
fprintf(pwm_polarity1, "%d", polarity1);
fflush(pwm_polarity1);

pwm_run1 = fopen("/sys/devices/ocp.2/pwm_test_P9_16.15/run", "w");
if(pwm_run1 == NULL) {printf("Unable to open pwm 1 run.\n");}


while(1)
  {
  //read analog sensors
  fseek(ifp_ain0, 0, SEEK_SET);
  fscanf(ifp_ain0, "%f", &ain0_value);
  printf("%f\n", ain0_value); 

  fseek(ifp_ain1, 0, SEEK_SET);
  fscanf(ifp_ain1, "%f", &ain1_value);
  printf("%f\n", ain1_value); 

  fseek(ifp_ain2, 0, SEEK_SET);
  fscanf(ifp_ain2, "%f", &ain2_value);
  printf("%f\n", ain2_value); 

  //implement truth to determine robot turns

  //no walls present – continue straight ahead
  if((ain0_value < threshold)&&(ain1_value < threshold)&&
     (ain2_value < threshold))
    {
    run0 = 1;  run1 = 1;        //both motors on  
    fseek(pwm_run0, 0, SEEK_SET);
    fprintf(pwm_run0, "%d", run0);
    fflush(pwm_run0);

    fseek(pwm_run1, 0, SEEK_SET);
    fprintf(pwm_run1, "%d", run1);
    fflush(pwm_run1);
    }
/*
  else if(...)
    {
 
    :
    insert other cases
    :
    }
*/
  }

fclose(ifp_ain0);
fclose(ifp_ain1);
fclose(ifp_ain2);

fclose(pwm_period0);
fclose(pwm_duty0);
fclose(pwm_polarity0);
fclose(pwm_run0);

fclose(pwm_period1);
fclose(pwm_duty1);
fclose(pwm_polarity1);
fclose(pwm_run1);

return 1;
}	
//*******************************************************************

