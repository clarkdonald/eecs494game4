#ifndef SPAWN_MENU_H
#define SPAWN_MENU_H

#include <zenilib.h>

class Spawn_Menu {
  public:

    Spawn_Menu(std::pair<Zeni::Point2i, Zeni::Point2i> screen_coord);

    ~Spawn_Menu();

    void clear_menu();

    void render();

    void move_up();
    void move_down();    

    void select_current_option();

    std::string get_selected_option();

    bool is_option_selected() {return option_selected;}

  private:
    // 0 Warrior, 1 Archer, 2 Mage
    static const int num_options = 3;
    
    std::vector<Zeni::Text_Button *> buttons;    

    std::vector<Zeni::Text_Button *> highlighted_buttons;    

    std::vector<Zeni::Text_Button *> render_buttons;    

    std::string selected_option;

    int current_option;

    bool option_selected;
};

#endif /* SPAWN_MENU_H */