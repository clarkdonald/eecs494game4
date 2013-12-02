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
#include "Percent_Bar.h"
#include "Player_Factory.h"
#include "Map_Manager.h"
#include "Crystal.h"
#include "Spawn_Menu.h"
#include <utility>
#include <fstream>
#include <map>
#include <vector>
#include <random>
#include <sstream>

using namespace Zeni;
using namespace Zeni::Collision;
using std::stringstream;
using std::make_pair;
using std::cout;
using std::string;
using std::getline;
using std::ifstream;
using std::bad_exception;
using std::to_string;
using std::map;
using std::vector;
using std::cerr;
using std::endl;
using std::to_string;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::istringstream;

Player_Wrapper::Player_Wrapper(Player *player_, const int &uid_)
: player(player_), uid(uid_) 
{
}
  
Player_Wrapper::~Player_Wrapper() {
  if (player != nullptr) delete player;
}

Player_Info::Player_Info(const Zeni::Point2f &start_position_, const Team &team_, Spawn_Menu * spawn_menu_)
: start_position(start_position_), spawn_menu(spawn_menu_), team(team_), up_axis_released(false), down_axis_released(false)
{}

Player_Info::~Player_Info() {
  if(spawn_menu != nullptr)
    delete spawn_menu;
}

Game_State::Game_State(const std::string &file_)
: gameover(false),
  vbo_ptr_floor(new Vertex_Buffer),
  vbo_ptr_lower(new Vertex_Buffer),
  vbo_ptr_middle(new Vertex_Buffer)
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
  for (auto it = collidable_environments.begin(); it != collidable_environments.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = projectiles.begin(); it != projectiles.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = player_wrappers.begin(); it != player_wrappers.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = player_infos.begin(); it != player_infos.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = npcs.begin(); it != npcs.end(); ++it)
    if (*it != nullptr) delete *it;
  for (auto it = crystals.begin(); it != crystals.end(); ++it)
    if (*it != nullptr) delete *it;
  delete vbo_ptr_floor;
  delete vbo_ptr_lower;
  delete vbo_ptr_middle;
}

void Game_State::perform_logic() {
  // calculate game time
  const Time_HQ current_time = get_Timer_HQ().get_time();
  float processing_time = float(current_time.get_seconds_since(time_passed));
  time_passed = current_time;
  float time_step = processing_time;
  
  // iterate through each player, updating its state
  for (auto player_wrapper : player_wrappers) {
    // get controls for each player
    Controls input = player_infos[player_wrapper->uid]->controls;

    if (player_wrapper->player->is_dead()) {
      float move_y = input.move_y;            
			if(move_y > 0.7f && player_infos[player_wrapper->uid]->down_axis_released) {
				player_infos[player_wrapper->uid]->down_axis_released = false;
        player_infos[player_wrapper->uid]->spawn_menu->move_down();
			}
      if(move_y < -0.7f && player_infos[player_wrapper->uid]->up_axis_released) {
				player_infos[player_wrapper->uid]->up_axis_released = false;
        player_infos[player_wrapper->uid]->spawn_menu->move_up();
			}

			if(move_y <= 0.2)
				player_infos[player_wrapper->uid]->down_axis_released = true;
			if(move_y >= -0.2)
				player_infos[player_wrapper->uid]->up_axis_released = true;

			if(input.A)
        player_infos[player_wrapper->uid]->spawn_menu->select_current_option();
      continue;
    }
    
    // check collision with terrain on movement for effects
    float move_x = input.move_x;
    float move_y = input.move_y;    
		bool is_submerged = false;
    
		if(abs(move_x) < .3) move_x = 0;
		if(abs(move_y) < .3) move_y = 0;
		
		for (auto terrain : terrains) {
      if (terrain->slow_player_down() && player_wrapper->player->touching_feet(*terrain)) {
        move_x *= 0.5f;
        move_y *= 0.5f;
				is_submerged = true;
        break;
      }
    }

		player_wrapper->player->set_submerged(is_submerged);

    // dodge logic for player
    //player_wrapper->player->stop_dodge(time_step);
    player_wrapper->player->update_dodge_timer(time_step);
    if(input.RB) {      
      if(!player_wrapper->player->is_dodging())
        player_wrapper->player->dodge();
    }
    if(player_wrapper->player->is_dodging()) {      
      move_x *= 8.0f;
      move_y *= 8.0f;      
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
      
      for (auto environment : collidable_environments) {
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
      
      for (auto environment : collidable_environments) {
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
    if (input.attack && !is_submerged) {
      // warrior melee sword attack
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
        melee->animation_timer.start();
        melees.push_back(melee);
      }

      // archer/mage ranged attack
      Weapon* projectile = player_wrapper->player->range();
      if (projectile != nullptr) projectiles.push_back(projectile);
    }

    // crystal depositing logic
    bool touching = false;
    if (input.A && player_wrapper->player->has_crystal()) {
      for (auto npc : npcs) {
        if (same_team(npc->get_team(), player_wrapper->player->get_team()) &&
            player_wrapper->player->pseudo_touching(*npc))
        {
          touching = true;
          if (!player_infos[player_wrapper->uid]->deposit_crystal_timer.is_running()) {
            player_infos[player_wrapper->uid]->deposit_crystal_timer.reset();
            player_infos[player_wrapper->uid]->deposit_crystal_timer.start();
          }
          else {
            if (player_infos[player_wrapper->uid]->deposit_crystal_timer.seconds() > DEPOSIT_TIME) {
              player_wrapper->player->drop_crystal();
              scores[player_wrapper->player->get_team()] += DEPOSIT_CRYSTAL_POINTS;
              --crystals_in_play;
              player_infos[player_wrapper->uid]->deposit_crystal_timer.stop();
            }
          }
        }
      }
      if (!touching && player_infos[player_wrapper->uid]->deposit_crystal_timer.is_running()) {
        player_infos[player_wrapper->uid]->deposit_crystal_timer.stop();
      }
    } else {
      if (player_infos[player_wrapper->uid]->deposit_crystal_timer.is_running())
        player_infos[player_wrapper->uid]->deposit_crystal_timer.stop();
    }
    
    // crystal pick up logic
    for (auto crystal = crystals.begin(); crystal != crystals.end();) {
      if (player_wrapper->player->touching(**crystal)) {
        player_wrapper->player->pick_up_crystal();
        delete *crystal;
        crystal = crystals.erase(crystal);
      } else {
        ++crystal;
      }
    }
  }
  
  // cloud movement logic
  for (auto atmosphere : atmospheres) {
    atmosphere->update(time_step);
    if (atmosphere->get_position().x + atmosphere->get_size().x >= dimension.width*UNIT_LENGTH) {
      Point2f pos = atmosphere->get_position();
      pos.x = 0.0f;
      atmosphere->set_position(pos);
    }
  }
  
  // iterate through each melee weapon, updating it
  for (auto melee = melees.begin(); melee != melees.end();) {
    if((*melee)->animation_over())
    {
      (*melee)->remove_from_owner();
      delete *melee;
      melee = melees.erase(melee);
    }
    else
      melee++;
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
        if (player_wrapper->player->is_dead()) {
          scores[(*projectile)->get_team()] += KILL_PLAYER_POINTS;
        }
        should_remove = true;
        break;
      }
      player_wrapper->player->update_blink_timer(time_step);
    }

    // do environment collision checks
    for (auto environment : collidable_environments) {
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
    if(!player_wrapper->player->is_dead()) continue;
    if (player_infos[player_wrapper->uid]->spawn_menu->is_option_selected()) {
      player_infos[player_wrapper->uid]->spawn_menu->clear_menu();
      crystals_in_play -= player_wrapper->player->get_crystals_held();
      Player *dead = player_wrapper->player;
      player_wrapper->player = create_player(String(player_infos[player_wrapper->uid]->spawn_menu->
                                             get_selected_option()),
                                             player_infos[player_wrapper->uid]->start_position, 
                                             player_wrapper->uid,
                                             player_wrapper->player->get_team());      
      delete dead;
    }
  }

  // respawn crystals
  if (crystals_in_play < total_num_crystals) respawn_crystal();
}

void Game_State::respawn_crystal() {
  // Set up random number generation
  random_device rd;
  mt19937 gen = mt19937(rd());
  uniform_int_distribution<> dis = uniform_int_distribution<>(0, crystal_locations.size()-1);
  
  while (crystals_in_play < total_num_crystals) {
    bool found = true;
    int index;
    do {
      index = dis(gen);
      cout << index << endl;
      for (auto crystal : crystals) {
        if (crystal->get_position().x == crystal_locations[index].x &&
            crystal->get_position().y == crystal_locations[index].y) {
          found = false;
          break;
        }
        else {
          found = true;
        }
      }
    } while (!found);
    crystals.push_back(new Crystal(crystal_locations[index]));
    ++crystals_in_play;
  }
}

void Game_State::render_spawn_menu(Player_Wrapper * player_wrapper) {  
  auto screen_coord = screen_coord_map[player_wrapper->uid]();
  get_Video().set_2d_view(std::make_pair(Point2f(screen_coord.first),
                                         Point2f(screen_coord.second)), 
                          screen_coord, 
                          false);
  player_infos[player_wrapper->uid]->spawn_menu->render();  
}

void Game_State::render_all(Player_Wrapper * player_wrapper) { 
  auto p_pos = player_wrapper->player->get_position();
  get_Video().set_2d_view(std::make_pair(p_pos - Vector2f(250.0f, 200.0f),
                                         p_pos + Vector2f(250.0f, 200.0f)), 
                      screen_coord_map[player_wrapper->uid](), 
                      false);
  
  // Render Map and Movable objects
  vbo_ptr_floor->render();
  vbo_ptr_lower->render();
  for (auto crystal : crystals) crystal->render();
  for (auto npc : npcs) npc->render();
  for (auto player_wrapper : player_wrappers) player_wrapper->player->render();
  for (auto projectile : projectiles) projectile->render();
  for (auto melee : melees) melee->render();
  vbo_ptr_middle->render();
  for (auto atmosphere : atmospheres) atmosphere->render();

  // Render Player health
  player_infos[player_wrapper->uid]->health_bar.set_position(p_pos - Vector2f(240.0f, 190.0f));
  player_infos[player_wrapper->uid]->health_bar.render(player_wrapper->player->get_hp_pctg());    

  // Render Player Score
  get_Fonts()["godofwar_20"].render_text(String("Crystals: " + to_string(
                                        scores[BLUE])),
                                        p_pos - Vector2f(240.0f,-150.0f),
                                        get_Colors()["blue"]);
  get_Fonts()["godofwar_20"].render_text(String("Crystals: " + to_string(
                                         scores[RED])),
                                         p_pos - Vector2f(240.0f,-175.0f),
                                         get_Colors()["red"]);

  // Render the number of crystals
  player_infos[player_wrapper->uid]->crystal_info.set_position(p_pos + Vector2f(190.0f,-190.0f));
  player_infos[player_wrapper->uid]->crystal_info.render(player_wrapper->player->get_crystals_held());

  // rendering crystal bar when depositing crystal at NPC
  if (player_infos[player_wrapper->uid]->deposit_crystal_timer.is_running()) {
    player_infos[player_wrapper->uid]->crystal_bar.set_position(p_pos - Vector2f(240.0f, 170.0f));
    player_infos[player_wrapper->uid]->crystal_bar.render(player_infos[player_wrapper->uid]->deposit_crystal_timer.seconds() / DEPOSIT_TIME);
  }
}

void Game_State::render(){
  // If we're done with the level, don't render anything
  if (gameover) return;
  
  for (auto player_wrapper : player_wrappers) {    
    if (player_wrapper->player->is_dead()) render_spawn_menu(player_wrapper);
    else render_all(player_wrapper);
  }
}

void Game_State::create_tree(const Point2f &position) {
  if (position.y - UNIT_LENGTH < 0)
    error_handle("Cannot place tree in the specified location");
  
  collidable_environments.push_back(create_environment("Tree", position, BOTTOM));
  environments.push_back(create_environment("Tree", position - Point2f(0, UNIT_LENGTH), TOP));
}

void Game_State::create_house(const Point2f &position) {
  if ((position.y - UNIT_LENGTH*3) < 0 ||
      (position.x - UNIT_LENGTH) < 0 ||
      (position.x + UNIT_LENGTH) >= (dimension.width*UNIT_LENGTH))
  {
    error_handle("Cannot place house in the specified location");
  }
  
  collidable_environments.push_back(create_environment("House", position, DOOR));
  collidable_environments.push_back(create_environment("House", position - Point2f(UNIT_LENGTH, 0), WINDOW_LEFT));
  collidable_environments.push_back(create_environment("House", position + Point2f(UNIT_LENGTH, 0), WINDOW_RIGHT));
  collidable_environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH), BLUE_ROOF_MIDDLE_EDGE));
  collidable_environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH) + Point2f(UNIT_LENGTH, 0), BLUE_ROOF_DOWN_RIGHT_CORNER_1));
  collidable_environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH) - Point2f(UNIT_LENGTH, 0), BLUE_ROOF_DOWN_LEFT_CORNER_1));
  collidable_environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*2),
      BLUE_ROOF_MIDDLE));
  collidable_environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*2) - Point2f(UNIT_LENGTH, 0), BLUE_ROOF_LEFT_SIDE));
  collidable_environments.push_back(create_environment("House", position - Point2f(0, UNIT_LENGTH*2) + Point2f(UNIT_LENGTH, 0), BLUE_ROOF_RIGHT_SIDE));
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
  string line;
  getline(file,line);
  istringstream sstream(line);
  if (line.find('#') != std::string::npos) {
    getline(file,line);
    istringstream temp(line);
    sstream.swap(temp);
  }
  if (!(sstream >> dimension.height)) error_handle("Could not input height");
  if (!(sstream >> dimension.width)) error_handle("Could not input width");
  
  // logging
  cout << "Map dimension (y,x): (" << dimension.height << ',' << dimension.width << ')' << endl;
  
  // Get starting location of players
  Team team;
  int start_y, start_x;
  for (int i = 0; i < NUM_PLAYERS && getline(file,line); ++i) {
    if (line.find('#') != std::string::npos) {--i; continue;}
    istringstream sstream(line);
    if (!(sstream >> start_y))
      error_handle("Could not input starting y for player");
    if (start_y < 0 || start_y >= dimension.height)
      error_handle("Invalid start y for player");
    if (!(sstream >> start_x))
      error_handle("Could not input starting x for player");
    if (start_x < 0 || start_x >= dimension.width)
      error_handle("Invalid start x for player");
    Point2f pos(start_x*UNIT_LENGTH, start_y*UNIT_LENGTH);
    team = (i < 2 ? BLUE : RED);
    scores[team] = 0;
    player_wrappers.push_back(new Player_Wrapper(create_player("Mage", pos, i, team), i));
    player_wrappers.back()->player->kill();
    player_infos.push_back(new Player_Info(pos, team, new Spawn_Menu(screen_coord_map[i]())));
    
    // logging
    cout << "Player " << i << " Location (y,x): (" << start_y << ',' << start_x << ')' << endl;
  }
  
  // Get starting location of npc
  String npc_type;
  for (int i = 0; i < NUM_PLAYERS && getline(file,line); i+=2) {
    if (line.find('#') != std::string::npos) {i -= 2; continue;}
    istringstream sstream(line);
    if (!(sstream >> start_y))
      error_handle("Could not input starting y for npc");
    if (start_y < 0 || start_y >= dimension.height)
      error_handle("Invalid start y for npc");
    if (!(sstream >> start_x))
      error_handle("Could not input starting x for npc");
    if (start_x < 0 || start_x >= dimension.width)
      error_handle("Invalid start x for npc");
    team = (i < 2 ? BLUE : RED);
    npc_type = (team == BLUE ? "Blonde_Kid" : "Girl");
    npcs.push_back(create_npc(npc_type, Point2f(start_x*UNIT_LENGTH, start_y*UNIT_LENGTH), team));
    
    // logging
    cout << npc_type << " Location (y,x): (" << start_y << ',' << start_x << ')' << endl;
  }
  
  // Get locations of crystals
  crystals_in_play = 0;
  int number_of_crystal_locations;
  {
    getline(file,line);
    istringstream sstream(line);
    if (line.find('#') != std::string::npos) {
      getline(file,line);
      istringstream temp(line);
      sstream.swap(temp);
    }
    if (!(sstream >> total_num_crystals)) error_handle("Could not input number of crystals in play");
    
    // logging
    cout << "Number of Crystals: " << total_num_crystals << endl;
    
    getline(file,line);
    istringstream temp(line);
    sstream.swap(temp);
    if (!(sstream >> number_of_crystal_locations)) error_handle("Could not input number of crystal locs");
    
    // logging
    cout << "Number of Crystal Locations: " << number_of_crystal_locations << endl;
  }
  for (int i = 0; i < number_of_crystal_locations && getline(file,line); ++i) {
    if (line.find('#') != std::string::npos) {--i; continue;}
    istringstream sstream(line);
    if (!(sstream >> start_y))
      error_handle("Could not input y for crystal location");
    if (start_y < 0 || start_y >= dimension.height)
      error_handle("Invalid y for crystal location");
    if (!(sstream >> start_x))
      error_handle("Could not input x for crystal location");
    if (start_x < 0 || start_x >= dimension.width)
      error_handle("Invalid x for crystal location");
    crystal_locations.push_back(Point2f(start_x*UNIT_LENGTH, start_y*UNIT_LENGTH));
    
    // logging
    cout << "Crystal " << i << " Location (y,x): (" << start_y << ',' << start_x << ')' << endl;
  }

  // Get map information
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
        error_handle(s);
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
  for (auto environment : collidable_environments)
    vbo_ptr_middle->give_Quadrilateral(create_quad_ptr(environment));
  
  // Spawn crystals
  respawn_crystal();

  // Logging
  cout << "Created Map!" << endl;
  
  file.close();
}

void Game_State::execute_controller_code(const Zeni_Input_ID &id,
                                         const float &confidence,
                                         const int &action)
{
	switch (action) {
		/* player 1 */
    case 101:
      break;

    case 102:
			player_infos[0]->controls.move_x = confidence;
      break;

    case 103:
			player_infos[0]->controls.move_y = confidence;
      break;

    case 104:
			player_infos[0]->controls.look_x = confidence;
      break;

    case 105:
			player_infos[0]->controls.look_y = confidence;
      break;

    case 106:
			player_infos[0]->controls.LT = (confidence == 1.0);
      break;

    case 107:
      player_infos[0]->controls.attack = confidence > 0.5f;
      break;

		case 108:
			player_infos[0]->controls.A = (confidence == 1.0);
			break;

    case 109:
      break;

		case 110:
			break;

		case 111:
			break;

		case 112:
			break;

		case 113:
			player_infos[0]->controls.RB = (confidence == 1.0);
			break;

		/* player 2 */
		case 201:
      break;

    case 202:
			player_infos[1]->controls.move_x = confidence;
      break;

    case 203:
			player_infos[1]->controls.move_y = confidence;
      break;

    case 204:
			player_infos[1]->controls.look_x = confidence;
      break;

    case 205:
			player_infos[1]->controls.look_y = confidence;
      break;

    case 206:
			player_infos[1]->controls.LT = (confidence == 1.0);
      break;

    case 207:
			player_infos[1]->controls.attack = confidence > 0.5f;
      break;

		case 208:
			player_infos[1]->controls.A = (confidence == 1.0);
			break;

    case 209:
      break;

		case 210:
			break;

		case 211:
			break;

		case 212:
			break;

		case 213:
			player_infos[1]->controls.RB = (confidence == 1.0);
			break;

		/* player 3 */
		case 301:
      break;

    case 302:
			player_infos[2]->controls.move_x = confidence;
      break;

    case 303:
			player_infos[2]->controls.move_y = confidence;
      break;

    case 304:
			player_infos[2]->controls.look_x = confidence;
      break;

    case 305:
			player_infos[2]->controls.look_y = confidence;
      break;

    case 306:
			player_infos[2]->controls.LT = (confidence == 1.0);
      break;

    case 307:
			player_infos[2]->controls.attack = confidence > 0.5f;
      break;

		case 308:
			player_infos[2]->controls.A = (confidence == 1.0);
			break;

    case 309:
      break;

		case 310:
			break;

		case 311:
			break;

		case 312:
			break;

		case 313:
			player_infos[2]->controls.RB = (confidence == 1.0);
			break;

		/* player 4 */
		case 401:
      break;

    case 402:
			player_infos[3]->controls.move_x = confidence;
      break;

    case 403:
			player_infos[3]->controls.move_y = confidence;
      break;

    case 404:
			player_infos[3]->controls.look_x = confidence;
      break;

    case 405:
			player_infos[3]->controls.look_y = confidence;
      break;

    case 406:
			player_infos[3]->controls.LT = (confidence == 1.0);
      break;

    case 407:
			player_infos[3]->controls.attack = confidence > 0.5f;
      break;

		case 408:
			player_infos[3]->controls.A = (confidence == 1.0);
			break;

    case 409:
      break;

		case 410:
			break;

		case 411:
			break;

		case 412:
			break;

		case 413:
			player_infos[3]->controls.RB = (confidence == 1.0);
			break;

    default:
      break;
	}
}
