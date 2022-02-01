var express = require('express');
var router = express.Router();

router.get('/', function(req, res) {
  res.render('index', { title: 'Página Inicial' });
});

router.get('/getESPs', function(req, res){
  res.send(global.esps);
});

module.exports = router;
