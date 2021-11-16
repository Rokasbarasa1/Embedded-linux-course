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
    socket.on('refreshData', (data) => handlerefreshData(socket, data));
    socket.on('changeStateLight', (data) => handleChangeStateLight(socket, data));
    socket.on('changeWindowState', (data) => handleChangeWindowState(socket, data));
    socket.on('changeHeaterState', (data) => handleChangeHeaterState(socket, data));
});

async function handlerefreshData(socket, data) {
    socket.emit("responseRefresh", 
        {
            temperature: 23.5,
            humidity: 50.5,
            light: "50",
            window: "OPEN",
            heater: "ON",
        }
    );
    
    // Read humidity/temperature
	await execFile('./test readTempAndHumidity', (error, stdout, stderr) => {
        if(error) { throw error;}
        console.log(stdout);
    });

    //Read light
    await execFile('./test readLightLevel', (error, stdout, stderr) => {
        if(error) { throw error;}
        console.log(stdout);
    });

    //Read window
    await execFile('./test readWindow', (error, stdout, stderr) => {
        if(error) { throw error;}
        console.log(stdout);
    });
    
    //Read heater
    await execFile('./test readHeater', (error, stdout, stderr) => {
        if(error) { throw error;}
        console.log(stdout);
    });
}

async function handleChangeStateLight(socket, data) {
    var newData = JSON.parse(data);
    console.log("Light = " + newData.state);

    //await execFile('./test setLightLevel '+ newData.state, (error, stdout, stderr) => {
    //     if(error) { throw error;}
    //     console.log(stdout);
    // });

    socket.emit("responseSetLight", 
        {
            light: newData.state
        }
    );
}

async function handleChangeWindowState(socket, data) {
    var newData = JSON.parse(data);
    console.log("Window = " + newData.state);
    // await execFile('./test setWindowSatus '+ newData.state, (error, stdout, stderr) => {
    //     if(error) { throw error;}
    //     console.log(stdout);
    // });

    socket.emit("responseSetWindow", 
        {
            window: newData.state
        }
    );
}

async function handleChangeHeaterState(socket, data) {
    var newData = JSON.parse(data);
    console.log("heater = " + newData.state);
    // await execFile('./test setHeaterStatus ' + newData.state, (error, stdout, stderr) => {
    //     if(error) { throw error;}
    //     console.log(stdout);
    // });

    socket.emit("responseSetHeater", 
        {
            heater: newData.state
        }
    );
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