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
#include "Percent_Bar.h"
#include "Object_Info.h"
#include <zenilib.h>

class Npc : public Game_Object {
  public:
    Npc(const Zeni::Point2f &position_,
        const Zeni::String &texture_,
        const Team &team_);
    
    void render() const override;
  
    const Team & get_team() const {return team;}

    void set_deposit_pctg(const float &pctg_);

    void set_depositing(int depositing_) { depositing = depositing_; }

    bool can_deposit(int player_id) const { return (player_id == depositing) || (depositing == -1); }

    void set_hold_a(bool hold_a_) { hold_a =  hold_a_;}

    bool get_hold_a() const { return hold_a; }
  
  private:
    int depositing;
    float deposit_pctg;
    Percent_Bar deposit_indicator;
    Zeni::String texture;
    Team team;
    bool hold_a;
    Object_Info a_button;
};

#endif /* NPC_H */
