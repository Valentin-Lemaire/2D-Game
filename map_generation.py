import numpy as np
from PIL import Image
from noise import pnoise2
import random

def generate_perlin_grid(width, height, scale, octaves=6, persistence=0.5, lacunarity=2.0, threshold=0.0):
    seed = random.randint(0, 100)
    
    grid = []
    for i in range(height):
        row = []
        for j in range(width):
            noise_val = pnoise2(i/scale, 
                              j/scale, 
                              octaves=octaves, 
                              persistence=persistence, 
                              lacunarity=lacunarity, 
                              repeatx=width, 
                              repeaty=height, 
                              base=seed)
            
            value = 1 if noise_val > threshold else 0
            row.append(value)
        grid.append(row)
    
    return grid

def matrix_to_image(matrix, output_path):
    height, width = 128, 128
    img = np.zeros((height, width, 3), dtype=np.uint8)

    color_map = {0: [0, 0, 255], 1: [0, 255, 0]}
    for i in range(height):
        for j in range(width):
            img[i, j] = color_map[matrix[i][j]]

    image = Image.fromarray(img)
    image.save(output_path)

def save_grid_to_file(grid, filename="map.txt"):
    with open(filename, 'w') as f:
        for row in grid:
            f.write(''.join(map(str, row)) + '\n')

width, height = 128, 128
terrain_map = generate_perlin_grid(width, height, 64)

save_grid_to_file(terrain_map, "maps/map3.txt")
matrix_to_image(terrain_map, "maps/map3.png")