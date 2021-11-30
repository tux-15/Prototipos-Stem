var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var moment = require('moment');

var WebSocket = require('ws');

var indexRouter = require('./routes/index');
var manipuladorRouter = require('./routes/manipulador');
var carrinhoRouter = require('./routes/carrinho'); 

// A comunicação dos protótipos se dá através de um websocket que é aberto na porta 1801
const wss = new WebSocket.Server({
  port:1801,
});

var Esp = require("./classes/ESP.js");
var ping  = Esp.ping;
var heartbeat = Esp.heartbeat;

var Page = require("./classes/Page.js");
var pingPage = Page.pingPage;
var heartbeatPage = Page.heartbeatPage;

function ab2str(buf) {
  return String.fromCharCode.apply(null, new Uint16Array(buf));
}

const interval = setInterval(function(){
  ping();
  pingPage();
}, 3000);

wss.on('close', function close() {
  clearInterval(interval);
});

// os 3 arrays tomam conta dos esps e páginas atualmente conectados ao servidor
//assim como da "sala" de bate-papo onde eles ficam

global.esps = [];
global.pages = [];
global.rooms = [];

wss.on('connection', function connection(ws, request) {

  ws.on('pong', function(){ //Quando receber "pong" pelo websocket, o dispositivo continua online
    heartbeat(ws);
    heartbeatPage(ws);
  });

  ws.on('message', function incoming(message) {

    try {
      messageJson = JSON.parse(message); // converte a mensagem string em JSON
    }
    catch(err){
      console.log("Erro: ", err);
    }

    if(messageJson['start'] == "ESP_on"){ // Indica que um novo esp entrou no servidor
      var id = request.socket.remoteAddress.toString().slice(14);

      global.esps.push(new Esp(ws, id, true));
      console.log(moment().format('MMMM Do YYYY, h:mm:ss a'), " || new ESP: ", global.esps[global.esps.length-1].id);
    };

    if(messageJson['start'] == "page_on"){ // Indica que uma nova página entrou no servidor

      var id = request.socket.remoteAddress.toString().slice(7);

      global.pages.push(new Page(ws, id, messageJson['to'], true));

      lastPage = global.pages[global.pages.length-1];

      //Verifica com qual ESP a página quer se comunicar e coloca os 2 em uma sala de bate-papo 
      global.esps.forEach(esp => {
        if (esp.id == lastPage.pageEsp){
          global.rooms.push({"pageConnection": lastPage.connection, "espConnection": esp.connection});
          esp.taken = true; // Informa que este ESP já está sendo usado por uma página
          console.log("The page ", lastPage.id, "is sending messages to ESP", esp.id);
        };
      });
      //console.log(global.rooms);
    };

    global.rooms.forEach(room => {
      if(ws == room["pageConnection"]){
        room["espConnection"].send(message);
      }
      else if (ws == room['espConnection']){
        room["pageConnection"].send(ab2str(message));
      };
    });

  //esps.forEach(esp => esp.connection.send(message));
  console.log('received: %s', message);
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
