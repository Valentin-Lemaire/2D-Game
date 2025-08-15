#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <map>
#include <string>

#include "file_extraction.h"
#include "moving.h"
#include "player.h"
#include "displayed_map.h"
#include "menus.h"

void main_loop(int screen_size, DisplayedMap& displayed_map, Player& player) {
    if (!al_init()) {
        std::cerr << "Failed to initialize allegro!" << std::endl;
        return;
    }

    if (!al_init_font_addon()) {
        std::cerr << "Failed to initialize font addon!" << std::endl;
        return;
    }

    if (!al_init_ttf_addon()) {
        std::cerr << "Failed to initialize ttf addon!" << std::endl;
        return;
    }

    if (!al_init_primitives_addon()) {
        std::cerr << "Failed to initialize primitives addon!" << std::endl;
        return;
    }

    if (!al_install_keyboard()) {
        std::cerr << "Failed to install keyboard!" << std::endl;
        return;
    }

    if (!al_install_mouse()) {
        std::cerr << "Failed to install mouse!" << std::endl;
        return;
    }

    ALLEGRO_DISPLAY* display = al_create_display(screen_size, screen_size);
    if (!display) {
        std::cerr << "Failed to create display!" << std::endl;
        return;
    }

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    if (!event_queue) {
        std::cerr << "Failed to create event queue!" << std::endl;
        al_destroy_display(display);
        return;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0); // 20 FPS
    if (!timer) {
        std::cerr << "Failed to create timer!" << std::endl;
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        return;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    PauseMenu pause_menu(display);
    bool running = true;
    ALLEGRO_KEYBOARD_STATE keyboard_state;

    al_start_timer(timer);

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                pause_menu.set_active(!pause_menu.is_active());
            }
        }

        if (event.type == ALLEGRO_EVENT_TIMER && !pause_menu.is_active()) {
            // Handle continuous key presses
            std::map<int, std::string> directions = {
                {ALLEGRO_KEY_W, "up"},
                {ALLEGRO_KEY_A, "left"},
                {ALLEGRO_KEY_S, "down"},
                {ALLEGRO_KEY_D, "right"}
            };

            std::map<int, std::string> zooms = {
                {ALLEGRO_KEY_I, "in"},
                {ALLEGRO_KEY_O, "out"}
            };

            al_get_keyboard_state(&keyboard_state);
            
            for (const auto& [key, direction] : directions) {
                if (al_key_down(&keyboard_state, key)) {
                    auto result = move(direction, &displayed_map, &player);
                    displayed_map = *result.first;
                    player = *result.second;
                }
            }

            for (const auto& [key, zoom] : zooms) {
                if (al_key_down(&keyboard_state, key)) {
                    auto [rel_x, rel_y] = displayed_map.zoom(zoom, player);
                    player.set_relative_x(rel_x);
                    player.set_relative_y(rel_y);
                }
            }
        }

        if (pause_menu.is_active()) {
            bool* menu_result = pause_menu.handle_events(event_queue);
            if (menu_result) {
                running = *menu_result;
                delete menu_result;
            }
        }

        // Draw everything
        al_clear_to_color(al_map_rgb(255, 255, 255));
        
        displayed_map.update_grid();
        displayed_map.draw(display);
        player.draw(display, displayed_map.get_n_cells(), displayed_map.get_cell_size());

        if (pause_menu.is_active()) {
            pause_menu.draw();
        }

        al_flip_display();
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> map = file_to_matrix("maps/map2.txt");
    
    std::vector<int> screen_sizes = {315, 495, 525, 585, 675, 693, 735, 765, 819, 825, 855};
    int screen_size = screen_sizes[5]; // 693
    
    int map_size = 128;
    int map_center = map_size / 2;
    
    DisplayedMap displayed_map(map, map_center, screen_size);
    Player player(map_center, map_center);

    main_loop(screen_size, displayed_map, player);

    return 0;
} 