//**********************************************************************
#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//define file handles
FILE *ofp_gpmc_a2, *pwm_freq, *pwm_req, *pwm_duty, *pwm_polarity, *pwm_run;

//define pin variables
int mux_mode = 0x006, request = 1, freq = 100, duty = 50, polarity = 1, run =1;

ofp_gpmc_a2 = fopen("/sys/kernel/debug/omap_mux/gpmc_a2", "w");
if(ofp_gpmc_a2 == NULL) {printf("Unable to open gpmc_a2.\n");}
fseek(ofp_gpmc_a2, 0, SEEK_SET);
fprintf(ofp_gpmc_a2, "0x%02x", mux_mode);
fflush(ofp_gpmc_a2);

pwm_req = fopen("/sys/class/pwm/ehrpwm.1:0/request", "w");
if(pwm_req == NULL) {printf("Unable to open pwm request.\n");}
fseek(pwm_req, 0, SEEK_SET);
fprintf(pwm_req, "%d", request);
fflush(pwm_req);

pwm_freq = fopen("/sys/class/pwm/ehrpwm.1:0/period_freq", "w");
if(pwm_freq == NULL) {printf("Unable to open pwm frequency.\n");}
fseek(pwm_freq, 0, SEEK_SET);
fprintf(pwm_freq, "%d", freq);
fflush(pwm_freq);

pwm_duty = fopen("/sys/class/pwm/ehrpwm.1:0/duty_percent", "w");
if(pwm_duty == NULL) {printf("Unable to open pwm duty cycle.\n");}
fseek(pwm_duty, 0, SEEK_SET);
fprintf(pwm_duty, "%d", duty);
fflush(pwm_duty);

pwm_polarity = fopen("/sys/class/pwm/ehrpwm.1:0/polarity", "w");
if(pwm_polarity == NULL) {printf("Unable to open pwm polarity.\n");}
fseek(pwm_polarity, 0, SEEK_SET);
fprintf(pwm_polarity, "%d", polarity);
fflush(pwm_polarity);

pwm_run = fopen("/sys/class/pwm/ehrpwm.1:0/run", "w");
if(pwm_run == NULL) {printf("Unable to open pwm run.\n");}
fseek(pwm_run, 0, SEEK_SET);
fprintf(pwm_run, "%d", run);
fflush(pwm_run);

while(1)
  {

  }

fclose(ofp_gpmc_a2);
fclose(pwm_req);
fclose(pwm_freq);
fclose(pwm_duty);
fclose(pwm_polarity);
fclose(pwm_run);

return 1;
}	
//**********************************************************************

