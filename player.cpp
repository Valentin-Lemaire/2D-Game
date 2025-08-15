#include "player.h"
#include <allegro5/allegro_primitives.h>

Player::Player(int x, int y) : direction("up"), absolute_x(x), absolute_y(y), relative_x(0), relative_y(0) {}

void Player::draw(ALLEGRO_DISPLAY* display, int n_cells, int cell_size) {
    int center_x = (n_cells * cell_size) / 2 + relative_x * cell_size;
    int center_y = (n_cells * cell_size) / 2 + relative_y * cell_size;
    int radius = cell_size / 2;
    
    al_draw_filled_circle(center_x, center_y, radius, al_map_rgb(0, 0, 0));
} 