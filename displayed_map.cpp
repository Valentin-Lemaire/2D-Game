#include "displayed_map.h"
#include "player.h"
#include <algorithm>
#include <cmath>

std::vector<int> DisplayedMap::divisors(int n) {
    std::vector<int> result;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<std::vector<int>> DisplayedMap::matrix_extractor(const std::vector<std::vector<int>>& matrix, int x, int y, int size) {
    std::vector<std::vector<int>> result;
    for (int j = 0; j < size; j++) {
        std::vector<int> row;
        for (int i = 0; i < size; i++) {
            row.push_back(matrix[y + j][x + i]);
        }
        result.push_back(row);
    }
    return result;
}

DisplayedMap::DisplayedMap(const std::vector<std::vector<int>>& map, int map_center, int screen_size) 
    : map(map), zoom_lvl(3) {
    
    divisors_tab = divisors(screen_size);
    n_cells = divisors_tab[zoom_lvl];
    cell_size = divisors_tab[divisors_tab.size() - zoom_lvl - 1];
    
    x = y = map_center - n_cells / 2;
    
    grid = matrix_extractor(map, x, y, n_cells);
}

void DisplayedMap::update_grid() {
    grid = matrix_extractor(map, x, y, n_cells);
}

std::pair<int, int> DisplayedMap::zoom(const std::string& in_or_out, Player& player) {
    if (in_or_out == "out" && zoom_lvl < 7) {
        zoom_lvl++;
    } else if (in_or_out == "in" && zoom_lvl > 3) {
        zoom_lvl--;
    }
    
    n_cells = divisors_tab[zoom_lvl];
    cell_size = divisors_tab[divisors_tab.size() - zoom_lvl - 1];
    
    int half_size = n_cells / 2;
    
    x = std::max(1, std::min(128 - n_cells, player.get_absolute_x() - half_size));
    y = std::max(1, std::min(128 - n_cells, player.get_absolute_y() - half_size));
    
    int player_relative_x = std::max(-half_size, std::min(half_size, player.get_absolute_x() - (x + half_size)));
    int player_relative_y = std::max(-half_size, std::min(half_size, player.get_absolute_y() - (y + half_size)));
    
    return std::make_pair(player_relative_x, player_relative_y);
}

void DisplayedMap::draw(ALLEGRO_DISPLAY* display) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            int cell = grid[i][j];
            ALLEGRO_COLOR color = cell ? al_map_rgb(0, 255, 0) : al_map_rgb(0, 0, 255);
            
            int x_pos = j * cell_size;
            int y_pos = i * cell_size;
            
            al_draw_filled_rectangle(x_pos, y_pos, x_pos + cell_size, y_pos + cell_size, color);
            al_draw_rectangle(x_pos, y_pos, x_pos + cell_size, y_pos + cell_size, al_map_rgb(0, 0, 0), 1);
        }
    }
} 