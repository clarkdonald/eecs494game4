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

/** Dimension for the map **/
struct Dimension {
  Dimension();
  Dimension(int width_, int height_);
  int width;
  int height;
};

/** Prints out msg and throws bad_excetion **/
void error_handle(const std::string &msg);

#endif /* UTILITY_H */
