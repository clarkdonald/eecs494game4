#include "Magic.h"

using namespace Zeni;
using namespace std;

Magic::Magic(const Zeni::Point2f &position_, const float &theta)
  : Weapon(position_),
    move_vec(Vector2f(MAGIC_SPD*cos(theta), MAGIC_SPD*sin(theta)))
{
  damage = 40.0f;
}

void Magic::render() const
{
  Game_Object::render("magic", Color(), move_vec.multiply_by(Vector2f(1.0f,-1.0f)).theta() + Global::pi_over_two);
}

void Magic::update(const float timestep)
{
  Point2f pos = get_position();
  pos += move_vec * timestep;
  set_position(pos);
}

Magic::~Magic()
{
}