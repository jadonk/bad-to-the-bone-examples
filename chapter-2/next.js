//******************************************************************
// next.js - A pattern for calling sequential functions in node.js
//******************************************************************

catch_events();
mysteps(done);
console.log("other tasks can continue");

//******************************************************************
//done
//******************************************************************

function done() {
  console.log("done");
}

//******************************************************************
//catch_events
//******************************************************************

function catch_events()
{
process.on('SIGINT', got_interrupt); //Capture ^C key presses
function got_interrupt()
  {
  console.log('got interrupt');
  }
}

//******************************************************************
//mysteps
//******************************************************************

function mysteps(callback)
{
//Provide a list of functions to call
var steps =
[
function(){ console.log("i = " + i); setTimeout(next, 1000); }, //delay 1s
function(){ console.log("i = " + i); setTimeout(next, 1000); }, //delay 1s
function(){ console.log("i = " + i); setTimeout(next, 1000); }, //delay 1s
function(){ console.log("i = " + i); setTimeout(next, 1000); }, //delay 1s
function(){ console.log("i = " + i); setTimeout(next, 1000); }, //delay 1s
function(){ callback(); }
];

//Start at 0
var i = 0;

next(); //Call the first function

//Nested helper function to call the next function in 'steps'
function next()
  {
  i++;
  steps[i-1]();
  }
}

//******************************************************************
