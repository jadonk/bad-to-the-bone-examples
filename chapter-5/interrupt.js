//*************************************************************
var b = require('bonescript');

//Old bonescript defines 'bone' globally
var pins = (typeof bone != 'undefined') ? bone : b.bone.pins;

var greenLED = pins.P8_13;
var redLED = pins.P9_14;
var inputSW = pins.P8_15;
var main_delay = 100;
var inter_delay = 50;
var state = b.LOW;

b.pinMode(greenLED, b.OUTPUT);
b.pinMode(redLED, b.OUTPUT);
b.pinMode(inputSW, b.INPUT);
b.attachInterrupt(inputSW, blink_red, b.RISING);

function loop() 
    {
    state = (state == b.HIGH) ? b.LOW : b.HIGH;
    b.digitalWrite(greenLED, state);
    setTimeout(loop, main_delay);
    }

function blink_red()
{
b.digitalWrite(redLED, b.HIGH);
setTimeout(blink_red2, inter_delay);
}

function blink_red2()
{
b.digitalWrite(redLED, b.LOW);
setTimeout(blink_red3, inter_delay);
}

function blink_red3()
{
b.digitalWrite(redLED, b.HIGH);
setTimeout(blink_red4, inter_delay);
}

function blink_red4()
{
b.digitalWrite(redLED, b.LOW);
}    
//*******************************************************    

