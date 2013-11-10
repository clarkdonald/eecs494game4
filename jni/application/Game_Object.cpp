//
//  Game_Object.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Game_Object.h"

using namespace Zeni;

Game_Object::Game_Object(const Point2f &position_)
: position(position_), size(OBJECT_SIZE)
{}

bool Game_Object::pseudo_touching(const Game_Object &rhs) const {
  const Vector2f dist_vec = position - rhs.position + 0.5f * (size - rhs.size);
  const float dist2 = dist_vec * dist_vec * 1.3f;
  const float radius_sum = get_radius() + rhs.get_radius();
  return dist2 < radius_sum * radius_sum;
}

bool Game_Object::touching(const Game_Object &rhs) const {
  float distance = UNIT_LENGTH - 3.0f;
  float centerX = get_position().x + (get_size().x / 2.0f);
  float centerY = get_position().y + (get_size().y / 2.0f);
  float rhsCenterX = rhs.get_position().x + (rhs.get_size().x / 2.0f);
  float rhsCenterY = rhs.get_position().y + (rhs.get_size().y / 2.0f);
  
  if ((abs(centerX - rhsCenterX) < distance) &&
      (abs(centerY - rhsCenterY) < distance))
    return true;
  return false;
}

const Point2f & Game_Object::get_position() const {
  return position;
}

const Vector2f & Game_Object::get_size() const {
  return size;
}

const float Game_Object::get_radius() const {
  return 0.5f * size.magnitude();
}

void Game_Object::set_position(const Point2f& position_) {
  position = position_;
}

void Game_Object::render(const String &texture, const Color &filter) const {
  render_image(texture, // which texture to use
               position, // upper-left corner
               position + size, // lower-right corner
               0.0f, // rotation in radians
               1.0f, // scaling factor
               position + 0.5f * size, // point to rotate & scale about
               false, // whether or not to horizontally flip the texture
               filter); // what Color to "paint" the texture
}
