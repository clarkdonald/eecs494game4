//
//  Instructions_State.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Instructions_State.h"
#include <utility>

using namespace Zeni;
using std::make_pair;

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
     "P Key: Restart level\n"
     "ESC Key: Pause entire game",
     Color())
{
  tb.give_BG_Renderer(new Widget_Renderer_Color(get_Colors()["black"]));
}

void Instructions_State::on_key(const SDL_KeyboardEvent &event) {
  if(event.keysym.sym == SDLK_ESCAPE) {
    if(event.state == SDL_PRESSED)
      get_Game().pop_state();
  }
}

void Instructions_State::render() {
  get_Video().set_2d(make_pair(Point2f(), Point2f(800.0f, 600.0f)), true);
  tb.render();
}
