//
//  Game_Object.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <zenilib.h>
#include "Utility.h"

class Game_Object {
  public:
  Game_Object(const Zeni::Point2f &position_, const Zeni::Vector2f &size_ = OBJECT_SIZE);
    
    virtual ~Game_Object() {}
    
    virtual void render() const = 0;
    
    bool pseudo_touching(const Game_Object &rhs) const;
    
    bool touching(const Game_Object &rhs) const;
    
    const Zeni::Point2f & get_position() const;

    const Zeni::Point2f & get_center() const;
    
    const Zeni::Vector2f & get_size() const;
    
    const float get_radius() const;
    
    void set_position(const Zeni::Point2f& position_);
    
  protected:
    void render(const Zeni::String &texture, const Zeni::Color &filter = Zeni::Color(), const float &theta = 0.0f) const;
    
  private:
    Zeni::Point2f position;
    Zeni::Vector2f size;
};

#endif /* GAME_OBJECT_H */
