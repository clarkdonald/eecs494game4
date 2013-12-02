#include "Sword.h"

using namespace Zeni;
using namespace std;

Sword::Sword(const Zeni::Point2f &position_,
             const float &theta_,
             const Team& team_,
             Player* player_)
: Weapon(position_, 50.0f, team_),
  dir(theta_),
  owner(player_)
{
}

bool Sword::animation_over()
{
  return animation_timer.seconds() >= SWING_TIME;
}

void Sword::render() const {
  Point2f pos = get_position();
  Vector2f size = get_size();
  Vector2f face_vec = Vector2f(cos(dir), sin(dir));

  float theta = face_vec.multiply_by(Vector2f(1.0f,-1.0f)).theta() + Global::pi_over_two;   // facing angle
  theta = theta + (animation_timer.seconds() - SWING_TIME/2)/(SWING_TIME/2) * Global::pi/3;
  
  render_image("sword", // which texture to use
              pos + size.get_j() * 0.5, // upper-left corner
              pos + size.get_j() * 0.5 + size, // lower-right corner
              theta, // rotation in radians
              1.0f, // scaling factor
              pos + 0.5f * OBJECT_SIZE, // point to rotate & scale about
              false, // whether or not to horizontally flip the texture
              Color()); // what Color to "paint" the texture  
}

void Sword::remove_from_owner()
{
  owner->remove_weapon();
}