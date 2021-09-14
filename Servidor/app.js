var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var manipuladorRouter = require('./routes/manipulador');
var carrinhoRouter = require('./routes/carrinho');
var calibracaoCarrinhoRouter = require('./routes/calibracao');

var WebSocket = require('ws');

var Esp = require("./classes/ESP.js");
var ping  = Esp.ping;
var heartbeat = Esp.heartbeat;

var Page = require("./classes/Page.js");
var pingPage = Page.pingPage;
var heartbeaPage = Page.heartbeaPage;

const wss = new WebSocket.Server({
  port: 1801,
});

const interval = setInterval(function(){
  ping();
  pingPage();
}, 3000);

wss.on('close', function close() {
  clearInterval(interval);
});

global.esps = [];
global.pages = [];
let rooms = [];

wss.on('connection', function connection(ws, request) {

  ws.on('pong', function(){
    heartbeat(ws);
    heartbeaPage(ws);
  });

  ws.on('message', function incoming(message) {

    messageJson = JSON.parse(message);

    if(messageJson['start'] == "ESP_on"){
      var id = request.socket.remoteAddress.toString().slice(17);
      global.esps.push(new Esp(ws, id, true));
      console.log("new ESP: ", global.esps[global.esps.length-1].id);
    };

    if(messageJson['start'] == "page_on"){

      var ip = request.socket.remoteAddress;

      global.pages.push(new Page(ws, ip, messageJson['to'], true));

      lastPage = global.pages[global.pages.length-1];
      console.log("page id no app.js", lastPage.id);

      global.esps.forEach(esp => {
        if (esp.id == lastPage.pageEsp){
          rooms.push({"pageConnection": lastPage.connection, "espConnection": esp.connection});
          esp.taken = true;
          console.log("The page ", lastPage.id, "is sending messages to ESP", esp.id);
        };
      });
      //console.log(rooms);
    };

    if(rooms[0] != undefined){
      rooms.forEach(room => {
        if(ws == room["pageConnection"]){
          room["espConnection"].send(message);
        };
      });
    };

  //esps.forEach(esp => esp.connection.send(message));
  //console.log('received: %s', message);
  });
});

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/manipulador', manipuladorRouter);
app.use('/carrinho', carrinhoRouter);
app.use('/calibracao', calibracaoCarrinhoRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
