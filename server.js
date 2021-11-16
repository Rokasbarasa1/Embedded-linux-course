var http = require('http');
var fs = require('fs');
var path = require('path');
const execFile = require('child_process').execFile;

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

io.on('connection', function (socket) {
    socket.on('refreshData', (data) => handleRefreshData(socket, data));
    socket.on('changeStateLight', (data) => handleChangeStateLight(socket, data));
    socket.on('changeWindowState', (data) => handleChangeWindowState(socket, data));
    socket.on('changeHeaterState', (data) => handleChangeHeaterState(socket, data));
});

async function handleRefreshData(socket, data) {
    var temperature = "NaN"
    var humidity = "NaN"
    var light = "NaN"
    var window = "NaN"
    var heater = "NaN"
    
    // Read humidity/temperature
	await execFile('./test', ['readTempAndHumidity'], (error, stdout, stderr) => {
        if(error) { throw error;}

        temperature = stdout[5];
        humidity = stdout[5];

        console.log("\""+stdout+"\"");
    });

    //Read light
    await execFile('./test', ['readLightLevel'], (error, stdout, stderr) => {
        if(error) { throw error;}

        light = stdout[5];

        console.log("\""+stdout+"\"");
    });

    //Read window
    await execFile('./test', ['readWindow'], (error, stdout, stderr) => {
        if(error) { throw error;}

        window = stdout[5];

        console.log("\""+stdout+"\"");
    });
    
    //Read heater
    await execFile('./test', ['readHeater'], (error, stdout, stderr) => {
        if(error) { throw error;}

        heater = stdout[5];
        
        console.log("\""+stdout+"\"");
    });

    socket.emit("responseRefresh", 
        {
            temperature: temperature,
            humidity: humidity,
            light: light,
            window: window,
            heater: heater,
        }
    );
}

async function handleChangeStateLight(socket, data) {
    var newData = JSON.parse(data);
    await execFile('./test', ['setLightLevel', newData.state], (error, stdout, stderr) => {
        if(error) { throw error;}
        execFile('./test', ['readLightLevel'], (error, stdout, stderr) => {
            if(error) { throw error;}

            socket.emit("responseSetLight", 
                {
                    light: newData.state
                }
            );
        });
        
    });
}

async function handleChangeWindowState(socket, data) {
    var newData = JSON.parse(data);
    var command;
    if(newData.state == 1){
        command = "open"
    }else{
        command = "close"
    }
    execFile('./test', ['setWindowStatus', command], (error, stdout, stderr) => {
        if(error) { throw error;}
        execFile('./test', ['readWindow'], (error, stdout, stderr) => {
            if(error) { throw error;}

            socket.emit("responseSetWindow", 
                {
                    window: command
                }
            );
        });
    });
}

async function handleChangeHeaterState(socket, data) {
    var newData = JSON.parse(data);
    if(newData.state == 1){
        command = "on"
    }else{
        command = "off"
    }
    await execFile('./test', ['setHeaterStatus', command], (error, stdout, stderr) => {
        if(error) { throw error;}
        execFile('./test', ['readHeater', command], (error, stdout, stderr) => {
            if(error) { throw error;}

            socket.emit("responseSetHeater", 
                {
                    heater: command
                }
            );
        });
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