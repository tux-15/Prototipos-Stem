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

function removeItemOnce(arr, value) {
  var index = arr.indexOf(value);
  if (index > -1) {
    arr.splice(index, 1);
  }
  return;
}

const wss = new WebSocket.Server({
  port: 1801,
});


global.esps = [];
let pages = [];

function noop() {};

function heartbeat() {
  current_ip = this['_socket']['_peername']['address'];
  global.esps.forEach(function each(esp){
    if(current_ip == esp.ip){
      esp.status = true;
    }
  })
}

class Esp {
  constructor(connection, ip, status){
    this.connection = connection;
    this.ip = ip;
    this.status = status
  }

}

wss.on('connection', function connection(ws, request) {

  ws.on('pong', heartbeat);
  
  ws.on('message', function incoming(message) {
    message_string = message.toString();

    if(message_string == "ESP_on"){
      global.esps.push(new Esp(ws, request.socket.remoteAddress, true));
      console.log("new ESP: ", global.esps[global.esps.length-1].ip);
      console.log("-----------------------------------------------------------------");
      //console.log("new ESP: ", global.esps[esps.length-1].status);
      //console.log("new ESP: ", global.esps[esps.length-1].connection);
      //esps.forEach(esp => console.log(esp.status, esp.ip));
    }

    if(message_string == "page_on"){
      page_data = {'ip': ws.ip, 'connection': ws};
      pages.push(page_data);
      pages.forEach(page => console.log("Pages = ", page.ip));
    }

    //esps.forEach(esp => esp.connection.send(message));
    console.log('received: %s', message);
  });

  //ws.send('Connected to Server\n');
});

const interval = setInterval(function ping() {

  global.esps.forEach(function each(esp) {
    if (esp.status === false) {
      console.log(esp.ip + " is dead");
      console.log("-----------------------------------------------------------------");
      esp.connection.terminate();
      removeItemOnce(global.esps, esp);
      return;
    }

    esp.status = false;
    esp.connection.ping(noop);
    // global.esps.forEach(esp => console.log("active esps: ", esp.ip));
    // console.log("-----------------------------------------------------------------");
  });
}, 1500);

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
