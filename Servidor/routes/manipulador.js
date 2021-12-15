var express = require('express');
var router = express.Router();

/* GET manipulador page. */
// router.get('/', function(req, res, next) {
//   res.render('/manipulador', {title: "Manipulador STEM"});
// });

router.get('/', function(req, res, next) {
  res.render('v2/manipulador', {title: "Manipulador STEM"});
});

module.exports = router;