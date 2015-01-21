global.$ = $;

var _ = require('underscore');
var http = require('http');

$(document).ready(function() {
  http.createServer(function(req, res) {
    document.write(req.url);
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('Hello World\n');
  }).listen(1337);
});