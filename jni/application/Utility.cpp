//
//  Utility.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Utility.h"

using std::cerr;
using std::endl;
using std::bad_exception;
using std::string;

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
  cerr << "Error: " << msg << endl;
  throw new bad_exception;
}
