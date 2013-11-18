#include "Arrow.h"

using namespace Zeni;
using namespace std;

Arrow::Arrow(const Zeni::Point2f &position_, const float &theta)
  : Weapon(position_),
    move_vec(Vector2f(ARROW_SPD*cos(theta), ARROW_SPD*-sin(theta)))
{
  damage = 25.0f;
}

void Arrow::render() const
{

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