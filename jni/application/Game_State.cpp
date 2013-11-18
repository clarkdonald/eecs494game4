//
//  Game_State.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Game_State.h"
#include "Utility.h"
#include "Dirt.h"
#include "Atmosphere.h"
#include "Atmosphere_Factory.h"
#include "Environment.h"
#include "Environment_Factory.h"
#include "Terrain.h"
#include "Terrain_Factory.h"
#include "Player.h"
#include "Player_Factory.h"
#include "Map_Manager.h"
#include <utility>
#include <fstream>
#include <map>
#include <vector>

using namespace Zeni;
using namespace Zeni::Collision;
using std::make_pair;
using std::string;
using std::getline;
using std::ifstream;
using std::bad_exception;
using std::to_string;
using std::map;
using std::vector;
using std::cerr;
using std::endl;

Game_State::Game_State(const std::string &file_)
: gameover(false)
{
  load_map(file_);
}

Game_State::~Game_State() {
  for (auto it = dirts.begin(); it != dirts.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = terrains.begin(); it != terrains.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = atmospheres.begin(); it != atmospheres.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = environments.begin(); it != environments.end(); ++it)
    if (*it != nullptr) delete *it;
}

void Game_State::perform_logic() {
  const Time_HQ current_time = get_Timer_HQ().get_time();
  float processing_time = float(current_time.get_seconds_since(time_passed));
  time_passed = current_time;
  float time_step = processing_time;
}

void Game_State::render(){
  // If we're done with the level, don't render anything
  if (gameover) return;

  get_Video().set_2d(VIDEO_DIMENSION, true);
  for (auto dirt : dirts) dirt->render();
  for (auto terrain : terrains) terrain->render();
  for (auto environment : environments) environment->render();
  for (auto atmosphere : atmospheres) atmosphere->render();
}

void Game_State::load_map(const std::string &file_) {
  ifstream file(file_);
  
  // Check if file exists
  if (!file.is_open()) {
    string s = "File does not exist: ";
    error_handle(s + file_);
  }
  
  // Get dimensions of map
  if (!(file >> dimension.height)) error_handle("Could not input height");
  if (!(file >> dimension.width)) error_handle("Could not input width");
  
  // Get starting location of players
  int start_y, start_x;
  for (int i = 0; i < NUM_PLAYERS; ++i) {
    if (!(file >> start_y))
      error_handle("Could not input starting y");
    if (start_y < 0 || start_y >= dimension.height)
      error_handle("Invalid start y");
    if (!(file >> start_x))
      error_handle("Could not input starting x");
    if (start_x < 0 || start_x >= dimension.width)
      error_handle("Invalid start x");
    // TODO: create player at location
  }

  // Get map information
  string line;
  getline(file,line); // waste a newline
  for (int height = 0; getline(file,line) && height < dimension.height;) {
    if (line.find('#') != std::string::npos) continue;
    for (int width = 0; width < line.length() && width < dimension.width; ++width) {
      Point2f position(UNIT_LENGTH*width, UNIT_LENGTH*height);
      if (line[width] == '.');
      else if (Map_Manager::get_Instance().find_terrain(line[width])) {
        terrains.push_back(
          create_terrain(
            Map_Manager::get_Instance().get_terrain(line[width]),position));
      }
      else {
        string s = "Invalid character found: ";
        error_handle(s + line[width]);
      }
      dirts.push_back(new Dirt(position));
    }
    ++height;
  }
  
  file.close();
}
