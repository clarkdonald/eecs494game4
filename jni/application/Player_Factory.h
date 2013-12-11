//
//  Player_Factory.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "Utility.h"
#include <Zeni/String.h>
#include <Zeni/Coordinate.h>

class Player;

Player * create_player(const Zeni::String &type_,
                       const Zeni::Point2f &position_,
                       const int &uid_,
                       const Team &team_,
                       const Zeni::Vector2f &size_ = OBJECT_SIZE);

#endif /* PLAYER_FACTORY_H */
