//
//  Tree.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef TREE_H
#define TREE_H

#include "Environment.h"
#include "Utility.h"
#include <zenilib.h>

class Tree : public Environment {
  public:
    Tree(const Zeni::Point2f &position_, const Zeni::String &texture_);
    
    void render() const override;
};

#endif /* TREE_H */
