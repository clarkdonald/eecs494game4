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
  sr.set_BGM("music/evanescence");
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
  //initialize player 1
  set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE, 0), 11);
  set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK, 0), 11);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX, 0 /* x-axis */), 12);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY, 0 /* y-axis */), 13);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX, 0 /* x-rotation */), 14);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY, 0 /* y-rotation */), 15);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERLEFT, 0 /* z-axis */), 16);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, 0 /* z-axis */), 17);


	//initialize player 2
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE, 1), 21);
  set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK, 1), 21);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX, 1 /* x-axis */), 22);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY, 1 /* y-axis */), 23);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX, 1 /* x-rotation */), 24);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY, 1 /* y-rotation */), 25);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERLEFT, 1 /* z-axis */), 26);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, 1 /* z-axis */), 27);

	//initialize player 3
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE, 2), 31);
  set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK, 2), 31);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX, 2 /* x-axis */), 32);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY, 2 /* y-axis */), 33);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX, 2 /* x-rotation */), 34);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY, 2 /* y-rotation */), 35);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERLEFT, 2 /* z-axis */), 36);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, 2 /* z-axis */), 37);

	//initialize player 4
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE, 3), 41);
  set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK, 3), 41);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX, 3 /* x-axis */), 42);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY, 3 /* y-axis */), 43);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX, 3 /* x-rotation */), 44);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY, 3 /* y-rotation */), 45);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERLEFT, 3 /* z-axis */), 46);
  set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, 3 /* z-axis */), 47);
}

void Play_State::on_event(const Zeni_Input_ID &id, const float &confidence, const int &action)
{
	game_state -> execute_controller_code(id, confidence, action);
}