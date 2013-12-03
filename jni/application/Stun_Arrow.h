#ifndef STUN_ARROW_H
#define STUN_ARROW_H

#include "Arrow.h"

class Stun_Arrow : public Arrow {
  public:
    Stun_Arrow(const Zeni::Point2f&, const float&, const Team&);

    void render() const override;
    
};

#endif /* STUN_ARROW_H */