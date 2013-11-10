//
//  Play_State.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Play_State.h"
#include "Map_Manager.h"
#include "Game_State.h"
#include <string>

using namespace Zeni;
using namespace Zeni::Collision;
using std::string;
using std::cerr;
using std::endl;

Play_State::Play_State()
{
  set_pausable(true);
  
  if (Map_Manager::get_Instance().empty()) {
    cerr << "No maps to play!" << endl;
    get_Game().pop_state();
  }
  game_state = new Game_State(Map_Manager::get_Instance().get_next());
  
  // Load BGM
  Sound &sr = get_Sound();
  sr.set_BGM("music/fortunedays");
  sr.set_BGM_looping(true);
  sr.play_BGM();
}

Play_State::~Play_State() {
  get_Sound().stop_BGM();
}

void Play_State::on_push() {
  get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
}

void Play_State::on_pop() {
  Map_Manager::get_Instance().reset();
  get_Window().set_mouse_state(Window::MOUSE_NORMAL);
}

void Play_State::on_key(const SDL_KeyboardEvent &event) {
  if (event.keysym.sym == SDLK_p &&
      event.type == SDL_KEYDOWN &&
      game_state != nullptr)
  {
    delete game_state;
    game_state = new Game_State(Map_Manager::get_Instance().get_previous());
  }
  
  if (game_state != nullptr) Gamestate_Base::on_key(event);
}

void Play_State::perform_logic() {
  bool over = false;
  if (game_state->is_done()) {
    delete game_state;
    if (Map_Manager::get_Instance().empty()) {
      over = true;
      get_Game().pop_state();
    }
    else {
      game_state = new Game_State(Map_Manager::get_Instance().get_next());
    }
  }

  if (!over) game_state->perform_logic();
}

void Play_State::render(){
  if (game_state != nullptr) game_state->render();
}
