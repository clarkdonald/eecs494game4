#include "Arrow.h"

using namespace Zeni;
using namespace std;

Arrow::Arrow(const Zeni::Point2f &position_, const float &theta)
  : Weapon(position_),
    move_vec(Vector2f(ARROW_SPD*cos(theta), ARROW_SPD*sin(theta)))
{
  damage = 25.0f;
}

void Arrow::render() const
{
  char msg[256];
  sprintf(msg, "%0.02f %0.02f\n", get_position().x, get_position().y);
  OutputDebugString(msg);

  //render_image("arrow",
  //             get_position(),              // upper left
  //             get_position() + get_size(), // bottom right
  //             move_vec.theta(),            // rotation in radians
  //             1.0f,                        // scale factor
  //             get_center(),                // point to rotate about
  //             false,                       // flip horizontal
  //             Color());                    // texture color
  Game_Object::render("arrow", Color(), move_vec.theta());
}

void Arrow::update(const float timestep)
{
  Point2f pos = get_position();
  pos += move_vec * timestep;
  set_position(pos);
}

Arrow::~Arrow()
{
}