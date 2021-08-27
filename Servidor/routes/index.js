var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/getESPs', function(req, res){
  esp_list = "";
  global.esps.forEach(esp => esp_list = esp_list + esp.ip + "<br>");
  res.send(esp_list);
});

// /* GET Hello World page. */
// router.get('/helloworld', function(req, res) {
//   res.render('helloworld', { title: 'Hello, World!' });
// });

module.exports = router;
