#ifndef HEAL_CIRCLE_H
#define HEAL_CIRCLE_H

#include "Game_Object.h"
#include "Utility.h"

class Heal_Circle : public Game_Object
{
public:
	Heal_Circle(const Zeni::Point2f&, Team team_);
	void render() const override;
  const Team & get_team() const{return team;}
private:
  Team team;
};

#endif