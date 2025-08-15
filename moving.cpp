#include "moving.h"
#include "displayed_map.h"
#include "player.h"

std::pair<DisplayedMap*, Player*> move(const std::string& direction, DisplayedMap* displayed_map, Player* player) {
    if (direction == "up") {
        player->set_direction("up");
        if (player->get_absolute_y() > 1) {
            player->set_absolute_y(player->get_absolute_y() - 1);
        }
        if (displayed_map->get_y() > 1 && player->get_relative_y() == 0) {
            displayed_map->set_y(displayed_map->get_y() - 1);
        } else if (player->get_relative_y() > (displayed_map->get_y() == 1 ? -(displayed_map->get_n_cells() / 2) : 0)) {
            player->set_relative_y(player->get_relative_y() - 1);
        }
    }

    if (direction == "left") {
        player->set_direction("left");
        if (player->get_absolute_x() > 1) {
            player->set_absolute_x(player->get_absolute_x() - 1);
        }
        if (displayed_map->get_x() > 1 && player->get_relative_x() == 0) {
            displayed_map->set_x(displayed_map->get_x() - 1);
        } else if (player->get_relative_x() > (displayed_map->get_x() == 1 ? -(displayed_map->get_n_cells() / 2) : 0)) {
            player->set_relative_x(player->get_relative_x() - 1);
        }
    }

    if (direction == "down") {
        player->set_direction("down");
        if (player->get_absolute_y() < 128) {
            player->set_absolute_y(player->get_absolute_y() + 1);
        }
        if (displayed_map->get_y() < 128 - displayed_map->get_n_cells() && player->get_relative_y() == 0) {
            displayed_map->set_y(displayed_map->get_y() + 1);
        } else if (player->get_relative_y() < (displayed_map->get_y() == 128 - displayed_map->get_n_cells() ? (displayed_map->get_n_cells() / 2) : 0)) {
            player->set_relative_y(player->get_relative_y() + 1);
        }
    }

    if (direction == "right") {
        player->set_direction("right");
        if (player->get_absolute_x() < 128) {
            player->set_absolute_x(player->get_absolute_x() + 1);
        }
        if (displayed_map->get_x() < 128 - displayed_map->get_n_cells() && player->get_relative_x() == 0) {
            displayed_map->set_x(displayed_map->get_x() + 1);
        } else if (player->get_relative_x() < (displayed_map->get_x() == 128 - displayed_map->get_n_cells() ? (displayed_map->get_n_cells() / 2) : 0)) {
            player->set_relative_x(player->get_relative_x() + 1);
        }
    }

    return std::make_pair(displayed_map, player);
} 