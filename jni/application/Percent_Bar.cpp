#include "Percent_Bar.h"

using namespace Zeni;

Percent_Bar::Percent_Bar(const Point2f &position_, const Vector2f &size_, const String &texture_)
: Game_Object(position_, size_), bar_type(texture_)
{}

void Percent_Bar::render(const float &percentage) const {
  auto bar_size = percentage * get_size();
  Point2f lower_right(get_position().x + bar_size.x, get_position().y + get_size().y);
  render_image(bar_type, // which texture to use
               get_position(), // upper-left corner
               lower_right, // lower-right corner
               0.0f, // rotation in radians
               1.0f, // scaling factor
               get_position() + 0.5f * bar_size, // point to rotate & scale about
               false, // whether or not to horizontally flip the texture
               Color()); // what Color to "paint" the texture
  Game_Object::render("health_bar");
}

void Percent_Bar::render(const Zeni::Point2f &position_, const Zeni::Vector2f &size_) {
  render_image(bar_type, // which texture to use
               position_, // upper-left corner
               position_ + size_, // lower-right corner
               0.0f, // rotation in radians
               1.0f, // scaling factor
               get_position() + 0.5f * size_, // point to rotate & scale about
               false, // whether or not to horizontally flip the texture
               Color()); // what Color to "paint" the texture
}
