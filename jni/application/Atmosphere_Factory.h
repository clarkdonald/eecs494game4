//
//  Atmosphere_Factory.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef ATMOSPHERE_FACTORY_H
#define ATMOSPHERE_FACTORY_H

#include "Utility.h"
#include <Zeni/String.h>
#include <Zeni/Coordinate.h>

class Atmosphere;

Atmosphere * create_atmosphere(const Zeni::String &type_,
                               const Zeni::Point2f &position_);

#endif /* ATMOSPHERE_FACTORY_H */
