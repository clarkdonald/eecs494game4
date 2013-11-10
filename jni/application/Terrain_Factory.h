//
//  Terrain_Factory.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef TERRAIN_FACTORY_H
#define TERRAIN_FACTORY_H

#include "Utility.h"
#include <Zeni/String.h>
#include <Zeni/Coordinate.h>

class Terrain;

Terrain * create_terrain(const Zeni::String &type_,
                         const Zeni::Point2f &position_);

#endif /* TERRAIN_FACTORY_H */
