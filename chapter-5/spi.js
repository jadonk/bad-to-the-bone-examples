//*********************************************************

var b = require('bonescript');

//Old bonescript defines 'bone' globally
var pins = (typeof bone != 'undefined') ? bone : b.bone.pins;

var spi_data_pin = pins.P8_13;
var spi_clk_pin = pins.P8_11;

b.pinMode(spi_data_pin, b.OUTPUT);
b.pinMode(spi_clk_pin, b.OUTPUT);
b.shiftOut(spi_data_pin, spi_clk_pin, b.LSBFIRST, 0xAC);

//*********************************************************

