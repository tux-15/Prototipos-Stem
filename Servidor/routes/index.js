var express = require('express');
var router = express.Router();

router.get('/', function(req, res) {
  res.render('index', { title: 'Express' });
});

router.get('/getESPs', function(req, res){
  res.send(global.esps);
  //res.render('select_prototype', {title: "aa"});
});

// router.post('/postInfo', function(req, res){
//   console.log(req.body);
//   res.redirect('/manipulador');
// });

module.exports = router;
