var express = require('express');
var router = express.Router();

/* GET carrinho page. */
router.get('/', function(req, res, next) {
    res.render('calibracao', { title: 'Calibração Carrinho' });
  });

module.exports = router;