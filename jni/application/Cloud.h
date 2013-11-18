//
//  Cloud.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef CLOUD_H
#define CLOUD_H

#include "Atmosphere.h"
#include "Utility.h"
#include <zenilib.h>

class Cloud : public Atmosphere {
  public:
    Cloud(const Zeni::Point2f &position_);
    
    void render() const override;
};

#endif /* CLOUD_H */
