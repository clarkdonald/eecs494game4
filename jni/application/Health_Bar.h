#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <Zeni/Coordinate.h>

class Health_Bar : public Game_Object {
  public:
    Health_Bar(const Zeni::Point2f &position_ = Zeni::Point2f(), const Zeni::Vector2f &size_ = Zeni::Vector2f(100.0f, 8.0f));        
      
    void render(const float &health_percentage) const;

  private:
    void render() const override {}
};

#endif /* HEALTH_BAR_H */
