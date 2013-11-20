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
#include "Terrain.h"
#include "Terrain_Factory.h"
#include "Npc.h"
#include "Npc_Factory.h"
#include "Player.h"
#include "Health_Bar.h"
#include "Player_Factory.h"
#include "Map_Manager.h"
#include <utility>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace Zeni;
using namespace Zeni::Collision;
using std::stringstream;
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

Player_Wrapper::Player_Wrapper(Player *player_, const int &uid_)
: player(player_), uid(uid_)
{}
  
Player_Wrapper::~Player_Wrapper() {
  if (player != nullptr) delete player;
}

Player_Info::Player_Info(const Zeni::Point2f &start_position_, const Team &team_)
: start_position(start_position_),
  team(team_)
{}

Game_State::Game_State(const std::string &file_)
: total_num_crystals(0),
  crystals_in_play(0),
  gameover(false),
  vbo_ptr_floor(new Vertex_Buffer),
  vbo_ptr_lower(new Vertex_Buffer),
  vbo_ptr_middle(new Vertex_Buffer),
  vbo_ptr_upper(new Vertex_Buffer)
{
  // set up function pointers for split screen methods
  screen_coord_map.push_back(&get_top_left_screen);
  screen_coord_map.push_back(&get_bottom_left_screen);
  screen_coord_map.push_back(&get_top_right_screen);
  screen_coord_map.push_back(&get_bottom_right_screen);
  
  // load map from the input file
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
  for (auto it = projectiles.begin(); it != projectiles.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = player_wrappers.begin(); it != player_wrappers.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = player_infos.begin(); it != player_infos.end(); ++it)
    if (*it != nullptr) delete *it;
  delete vbo_ptr_floor;
  delete vbo_ptr_lower;
  delete vbo_ptr_middle;
  delete vbo_ptr_upper;
}

void Game_State::perform_logic() {
  // calculate game time
  const Time_HQ current_time = get_Timer_HQ().get_time();
  float processing_time = float(current_time.get_seconds_since(time_passed));
  time_passed = current_time;
  float time_step = processing_time;
  
  // iterate through each player, updating its state
  for (auto player_wrapper : player_wrappers) {
    if (player_wrapper->player->is_dead()) continue;
    
    // get controls for each player
    Controls input = player_infos[player_wrapper->uid]->controls;
    
    // check collision with terrain on movement for effects
    float move_x = input.move_x;
    float move_y = input.move_y;
    for (auto terrain : terrains) {
      if (terrain->slow_player_down() && player_wrapper->player->touching(*terrain)) {
        move_x *= 0.5f;
        move_y *= 0.5f;
        break;
      }
    }
    
    // check collision with environment/npc/player on movement
    // first check boundary collision, then env, then npc, then oppo player
    bool moved_back = false;
    float delta_x = player_wrapper->player->get_position().x + move_x;
    float delta_y = player_wrapper->player->get_position().y + move_y;
    if ((move_x > 0.0f &&
         delta_x < (dimension.width*UNIT_LENGTH - (UNIT_LENGTH - 1.0f))) ||
        (move_x < 0.0f &&
         delta_x > 0.0f))
    {
      // make an initial attempt at movement
      player_wrapper->player->move_x(move_x, time_step, true);
      
      for (auto environment : environments) {
        if (player_wrapper->player->touching(*environment)) {
          player_wrapper->player->move_x(-move_x, time_step, false);
          moved_back = true;
          break;
        }
      }
      if (!moved_back) {
        for (auto npc : npcs) {
          if (player_wrapper->player->touching(*npc)) {
            player_wrapper->player->move_x(-move_x, time_step, false);
            moved_back = true;
            break;
          }
        }
      }
      if (!moved_back) {
        for (auto player_check : player_wrappers) {
          if (player_check->player->is_dead() ||
              same_team(player_wrapper->player->get_team(), player_check->player->get_team()))
          {
            continue;
          }
          if (player_wrapper->player->touching(*(player_check->player))) {
            player_wrapper->player->move_x(-move_x, time_step, false);
            break;
          }
        }
      }
    }
    moved_back = false;
    if ((move_y > 0.0f &&
         delta_y < (dimension.height*UNIT_LENGTH - (UNIT_LENGTH - 1.0f))) ||
        (move_y < 0.0f &&
         delta_y > 0.0f))
    {
      // make an initial attempt at movement
      player_wrapper->player->move_y(move_y, time_step, true);
      
      for (auto environment : environments) {
        if (player_wrapper->player->touching(*environment)) {
          player_wrapper->player->move_y(-move_y, time_step, false);
          moved_back = true;
          break;
        }
      }
      if (!moved_back) {
        for (auto npc : npcs) {
          if (player_wrapper->player->touching(*npc)) {
            player_wrapper->player->move_y(-move_y, time_step, false);
            moved_back = true;
            break;
          }
        }
      }
      if (!moved_back) {
        for (auto player_check : player_wrappers) {
          if (player_check->player->is_dead() ||
              same_team(player_wrapper->player->get_team(), player_check->player->get_team()))
          {
            continue;
          }
          if (player_wrapper->player->touching(*(player_check->player))) {
            player_wrapper->player->move_y(-move_y, time_step, false);
            break;
          }
        }
      }
    }

    // directional logic for player
	  Vector2f direction_vector(input.look_x, input.look_y);
    if (direction_vector.magnitude() > 0.4f) // deadzone for right stick; magnitude : [0,1]
	    player_wrapper->player->turn_to_face(direction_vector.theta());
    
    // attack logic for player
    if (input.attack) {
      // Warrior melee sword attack
      Weapon* melee = player_wrapper->player->melee();
      if (melee != nullptr) {
        for (auto player_check : player_wrappers) {
          if (player_check->player->is_dead() ||
              same_team(player_wrapper->player->get_team(), player_check->player->get_team()))
          {
            continue;
          }
          if (melee->touching(*(player_check->player)))
            player_check->player->take_dmg(melee->get_damage());
        }
      }
      delete melee;

      // Archer/Mage ranged attack
      Weapon* projectile = player_wrapper->player->range();
      if (projectile != nullptr) projectiles.push_back(projectile);
    } else {
      player_wrapper->player->set_can_attack();
    }
  }
  
  // iterate through each projectile, updating it
  for (auto projectile = projectiles.begin(); projectile != projectiles.end();) {
    (*projectile)->update(time_step);

    bool should_remove = false;

    // do player collision checks 
    for (auto player_wrapper : player_wrappers) {
      if (player_wrapper->player->is_dead() ||
          same_team(player_wrapper->player->get_team(), (*projectile)->get_team()))
      {
        continue;
      }
      if ((*projectile)->touching(*(player_wrapper->player))) {
        player_wrapper->player->take_dmg((*projectile)->get_damage());
        should_remove = true;
        break;
      }
    }

    // do environment collision checks
    for (auto environment : environments) {
      if ((*projectile)->touching(*environment)) {
        should_remove = true;
        break;
      }
    }

    // do map boundary checks
    Point2f proj_pos = (*projectile)->get_center();
    if (proj_pos.x < 0.0f || proj_pos.x >= dimension.width*UNIT_LENGTH ||
       proj_pos.y < 0.0f || proj_pos.y >= dimension.height*UNIT_LENGTH)
    {
       should_remove = true;
    }

    if (should_remove) {
      delete *projectile;
      projectile = projectiles.erase(projectile);
    } else {
      projectile++;
    }
  }
  
  // respawn dead players
  for (auto player_wrapper : player_wrappers) {
    if (!player_wrapper->player->is_dead()) continue;
    Player *dead = player_wrapper->player;
    // TODO: logic to choose right player type
    player_wrapper->player = create_player("Mage", player_infos[player_wrapper->uid]->start_position, player_wrapper->uid, player_infos[player_wrapper->uid]->team);
    delete dead;
  }
}

void Game_State::render_spawn_menu() {
  Text_Button warrior(Point2f(200.0f, 250.0f), Point2f(600.0f, 310.0f), "system_36_800x600", "Warrior");
  Text_Button archer(Point2f(200.0f, 330.0f), Point2f(600.0f, 390.0f), "system_36_800x600", "Archer");
  Text_Button mage(Point2f(200.0f, 410.0f), Point2f(600.0f, 470.0f), "system_36_800x600", "Mage");
  warrior.render();
  archer.render();
  mage.render();
}

void Game_State::render_all() {
  vbo_ptr_floor->render();
  vbo_ptr_lower->render();
  vbo_ptr_middle->render();
  for (auto npc : npcs) npc->render();
  for (auto player_wrapper : player_wrappers) player_wrapper->player->render();
  for (auto projectile : projectiles) projectile->render();
  vbo_ptr_upper->render();
}

void Game_State::render(){
  // If we're done with the level, don't render anything
  if (gameover) return;
 
  for (auto player_wrapper : player_wrappers) {
    auto p_pos = player_wrapper->player->get_position();
    get_Video().set_2d_view(std::make_pair(p_pos - Vector2f(150.0f, 100.0f),
        p_pos + Vector2f(250.0f, 200.0f)), screen_coord_map[player_wrapper->uid](), false);
    render_all();
    player_infos[player_wrapper->uid]->health_bar.set_position(p_pos - Vector2f(140.0f, 90.0f));
    player_infos[player_wrapper->uid]->health_bar.render(player_wrapper->player->get_hp_pctg());
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
  
  // Set up number of crystals based on dimensions
  crystals_in_play = total_num_crystals = ((dimension.width * dimension.height / 1000) + 2);
  
  // Get starting location of players
  string line;
  Team team;
  int start_y, start_x;
  for (int i = 0; i < NUM_PLAYERS; ++i) {
    getline(file,line); // waste new line
    getline(file,line); // waste comment
    if (!(file >> start_y))
      error_handle("Could not input starting y for player");
    if (start_y < 0 || start_y >= dimension.height)
      error_handle("Invalid start y for player");
    if (!(file >> start_x))
      error_handle("Could not input starting x for player");
    if (start_x < 0 || start_x >= dimension.width)
      error_handle("Invalid start x for player");
    Point2f pos(start_x*UNIT_LENGTH, start_y*UNIT_LENGTH);
    team = (i < 2 ? WHITE : BLACK);
    player_wrappers.push_back(new Player_Wrapper(create_player("Mage", pos, i, team), i));
    player_infos.push_back(new Player_Info(pos, team));
  }
  
  // Get starting location of npc
  String npc_type;
  for (int i = 0; i < NUM_PLAYERS; i += 2) {
    getline(file,line); // waste new line
    getline(file,line); // waste comment
    if (!(file >> start_y))
      error_handle("Could not input starting y for npc");
    if (start_y < 0 || start_y >= dimension.height)
      error_handle("Invalid start y for npc");
    if (!(file >> start_x))
      error_handle("Could not input starting x for npc");
    if (start_x < 0 || start_x >= dimension.width)
      error_handle("Invalid start x for npc");
    Point2f pos(start_x*UNIT_LENGTH, start_y*UNIT_LENGTH);
    team = (i < 2 ? WHITE : BLACK);
    npc_type = (team == WHITE ? "Blonde_Kid" : "Girl");
    npcs.push_back(create_npc(npc_type, pos, team));
  }

  // Get map information
  getline(file,line); // waste a newline
  for (int height = 0; getline(file,line) && height < dimension.height;) {
    if (line.find('#') != std::string::npos) continue;
    for (int width = 0; width < line.length() && width < dimension.width; ++width) {
      Point2f position(UNIT_LENGTH*width, UNIT_LENGTH*height);

      // every space will always have a grass tile
      grasss.push_back(create_terrain("Grass", position));

      if (line[width] == '.');
      else if (line[width] == 't') {
        create_tree(position);
      } else if (line[width] == 'h') {
        create_house(position);
      } else if (Map_Manager::get_Instance().find_terrain(line[width])) {
        terrains.push_back(create_terrain(
            Map_Manager::get_Instance().get_terrain(line[width]),position));                  
      } else if (Map_Manager::get_Instance().find_atmosphere(line[width])) {
        atmospheres.push_back(
          create_atmosphere(Map_Manager::get_Instance().get_atmosphere(line[width]),position));
      } else {
        string s = "Invalid character found in map: ";
        error_handle(s + line[width]);
      }
    }
    ++height;
  }

  // Put objects into the Vertex_Buffer
  for (auto grass : grasss)
    vbo_ptr_floor->give_Quadrilateral(create_quad_ptr(grass));
  for (auto terrain : terrains)
    vbo_ptr_lower->give_Quadrilateral(create_quad_ptr(terrain));
  for (auto environment : environments)
     vbo_ptr_middle->give_Quadrilateral(create_quad_ptr(environment));
  for (auto atmosphere : atmospheres)
     vbo_ptr_upper->give_Quadrilateral(create_quad_ptr(atmosphere));
  
  file.close();
}

void Game_State::execute_controller_code(const Zeni_Input_ID &id,
                                         const float &confidence,
                                         const int &action)
{
	switch (action) {
		/* player 1 */
    case 11:
      break;

    case 12:
			player_infos[0]->controls.move_x = confidence;
      break;

    case 13:
			player_infos[0]->controls.move_y = confidence;
      break;

    case 14:
			player_infos[0]->controls.look_x = confidence;
      break;

    case 15:
			player_infos[0]->controls.look_y = confidence;
      break;

    case 16:
      break;

    case 17:
      player_infos[0]->controls.attack = confidence > 0.5f;
      break;

		case 18:
			break;

    case 10:
      break;

		/* player 2 */
		case 21:
      break;

    case 22:
			player_infos[1]->controls.move_x = confidence;
      break;

    case 23:
			player_infos[1]->controls.move_y = confidence;
      break;

    case 24:
			player_infos[1]->controls.look_x = confidence;
      break;

    case 25:
			player_infos[1]->controls.look_y = confidence;
      break;

    case 26:
      break;

    case 27:
			player_infos[1]->controls.attack = confidence > 0.5f;
      break;

		case 28:
			break;

    case 20:
      break;

		/* player 3 */
		case 31:
      break;

    case 32:
			player_infos[2]->controls.move_x = confidence;
      break;

    case 33:
			player_infos[2]->controls.move_y = confidence;
      break;

    case 34:
			player_infos[2]->controls.look_x = confidence;
      break;

    case 35:
			player_infos[2]->controls.look_y = confidence;
      break;

    case 36:
      break;

    case 37:
			player_infos[2]->controls.attack = confidence > 0.5f;
      break;

		case 38:
			break;

    case 30:
      break;

		/* player 4 */
		case 41:
      break;

    case 42:
			player_infos[3]->controls.move_x = confidence;
      break;

    case 43:
			player_infos[3]->controls.move_y = confidence;
      break;

    case 44:
			player_infos[3]->controls.look_x = confidence;
      break;

    case 45:
			player_infos[3]->controls.look_y = confidence;
      break;

    case 46:
      break;

    case 47:
			player_infos[3]->controls.attack = confidence > 0.5f;
      break;

		case 48:
			break;

    case 40:
      break;

    default:
      break;
	}
}
