//
//  Npc_Factory.h
//  game
//
//  Created by Donald Clark on 11/19/13.
//
//

#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "Utility.h"
#include <Zeni/String.h>
#include <Zeni/Coordinate.h>

class Npc;

Npc * create_npc(const Zeni::String &type_,
                 const Zeni::Point2f &position_,
                 const Team &team_);

#endif /* NPC_FACTORY_H */
