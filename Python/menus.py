import pygame

class PauseMenu:
    def __init__(self, screen):
        self.screen = screen
        self.font = pygame.font.Font(None, 36)
        self.menu_active = False
        self.options = [
            "Resume",
            "Settings",
            "Quit"
        ]
        self.option_rects = []

    def draw(self):
        # Dim the screen
        s = pygame.Surface((self.screen.get_width(), self.screen.get_height()))
        s.fill((64,64,64))
        s.set_alpha(2)
        self.screen.blit(s, (0,0))
        
        # Draw menu options
        self.option_rects = []
        for i, option in enumerate(self.options):
            mouse_pos = pygame.mouse.get_pos()
            text = self.font.render(option, True, (255, 255, 255))
            text_rect = text.get_rect(center=(self.screen.get_width() // 2, 
                                            self.screen.get_height() // 2 + i * 50 - 50 * (len(self.options) - 1) // 2))
            
            self.option_rects.append(text_rect)
            if text_rect.collidepoint(mouse_pos):
                color = (255, 255, 255)
            else:
                color = (127, 127, 127)
                
            text = self.font.render(option, True, color)
            self.screen.blit(text, text_rect)
        
    def handle_events(self):
        while self.menu_active:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    return False
                    
                # Handle keyboard input
                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    self.menu_active = False

                # Handle mouse input
                elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    mouse_pos = pygame.mouse.get_pos()
                    for i, rect in enumerate(self.option_rects):
                        if rect.collidepoint(mouse_pos):
                            self.selected_option = i
                            return self.select_option()
            
            self.draw()
            pygame.display.flip()
        
        return None
    
    def select_option(self):
        if self.selected_option == 0:  # Resume
            self.menu_active = False
        elif self.selected_option == 1:  # Settings
            print("Settings menu not implemented")
        elif self.selected_option == 2:  # Quit
            return False
        return None