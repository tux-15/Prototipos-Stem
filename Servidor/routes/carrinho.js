var express = require('express');
var router = express.Router();

/* GET carrinho page. */

// router.get('/', function(req, res, next) {
//   res.render('carrinho', { title: 'Carrinho STEM' });
// });

router.get('/', function(req, res, next) {
  res.render('v2/carrinho', { title: 'Carrinho STEM' });
});


// router.get('/', function(req, res, next) {
//     res.render('v2/carrinho', { title: 'Carrinho STEM' });
//   });

module.exports = router;