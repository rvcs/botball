// Created on Sun December 28 2014

// Replace FILE with your file's name
#ifndef _RVCS_LOG_HPP_
#define _RVCS_LOG_HPP_

#include <deque>

namespace rvcs {
  int  start(int argc, char * argv[], int s0_pos, int s1_pos, int s2_pos, int s3_pos, int defState);
  int  die(char const * msg = NULL);

  bool   rvcs_should_run_loop(int ctrl_state, int loop_num);
  bool   rvcs_transitioning_to_this_state();
  double time_since_transition();
  int    ms_since_transition(int ms1, int ms2 = -1, int ms3 = -1, int ms4 = -1, int ms5 = -1);

  int               rvcs_camera_update();
  struct rectangle  rvcs_object_bbox(int channel, int obj_id);
  struct point2     rvcs_object_center(int channel, int obj_id);
  struct point2     rvcs_object_centroid(int channel, int obj_id);

  void move(int left, int right);

  void rvcs_set_servo(int servo_num, int pos);

  void log(char const * var_name, double value);
  void log(char const * var_name, int value, char const * comment = NULL);
  void log(char const * format, char const * var_name, int a, int b);
  void log(char const * var_name, int which, int value, char const * comment = NULL);
  void log(char const * var_name, bool value);
  void log(char const * var_name, struct rectangle const & value);
  void log(char const * var_name, struct point2 const & value);

  double time_since(double const & other);

  void end();
  
  struct Blob {
    struct rectangle  rect;
    struct point2     center, centroid;
    int               left, hcenter, right;
    int               top, vcenter, bottom;
    float             score;

    Blob(struct rectangle const & r, struct point2 const & cent);
    Blob(bool);
    Blob(Blob const & that);
    Blob & operator=(Blob const & that);
    void _copy(Blob const & that);
    virtual bool is_wonky() const;
    float aspect_ratio() const;
    float skininess() const;
    int area() const;
    bool contains(struct point2 const & pt) const;
    void _set(struct rectangle const & r, struct point2 const & cent);
    void log() const;
  };
  typedef std::deque<Blob> BlobList;

  BlobList rvcs_objects(int channel, int min_area = 0);

  void log(BlobList const & list, char const * item_msg = NULL, char const * msg = NULL);
  void log(BlobList const * list, char const * item_msg = NULL, char const * msg = NULL);

  BlobList filter_skininess(BlobList const & list, float lt = 1.0, float gt = 3.0, BlobList * premoved = NULL, char const * logging_suffix = NULL);
  BlobList filter_area(BlobList const & list, int lt, int gt, BlobList * premoved = NULL, char const * logging_suffix = NULL);
  BlobList filter_x(BlobList const & list, int lt, int gt, BlobList * premoved = NULL, char const * logging_suffix = NULL);
  BlobList filter_y(BlobList const & list, int lt, int gt, BlobList * premoved = NULL, char const * logging_suffix = NULL);
  BlobList filter_doesnt_contain(BlobList const & list, struct point2 const & pt, BlobList * premoved = NULL, char const * logging_suffix = NULL);

  BlobList zero_scores(BlobList const & list);
  BlobList score_by_x(BlobList const & list);
  BlobList score_by_nx(BlobList const & list);

  BlobList first(BlobList const & list, int count = 1, BlobList * premoved = NULL);

  Blob const & head(BlobList const & list);

  BlobList reorder_by_score(BlobList const & list);
};


#endif
