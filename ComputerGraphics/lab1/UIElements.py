import pygame

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
BLUE = (50, 100, 200)

class UIElement :
    #Конструктор по умолчанию
    def __init__(self, rect, element_type, label="", min_val=0, max_val=1, value=0):
        self.rect = rect #pygame.Rect для позицирования 
        self.type = element_type #'button' или 'slider'
        self.label = label #отображение текста
        self.min_val = min_val #минимальное значение слайдера
        self.max_val = max_val #Максимальное значение слайдера
        self.value = value #Начальное значение слайдера
        self.active = False #Работоспособность кнопок
        self.handle_radius = 12 #Радиус ползунка

    #Метод, который рисует кнопки и ползунки
    def draw(self, screen):
        font = pygame.font.SysFont(None, 24 if self.type == 'slider' else 28)
        if self.type == 'slider':
            pygame.draw.rect(screen, GRAY, self.rect)
            # По умолчанию ползунок расположен по середине
            ratio = (self.value - self.min_val) / (self.max_val - self.min_val) # Значение [0;1]
            handle_x = self.rect.x + int(ratio * self.rect.width)
            handle_y = self.rect.y + self.rect.height // 2
            pygame.draw.circle(screen, BLUE, (handle_x, handle_y), self.handle_radius)
            txt = font.render(f"{self.label}: {self.value}", True, BLACK)
            screen.blit(txt, (self.rect.x + self.rect.width + 20, self.rect.y))
            return pygame.Rect(handle_x - self.handle_radius, handle_y - self.handle_radius,
                               self.handle_radius*2, self.handle_radius*2)
        elif self.type == 'button':
            color = BLUE if self.active else GRAY
            pygame.draw.rect(screen, color, self.rect)
            txt = font.render(self.label, True, WHITE)
            screen.blit(txt, (self.rect.x + 10, self.rect.y + 8))
            return self.rect
        
    #Метод, который обрабатывает события кнопок
    def handle_event(self, event):
        if self.type == 'button':
            if event.type == pygame.MOUSEBUTTONDOWN and self.rect.collidepoint(event.pos):
                self.active = True
                return True
        elif self.type == 'slider':
            if (event.type == pygame.MOUSEBUTTONDOWN or event.type == pygame.MOUSEMOTION) and pygame.mouse.get_pressed()[0]:
                if self.rect.collidepoint(event.pos):
                    ratio = (event.pos[0] - self.rect.x) / self.rect.width
                    self.value = int(self.min_val + ratio * (self.max_val - self.min_val))
