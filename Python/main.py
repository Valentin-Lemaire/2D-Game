import pygame
from file_extraction import file_to_matrix
from moving import move
from player import Player
from displayed_map import DisplayedMap
from menus import PauseMenu

def main(screen_size: int, displayed_map: DisplayedMap, player: Player):
    pygame.init()
    screen = pygame.display.set_mode((screen_size, screen_size))
    clock = pygame.time.Clock()
    running = True

    pause_menu = PauseMenu(screen)

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pause_menu.menu_active = not pause_menu.menu_active

        keys = pygame.key.get_pressed()
        directions = {
            pygame.K_z: "up",
            pygame.K_q: "left", 
            pygame.K_s: "down", 
            pygame.K_d: "right"
        }
        zooms = {
            pygame.K_i: "in",
            pygame.K_o: "out"
        }

        for key, direction in directions.items():
            if keys[key]:
                displayed_map, player = move(direction, displayed_map, player)
        
        for key, zoom in zooms.items():
            if keys[key]:
                player.relative_x, player.relative_y = displayed_map.zoom(zoom, player)

        displayed_map.update_grid()
        displayed_map.draw(screen)
        player.draw(screen, displayed_map.n_cells, displayed_map.cell_size)

        if pause_menu.menu_active:
            pause_menu.draw()
            menu_result = pause_menu.handle_events()
            if menu_result == False:
                running = False

        pygame.display.flip()
        clock.tick(20)
    pygame.quit()

map = file_to_matrix("maps/map2.txt")
screen_sizes = [315, 495, 525, 585, 675, 693, 735, 765, 819, 825, 855] # Screen sizes that works well (in px)
screen_size = screen_sizes[5]
map_size = 128 # in number of cells
map_center = map_size // 2
displayed_map = DisplayedMap(map, map_center, screen_size)
player = Player(map_center, map_center)

main(screen_size, displayed_map, player)