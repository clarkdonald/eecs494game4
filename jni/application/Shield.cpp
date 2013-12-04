#include "Shield.h"

using namespace Zeni;
using namespace std;


Shield::Shield(const Zeni::Point2f &position_,
               const float &theta_,
               const Team& team_,
               Player* player_)
: Weapon(position_, 50.0f, team_),
  owner(player_),
  dir(theta_)
{
  shield = true;
}

bool Shield::animation_over()
{
  return animation_timer.seconds() >= SKILL_DURATION;
}

void Shield::render() const {
  float face = owner->get_facing();
  Vector2f face_vec = Vector2f(cos(face), sin(face));

  Point2f pos = get_position();
  Vector2f size = get_size();

  float theta = face_vec.multiply_by(Vector2f(1.0f,-1.0f)).theta() + Global::pi_over_two;   // facing angle
  
  render_image("shield", // which texture to use
              pos, // upper-left corner
              pos + size, // lower-right corner
              theta, // rotation in radians
              1.0f, // scaling factor
              owner->get_center(), // point to rotate & scale about
              false, // whether or not to horizontally flip the texture
              Color()); // what Color to "paint" the texture 
}

void Shield::remove_from_owner()
{
  owner->remove_shield();
}