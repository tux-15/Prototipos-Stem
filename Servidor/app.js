var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const fs = require('fs')

var indexRouter = require('./routes/index');
var manipuladorRouter = require('./routes/manipulador');
var usersRouter = require('./routes/users');
var carrinhoRouter = require('./routes/carrinho');
var calibracaoCarrinhoRouter = require('./routes/calibracao');

var WebSocket = require('ws');

function noop() {}

function heartbeat() {
  this.isAlive = true;
}

const wss = new WebSocket.Server({
  port: 1801,
});


global.esps = [];
let pages = [];

wss.on('connection', function connection(ws, request) {

  ws.ip= request.socket.remoteAddress;
  ws.isAlive = true;
  ws.on('pong', heartbeat);

  ws.on('message', function incoming(message) {

    message_string = message.toString();

    if(message_string == "ESP_on"){

      esps_data = {'ip': ws.ip, 'connection': ws};
      global.esps.push(esps_data);
      console.log("new ESP: ", global.esps[esps.length-1].ip);

    }

    if(message_string == "page_on"){

      page_data = {'ip': ws.ip, 'connection': ws};
      pages.push(page_data);
      pages.forEach(page => console.log("Pages = ", page.ip));

    }

    // if(esps.length > 2){
    //   esps[2].connection.send(message);
    // } 

    //esps.forEach(esp => esp.connection.send(message));

    console.log('received: %s', message);
  });

  //ws.send('Connected to Server\n');
});

const interval = setInterval(function ping() {
  wss.clients.forEach(function each(ws) {
    if (ws.isAlive === false) {
      console.log("dead")
      return ws.terminate();
    }
    ws.isAlive = false;
    ws.ping(noop);
  });
}, 3000);

wss.on('close', function close() {
  clearInterval(interval);
});


var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
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

//module.exports = app;
var haha = "sono";

module.exports = app;
