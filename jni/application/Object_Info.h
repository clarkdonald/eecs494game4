#ifndef OBJECT_INFO_H
#define OBJECT_INFO_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <Zeni/Coordinate.h>

class Object_Info : public Game_Object {
  public:
    Object_Info(const Zeni::Point2f &position_ = Zeni::Point2f(),
                const Zeni::Vector2f &size_ = Zeni::Vector2f(16.0f, 16.0f));
      
    void render(const unsigned int &num_objects) const;

  private:
    void render() const override {}
};

#endif /* OBJECT_INFO_H */