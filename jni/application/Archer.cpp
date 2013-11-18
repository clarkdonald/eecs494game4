#include "Archer.h"
#include "Arrow.h"

using namespace Zeni;
using namespace std;

Archer::Archer(const Zeni::Point2f &position_, const int &uid_)
  : Player(position_, uid_)
{
  max_hp = 150.0f;
  hp = max_hp;
}

void Archer::render() const
{
	Game_Object::render("downidle");
}

Weapon* Archer::range()
{
  Arrow* projectile = NULL;
  if(can_attack)
  {
    Point2f pos = get_center();
    Vector2f size = get_size();

    pos += Vector2f(size.magnitude() * cos(facing), size.magnitude() * -sin(facing)) * 2; // this is the center of the arrow
    pos -= size * 0.5f; // top left corner of arrow image

    projectile = new Arrow(pos, facing);

    can_attack = false;
  }
  return projectile;
}

void Archer::spc_skill()
{
}

Archer::~Archer()
{
}