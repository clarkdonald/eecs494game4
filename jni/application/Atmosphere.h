//
//  Atmosphere.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <zenilib.h>

class Atmosphere : public Game_Object {
  public:
    Atmosphere(const Zeni::Point2f &position_, const Zeni::String &texture_);
    
    virtual ~Atmosphere() = 0;
  
    const Zeni::String get_texture() const {return texture;}
  
    virtual void update(const float &);

  private:
    Zeni::String texture;
};

#endif /* ATMOSPHERE_H */
