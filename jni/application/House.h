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
    House(const Zeni::Point2f &position_, const House_Part &house_part_);
    
    Zeni::String get_texture() const override;

    void render() const override;
    
  private:
    House_Part house_part;
};

#endif /* HOUSE_H */
