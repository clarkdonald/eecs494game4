//
//  Environment_Factory.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef ENVIRONMENT_FACTORY_H
#define ENVIRONMENT_FACTORY_H

#include "Utility.h"
#include <Zeni/String.h>
#include <Zeni/Coordinate.h>

class Environment;

Environment * create_environment(const Zeni::String &type_,
                                 const Zeni::Point2f &position_);

#endif /* ENVIRONMENT_FACTORY_H */
