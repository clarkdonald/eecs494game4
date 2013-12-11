//
//  Instructions_State.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Instructions_State.h"
#include "Player_Includes.h"
#include "Player_Factory.h"
#include "Terrain_Includes.h"
#include "Terrain_Factory.h"
#include "Npc_Includes.h"
#include "Npc_Factory.h"
#include "Crystal.h"
#include "Game_Object.h"
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace Zeni;
using std::make_pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

Instructions_State::Instructions_State()
: tb(Point2f(),
     Point2f(800.0f, 600.0f),
     "system_36_800x600",
     "P U R P O S E\n"
     "Your goal is to find and capture crystals scattered randomly around "
     "the map and bring them back to your master.\n\n"
     "C O N T R O L S\n"
     "Left Stick: Move the explorer\n"
     "Right Stick: Look around, aim\n"
     "Right Trigger: Attack\n"
     "Start Button: Pause\n"
     "A Button: Hold down to deposit crystal to master\n"
     "Start Button: Pause entire game",
     Color()),
  timer_index(0),
  text_y_scroll(0.0f)
{
  tb.give_BG_Renderer(new Widget_Renderer_Color(get_Colors()["black"]));
  
  // set up map and players
  load_map("../assets/maps/tutorial.txt");
  
  for (int i = 0; i < 4; ++i) {
    text_timers.push_back(Chronometer<Time>());
  }
  
  // set up texts
  texts.push_back("Six companions fought many battles together.");
  texts.push_back("After years of victory, they finally wanted to split the wealth.");
  texts.push_back("However, there was dispute over how the wealth was to be split.");
  texts.push_back("The companions split into two sides.");
  texts.push_back("And forever, their relationship will never be the same..");
  
  // fire off first timer
  text_timers[timer_index].start();
}

Instructions_State::~Instructions_State() {
  for (auto terrain : terrains) delete terrain;
  for (auto crystal : crystals) delete crystal;
  delete player_blue0;
  delete player_blue1;
  delete player_red0;
  delete player_red1;
  delete npc_blue;
  delete npc_red;
}

void Instructions_State::on_key(const SDL_KeyboardEvent &event) {
  if (event.keysym.sym == SDLK_ESCAPE)
    if (event.state == SDL_PRESSED)
      get_Game().pop_state();
}

void Instructions_State::perform_logic() {
  // calculate game time
  const Time_HQ current_time = get_Timer_HQ().get_time();
  float processing_time = float(current_time.get_seconds_since(time_passed));
  time_passed = current_time;
  float time_step = processing_time;
  
  
}

void Instructions_State::render() {
  get_Video().set_2d(make_pair(Point2f(), Point2f(800.0f, 600.0f)), false);
  
  if (timer_index > text_timers.size()) {
    tb.render();
  }
  else {
    for (auto terrain : terrains) terrain->render();
    for (auto crystal : crystals) crystal->render();
    player_blue0->render();
    player_blue1->render();
    player_red0->render();
    player_red1->render();
    npc_blue->render();
    npc_red->render();
    
    auto text_y_scroll = 0.0f;            
    for(int i = 0; i < timer_index - 1; ++i) {
      get_Fonts()["godofwar_20"].render_text(String(texts[i]),
                                        Point2f(485.0f, text_y_scroll),
                                        get_Colors()["white"]);
      text_y_scroll += 25.0f;
    }

    if (text_timers[timer_index].seconds() > 2.0f) {      
      text_timers[++timer_index].start();
    }    
  }
}

void Instructions_State::load_map(const string &file_) {
  // logging
  cout << "Creating map: " << file_ << endl;
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
  
  // Get map information
  for (int height = 0; getline(file,line) && height < dimension.height;) {
    if (line.find('#') != std::string::npos) continue;
    for (int width = 0; width < line.length() && width < dimension.width; ++width) {
      Point2f position(UNIT_LENGTH*width, UNIT_LENGTH*height);
      
      terrains.push_back(create_terrain("Wood_Floor", position));
      
      if (line[width] == '.');
      else if (line[width] == '0') { // person 0
        player_blue0 = create_player("Mage", position, 0, BLUE);
      } else if (line[width] == '1') { // person 1
        player_blue1 = create_player("Archer", position, 1, BLUE);
      } else if (line[width] == '2') { // person 2
        player_red0 = create_player("Mage", position, 2, RED);
      } else if (line[width] == '3') { // person 3
        player_red1 = create_player("Warrior", position, 3, RED);
      } else if (line[width] == '4') { // npc blue
        npc_blue = create_npc("Blonde_Kid", position, BLUE);
      } else if (line[width] == '5') { // npc red
        npc_red = create_npc("Girl", position, RED);
      } else if (line[width] == 'L') { // left wall
        terrains.push_back(create_terrain("Left_Wall", position));
      } else if (line[width] == 'U') { // up wall
        terrains.push_back(create_terrain("Up_Wall", position));
      } else if (line[width] == 'D') { // down wall
        terrains.push_back(create_terrain("Down_Wall", position));
      } else if (line[width] == 'R') { // right wall
        terrains.push_back(create_terrain("Right_Wall", position));
      } else if (line[width] == 'l') { // up left wall
        terrains.push_back(create_terrain("Up_Left_Wall", position));
      } else if (line[width] == 'u') { // up right wall
        terrains.push_back(create_terrain("Up_Right_Wall", position));
      } else if (line[width] == 'd') { // down right wall
        terrains.push_back(create_terrain("Down_Right_Wall", position));
      } else if (line[width] == 'r') { // down left wall
        terrains.push_back(create_terrain("Down_Left_Wall", position));
      } else if (line[width] == 'x') { // door
        terrains.push_back(create_terrain("Tan_Wall_Door", position));
      } else if (line[width] == 'T') { // table
        terrains.push_back(create_terrain("Table", position));
        terrains.push_back(create_terrain("Flower", position));
      } else if (line[width] == 't') { // table
        terrains.push_back(create_terrain("Table", position));
      } else if (line[width] == 'c') { // chair
        terrains.push_back(create_terrain("Chair", position));
      } else if (line[width] == 's') { // shelves
        terrains.push_back(create_terrain("Bookshelf", position));
      } else if (line[width] == 'b') { // bed
        terrains.push_back(create_terrain("Bed", position));
      } else if (line[width] == 'z') { // dresser
        position.y -= (UNIT_LENGTH/2.0f);
        terrains.push_back(create_terrain("Dresser", position));
      } else if (line[width] == 'i') { // chest
        terrains.push_back(create_terrain("Chest", position));
      } else if (line[width] == 'k') { // crystal
        crystals.push_back(new Crystal(position));
      } else {
        string s = "Invalid character found in map: ";
        error_handle(s);
      }
    }
    ++height;
  }
}

void Instructions_State::load_scripted_movement() {
  
}
