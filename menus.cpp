#include "menus.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

PauseMenu::PauseMenu(ALLEGRO_DISPLAY* display) : display(display), menu_active(false), selected_option(0) {
    font = al_create_builtin_font();
    if (!font) {
        std::cerr << "Error: Could not create font" << std::endl;
    }
    
    options = {"Resume", "Settings", "Quit"};
    option_rects.resize(options.size());
}

PauseMenu::~PauseMenu() {
    if (font) {
        al_destroy_font(font);
    }
}

void PauseMenu::draw() {
    // Dim the screen
    int width = al_get_display_width(display);
    int height = al_get_display_height(display);
    
    al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(64, 64, 64, 128));
    
    // Draw menu options
    option_rects.clear();
    for (int i = 0; i < options.size(); i++) {
        int mouse_x, mouse_y;
        al_get_mouse_cursor_position(&mouse_x, &mouse_y);
        
        ALLEGRO_COLOR color = al_map_rgb(127, 127, 127);
        if (i == selected_option) {
            color = al_map_rgb(255, 255, 255);
        }
        
        int text_x = width / 2;
        int text_y = height / 2 + i * 50 - 50 * (options.size() - 1) / 2;
        
        int text_x_pos, text_y_pos, text_w, text_h;
        al_get_text_dimensions(font, options[i].c_str(), 
                              &text_x_pos, &text_y_pos, 
                              &text_w, &text_h);
        
        float rect_x = text_x - text_w / 2;
        float rect_y = text_y - text_h / 2;
        
        option_rects.push_back(Rect(rect_x, rect_y, text_w, text_h));
        
        al_draw_text(font, color, text_x, text_y, ALLEGRO_ALIGN_CENTER, options[i].c_str());
    }
}

bool* PauseMenu::handle_events(ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_EVENT event;
    
    while (menu_active) {
        if (al_get_next_event(event_queue, &event)) {
            
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                return new bool(false);
            }
            
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    menu_active = false;
                    return nullptr;
                }
                
                if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                    selected_option = (selected_option - 1 + options.size()) % options.size();
                }
                
                if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    selected_option = (selected_option + 1) % options.size();
                }
                
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    return select_option();
                }
            }
            
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.mouse.button == 1) {
                    int mouse_x = event.mouse.x;
                    int mouse_y = event.mouse.y;
                    
                    for (int i = 0; i < option_rects.size(); i++) {
                        if (mouse_x >= option_rects[i].x && mouse_x <= option_rects[i].x + option_rects[i].w &&
                            mouse_y >= option_rects[i].y && mouse_y <= option_rects[i].y + option_rects[i].h) {
                            selected_option = i;
                            return select_option();
                        }
                    }
                }
            }
        }
        
        draw();
        al_flip_display();
    }
    
    return nullptr;
}

bool* PauseMenu::select_option() {
    if (selected_option == 0) {  // Resume
        menu_active = false;
    } else if (selected_option == 1) {  // Settings
        std::cout << "Settings menu not implemented" << std::endl;
    } else if (selected_option == 2) {  // Quit
        return new bool(false);
    }
    return nullptr;
} 