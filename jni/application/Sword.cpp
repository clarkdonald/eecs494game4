#include "Sword.h"

using namespace Zeni;
using namespace std;

Sword::Sword(const Zeni::Point2f &position_, const float &theta)
  : Weapon(position_),
    dir(theta)
{
  damage = 50.0f;
}

void Sword::render() const
{
  //char msg[256];
  //sprintf(msg, "%0.02f %0.02f\n", get_position().x, get_position().y);
  //OutputDebugString(msg);

  //render_image("arrow",
  //             get_position(),              // upper left
  //             get_position() + get_size(), // bottom right
  //             dir,                         // rotation in radians
  //             1.0f,                        // scale factor
  //             get_center(),                // point to rotate about
  //             false,                       // flip horizontal
  //             Color());                    // texture color
  Game_Object::render("arrow", Color(), dir + Global::pi_over_two); // TODO: find sword.png and get a corrected angle
}

Sword::~Sword()
{
}