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
: move_forward(false),
  move_left(false),
  move_back(false),
  move_right(false),
  look_forward(false),
  look_left(false),
  look_back(false),
  look_right(false),
  attack(false)
{}

Dimension::Dimension()
: width(0), height(0)
{}

Dimension::Dimension(int width_, int height_)
: width(width_), height(height_)
{}

void error_handle(const string &msg) {
  std::cout << "Error: " << msg << endl;
  throw new bad_exception;
}
