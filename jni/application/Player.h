//
//  Player.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Game_Object.h"

class Player : public Game_Object {
  public:
    virtual ~Player() = 0;
    virtual void render() = 0;
  
  private:
};

#endif /* PLAYER_H */
