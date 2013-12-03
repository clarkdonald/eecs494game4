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

#define CLOUD_SPD 10.0f

class Cloud : public Atmosphere {
  public:
    Cloud(const Zeni::Point2f &position_);
    
    void render() const override;
  
    void update(const float &) override;
};

#endif /* CLOUD_H */
