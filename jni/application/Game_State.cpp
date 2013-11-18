//
//  Game_State.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Game_State.h"
#include "Utility.h"
#include "Atmosphere.h"
#include "Atmosphere_Factory.h"
#include "Environment.h"
#include "Environment_Factory.h"
#include "Tree.h"
#include "Terrain.h"
#include "Terrain_Factory.h"
#include "Grass.h"
#include "Player.h"
#include "Player_Factory.h"
#include "Map_Manager.h"
#include "Warrior.h"				//for controls testing
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
	player = new Warrior(Point2f(100, 100));
}

Game_State::~Game_State() {
  for (auto it = grasss.begin(); it != grasss.end(); ++it)
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

	player -> handle_inputs(controls, time_step);
}

void Game_State::render_spawn_menu() {
  Text_Button warrior(Point2f(200.0f, 250.0f), Point2f(600.0f, 310.0f), "system_36_800x600", "Warrior");
  Text_Button archer(Point2f(200.0f, 330.0f), Point2f(600.0f, 390.0f), "system_36_800x600", "Archer");
  Text_Button mage(Point2f(200.0f, 410.0f), Point2f(600.0f, 470.0f), "system_36_800x600", "Mage");
  //warrior.
  warrior.render();
  archer.render();
  mage.render();
}

void Game_State::render_all() {
  for (auto grass : grasss) grass->render();
  for (auto terrain : terrains) terrain->render();
  for (auto environment : environments) environment->render();
  for (auto atmosphere : atmospheres) atmosphere->render();
  player -> render();
}

void Game_State::render(){
  // If we're done with the level, don't render anything
  if (gameover) return;

  // Todo: Each VIDEO_DIMENSION should actually be the coordinates 
  // for each player
	//get_Video().set_2d(VIDEO_DIMENSION, true);
 
  // Top left corner  
  get_Video().set_2d_view(VIDEO_DIMENSION, get_top_left_screen(), true);
  //if(player_not_dead)
  render_all();
  //else
  //render_spawn_menu();  

  // Top right corner
  get_Video().set_2d_view(make_pair(Point2f(0.0f,0.0f), Point2f(100.0f,100.0f)), get_top_right_screen(), true);
  render_all();

  // Bottom left corner
  get_Video().set_2d_view(VIDEO_DIMENSION, get_bottom_left_screen(), true);
  render_all();

  // Bottom right corner  
  get_Video().set_2d_view(VIDEO_DIMENSION, get_bottom_right_screen(), true);    
  render_all();    
}

void Game_State::create_tree(const Point2f &position) {
  environments.push_back(create_environment("Tree", position, BOTTOM));
  if (position.y - UNIT_LENGTH < 0) error_handle("Cannot place tree in the specified location");
  environments.push_back(create_environment("Tree", position - Point2f(0, UNIT_LENGTH), TOP));
}

void Game_State::create_house(const Point2f &position) {
  environments.push_back(create_environment("House", position, DOOR));
  environments.push_back(create_environment("House", position - Point2f(UNIT_LENGTH, 0), WINDOW_LEFT));
  environments.push_back(create_environment("House", position + Point2f(UNIT_LENGTH, 0), WINDOW_RIGHT));
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
      else if (line[width] == 't') {
        create_tree(position);
      }
      else if (line[width] == 'h') {
        create_house(position);
      }
      else if (Map_Manager::get_Instance().find_terrain(line[width])) {
        terrains.push_back(
          create_terrain(
            Map_Manager::get_Instance().get_terrain(line[width]),position));
      }
      else {
        string s = "Invalid character found: ";
        error_handle(s + line[width]);
      }
      grasss.push_back(new Grass(position));
    }
    ++height;
  }
  
  file.close();
}

void Game_State::execute_controller_code(const Zeni_Input_ID &id, const float &confidence, const int &action)
{
	switch(action) {
    case 1:
      break;

    case 2:
			controls.move_x = confidence;
      break;

    case 3:
			controls.move_y = confidence;
      break;

    case 4:
			controls.look_x = confidence;
      break;

    case 5:
			controls.look_y = confidence;
      break;

    case 6:
      break;

    case 7:
			controls.attack = true;
      break;

    case 0:
      break;

    default:
      break;
	}
}
