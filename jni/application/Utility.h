//
//  Utility.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef UTILITY_H
#define UTILITY_H

#include <utility>
#include <string>
#include <Zeni/Coordinate.h>

/** Game Information **/
const int NUM_PLAYERS = 4;

/** Size of units in the game **/
const float UNIT_LENGTH = 32.0f;
const Zeni::Vector2f OBJECT_SIZE = Zeni::Vector2f(UNIT_LENGTH, UNIT_LENGTH);

/** Relative size of entire video window **/
const std::pair<Zeni::Point2f, Zeni::Point2f> VIDEO_DIMENSION =
std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(854.0f, 480.0f));

/** Controls of the player **/
struct Controls {
  Controls();
  float move_y;
  float move_x;
  float look_y;
  float look_x;
  bool attack;
};

/** Parts of the Tree object for rendering **/
enum Two_Part_Object {
  TOP,
  BOTTOM
};

/** Parts of the House object for rendering **/
enum House_Part {
  DOOR,
  WINDOW_RIGHT,
  WINDOW_LEFT,
  BLUE_ROOF_UP_RIGHT_CORNER,
  BLUE_ROOF_UP_MIDDLE,
  BLUE_ROOF_UP_LEFT_CORNER,
  BLUE_ROOF_SIDE,
  BLUE_ROOF_MIDDLE_EDGE,
  BLUE_ROOF_MIDDLE,
  BLUE_ROOF_DOWN_RIGHT_CORNER_1,
  BLUE_ROOF_DOWN_RIGHT_CORNER_2,
  BLUE_ROOF_DOWN_LEFT_CORNER_1,
  BLUE_ROOF_DOWN_LEFT_CORNER_2
};

/** Dimension for the map **/
struct Dimension {
  Dimension();
  Dimension(int width_, int height_);
  int width;
  int height;
};

/** Prints out msg and throws bad_excetion **/
void error_handle(const std::string &msg);

/** Prints out msg and throws bad_excetion **/
void error_handle(const std::string &msg);

/** Coordinates for Top Left Screen Coordinates**/
std::pair<Zeni::Point2i, Zeni::Point2i> get_top_left_screen();

/** Coordinates for Top Right Screen Coordinates**/
std::pair<Zeni::Point2i, Zeni::Point2i> get_top_right_screen();

/** Coordinates for Bottom Left Screen Coordinates**/
std::pair<Zeni::Point2i, Zeni::Point2i> get_bottom_left_screen();

/** Coordinates for Bottom Rigth Screen Coordinates**/
std::pair<Zeni::Point2i, Zeni::Point2i> get_bottom_right_screen();


#endif /* UTILITY_H */
