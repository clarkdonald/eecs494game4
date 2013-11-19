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

  private:
    Map_Manager();
    ~Map_Manager();
    
    int index;
    std::vector<std::string> files;
    std::map<char, Zeni::String> environment_charmap;
    std::map<char, Zeni::String> atmosphere_charmap;
    std::map<char, Zeni::String> terrain_charmap;
};

#endif /* MAP_MANAGER_H */
