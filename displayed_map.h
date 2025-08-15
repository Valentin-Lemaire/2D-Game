#ifndef DISPLAYED_MAP_H
#define DISPLAYED_MAP_H

#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Player;

class DisplayedMap {
private:
    std::vector<std::vector<int>> map;
    std::vector<int> divisors_tab;
    int zoom_lvl;
    int n_cells;
    int cell_size;
    int x, y;
    std::vector<std::vector<int>> grid;

    std::vector<int> divisors(int n);
    std::vector<std::vector<int>> matrix_extractor(const std::vector<std::vector<int>>& matrix, int x, int y, int size);

public:
    DisplayedMap(const std::vector<std::vector<int>>& map, int map_center, int screen_size);
    
    void update_grid();
    std::pair<int, int> zoom(const std::string& in_or_out, Player& player);
    void draw(ALLEGRO_DISPLAY* display);
    
    // Getters
    int get_n_cells() const { return n_cells; }
    int get_cell_size() const { return cell_size; }
    int get_x() const { return x; }
    int get_y() const { return y; }
    
    // Setters
    void set_x(int new_x) { x = new_x; }
    void set_y(int new_y) { y = new_y; }
};

#endif // DISPLAYED_MAP_H 