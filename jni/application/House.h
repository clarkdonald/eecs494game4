//
//  House.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef HOUSE_H
#define HOUSE_H

#include "Environment.h"
#include "Utility.h"
#include <zenilib.h>

class House : public Environment {
  public:
    House(const Zeni::Point2f &position_, const Zeni::String &texture_);
  
    void render() const override;
};

#endif /* HOUSE_H */
