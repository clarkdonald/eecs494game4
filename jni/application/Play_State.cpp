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
  initialize_xbox_controller();
  
  if (Map_Manager::get_Instance().empty()) {
    cerr << "No maps to play!" << endl;
    get_Game().pop_state();
  }
  game_state = new Game_State(Map_Manager::get_Instance().get_next());
  
  // Load BGM
  Sound &sr = get_Sound();
  sr.set_BGM("music/battle_song");
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
  if (game_state->is_gameover()) {
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

// --- Code to detect xbox controller button presses ---
void Play_State::initialize_xbox_controller()
{
  set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
  set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK), 1);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX /* x-axis */), 2);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY /* y-axis */), 3);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX /* x-rotation */), 4);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY /* y-rotation */), 5);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERLEFT /* z-axis */), 6);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT /* z-axis */), 7);
}

void Play_State::on_event(const Zeni_Input_ID &id, const float &confidence, const int &action)
{
	game_state -> execute_controller_code(id, confidence, action);
}