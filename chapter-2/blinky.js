//***********************************************************************

var b = require('bonescript');

//Old bonescript defines 'bone' globally
var pins = (typeof bone != 'undefined') ? bone : b.bone.pins;

var left_IR_sensor = pins.P9_39;        //analog input for left IR sensor
var center_IR_sensor = pins.P9_40;      //analog input for center IR sensor
var right_IR_sensor = pins.P9_37;       //analog input for right IR sensor

var left_motor_pin = pins.P9_14;        //PWM pin for left motor
var right_motor_pin = pins.P9_16;       //PWM pin for right motor

var left_sensor_value;
var center_sensor_value;
var right_sensor_value;

b.pinMode(left_motor_pin, b.OUTPUT); //left motor pin
b.pinMode(right_motor_pin, b.OUTPUT);//right motor pin

while(1)
  {
                                   //read analog output from IR sensors
                                   //normalized value ranges from 0..1
  left_sensor_value   = b.analogRead(left_IR_sensor);
  center_sensor_value = b.analogRead(center_IR_sensor); 
  right_sensor_value  = b.analogRead(right_IR_sensor); 
  
                                   //assumes desired threshold at 
                                   //1.25 VDC with max value of 1.75 VDC
   if((left_sensor_value > 0.714)&&
      (center_sensor_value <= 0.714)&& 
      (right_sensor_value > 0.714))       
     {                             //robot continues straight ahead
     b.analogWrite(left_motor_pin, 0.7);
     b.analogWrite(right_motor_pin, 0.7);
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

