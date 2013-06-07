//******************************************************************
// almanzas.js
//******************************************************************

var counter = 1;
var driveup = 1;

setTimeout(counterOrder, 1000);//Counter customer at second 1
setTimeout(counterOrder, 2000);//Counter customer at second 2
setTimeout(driveupOrder, 3000);//Driveup customer at second 3
setTimeout(counterOrder, 4000);//Counter customer at second 4
setTimeout(counterOrder, 5000);//Counter customer at second 5
setTimeout(driveupOrder, 6000);//Driveup customer at second 6
setTimeout(driveupOrder, 7000);//Driveup customer at second 7
setTimeout(counterOrder, 8000);//Counter customer at second 8

//******************************************************************
//server(task)
//
//The server takes the orders from the customers and gives them
//to the kitchen, as well as delivering orders from the kitchen
//******************************************************************

function server(customer)
{
    console.log("Take order " + customer);
    kitchen(deliver);

    function deliver()
    {
        console.log("Deliver " + customer + " food order");
    }
}

//******************************************************************
//kitchen(callback)
//
//The kitchen takes tasks and completes them at a random time
//between 1 and 5 seconds
//******************************************************************

function kitchen(callback)
{
    var delay = 1000 + Math.round(Math.random() * 4000);
    setTimeout(callback, delay);
}

//******************************************************************
//counterOrder()
//
//Give order to server
//******************************************************************

function counterOrder()
{
    server("C" + counter);
    counter++;
}

//******************************************************************
//driveupOrder()
//
//Give order to server
//******************************************************************

function driveupOrder()
{
    server("A" + driveup);
    driveup++;
}

