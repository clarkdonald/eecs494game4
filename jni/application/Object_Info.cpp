#include "Object_Info.h"
//#include <string>

using namespace Zeni;

Object_Info::Object_Info(const Point2f &position_, const Vector2f &size_)
: Game_Object(position_, size_)
{}

void Object_Info::render(const unsigned int &num_objects) const {
  auto pos = get_position();
  Game_Object::render("crystal");
  get_Fonts()["system_24"].render_text(String(" x" + std::to_string(num_objects)),
                                   Point2f(pos.x + 20, pos.y + 4), 
                                   get_Colors()["white"]);  
}
