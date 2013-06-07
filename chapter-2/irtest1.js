//***********************************************************************

var b=require('bonescript');

//Old bonescript defines 'bone' globally
var pins = (typeof bone != 'undefined') ? bone : b.bone.pins;

var ledPin = pins.P8_13;                 //digital pin for LED interface
var ainPin = pins.P9_39;                 //analog input pin for IR sensor
var IR_sensor_value;

b.pinMode(ledPin, b.OUTPUT);          //set pin to digital output

while(1)
  {
                                   //read analog output from IR sensor
                                   //normalized value ranges from 0..1
   IR_sensor_value = b.analogRead(ainPin); 
                                   //assumes desired threshold at 
                                   //1.25 VDC with max value of 1.75 VDC
   if(IR_sensor_value > 0.714)       
     {
     b.digitalWrite(ledPin, b.HIGH);  //turn LED on
     }
   else
     {
     b.digitalWrite(ledPin, b.LOW);   //turn LED off
     } 
  }

//***********************************************************************

