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

Weapon* Archer::range(const float timestep)
{
  Arrow* projectile = NULL;

  if(std_cd <= 0)
  {
    Point2f pos = get_position();
    Vector2f size = get_size();

    pos += Vector2f(size.magnitude() * cos(facing), size.magnitude() * sin(facing)); // top left of arrow image

    projectile = new Arrow(pos, facing);
    
    std_cd = RANGE_CD;
  }
  else
    std_cd -= timestep;

  return projectile;
}

void Archer::spc_skill()
{
}

Archer::~Archer()
{
}