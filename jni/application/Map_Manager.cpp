//
//  Map_Manager.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Map_Manager.h"
#include "Utility.h"
#include <zenilib.h>

using namespace Zeni;
using std::string;
using std::cerr;
using std::endl;
using std::bad_exception;
using std::map;
using std::make_pair;
using std::pair;

Map_Manager& Map_Manager::get_Instance()
{
  static Map_Manager Map_Manager;
  return Map_Manager;
}

Map_Manager::Map_Manager()
: index(0)
{
  for (int i = 0; i < NUM_FILES; ++i) {
    string str = "../assets/maps/level" + std::to_string(i) + ".txt";
    files.push_back(str);
  }
  
  // load the character mapping for terrains
  terrain_charmap['w'] = "Water";
}

const int & Map_Manager::get_files_left() const {
  return index;
}

bool Map_Manager::empty() const {
  return (files.size() - index) <= 0;
}

void Map_Manager::reset() {
  index = 0;
}

bool Map_Manager::find_terrain(char c) const {
  return terrain_charmap.find(c) != terrain_charmap.end();
}

const String & Map_Manager::get_terrain(char c) const {
  map<char, String>::const_iterator it;
  if ((it = terrain_charmap.find(c)) == terrain_charmap.end()) {
    string s = "There is no terrain mapping to ";
    error_handle(s + c);
  }
  return it->second;
}

const std::string & Map_Manager::get_next() {
  if (empty()) error_handle("Map Manager is empty; cannot get next");
  return files[index++];
}

const std::string & Map_Manager::get_previous() {
  if (index == 0) error_handle("Map Manager index is 0; cannot get previous");
  --index;
  return files[index++];
}
