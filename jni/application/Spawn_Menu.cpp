#include "Utility.h"
#include "Spawn_Menu.h"

using namespace Zeni;

Spawn_Menu::Spawn_Menu(std::pair<Point2i, Point2i> screen_coord) {    
  auto screen_center_x = screen_coord.first.x + (screen_coord.second.x - screen_coord.first.x) / 2;
  auto screen_center_y = screen_coord.first.y + (screen_coord.second.y - screen_coord.first.y) / 2;  

  // Warrior
  buttons.push_back(new Text_Button(Point2f(screen_center_x - 100, screen_center_y - 82), Point2f(screen_center_x + 100, screen_center_y - 34), "spawn_menu", "Warrior"));    
  // Archer
  buttons.push_back(new Text_Button(Point2f(screen_center_x - 100, screen_center_y - 24), Point2f(screen_center_x + 100, screen_center_y + 24), "spawn_menu", "Archer"));    
  // Mage
  buttons.push_back(new Text_Button(Point2f(screen_center_x - 100, screen_center_y + 34), Point2f(screen_center_x + 100, screen_center_y + 82), "spawn_menu", "Mage"));   

  highlighted_buttons.push_back(new Text_Button(Point2f(screen_center_x - 100, screen_center_y - 82), Point2f(screen_center_x + 100, screen_center_y - 34), "spawn_menu", "Warrior"));    
  highlighted_buttons.push_back(new Text_Button(Point2f(screen_center_x - 100, screen_center_y - 24), Point2f(screen_center_x + 100, screen_center_y + 24), "spawn_menu", "Archer"));    
  highlighted_buttons.push_back(new Text_Button(Point2f(screen_center_x - 100, screen_center_y + 34), Point2f(screen_center_x + 100, screen_center_y + 82), "spawn_menu", "Mage")); 
  
  highlighted_buttons[0]->give_Renderer(new Widget_Renderer_Tricolor(get_Colors()["white"], // bg_normal
                                                                      get_Colors()["white"], // bg_clicked
                                                                      get_Colors()["white"], // bg_hoovered
                                                                      get_Colors()["black"], // text_normal
                                                                      get_Colors()["white"], // text_clicked
                                                                      get_Colors()["white"])); // text_hoovered
  highlighted_buttons[1]->give_Renderer(new Widget_Renderer_Tricolor(get_Colors()["white"], // bg_normal
                                                                      get_Colors()["white"], // bg_clicked
                                                                      get_Colors()["white"], // bg_hoovered
                                                                      get_Colors()["black"], // text_normal
                                                                      get_Colors()["white"], // text_clicked
                                                                      get_Colors()["white"])); // text_hoovered
  highlighted_buttons[2]->give_Renderer(new Widget_Renderer_Tricolor(get_Colors()["white"], // bg_normal
                                                                      get_Colors()["white"], // bg_clicked
                                                                      get_Colors()["white"], // bg_hoovered
                                                                      get_Colors()["black"], // text_normal
                                                                      get_Colors()["white"], // text_clicked
                                                                      get_Colors()["white"])); // text_hoovered
  render_buttons.resize(num_options);
  clear_menu();  
}

void Spawn_Menu::clear_menu() {
  option_selected = false;
  current_option = 0;
  render_buttons[0] = highlighted_buttons[0];
  render_buttons[1] = buttons[1];
  render_buttons[2] = buttons[2];
}

Spawn_Menu::~Spawn_Menu() {
  for(auto button : buttons) 
    delete button;  
  for(auto button : highlighted_buttons) 
    delete button;  
}

void Spawn_Menu::render() {
  for(auto render_button : render_buttons) 
    render_button->render();
}

void Spawn_Menu::move_up() {
  render_buttons[current_option] = buttons[current_option];
  current_option--;
  if(current_option < 0)
    current_option = num_options - 1;
  render_buttons[current_option] = highlighted_buttons[current_option];
}

void Spawn_Menu::move_down() {
  render_buttons[current_option] = buttons[current_option];
  current_option++;
  if(current_option >= num_options)
    current_option = 0;
  render_buttons[current_option] = highlighted_buttons[current_option];
}

void Spawn_Menu::select_current_option() {
  option_selected = true;
  switch(current_option) {
    case 0:
      selected_option = "Warrior";
      break;
    case 1:
      selected_option = "Archer";
      break;
    case 2:
      selected_option = "Mage";
      break;
    default:
      error_handle("This is not an available option for the spawn_menu");
  }  
}

std::string Spawn_Menu::get_selected_option() {  
  return selected_option;
}