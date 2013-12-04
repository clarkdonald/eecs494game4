#include "Object_Info.h"
#include <string>

using namespace Zeni;

Object_Info::Object_Info(const String &  texture_, const Point2f &position_, const Vector2f &size_)
: Game_Object(position_, size_), texture(texture_)
{}

void Object_Info::render(const unsigned int &num_objects) const {
  auto pos = get_position();
  Game_Object::render(texture);
  get_Fonts()["godofwar_20"].render_text(String(" x" + std::to_string(num_objects)),
                                   Point2f(pos.x + 22.0f, pos.y + 4.0f), 
                                   get_Colors()["white"]);  
}

void Object_Info::render(const Zeni::String &texture_) const {
  Game_Object::render(texture_);
}

void Object_Info::render() const {
  Game_Object::render(texture);
}
