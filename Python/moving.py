from displayed_map import DisplayedMap
from player import Player

def move(direction: str, displayed_map: DisplayedMap, player: Player):
    if direction == "up":
        player.direction = "up"
        if player.absolute_y > 1:
            player.absolute_y -= 1
        if displayed_map.y > 1 and player.relative_y == 0:
            displayed_map.y -= 1
        elif player.relative_y > (-(displayed_map.n_cells // 2) if displayed_map.y == 1 else 0):
            player.relative_y -= 1

    if direction == "left":
        player.direction = "left"
        if player.absolute_x > 1:
            player.absolute_x -= 1
        if displayed_map.x > 1 and player.relative_x == 0:
            displayed_map.x -= 1
        elif player.relative_x > (-(displayed_map.n_cells // 2) if displayed_map.x == 1 else 0):
            player.relative_x -= 1

    if direction == "down":
        player.direction = "down"
        if player.absolute_y < 128:
            player.absolute_y += 1
        if displayed_map.y < 128 - displayed_map.n_cells and player.relative_y == 0:
            displayed_map.y += 1
        elif player.relative_y < ((displayed_map.n_cells // 2) if displayed_map.y == 128 - displayed_map.n_cells else 0):
            player.relative_y += 1

    if direction == "right":
        player.direction = "right"
        if player.absolute_x < 128:
            player.absolute_x += 1
        if displayed_map.x < 128 - displayed_map.n_cells and player.relative_x == 0:
            displayed_map.x += 1
        elif player.relative_x < ((displayed_map.n_cells // 2) if displayed_map.x == 128 - displayed_map.n_cells else 0):
            player.relative_x += 1

    return displayed_map, player