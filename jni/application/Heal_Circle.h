#ifndef HEAL_CIRCLE_H
#define HEAL_CIRCLE_H

#include "Game_Object.h"

class Heal_Circle : public Game_Object
{
public:
	Heal_Circle(const Zeni::Point2f&);
	void render() const override;

private:
};

#endif