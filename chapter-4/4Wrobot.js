//***********************************************************************
var b = require('bonescript');


//Old bonescript defines 'bone' globally
var pins = (typeof bone != 'undefined') ? bone : b.bone.pins;

var left_IR_sensor   = pins.P9_39;      //analog input for left IR sensor
var center_IR_sensor = pins.P9_40;      //analog input for center IR sensor
var right_IR_sensor  = pins.P9_37;      //analog input for right IR sensor

var IMU_xout = pins.P9_35;              //IMU xout analog signal
var IMU_yout = pins.P9_36;              //IMU yout analog signal

var left_motor_pin = pins.P9_14;        //PWM pin for left motor
var right_motor_pin = pins.P9_16;       //PWM pin for right motor
var left_motor_for_rev = pins.P9_13;    //left motor forward/reverse
var right_motor_for_rev= pins.P9_15;    //right motor forward/reverse

var left_sensor_value;
var center_sensor_value;
var right_sensor_value;
  

b.pinMode(left_motor_pin, b.OUTPUT);        //set pin to digital output
b.pinMode(right_motor_pin, b.OUTPUT);       //set pin to digital output
b.pinMode(left_motor_for_rev, b.OUTPUT);    //set pin to digital output
b.pinMode(right_motor_for_rev, b.OUTPUT);   //set pin to digital output

while(1)
  {
                                   //read analog output from IR sensors
                                   //normalized value ranges from 0..1
  left_sensor_value = b.analogRead(left_IR_sensor);
  center_sensor_value = b.analogRead(center_IR_sensor); 
  right_sensor_value = b.analogRead(right_IR_sensor); 
  
                                   //assumes desired threshold at 
                                   //1.25 VDC with max value of 1.75 VDC
   if((left_sensor_value > 0.714)&&
      (center_sensor_value <= 0.714)&& 
      (right_sensor_value > 0.714))       
     {                                           //robot straight ahead
     b.digitalWrite(left_motor_for_rev, b.HIGH); //left motor forward
     b.analogWrite(left_motor_pin, 0.7);         //left motor RPM
     b.digitalWrite(right_motor_for_rev, b.HIGH);//right motor forward
     b.analogWrite(right_motor_pin, 0.7);        //right motor RPM
     }
/*
   else if(...)
     {
     :
     :
     :
     } 
*/
  }

//***********************************************************************

