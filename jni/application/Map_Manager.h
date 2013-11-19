//
//  Map_Manager.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <zenilib.h>
#include <vector>
#include <map>
#include <string>

const int NUM_FILES = 1;

class Map_Manager {
  public:
    static Map_Manager& get_Instance();
    
    const int & get_files_left() const;
    
    bool empty() const;
    
    void reset();
    
    bool find_terrain(char c) const;
    
    const Zeni::String & get_terrain(char c) const;
  
    bool find_atmosphere(char c) const;
  
    const Zeni::String & get_atmosphere(char c) const;
  
    const std::string & get_next();
    
    const std::string & get_previous();

    Zeni::Vertex_Buffer * get_vbo_ptr_below();

    Zeni::Vertex_Buffer * get_vbo_ptr_above();
    
  private:
    Map_Manager();
    ~Map_Manager();

    // This is used for rendering the lower level of the map
    Zeni::Vertex_Buffer *vbo_ptr;

    // This is used for rendering the level above the movable objects (i.e. Atmosphere)
    Zeni::Vertex_Buffer *vbo_ptr2;
    
    int index;
    std::vector<std::string> files;
    std::map<char, Zeni::String> environment_charmap;
    std::map<char, Zeni::String> atmosphere_charmap;
    std::map<char, Zeni::String> terrain_charmap;
};

#endif /* MAP_MANAGER_H */
