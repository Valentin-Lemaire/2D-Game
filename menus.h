#ifndef MENUS_H
#define MENUS_H

#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

struct Rect {
    float x, y, w, h;
    Rect(float x = 0, float y = 0, float w = 0, float h = 0) : x(x), y(y), w(w), h(h) {}
};

class PauseMenu {
private:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;
    bool menu_active;
    std::vector<std::string> options;
    std::vector<Rect> option_rects;
    int selected_option;

public:
    PauseMenu(ALLEGRO_DISPLAY* display);
    ~PauseMenu();
    
    void draw();
    bool* handle_events(ALLEGRO_EVENT_QUEUE* event_queue);
    bool* select_option();
    
    bool is_active() const { return menu_active; }
    void set_active(bool active) { menu_active = active; }
};

#endif // MENUS_H 