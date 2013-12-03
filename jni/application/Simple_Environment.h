//
//  Simple_Environment.h
//  game
//
//  Created by Donald Clark on 12/3/13.
//
//

#ifndef SIMPLE_ENVIRONMENT_H
#define SIMPLE_ENVIRONMENT_H

#include "Environment.h"
#include "Utility.h"
#include <zenilib.h>

class Simple_Environment : public Environment {
  public:
    Simple_Environment(const Zeni::Point2f &position_, const Zeni::String &texture_);
    
    void render() const override;
};

#endif /* SIMPLE_ENVIRONMENT_H */
