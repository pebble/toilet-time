var express = require('express');
var bodyParser = require("body-parser");
var app = express();

app.use(bodyParser());

app.post('/v1/update', function(req, res) {
  console.log(req.body)
})

app.listen(8080,function(){
  console.log("Started on PORT 8080");
})
