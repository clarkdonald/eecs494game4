//
//  Game_Object.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Game_Object.h"

using namespace Zeni;

Game_Object::Game_Object(const Point2f &position_,
                         const Vector2f &size_,
                         const Collider &collider_)
: position(position_), size(size_), collider(collider_)
{}

bool Game_Object::pseudo_touching(const Game_Object &rhs) const {
  const Vector2f dist_vec = position - rhs.position + 0.5f * (size - rhs.size);
  const float dist2 = dist_vec * dist_vec * 1.3f;
  const float radius_sum = get_radius() + rhs.get_radius();
  return dist2 < radius_sum * radius_sum;
}

bool Game_Object::collide1(const Game_Object &square1,
                           const Game_Object &square2) const
{
  float centerX1 = square1.position.x + (square1.size.x / 2.0f);
  float centerY1 = square1.position.y + (square1.size.y / 2.0f);
  float centerX2 = square2.position.x + (square2.size.x / 2.0f);
  float centerY2 = square2.position.y + (square2.size.y / 2.0f);
  float distance = UNIT_LENGTH - 3.0f;
  
  if ((fabs(centerX1 - centerX2) < distance) &&
      (fabs(centerY1 - centerY2) < distance))
  {
    return true;
  }
  
  return false;
}

bool Game_Object::collide2(const Game_Object &circle1,
                           const Game_Object &circle2) const
{
  float centerX1 = circle1.position.x + (circle1.size.x / 2.0f);
  float centerY1 = circle1.position.y + (circle1.size.y / 2.0f);
  float centerX2 = circle2.position.x + (circle2.size.x / 2.0f);
  float centerY2 = circle2.position.y + (circle2.size.y / 2.0f);
  float dx = centerX2 - centerX1;
  float dy = centerY2 - centerY1;
  float radii = (size.x / 2.0f) + (circle2.size.x / 2.0f);
  
  if (((dx * dx) + (dy * dy)) < (radii * radii)) return true;
  
  return false;
}

bool Game_Object::collide3(const Game_Object &circle,
                           const Game_Object &rectangle) const
{
  float circleDistanceX = fabs(circle.position.x - rectangle.position.x);
  float circleDistanceY = fabs(circle.position.y - rectangle.position.y);
  float circleRadius = circle.size.x / 4.0f;
  float rectWidth = (rectangle.collider == RECTANGLE ? rectangle.size.x : rectangle.size.x / 2.0f);
  float rectHeight = rectangle.size.y;
  
  if (circleDistanceX > (rectWidth/2 + circleRadius) ||
      circleDistanceY > (rectHeight/2 + circleRadius))
  {
    return false;
  }
  
  if (circleDistanceX <= (rectWidth/2) ||
      circleDistanceY <= (rectHeight/2))
  {
    return true;
  }
  
  return pow(circleDistanceX - rectWidth/2, 2.0f) +
    pow(circleDistanceY - rectHeight/2, 2.0f) <= (circleRadius * circleRadius);
}

bool Game_Object::collide4(const Game_Object &rectangle1,
                           const Game_Object &rectangle2) const
{
  float rectangle1X1;
  float rectangle1X2;
  float rectangle2X1;
  float rectangle2X2;
  float rectangle1Y1 = rectangle1.position.y + 2.0f;
  float rectangle1Y2 = rectangle1.position.y + size.y;
  float rectangle2Y1 = rectangle2.position.y;
  float rectangle2Y2 = rectangle2.position.y + rectangle2.size.y;
  float rectangle1CenterX = rectangle1.position.x + (rectangle1.size.x / 2.0f);
  float rectangle2CenterX = rectangle2.position.x + (rectangle2.size.x / 2.0f);
  float rectangle1WidthFactor = rectangle1.size.x / 4.0f;
  float rectangle2WidthFactor = rectangle2.size.x / 4.0f;
  
  // set up dimensions for this
  switch (rectangle1.collider) {
    case SQUARE:
      rectangle1X1 = rectangle1.position.x;
      rectangle1X2 = rectangle1.position.x + rectangle1.size.x;
      break;
      
    case RECTANGLE:
      rectangle1X1 = rectangle1CenterX - rectangle1WidthFactor;
      rectangle1X2 = rectangle1CenterX + rectangle1WidthFactor;
      break;
      
    default:
      return false;
  }
  
  // set up dimensions for rectangle2
  switch (rectangle2.collider) {
    case SQUARE:
      rectangle2X1 = rectangle2.position.x;
      rectangle2X2 = rectangle2.position.x + rectangle2.size.x;
      break;
      
    case RECTANGLE:
      rectangle2X1 = rectangle2CenterX - rectangle2WidthFactor;
      rectangle2X2 = rectangle2CenterX + rectangle2WidthFactor;
      rectangle2Y2 -= 4.0f;
      break;
      
    default:
      return false;
  }
  
  if (rectangle1X1 < rectangle2X2 &&
      rectangle1X2 > rectangle2X1 &&
      rectangle1Y1 < rectangle2Y2 &&
      rectangle1Y2 > rectangle2Y1)
  {
    return true;
  }
  
  return false;
}

bool Game_Object::touching(const Game_Object &rhs) const {
  // optimized square-square collision detection
  if (collider == SQUARE && rhs.collider == SQUARE) return collide1(*this, rhs);

  // optimized circle-circle collision detection
  if (collider == CIRCLE && rhs.collider == CIRCLE) return collide2(*this, rhs);
  
  // optimized circle-rectangle collision detection
  if (collider == CIRCLE || rhs.collider == CIRCLE) {
    if (collider == CIRCLE) return collide3(*this, rhs);
    return collide3(rhs, *this);
  }
  
  // optimized rectangle-rectangle collision detection
  return collide4(*this, rhs);
}

const Point2f & Game_Object::get_position() const {
  return position;
}

Point2f Game_Object::get_center() const {
  return position + size * 0.5f;
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

void Game_Object::render(const String &texture, const Color &filter, const float &theta) const {
  render_image(texture, // which texture to use
               position, // upper-left corner
               position + size, // lower-right corner
               theta, // rotation in radians
               1.0f, // scaling factor
               position + 0.5f * size, // point to rotate & scale about
               false, // whether or not to horizontally flip the texture
               filter); // what Color to "paint" the texture  
}
