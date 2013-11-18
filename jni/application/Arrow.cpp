#include "Arrow.h"

using namespace Zeni;
using namespace std;

Arrow::Arrow(const Zeni::Point2f &position_)
  : Weapon(position_)
{
  damage = 25.0f;
}

void Arrow::render()
{
}

Arrow::~Arrow()
{
}