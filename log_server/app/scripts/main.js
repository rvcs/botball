
var width = 512, height = 512;
var botWidth = 160, botHeight = 120;
var hScale = width / botWidth, theScale = hScale;
var vScale = height / botHeight;

var fetchDelay = 750;
var startFrameNum = 18;

if (vScale < theScale) {
  theScale = vScale;
}

var normBbox, scale, fetch;

var frame = {};

function sketchProc(pr) {
  "use strict";

  pr.size(width, height);

  pr.draw = function() {
    pr.background(128);

    pr.strokeWeight(1);
    pr.line(width/2, 0, width/2, height);
    pr.line(0, height/2, width, height/2);

    pr.strokeWeight(3);
    if (frame.good_objects) {
      frame.good_objects.forEach(function(obj) {
        var bbox = normBbox(obj.bbox);
        if (bbox) {
          pr.fill(255, 255, 255);
          pr.rect(bbox.x, bbox.y, bbox.w, bbox.h);
		  pr.fill(255, 255, 255);
		  pr.text("(" + bbox.x + "," + bbox.y + ")", bbox.x, bbox.y);
        }
      });
    }

    if (frame.good_objectsY) {
      frame.good_objectsY.forEach(function(obj) {
        var bbox = normBbox(obj.bbox);
        if (bbox) {
          pr.fill(221, 255, 0);
          pr.rect(bbox.x, bbox.y, bbox.w, bbox.h);
		  pr.fill(255, 255, 255);
		  pr.text("(" + bbox.x + "," + bbox.y + ")", bbox.x, bbox.y);
        }
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
			pr.text("(" + bbox.x + "," + bbox.y + ")", bbox.x, bbox.y);
          }
        });
      }
    });
  };
}

var fetch = function(frameNum) {
  "use strict";
  $.ajax({
    url: "http://192.168.11.117:9011/frame",
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

normBbox = function(bbox) {
  var result = {};

  result.x = scale(bbox.x) + width/2;
  result.y = height/2 - scale(bbox.y);
  result.w = scale(bbox.w);
  result.h = scale(-bbox.h);

  return result;
};

setTimeout(function() {
  $.ajax({
    url: "http://192.168.11.117:9011/restart",
    dataType: "jsonp",
    success:function() {
      fetch(startFrameNum);
    }
  });
}, 100);

