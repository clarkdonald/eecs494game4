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
  vbo_ptr_grass = new Vertex_Buffer;
  vbo_ptr_terrain = new Vertex_Buffer;
  vbo_ptr_environment = new Vertex_Buffer;
  vbo_ptr_atmosphere = new Vertex_Buffer;       

  for (int i = 0; i < NUM_FILES; ++i) {
    string str = "../assets/maps/level" + std::to_string(i) + ".txt";
    files.push_back(str);
  }
  
  // load the character mapping for terrains
  //terrain_charmap['w'] = "Water";
  terrain_charmap['d'] = "Dirt";
  terrain_charmap['r'] = "Rock_Pile";
  terrain_charmap['s'] = "Stone_Road";
  terrain_charmap['w'] = "Wood_Floor";
  terrain_charmap['b'] = "Bush";
  
  // load the character mapping for atmosphere
  atmosphere_charmap['c'] = "Cloud";
}

Map_Manager::~Map_Manager() {
  delete vbo_ptr_grass;
  delete vbo_ptr_terrain;
  delete vbo_ptr_environment;
  delete vbo_ptr_atmosphere;
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

bool Map_Manager::find_atmosphere(char c) const {
  return atmosphere_charmap.find(c) != atmosphere_charmap.end();
}

const Zeni::String & Map_Manager::get_atmosphere(char c) const {
  map<char, String>::const_iterator it;
  if ((it = atmosphere_charmap.find(c)) == atmosphere_charmap.end()) {
    string s = "There is no atmosphere mapping to ";
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


Vertex_Buffer * Map_Manager::get_vbo_ptr_grass() {
  return vbo_ptr_grass;
}

Vertex_Buffer * Map_Manager::get_vbo_ptr_terrain() {
  return vbo_ptr_terrain;
}

Vertex_Buffer * Map_Manager::get_vbo_ptr_environment() {
  return vbo_ptr_environment;
}

Vertex_Buffer * Map_Manager::get_vbo_ptr_atmosphere() {
  return vbo_ptr_atmosphere;
}

