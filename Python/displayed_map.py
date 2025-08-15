import pygame
from player import Player

def divisors(n: int):
    return [i for i in range(1, n + 1) if n % i == 0]

def matrix_extractor(matrix: list[list], x: int, y: int, size: int):
    return [[matrix[y + j][x + i] for i in range(size)] for j in range(size)]

class DisplayedMap:
    def __init__(self, map: list[list], map_center: int, screen_size: int):
        self.map = map

        self.divisors_tab = divisors(screen_size)
        self.zoom_lvl = 3

        self.n_cells = self.divisors_tab[self.zoom_lvl]
        self.cell_size = self.divisors_tab[-self.zoom_lvl-1]

        self.x = self.y = map_center - self.n_cells // 2

        self.grid = matrix_extractor(self.map, self.x, self.y, self.n_cells)
    
    def update_grid(self):
        self.grid = matrix_extractor(self.map, self.x, self.y, self.n_cells)
    
    def zoom(self, in_or_out: str, player: Player):
        if in_or_out == "out" and self.zoom_lvl < 7:
            self.zoom_lvl += 1
        elif in_or_out == "in" and self.zoom_lvl > 3:
            self.zoom_lvl -= 1
        
        self.n_cells = self.divisors_tab[self.zoom_lvl]
        self.cell_size = self.divisors_tab[-self.zoom_lvl - 1]

        half_size = self.n_cells // 2 # half the size of the displayed map

        self.x = max(1, min(128 - self.n_cells, player.absolute_x - half_size))
        self.y = max(1, min(128 - self.n_cells, player.absolute_y - half_size))

        player_relative_x = max(-half_size, min(half_size, player.absolute_x - (self.x + half_size)))
        player_relative_y = max(-half_size, min(half_size, player.absolute_y - (self.y + half_size)))

        return player_relative_x, player_relative_y
    
    def draw(self, screen):
        for i in range(len(self.grid)):
            row = self.grid[i]
            for j in range(len(row)):
                cell = row[j]
                color = "green" if cell else "blue"
                cell_square = pygame.Rect(j * self.cell_size, i * self.cell_size, self.cell_size, self.cell_size)
                pygame.draw.rect(screen, color, cell_square) # Grid squares
                pygame.draw.rect(screen, "black", cell_square, 1) # Grid lines