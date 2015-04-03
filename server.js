var http = require('http');
var sockjs = require('sockjs');
var request = require('request');
var nodeStatic = require('node-static');

var staticServer = new nodeStatic.Server(__dirname);

var socketServer = sockjs.createServer(
  { sockjs_url: 'http://cdn.jsdelivr.net/sockjs/0.3.4/sockjs.min.js' }
);

var httpServer = http.createServer();

var port = process.argv[2] || 9999;

var host = '0.0.0.0';

var sockets = [];

socketServer.on('connection', function(socket) {
  sockets.push(socket);
  socket.on('close', function() {
    sockets.splice(sockets.indexOf(socket),1);
  });
});

setInterval(function(){
  request('http://10.0.126.68',function(err, res, body){
    for (var i in sockets){
      sockets[i].write(body);
    }
  });
},1000);


httpServer.addListener('request', function(req, res) {
  staticServer.serve(req, res);
});

httpServer.addListener('upgrade', function(req, res) {
  res.end();
});

socketServer.installHandlers(httpServer, {prefix:'/ws'});

httpServer.listen(port, host);
