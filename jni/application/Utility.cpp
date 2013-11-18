//
//  Utility.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Utility.h"
#include <utility>
#include "zenilib.h"

using std::cout;
using std::endl;
using std::bad_exception;
using std::string;
using std::pair;
using std::make_pair;
using Zeni::Point2i;

Controls::Controls()
: move_y(0.0f),
  move_x(0.0f),
  look_y(0.0f),
  look_x(0.0f),
  attack(false)
{}

Dimension::Dimension()
: width(0), height(0)
{}

Dimension::Dimension(int width_, int height_)
: width(width_), height(height_)
{}

void error_handle(const string &msg) {
  cout << "Error: " << msg << endl;
  throw new bad_exception;
}

pair<Point2i, Point2i> get_top_left_screen() {
  int x2 = Zeni::get_Window().get_width() / 2;
  int y2 = Zeni::get_Window().get_height() / 2;
  return make_pair(Point2i(0,0), Point2i(x2, y2));
}

pair<Point2i, Point2i> get_top_right_screen() {
  int x1 = (Zeni::get_Window().get_width() / 2) + 1;
  int x2 = Zeni::get_Window().get_width();
  int y2 = Zeni::get_Window().get_height() / 2;
  return make_pair(Point2i(x1,0), Point2i(x2, y2));
}

pair<Point2i, Point2i> get_bottom_left_screen() {  
  int x2 = Zeni::get_Window().get_width() / 2;
  int y1 = (Zeni::get_Window().get_height() / 2) + 1; 
  int y2 = Zeni::get_Window().get_height();
  return make_pair(Point2i(0,y1), Point2i(x2, y2));
}

pair<Point2i, Point2i> get_bottom_right_screen() {
  int x1 = (Zeni::get_Window().get_width() / 2) + 1;
  int x2 = Zeni::get_Window().get_width();
  int y1 = (Zeni::get_Window().get_height() / 2) + 1; 
  int y2 = Zeni::get_Window().get_height();
  return make_pair(Point2i(x1,y1), Point2i(x2, y2));
}
