#include "Sword.h"

using namespace Zeni;
using namespace std;

Sword::Sword(const Zeni::Point2f &position_,
             const float &theta_,
             const Team& team_)
: Weapon(position_, 50.0f, team_),
  dir(theta_)
{
}

void Sword::render() const {
  Vector2f face_vec = Vector2f(cos(dir), sin(dir));
  Game_Object::render("sword",
                      Color(),
                      face_vec.multiply_by(Vector2f(1.0f,-1.0f)).theta() - Global::pi_over_two); // TODO: find sword.png and get a corrected angle
}
