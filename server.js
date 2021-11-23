/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */
var http = require('http');
var fs = require('fs');
var path = require('path');
const exec = require('child_process').execSync; 
const execFile = require('child_process').execFile;

/// SET DEFAULT STATE 
//Set light to default 0
execFile('./greenhouse', ['setLedLight', '0'], (error, stdout, stderr) => {
    if(error) { throw error;}
});

//Set window to default closed
execFile('./greenhouse', ['setWindowStatus', 'close'], (error, stdout, stderr) => {
    if(error) { throw error;}
});

//Set window to default closed
execFile('./greenhouse', ['setHeaterStatus', 'off'], (error, stdout, stderr) => {
    if(error) { throw error;}
});



//Create server and start to listen
var server = http.createServer(function (req, res) {
    var file = '.'+((req.url=='/')?'/index.html':req.url);
    var fileExtension = path.extname(file);
    var contentType = 'text/html';

    fs.exists(file, function(exists){
        if(exists){
            fs.readFile(file, function(error, content){
                if(!error){
                    // Page found, write content
                    res.writeHead(200,{'content-type':contentType});
                    res.end(content);
                }
            });
        }else{
            // Page not found
            res.writeHead(404);
            res.end('Page not found');
        }
    });
}).listen(8888);

var io = require('socket.io')(server);

// Recieve client requests
io.on('connection', function (socket) {
    // Pass the socket and the data that was sent to the function.
    socket.on('refreshData', (data) => handleRefreshData(socket, data));
    socket.on('changeStateLight', (data) => handleChangeStateLight(socket, data));
    socket.on('changeWindowState', (data) => handleChangeWindowState(socket, data));
    socket.on('changeHeaterState', (data) => handleChangeHeaterState(socket, data));
});

// Read all current values form the peripherals and return it to the client that is connected to socket
async function handleRefreshData(socket, data) {
    var temperature = "NaN"
    var humidity = "NaN"
    var light = "NaN"
    var window = "NaN"
    var heater = "NaN"
    var ledLight = "NaN"


    // Read humidity/temperature
    var result = exec('./greenhouse readTempAndHumidity');
    strings = result.toString("utf8").split('\n');
    temperature = strings[0].substring(13, 17);
    humidity = strings[1].substring(13, 17);

    // Perform synchronus calls to the peripheral, get result then parse it

    //Read light
    var result = exec('./greenhouse readLightLevel');
    light = result.toString("utf8").substring(13, 18);

    //Read window
    var result = exec('./greenhouse readWindow');
    window = result.toString("utf8").substring(13, 19);

    //Read heater
    var result = exec('./greenhouse readHeater');
    heater = result.toString("utf8").substring(13, 16);

    //Read led light
    var result = exec('./greenhouse readLedLight');
    ledLight = result.toString("utf8").substring(13, 19);
  
    // Compile every result into specific json dictionary and send it to user
    socket.emit("responseRefresh", 
        {
            temperature: temperature,
            humidity: humidity,
            light: light,
            window: window,
            heater: heater,
            ledLight: ledLight
        }
    );
}

// Handle user changing led light state
async function handleChangeStateLight(socket, data) {
    // Parse the json data into a dictionary
    var newData = JSON.parse(data);

    // Asynchronously change the state of the led light by passing what functionality to perform
    // and parameter to set
    execFile('./greenhouse', ['setLedLight', newData.state], (error, stdout, stderr) => {
        if(error) { throw error;}
        
        // After each modify peripheral call make call to read the current state and return that to the client.

        // Read led light
        var result = exec('./greenhouse readLedLight');
        var ledLight = result.toString("utf8").substring(13, 19);
        
        socket.emit("responseSetLight", 
            {
                ledLight: ledLight
            }
        );
    });
}

// Same as "handleChangeStateLight" just different peripheral called
async function handleChangeWindowState(socket, data) {
    var newData = JSON.parse(data);
    var command;
    if(newData.state == 1){
        command = "open"
    }else{
        command = "close"
    }
    execFile('./greenhouse', ['setWindowStatus', command], (error, stdout, stderr) => {
        if(error) { throw error;}

        //Read window
        var result = exec('./greenhouse readWindow');
        var window = result.toString("utf8").substring(13, 19);

        socket.emit("responseSetWindow", 
            {
                window: window
            }
        );
    });
}

// Same as "handleChangeStateLight" just different peripheral called
async function handleChangeHeaterState(socket, data) {
    var newData = JSON.parse(data);
    if(newData.state == 1){
        command = "on"
    }else{
        command = "off"
    }
    execFile('./greenhouse', ['setHeaterStatus', command], (error, stdout, stderr) => {
        if(error) { throw error;}

        //Read heater
        var result = exec('./greenhouse readHeater');
        var heater = result.toString("utf8").substring(13, 16);
        socket.emit("responseSetHeater", 
            {
                heater: heater
            }
        );
    });
}

console.log("Server Running ...");


//Requirements 
// See temp
// See humidity
// See ligh intensity
// See window open or closed
// See heater status
// Set light intensity level
// Set window open or closed
// Set heater status