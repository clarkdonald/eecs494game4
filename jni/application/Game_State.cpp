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
#include "Archer.h"
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
  screen_coord_map.push_back(&get_top_left_screen);
  screen_coord_map.push_back(&get_bottom_left_screen);
  screen_coord_map.push_back(&get_top_right_screen);
  screen_coord_map.push_back(&get_bottom_right_screen);
  load_map(file_);
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
  for (auto it = players.begin(); it != players.end(); ++it)
    if (*it != nullptr) delete *it;
}

void Game_State::perform_logic() {
  const Time_HQ current_time = get_Timer_HQ().get_time();
  float processing_time = float(current_time.get_seconds_since(time_passed));
  time_passed = current_time;
  float time_step = processing_time;
  for (auto player : players)
  {
    Controls input = controls[player->get_uid()];
    Point2f pos = player->get_position();
    
    if ((pos.x + input.move_x) >= 0 || (pos.x + input.move_x) < dimension.width*UNIT_LENGTH)
      player->move_x(input.move_x, time_step);
    if ((pos.y + input.move_y) >= 0 || (pos.y + input.move_y) < dimension.height*UNIT_LENGTH)
      player->move_y(input.move_y, time_step);

	  Vector2f direction_vector(input.look_x, input.look_y);
	  player->turn_to_face(direction_vector.theta());

    if(input.attack)
    {
      //player->melee();

      Weapon* projectile = player->range();
      if( projectile )
        projectiles.push_back(projectile);
    }
  }

  for(auto it = projectiles.begin(); it != projectiles.end(); it++)
  {
    (*it)->update(time_step);
  }
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
  for (auto player : players) player->render();
  for (auto projectile : projectiles) projectile->render();
}

void Game_State::render(){
  // If we're done with the level, don't render anything
  if (gameover) return;

	//get_Video().set_2d(VIDEO_DIMENSION, true);
 
  // Top left corner
  for (auto player : players) {
    get_Video().set_2d_view(std::make_pair(player->get_position() - Vector2f(150.0f, 100.0f),
        player->get_position() + Vector2f(250.0f, 200.0f)), screen_coord_map[player->get_uid()](), true);
    render_all();
  }
}

void Game_State::create_tree(const Point2f &position) {
  if (position.y - UNIT_LENGTH < 0)
    error_handle("Cannot place tree in the specified location");
  
  environments.push_back(create_environment("Tree", position, BOTTOM));
  environments.push_back(create_environment("Tree", position - Point2f(0, UNIT_LENGTH), TOP));
}

void Game_State::create_house(const Point2f &position) {
  if ((position.y - UNIT_LENGTH*3) < 0 ||
      (position.x - UNIT_LENGTH) < 0 ||
      (position.x + UNIT_LENGTH) >= (dimension.width*UNIT_LENGTH))
  {
    error_handle("Cannot place house in the specified location");
  }
  
  environments.push_back(create_environment("House", position, DOOR));
  environments.push_back(create_environment("House", position - Point2f(UNIT_LENGTH, 0), WINDOW_LEFT));
  environments.push_back(create_environment("House", position + Point2f(UNIT_LENGTH, 0), WINDOW_RIGHT));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH), BLUE_ROOF_MIDDLE_EDGE));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH) + Point2f(UNIT_LENGTH, 0), BLUE_ROOF_DOWN_RIGHT_CORNER_1));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH) - Point2f(UNIT_LENGTH, 0), BLUE_ROOF_DOWN_LEFT_CORNER_1));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*2),
      BLUE_ROOF_MIDDLE));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*2) - Point2f(UNIT_LENGTH, 0), BLUE_ROOF_LEFT_SIDE));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*2) + Point2f(UNIT_LENGTH, 0), BLUE_ROOF_RIGHT_SIDE));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*3),
      BLUE_ROOF_UP_MIDDLE));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*3) + Point2f(UNIT_LENGTH, 0), BLUE_ROOF_UP_RIGHT_CORNER));
  environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*3) - Point2f(UNIT_LENGTH, 0), BLUE_ROOF_UP_LEFT_CORNER));
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
    players.push_back(create_player("Warrior", Point2f(start_x*UNIT_LENGTH, start_y*UNIT_LENGTH), i));
    controls.push_back(Controls());
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
      else if (Map_Manager::get_Instance().find_atmosphere(line[width])) {
        atmospheres.push_back(
          create_atmosphere(Map_Manager::get_Instance().get_atmosphere(line[width]),position));
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

void Game_State::execute_controller_code(const Zeni_Input_ID &id,
                                         const float &confidence,
                                         const int &action)
{
	switch(action) {
		/* player 1 */
    case 11:
      break;

    case 12:
			controls[0].move_x = confidence;
      break;

    case 13:
			controls[0].move_y = confidence;
      break;

    case 14:
			controls[0].look_x = confidence;
      break;

    case 15:
			controls[0].look_y = confidence;
      break;

    case 16:
      break;

    case 17:
      controls[0].attack = confidence > .5;
      break;

    case 10:
      break;

		/* player 2 */
		case 21:
      break;

    case 22:
			controls[1].move_x = confidence;
      break;

    case 23:
			controls[1].move_y = confidence;
      break;

    case 24:
			controls[1].look_x = confidence;
      break;

    case 25:
			controls[1].look_y = confidence;
      break;

    case 26:
      break;

    case 27:
			controls[1].attack = true;
      break;

    case 20:
      break;

		/* player 3 */
		case 31:
      break;

    case 32:
			controls[2].move_x = confidence;
      break;

    case 33:
			controls[2].move_y = confidence;
      break;

    case 34:
			controls[2].look_x = confidence;
      break;

    case 35:
			controls[2].look_y = confidence;
      break;

    case 36:
      break;

    case 37:
			controls[2].attack = true;
      break;

    case 30:
      break;

		/* player 4 */
		case 41:
      break;

    case 42:
			controls[3].move_x = confidence;
      break;

    case 43:
			controls[3].move_y = confidence;
      break;

    case 44:
			controls[3].look_x = confidence;
      break;

    case 45:
			controls[3].look_y = confidence;
      break;

    case 46:
      break;

    case 47:
			controls[3].attack = true;
      break;

    case 40:
      break;

    default:
      break;
	}
	
}
