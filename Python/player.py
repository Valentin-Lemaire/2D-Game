class Player:
    def __init__(self, x: int, y: int):
        self.direction = "up"
        self.absolute_x = x
        self.absolute_y = y
        self.relative_x = 0
        self.relative_y = 0
    
    def draw(self, screen, n_cells: int, cell_size: int):
        import pygame
        center_x = (n_cells * cell_size) // 2 + self.relative_x * cell_size
        center_y = (n_cells * cell_size) // 2 + self.relative_y * cell_size
        radius = cell_size // 2
        pygame.draw.circle(screen, (0, 0, 0), (center_x, center_y), radius)