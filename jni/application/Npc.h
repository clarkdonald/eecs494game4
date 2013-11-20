//
//  Npc.h
//  game
//
//  Created by Donald Clark on 11/19/13.
//
//

#ifndef NPC_H
#define NPC_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Npc : public Game_Object {
  public:
    Npc(const Zeni::Point2f &position_,
        const Zeni::String &texture_,
        const Team &team_);
    
    void render() const override;
  
    const Team & get_team() const {return team;}
  
  private:
    Zeni::String texture;
    Team team;
};

#endif /* NPC_H */
