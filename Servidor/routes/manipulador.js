var express = require('express');
var router = express.Router();

/* GET manipulador page. */
router.get('/', function(req, res, next) {
  console.log("Mandando página do manipulador");
  res.render('manipulador', {title: "Manipulador"});
});

module.exports = router;