
var width = 512, height = 512;
var botWidth = 160, botHeight = 120;
var hScale = width / botWidth, theScale = hScale;
var vScale = height / botHeight;

var startData    = g_startData || {};      // jshint ignore:line
startData.port   = startData.port || 8502;
startData.server = startData.server || "192.168.11.111";
//startData.server = startData.server || "192.168.11.117";

var config = {port:startData.port, server:startData.server};

var fetchDelay = 5;
var startFrameNum = 18;

if (vScale < theScale) {
  theScale = vScale;
}

var normBbox, normPt, scale, fetch;

var frame = {};



function sketchProc(pr) {
  "use strict";

  pr.size(width, height);

  pr.draw = function() {
    var i;
    pr.background(128);

    pr.strokeWeight(1);
    pr.line(width/2, 0, width/2, height);
    pr.line(0, height/2, width, height/2);

    pr.strokeWeight(3);
    if (frame.good_objects) {
      i = 1;
      frame.good_objects.forEach(function(obj) {
        var bbox = normBbox(obj.bbox);
        if (bbox) {
          pr.fill(255, 255, 255);
          pr.rect(bbox.x, bbox.y, bbox.w, bbox.h);
          pr.fill(0, 0, 255);
          pr.text(i + " (" + obj.bbox.x + "," + obj.bbox.y + ") ", bbox.x + bbox.w/3, bbox.y + bbox.h/3);
          
        }
        i++;
      }); 
    }

    if (frame.good_objectsY) {
      i = 1;
      frame.good_objectsY.forEach(function(obj) {
        var bbox = normBbox(obj.bbox);
        if (bbox) {
          pr.fill(221, 255, 0);
          pr.rect(bbox.x, bbox.y, bbox.w, bbox.h);
          pr.fill(0, 0, 0);
          pr.text(i + " (" + obj.bbox.x + "," + obj.bbox.y + ") ", bbox.x + bbox.w/3, bbox.y + bbox.h/3);
          
        }
        i++;
      });
    }

    _.each(frame, function(_value, key) {       // jshint ignore:line
      if (/^removed.*objects$/i.exec(key)) {
        frame[key].forEach(function(obj) {
          var bbox = normBbox(obj.bbox);
          if (bbox) {
            pr.fill(194, 84, 0);
            pr.rect(bbox.x, bbox.y, bbox.w, bbox.h);
            pr.fill(255, 255, 255);
            pr.text("(" + obj.bbox.x + "," + obj.bbox.y + ")", bbox.x + bbox.w/3, bbox.y + bbox.h/3);
          }
        });
      }
    });
  };
}

var fetch = function(frameNum) {
  "use strict";
  $.ajax({
    //url: "http://192.168.11.117:9011/frame",
    url: "http://" + config.server + ":" + config.port + "/frame",
    data:{id:frameNum},
    dataType: "jsonp",
    success:function(data) {
      if (data.frame) {
        frame = data.frame;
      }
      if (data.frameNum) {
        $('#frame-num').each(function() {
          $(this).text(data.frameNum);
        });
      }

      if (frameNum === 'latest') {
        setTimeout(function() {fetch(frameNum); }, 1);
      } else /* if (data.frameNum < data._meta.totalFrames) */ {
        setTimeout(function() {fetch(data.frameNum + 1); }, fetchDelay);
      }
    }
  });
};
var canvas = document.getElementById("canvas1");

var processingInstance = new Processing(canvas, sketchProc);  // jshint ignore:line

scale = function(x) {
  return x * theScale;
};

normPt = function(point) {
  var result = {};

  result.x = Math.floor(scale(point.x) + width/2);
  result.y = Math.floor(height/2 - scale(point.y));

  return result;
};

normBbox = function(bbox) {
  var result = {};

  result.x = Math.floor(scale(bbox.x) + width/2);
  result.y = Math.floor(height/2 - scale(bbox.y));
  result.w = Math.floor(scale(bbox.w));
  result.h = Math.floor(scale(-bbox.h));

  return result;
};

setTimeout(function() {
  $.ajax({
    //url: "http://192.168.11.117:9011/restart",
    url: "http://" + config.server + ":" + config.port + "/restart",
    data: startData,
    dataType: "jsonp",
    success:function(data) {
      config = _.extend({}, startData, config, data);           // jshint ignore:line
      fetch(startFrameNum);
    }
  });
}, 100);


/*
 * Gamepad API Test
 * Written in 2013 by Ted Mielczarek <ted@mielczarek.org>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
var haveEvents = 'GamepadEvent' in window;
var controllers = {};
var rAF = window.mozRequestAnimationFrame ||
  window.webkitRequestAnimationFrame ||
  window.requestAnimationFrame;

function connecthandler(e) {
  addgamepad(e.gamepad);
}
function addgamepad(gamepad) {
  var e;
  controllers[gamepad.index] = gamepad; var d = document.createElement("div");
  d.setAttribute("id", "controller" + gamepad.index);
  var t = document.createElement("h1");
  t.appendChild(document.createTextNode("gamepad: " + gamepad.id));
  d.appendChild(t);
  var b = document.createElement("div");
  b.className = "buttons";
  for (var i=0; i<gamepad.buttons.length; i++) {
    e = document.createElement("span");
    e.className = "button";
    //e.id = "b" + i;
    e.innerHTML = i;
    b.appendChild(e);
  }
  d.appendChild(b);
  var a = document.createElement("div");
  a.className = "axes";
  for (i=0; i<gamepad.axes.length; i++) {
    e = document.createElement("progress");
    e.className = "axis";
    //e.id = "a" + i;
    e.setAttribute("max", "2");
    e.setAttribute("value", "1");
    e.innerHTML = i;
    a.appendChild(e);
  }
  d.appendChild(a);
  document.getElementById("start").style.display = "none";
  document.body.appendChild(d);
  rAF(updateStatus);
}

function disconnecthandler(e) {
  removegamepad(e.gamepad);
}

function removegamepad(gamepad) {
  var d = document.getElementById("controller" + gamepad.index);
  document.body.removeChild(d);
  delete controllers[gamepad.index];
}

function updateStatus() {
  var i, j;
  scangamepads();
  for (j in controllers) {
    var controller = controllers[j];
    var d = document.getElementById("controller" + j);
    var buttons = d.getElementsByClassName("button");
    for (i=0; i<controller.buttons.length; i++) {
      var b = buttons[i];
      var val = controller.buttons[i];
      var pressed = val == 1.0;
      if (typeof(val) == "object") {
        pressed = val.pressed;
        val = val.value;
      }
      var pct = Math.round(val * 100) + "%";
      b.style.backgroundSize = pct + " " + pct;
      if (pressed) {
        b.className = "button pressed";
      } else {
        b.className = "button";
      }
    }

    var axes = d.getElementsByClassName("axis");
    for (i=0; i<controller.axes.length; i++) {
      var a = axes[i];
      a.innerHTML = i + ": " + controller.axes[i].toFixed(4);
      a.setAttribute("value", controller.axes[i] + 1);
      //console.log(controller.axes[i]);
    }
  }
  rAF(updateStatus);
}

function scangamepads() {
  var gamepads = navigator.getGamepads ? navigator.getGamepads() : (navigator.webkitGetGamepads ? navigator.webkitGetGamepads() : []);
  for (var i = 0; i < gamepads.length; i++) {
    if (gamepads[i]) {
      if (!(gamepads[i].index in controllers)) {
        addgamepad(gamepads[i]);
      } else {
        controllers[gamepads[i].index] = gamepads[i];
      }
    }
  }
}

if (haveEvents) {
  window.addEventListener("gamepadconnected", connecthandler);
  window.addEventListener("gamepaddisconnected", disconnecthandler);
} else {
  setInterval(scangamepads, 500);
}

