#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Player {
private:
    std::string direction;
    int absolute_x, absolute_y;
    int relative_x, relative_y;

public:
    Player(int x, int y);
    
    void draw(ALLEGRO_DISPLAY* display, int n_cells, int cell_size);
    
    // Getters
    std::string get_direction() const { return direction; }
    int get_absolute_x() const { return absolute_x; }
    int get_absolute_y() const { return absolute_y; }
    int get_relative_x() const { return relative_x; }
    int get_relative_y() const { return relative_y; }
    
    // Setters
    void set_direction(const std::string& dir) { direction = dir; }
    void set_absolute_x(int x) { absolute_x = x; }
    void set_absolute_y(int y) { absolute_y = y; }
    void set_relative_x(int x) { relative_x = x; }
    void set_relative_y(int y) { relative_y = y; }
};

#endif // PLAYER_H 