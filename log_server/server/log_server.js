
var _    = require('underscore');
var net  = require('net');
var http = require('http');
var urlLib = require('url');
var util = require('util');

var tcpPort = 8402, defHttpPort = 8502, httpPort = defHttpPort;

var mkkeyvP; // like mkdir -p but for objects
var valueOf;

var data = [], currLoopNum = -1, stableLoopNum;

if (process.argv.length > 2) {
  httpPort = process.argv[2];
  tcpPort += (httpPort - defHttpPort);
}

// Listen for TCP stream, it is data from the bot
var server = net.createServer(function(c) {
  'use strict';

  c.setEncoding('utf8');

  var dict = {}, currObjectTypes, currObjectNum, currObjectName;

  var remainder = '';
  c.on('data', function(chunk) {
    var str = remainder + chunk;
    var lines = str.split('\n');
    remainder = lines.pop();

    _.each(lines, function(line) {
      var m;
      
      if (line === '==START==') {
        data = [];
      } else if ((m = /^([a-zA-Z0-9_]+): *([^;]*)/.exec(line))) {
        var name = m[1], value = {};
        var rest = m[2];

        m = /:/.exec(rest);
        if (!m) {
          // non-compound
          value = rest;

        } else {
          // compound
          var subs = rest.split(/ +/g);
          _.each(subs, function(sub) {
            var parts = sub.split(':'), subName = parts[0], subValue = parts[1] || 0;
            value[subName] = valueOf(subValue);
          });
        }

        // We now have the name and value
        dict[name] = value;

        if (name === 'loop_num') {
          stableLoopNum = currLoopNum;
          currLoopNum = valueOf(value);
          data[value] = data[value] || {};
        } else if (/^good_objects/i.exec(name)) {
          currObjectTypes = name;
        } else if (/^removed.*objects/i.exec(name)) {
          currObjectTypes = name;
        } else if (/^object/i.exec(name)) {
          currObjectName = name;
          currObjectNum = value;

        } else if (name in {area:true, bbox:true, center:true, centroid:true, skininess:true, score:true}) {
          if (currObjectName === 'object' || currObjectTypes !== 'good_objects') {
            mkkeyvP(data, currLoopNum, [currObjectTypes], currObjectNum, name, value);
          } else {
            mkkeyvP(data, currLoopNum, [currObjectTypes], currObjectNum, name, value);
          }
        } else if (/^servo_/i.exec(name)) {
          mkkeyvP(data, currLoopNum, name, value);
        } else if (name in {'loop_start_time':true, 'ctrl_state':true, 'loop_compute_time':true}) {
          mkkeyvP(data, currLoopNum, name, value);
        }

        if (name === 'loop_num' && data[stableLoopNum]) {
          console.log('----- Loop: ' + stableLoopNum);
          //console.log(util.inspect(data[stableLoopNum], {depth:null, colors:true}));
        }
      }
    });
  });

});

console.log("Listening for TCP data on: " + tcpPort);
server.listen(tcpPort);

http.createServer(function(req, res) {
  var url       = urlLib.parse(req.url, true);
  var query     = url.query;
  var pathParts = _.rest(url.pathname.split('/'));
  
  var stableLoopNumAtStart = stableLoopNum;

  var result = {_meta:{}};

  var sendResult = function() {
    result._meta.totalFrames = stableLoopNum;

    console.log(req.url, util.inspect(result, {depth:null, colors:true}));

    res.writeHead(200, {'Content-Type': 'application/javascript'});
    res.end(url.query.callback + "(" + JSON.stringify(result) + ");");
  };

  var id;

  // path: /frame
  if (pathParts[0] === 'frame') {
    if (query.id) {
      id = valueOf(query.id);
    } else {
      id = 11;
    }

    var tryAndGetIt = function() {
      if (id <= stableLoopNum && data && data[id]) {
        result.frameNum = valueOf(id);
        result.frame = data[id];
        return sendResult();
      }
      
      /* otherwise, see if stableLoopNum has jumped backward (the bot has restarted) */
      if (stableLoopNum < stableLoopNumAtStart) {
        id = stableLoopNum;
        return tryAndGetIt();
      }

      /* otherwise, don't have the item... wait for it */
      return setTimeout(tryAndGetIt, 10);
    };

    if (_.isNumber(id)) {
      return tryAndGetIt();
    }

    /* otherwise */
    id = stableLoopNum;
    return tryAndGetIt();
  }

  /* otherwise */
  if (pathParts[0] === 'restart') {
    //data = [];
    return sendResult();
  }

  res.writeHead(200, {'Content-Type': 'application/javascript'});
  res.end(url.query.callback + "(" + JSON.stringify(result) + ");");
}).listen(httpPort);
console.log("Listening for HTTP on: " + httpPort);

var mkOneKey = function(obj, key) {
  'use strict';
  // Mostly, we just do obj[key], but if the caller wants an array...
  var wantsArray = false;
  if (_.isArray(key)) {
    wantsArray = true;
    key = key[0];
  }

  if (!wantsArray) {
    obj[key] = obj[key] || {};
    return obj[key];
  }

  /* otherwise */
  obj[key] = obj[key] || [];
  return obj[key];
};

valueOf = function(value) {
  'use strict';
  if (/^[-0-9]+$/.exec(value)) {
    return parseInt(value);
  } else if (/^[-0-9\.]+$/.exec(value)) {
    return parseFloat(value);
  }
  return value;
};

mkkeyvP = function(obj) {
  'use strict';
  if (arguments.length < 2) { return; }

  var args = _.rest(arguments);

  if (args.length === 1) {
    return mkOneKey(obj, args[0]);
  }

  /* otherwise */
  var value = args.pop(), key;
  var dict  = obj;
  while (args.length > 1) {
    key = args.shift();
    dict = mkOneKey(dict, key);
  }

  key = args.shift();
  if (value === null) {
    mkOneKey(dict, key);
  } else {
    //if (/^[-0-9]+$/.exec(value)) {
    //  value = parseInt(value);
    //} else if (/^[-0-9\.]+$/.exec(value)) {
    //  value = parseFloat(value);
    //}
    dict[key] = valueOf(value);
  }

  return obj;
};

