#ifndef PERCENT_BAR_H
#define PERCENT_BAR_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <Zeni/Coordinate.h>

class Percent_Bar : public Game_Object {
  public:
    Percent_Bar(const Zeni::Point2f &position_ = Zeni::Point2f(),
                const Zeni::Vector2f &size_ = Zeni::Vector2f(150.0f, 16.0f),
                const Zeni::String &texture_ = "health");    

    void render(const float &percentage) const;

    void render(const Zeni::Point2f &position_,
                const Zeni::Vector2f &size_);        

  private:    
    void render() const override {}

    Zeni::String bar_type;
};

#endif /* PERCENT_BAR_H */
