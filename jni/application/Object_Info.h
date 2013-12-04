#ifndef OBJECT_INFO_H
#define OBJECT_INFO_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <Zeni/Coordinate.h>

class Object_Info : public Game_Object {
  public:
    Object_Info(const Zeni::String &texture_ = "",
                const Zeni::Point2f &position_ = Zeni::Point2f(),
                const Zeni::Vector2f &size_ = Zeni::Vector2f(32.0f, 32.0f));

    //void set_texture(const std::string texture_)
      
    void render(const unsigned int &num_objects) const;

    void render(const Zeni::String &texture_) const;
  
    void render() const;

private:
    Zeni::String texture;
};

#endif /* OBJECT_INFO_H */