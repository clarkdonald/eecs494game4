#include "Stun_Arrow.h"

using namespace Zeni;
using namespace std;

Stun_Arrow::Stun_Arrow(const Zeni::Point2f &position_,
                       const float &theta,
                       const Team& team_)
: Arrow(position_, theta, team_)
{
  stun_attack = true;
  damage = 5.0f;
}

void Stun_Arrow::render() const {
  Game_Object::render("stun_arrow",
                      Color(),
                      move_vec.multiply_by(Vector2f(1.0f,-1.0f)).theta() + Global::pi_over_two);
}
