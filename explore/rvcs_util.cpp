// Created on Sun December 28 2014

#include "rvcs_util.hpp"
#include "kovan/kovan.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

using std::string;

char* itoa(int num, char* str, int base);

namespace rvcs {
  int state_to_run = -1, state_to_stop = -1;

  int norm_x(int x);
  int norm_y(int y);

  int cam_height = 0, cam_width = 0, half_cam_height = 0, half_cam_width = 0;

  int start(int argc, char * argv[], int s0_pos, int s1_pos, int s2_pos, int s3_pos, int defState) {
    int result = 1;
    int state = defState;

    int x = 0;
    for (int i = 1; i < argc; ++i) {
      x = atoi(argv[i]);
      if (x < 100 && state_to_run == -1) {
        state_to_run = state = x;
      } else if (x < 100) {
        state_to_stop = x;
      }
    }

    set_camera_config_base_path("/etc/botui/channels");

    result = result && camera_open();
    if (!result) { die("camera_open() failed"); }

    result = result && camera_load_config("orange");
    if (!result) { die("camera_load_config failed"); }

    set_servo_position(0, s0_pos);
    set_servo_position(1, s1_pos);
    set_servo_position(2, s2_pos);
    set_servo_position(3, s3_pos);
    enable_servos();
    
    log("==START==", -999);

    return state;
  }

  void end() {
    log("==END==", -999);
    camera_close();
    disable_servos();
    alloff();
  }

  bool rvcs_should_run_loop(int ctrl_state) {
    if (state_to_run == -1) { return true; }

    if (state_to_stop == -1 && state_to_run != ctrl_state) { return false; }
    if (state_to_stop == ctrl_state) { return false; }

    return true;
  }

  void move(int left, int right) {
    motor(0, left);
    motor(1, right);
    log("%s: left:%d right:%d\n", "motor", left, right);
  }

  void rvcs_set_servo(int servo_num, int pos) {
    set_servo_position(servo_num, pos);
    log("servo", servo_num, pos);
  }

  int  rvcs_camera_update() {
    int result = camera_update();

    if (result) {
      cam_height = get_camera_height();
      cam_width  = get_camera_width();

      half_cam_height = cam_height >> 1;
      half_cam_width  = cam_width  >> 1;
    }

    return result;
  }

  struct point2     rvcs_object_center(int channel, int obj_id) {
    struct point2 result = get_object_center(channel, obj_id);
    result.x = norm_x(result.x);
    result.y = norm_y(result.y);
    return result;
  }

  struct point2     rvcs_object_centroid(int channel, int obj_id) {
    struct point2 result = get_object_centroid(channel, obj_id);
    result.x = norm_x(result.x);
    result.y = norm_y(result.y);
    return result;
  }

  struct rectangle  rvcs_object_bbox(int channel, int obj_id) {
    struct rectangle result = get_object_bbox(channel, obj_id);
    result.ulx = norm_x(result.ulx);
    result.uly = norm_y(result.uly + result.height);
    return result;
  }

  int die(char const * msg_) {
    char const * msg = msg_ ? msg_ : "";
    printf("Dying: %s\n", msg);
    exit(2);
    return 1;
  }

  double time_since(double const & other) {
    return seconds() - other;
  }

  void log(char const * var_name, double value) {
    printf("%s: %lf\n", var_name, value);
  }

  void log(char const * var_name, int value, char const * comment) {
    if (comment) {
      printf("%s: %d; --%s\n", var_name, value, comment);
    } else {
      printf("%s: %d\n", var_name, value);
    }
  }

  void log(char const * var_name, int which, int value, char const * comment) {
    char buf[32];
    string name(var_name);
    name += "_";
    name += itoa(which, buf, 10);
    log(name.c_str(), value, comment);
  }

  void log(char const * format, char const * var_name, int a, int b) {
    printf(format, var_name, a, b);
  }
  
  void log(char const * var_name, bool value) {
    printf("%s: %s\n", var_name, value ? "1" : "0");
  }

  void log(char const * var_name, struct point2 const & value) {
    printf("%s: x:%d y:%d\n", var_name, value.x, value.y);
  }

  void log(char const * var_name, struct rectangle const & value) {
    printf("%s: x:%d y:%d w:%d h:%d\n", var_name, value.ulx, value.uly, value.width, value.height);
  }

  static Blob theNullBlob(false);

  BlobList filter_skininess(BlobList const & list, float lt, float gt, BlobList * premoved) {
    BlobList result;

    if (premoved) {
      premoved->clear();
    }

    for (BlobList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Blob const & blob = *i;
      if (blob.skininess() >= lt && blob.skininess() <= gt) {
        result.push_back(blob);
      } else {
        if (premoved) {
          premoved->push_back(blob);
        }
      }
    }

    return result;
  }

  BlobList filter_area(BlobList const & list, int lt, int gt, BlobList * premoved) {
    BlobList result;

    if (premoved) {
      premoved->clear();
    }

    for (BlobList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Blob const & blob = *i;
      if (blob.area() >= lt && blob.area() <= gt) {
        result.push_back(blob);
      } else {
        if (premoved) {
          premoved->push_back(blob);
        }
      }
    }

    return result;
  }

  BlobList filter_x(BlobList const & list, int lt, int gt, BlobList * premoved) {
    BlobList result;

    if (premoved) {
      premoved->clear();
    }

    for (BlobList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Blob const & blob = *i;
      if (blob.center.x >= lt && blob.center.x <= gt) {
        result.push_back(blob);
      } else {
        if (premoved) {
          premoved->push_back(blob);
        }
      }
    }

    return result;
  }

  BlobList filter_y(BlobList const & list, int lt, int gt, BlobList * premoved) {
    BlobList result;

    if (premoved) {
      premoved->clear();
    }

    for (BlobList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Blob const & blob = *i;
      if (blob.center.y >= lt && blob.center.y <= gt) {
        result.push_back(blob);
      } else {
        if (premoved) {
          premoved->push_back(blob);
        }
      }
    }

    return result;
  }

  BlobList filter_doesnt_contain(BlobList const & list, struct point2 const & pt, BlobList * premoved) {
    BlobList result;

    if (premoved) {
      premoved->clear();
    }

    for (BlobList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Blob const & blob = *i;
      if (blob.contains(pt)) {
        result.push_back(blob);
      } else {
        if (premoved) {
          premoved->push_back(blob);
        }
      }
    }

    return result;
  }

  BlobList score_by_x(BlobList const & list) {
    BlobList result;

    for (BlobList::const_iterator blob = list.begin(); blob != list.end(); ++blob) {
      Blob new_blob = *blob;
      new_blob.score = (float)new_blob.center.x;
      result.push_back(new_blob);
    }

    return reorder_by_score(result);
  }

  BlobList score_by_nx(BlobList const & list) {
    BlobList result;

    for (BlobList::const_iterator blob = list.begin(); blob != list.end(); ++blob) {
      Blob new_blob = *blob;
      new_blob.score = -1 * (float)new_blob.center.x;
      result.push_back(new_blob);
    }

    return reorder_by_score(result);
  }

  BlobList first(BlobList const & list, int count, BlobList * premoved) {
    BlobList result;

    if (premoved) {
      premoved->clear();
    }

    BlobList::const_iterator blob;
    for (blob = list.begin(); blob != list.end() && count > 0; ++blob, --count) {
      result.push_back(*blob);
    }

    if (premoved) {
      for (; blob != list.end(); ++blob) {
        premoved->push_back(*blob);
      }
    }

    return result;
  }

  Blob const & head(BlobList const & list) {
    for (BlobList::const_iterator blob = list.begin(); blob != list.end(); ++blob) {
      return *blob;
    }
    return theNullBlob;
  }

  float high_score_lt(BlobList const & list, float high_known) {
    float high_found = -99999999.9;

    for (BlobList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Blob const & blob = *i;
      if (blob.score > high_found && blob.score < high_known) {
        high_found = blob.score;
      }
    }

    return high_found;
  }

  BlobList reorder_by_score(BlobList const & list) {
    BlobList result;

    if (list.size() <= 1) {
      return list;
    } else if (list.size() == 2) {
      BlobList::const_iterator i = list.begin();
      Blob const & first = *i++;
      Blob const & second = *i;
      if (first.score >= second.score) {
        return list;
      }

      result.push_back(second);
      result.push_back(first);
      return result;

    } else {

      float highest = 99999999.9;
      while (list.size() != result.size()) {
        highest = high_score_lt(list, highest);
        for (BlobList::const_iterator i = list.begin(); i != list.end(); ++i) {
          Blob const & blob = *i;
          if (blob.score == highest) {
            result.push_back(blob);
          }
        }
      }
    }

    return result;
  }

  void log(BlobList const & list, char const * item_msg, char const * msg) {
    if (msg) { log(msg, (int)list.size()); }
    if (list.size() > 0) {

      int i = 0;
      for (BlobList::const_iterator blob = list.begin(); blob != list.end(); ++blob, ++i) {
        if (item_msg) { log(item_msg, i); }
        blob->log();
      }
    }
  }

    Blob::Blob(struct rectangle const & r, struct point2 const & cent)
      : score(0.0)
    {
      _set(r, cent);
    }

    Blob::Blob(Blob const & that)
      : score(0.0)
    {
      _copy(that);
    }

    Blob::Blob(bool)
    {
      struct rectangle r;
      struct point2    c;

      r.ulx = r.uly = r.width = r.height = c.x = c.y = 0;
      _set(r, c);
    }

    Blob & Blob::operator=(Blob const & that)
    {
      _copy(that);
      return *this;
    }

    void Blob::_copy(Blob const & that) {
      if (this != &that) {
        _set(that.rect, that.centroid);
        score = that.score;
      }
    }

    bool Blob::is_wonky() const {
      if (!contains(centroid)) { return true; }

      return false;
    }

    float Blob::aspect_ratio() const {
      return ((float)rect.width / (float)rect.height);
    }

    float Blob::skininess() const {
      float ar = aspect_ratio();
      if (ar >= 1.0) { return ar; }

      return 1.0 / ar;
    }

    int Blob::area() const {
      return rect.width * rect.height;
    }

    bool Blob::contains(struct point2 const & pt) const {
      if (pt.x < left)   { return false; }
      if (pt.x > right)  { return false; }
      if (pt.y < bottom) { return false; }
      if (pt.y > top)    { return false; }

      return true;
    }

    void Blob::_set(struct rectangle const & r, struct point2 const & cent) {
      left   = rect.ulx = r.ulx;
      bottom = rect.uly = r.uly;
      right  = r.ulx + r.width;
      top    = r.uly + r.height;

      rect.width  = r.width;
      rect.height = r.height;

      center.x = (left   + right) / 2;
      center.y = (bottom + top) / 2;

      centroid.x = cent.x;
      centroid.y = cent.y;
    }

    void Blob::log() const {
      rvcs::log("area", area());
      rvcs::log("bbox", rect);
      rvcs::log("center", center);
      rvcs::log("centroid", centroid);
      rvcs::log("skininess", skininess());
      rvcs::log("score", score);
    }

  BlobList rvcs_objects(int channel, int min_area) {
    BlobList      result;
    bool          is_good = true;
    struct point2 centroid;

    int num_objects = get_object_count(channel);
    log("num_objects", num_objects);

    for (int i = 0; i < num_objects; ++i) {
      //log("________________________b", 0);

      //log("object", i);
      Blob blob(rvcs_object_bbox(channel, i), rvcs_object_centroid(channel, i));

      is_good = is_good && !blob.is_wonky();
      is_good = is_good && blob.area() > min_area;

      //blob.log();
      if (is_good) {
        result.push_back(blob);
      } else {
        //log("rejected", !is_good);
      }

    }

    return result;
  }

  // 'private' helpers
  int norm_x(int x) {
    return x - half_cam_width;
  }

  int norm_y(int y) {
    return half_cam_height - y;
  }
};

static void swap(char * pa, char * pb) {
  char temp = *pa;
  *pa = *pb;
  *pb = temp;
}

/* A utility function to reverse a string  */
static void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(str+start, str+end);
        start++;
        end--;
    }
}
 
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

