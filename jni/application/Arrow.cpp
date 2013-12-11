#include "Arrow.h"

using namespace Zeni;
using namespace std;

Arrow::Arrow(const Zeni::Point2f &position_,
             const float &theta,
             const Team& team_)
: Weapon(position_, 25.0f, team_, SMALL_SIZE*2),
  move_vec(Vector2f(ARROW_SPD*cos(theta), ARROW_SPD*sin(theta)))
{}

void Arrow::render() const {
  String str = get_color_str();

  Game_Object::render(str + "arrow",
                      Color(),
                      move_vec.multiply_by(Vector2f(1.0f,-1.0f)).theta() + Global::pi_over_two);
}

void Arrow::update(const float timestep) {
  Point2f pos = get_position();
  pos += move_vec * timestep;
  set_position(pos);
}
