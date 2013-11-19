#include "Health_Bar.h"

using namespace Zeni;

Health_Bar::Health_Bar(const Point2f &position_, const Vector2f &size_)
: Game_Object(position_, size_)
{}

void Health_Bar::render(const float &health_percentage) const {
  auto health_size = health_percentage * get_size();
  Point2f lower_right(get_position().x + health_size.x, get_position().y + get_size().y);
  render_image("health", // which texture to use
               get_position(), // upper-left corner
               lower_right, // lower-right corner
               0.0f, // rotation in radians
               1.0f, // scaling factor
               get_position() + 0.5f * health_size, // point to rotate & scale about
               false, // whether or not to horizontally flip the texture
               Color()); // what Color to "paint" the texture
  Game_Object::render("health_bar");
}
