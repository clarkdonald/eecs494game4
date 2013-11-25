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
#include "zenilib.h"

class Terrain;
class Environment;
class Atmosphere;

/** Game Information **/
const int NUM_PLAYERS = 4;

/** Game Point System **/
const int DEPOSIT_CRYSTAL_POINTS = 1;
const int KILL_PLAYER_POINTS = 10;

/** Required crystal deposit duration time **/
const float DEPOSIT_TIME = 5.0f;

/** Size of units in the game **/
const float UNIT_LENGTH = 32.0f;
const Zeni::Vector2f OBJECT_SIZE = Zeni::Vector2f(UNIT_LENGTH, UNIT_LENGTH);
const Zeni::Vector2f SMALL_SIZE = Zeni::Vector2f(0.25f*UNIT_LENGTH, 0.25f*UNIT_LENGTH);
const Zeni::Vector2f LARGE_SIZE = Zeni::Vector2f(3*UNIT_LENGTH, 3*UNIT_LENGTH);

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
  bool A;
  bool attack;
  bool RB;
};

/** Team identifier **/
enum Team {
  RED,
  BLUE
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
  BLUE_ROOF_RIGHT_SIDE,
  BLUE_ROOF_LEFT_SIDE,
  BLUE_ROOF_MIDDLE_EDGE,
  BLUE_ROOF_MIDDLE,
  BLUE_ROOF_DOWN_RIGHT_CORNER_1,
  BLUE_ROOF_DOWN_RIGHT_CORNER_2,
  BLUE_ROOF_DOWN_LEFT_CORNER_1,
  BLUE_ROOF_DOWN_LEFT_CORNER_2
};

/** Parts of the Stone Road object for rendering **/
enum Stone_Road_Part {
  STONE_DOWN,
  STONE_DOWN_END,
  STONE_DOWN_LEFT,
  STONE_DOWN_RIGHT,
  STONE_HORIZONTAL,
  STONE_LEFT,
  STONE_LEFT_END,
  STONE_MIDDLE,
  STONE_RIGHT,
  STONE_RIGHT_END,
  STONE_UP,
  STONE_UP_END,
  STONE_UP_LEFT,
  STONE_UP_RIGHT,
  STONE_VERTICAL
};

/** Dimension for the map **/
struct Dimension {
  Dimension();
  Dimension(int width_, int height_);
  int width;
  int height;
};

Zeni::Quadrilateral<Zeni::Vertex2f_Texture> * create_quad_ptr(const Terrain * const terrain_ptr);
Zeni::Quadrilateral<Zeni::Vertex2f_Texture> * create_quad_ptr(const Environment * const terrain_ptr);
Zeni::Quadrilateral<Zeni::Vertex2f_Texture> * create_quad_ptr(const Atmosphere * const terrain_ptr);

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

/** Check if two teams are the same **/
bool same_team(const Team &lhs, const Team &rhs);

#endif /* UTILITY_H */
