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
double threshold = 2500.0;               //experimentally determined       

//configure adc channels
//define file handles for adc related files
FILE *ifp_ain1, *ifp_ain2, *ifp_ain3;
float ain0_value, ain1_value, ain2_value;

//open adc related files for access to ain0, 1 and 2
ifp_ain1 = fopen("/sys/bus/platform/devices/tsc/ain1", "r");
if (ifp_ain1 == NULL) {printf("Unable to ain1.\n");}

ifp_ain2 = fopen("/sys/bus/platform/devices/tsc/ain2", "r");
if (ifp_ain2 == NULL) {printf("Unable to ain2.\n");}

ifp_ain3 = fopen("/sys/bus/platform/devices/tsc/ain3", "r");
if (ifp_ain3 == NULL) {printf("Unable to ain3.\n");}

//configure pwm channels 0 and 1
//define file handles for channel 0 – EHRPWM1A (P9, pin 14)
//designated as ehrpwm.1:0
FILE *ofp_gpmc_a2, *pwm_freq0, *pwm_req0, *pwm_duty0;
FILE *pwm_polarity0, *pwm_run0;

//define pin variables for channel 0 
int mux_mode0 = 0x006, request0 = 1, freq0 = 100, duty0 = 50;
int polarity0 = 1, run0 = 1;

ofp_gpmc_a2 = fopen("/sys/kernel/debug/omap_mux/gpmc_a2", "w");
if(ofp_gpmc_a2 == NULL) {printf("Unable to open gpmc_a2.\n");}
fseek(ofp_gpmc_a2, 0, SEEK_SET);
fprintf(ofp_gpmc_a2, "0x%02x", mux_mode0);
fflush(ofp_gpmc_a2);

pwm_req0 = fopen("/sys/class/pwm/ehrpwm.1:0/request", "w");
if(pwm_req0 == NULL) {printf("Unable to open pwm 0 request.\n");}
fseek(pwm_req0, 0, SEEK_SET);
fprintf(pwm_req0, "%d", request0);
fflush(pwm_req0);

pwm_freq0 = fopen("/sys/class/pwm/ehrpwm.1:0/period_freq", "w");
if(pwm_freq0 == NULL) {printf("Unable to open pwm 0 frequency.\n");}
fseek(pwm_freq0, 0, SEEK_SET);
fprintf(pwm_freq0, "%d", freq0);
fflush(pwm_freq0);

pwm_duty0 = fopen("/sys/class/pwm/ehrpwm.1:0/duty_percent", "w");
if(pwm_duty0 == NULL) {printf("Unable to open pwm 0 duty cycle.\n");}
fseek(pwm_duty0, 0, SEEK_SET);
fprintf(pwm_duty0, "%d", duty0);
fflush(pwm_duty0);

pwm_polarity0 = fopen("/sys/class/pwm/ehrpwm.1:0/polarity", "w");
if(pwm_polarity0 == NULL) {printf("Unable to open pwm 0 polarity.\n");}
fseek(pwm_polarity0, 0, SEEK_SET);
fprintf(pwm_polarity0, "%d", polarity0);
fflush(pwm_polarity0);

pwm_run0 = fopen("/sys/class/pwm/ehrpwm.1:0/run", "w");
if(pwm_run0 == NULL) {printf("Unable to open pwm 0 run.\n");}

//define file handles for channel 1 – EHRPWM1B (P9, pin 16)
//designated as ehrpwm.1:1
FILE *ofp_gpmc_a3, *pwm_freq1, *pwm_req1, *pwm_duty1;
FILE *pwm_polarity1, *pwm_run1;

//define pin variables for channel 1
int mux_mode1 = 0x006, request1 = 1, freq1 = 100, duty1 = 50;
int polarity1 = 1, run1 = 1;

ofp_gpmc_a3 = fopen("/sys/kernel/debug/omap_mux/gpmc_a3", "w");
if(ofp_gpmc_a3 == NULL) {printf("Unable to open gpmc_a3.\n");}
fseek(ofp_gpmc_a3, 0, SEEK_SET);
fprintf(ofp_gpmc_a3, "0x%02x", mux_mode1);
fflush(ofp_gpmc_a3);

pwm_req1 = fopen("/sys/class/pwm/ehrpwm.1:1/request", "w");
if(pwm_req1 == NULL) {printf("Unable to open pwm 1 request.\n");}
fseek(pwm_req1, 0, SEEK_SET);
fprintf(pwm_req1, "%d", request1);
fflush(pwm_req1);

pwm_freq1 = fopen("/sys/class/pwm/ehrpwm.1:1/period_freq", "w");
if(pwm_freq1 == NULL) {printf("Unable to open pwm 1 frequency.\n");}
fseek(pwm_freq1, 0, SEEK_SET);
fprintf(pwm_freq1, "%d", freq1);
fflush(pwm_freq1);

pwm_duty1 = fopen("/sys/class/pwm/ehrpwm.1:1/duty_percent", "w");
if(pwm_duty1 == NULL) {printf("Unable to open pwm 1 duty cycle.\n");}
fseek(pwm_duty1, 0, SEEK_SET);
fprintf(pwm_duty1, "%d", duty1);
fflush(pwm_duty1);

pwm_polarity1 = fopen("/sys/class/pwm/ehrpwm.1:1/polarity", "w");
if(pwm_polarity1 == NULL) {printf("Unable to open pwm 1 polarity.\n");}
fseek(pwm_polarity1, 0, SEEK_SET);
fprintf(pwm_polarity1, "%d", polarity1);
fflush(pwm_polarity1);

pwm_run1 = fopen("/sys/class/pwm/ehrpwm.1:1/run", "w");
if(pwm_run1 == NULL) {printf("Unable to open pwm 1 run.\n");}


while(1)
  {
  //read analog sensors
  fseek(ifp_ain1, 0, SEEK_SET);
  fscanf(ifp_ain1, "%f", &ain0_value);
  printf("%f\n", ain0_value); 

  fseek(ifp_ain2, 0, SEEK_SET);
  fscanf(ifp_ain2, "%f", &ain1_value);
  printf("%f\n", ain1_value); 

  fseek(ifp_ain3, 0, SEEK_SET);
  fscanf(ifp_ain3, "%f", &ain2_value);
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

fclose(ifp_ain1);
fclose(ifp_ain2);
fclose(ifp_ain3);

fclose(ofp_gpmc_a2);
fclose(pwm_req0);
fclose(pwm_freq0);
fclose(pwm_duty0);
fclose(pwm_polarity0);
fclose(pwm_run0);

fclose(ofp_gpmc_a3);
fclose(pwm_req1);
fclose(pwm_freq1);
fclose(pwm_duty1);
fclose(pwm_polarity1);
fclose(pwm_run1);

return 1;
}	
//*******************************************************************

