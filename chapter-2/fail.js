//******************************************************************
// next.js - A pattern for calling sequential functions in node.js
//******************************************************************

mysteps(done);

//******************************************************************
//done
//******************************************************************

function done() {
  console.log("done");
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
function(){ console.log("i = " + i); setTimeout(next, 1000); }, //delay 1s
function(){ callback(); }
];

//Start at 0
var i = 0;

process.on('SIGINT', next);
console.log("i = " + i);
next(); //Call the first function

//Nested helper function to call the next function in 'steps'
function next()
  {
  i++
  steps[i-1]();
  }
}

//******************************************************************
