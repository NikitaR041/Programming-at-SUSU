import pygame
from STriangle import STriangle
from SSquare import SSquare
from UIElements import UIElement

pygame.init()

# Окно
WIDTH, HEIGHT = 900, 700
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Фрактальные фигуры Серпинского")

# Цвета для объектов - кнопок, надписей и курсора
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
BLUE = (50, 100, 200)

clock = pygame.time.Clock()
running = True

# Значение по умолчанию 
size = 400 # Длина треугольника
depth = 4 # Глубина рекурсии

# Состояния ползунков и кнопок
# dragging1 = False
# dragging2 = False
mode = "triangle" # Треугольник Сперанского (иначе квадрат Сперанского)

# Параметры ползунков
# slider_width = 300
# slider_height = 5
# handle_radius = 12

# Объекты ползунков
# slider1_rect = pygame.Rect(50, HEIGHT - 100, slider_width, slider_height)
# slider2_rect = pygame.Rect(50, HEIGHT - 50, slider_width, slider_height)
 
# Объекты кнопок
# button_triangle = pygame.Rect(650, HEIGHT - 120, 150, 40)
# button_square = pygame.Rect(650, HEIGHT - 70, 150, 40)

# Функция, рисующая ползунок 
# def drawSlider(rect, value, min_val, max_val, label):
#     pygame.draw.rect(screen, GRAY, rect)
#     # По умолчанию ползунок расположен по середине
#     ratio = (value - min_val) / (max_val - min_val) # Значение [0;1]
#     handle_x = rect.x + int(ratio * rect.width)
#     handle_y = rect.y
#     pygame.draw.circle(screen, BLUE, (handle_x, handle_y), handle_radius)

#     font = pygame.font.SysFont(None, 24)
#     txt = font.render(f"{label}: {value}", True, BLACK)
#     screen.blit(txt, (rect.x + rect.width + 20, rect.y - 10))
#     return pygame.Rect(handle_x - handle_radius, handle_y - handle_radius, handle_radius*2, handle_radius*2)

# # Функция, рисующая кнопку
# def drawButton(rect, text, active):
#     color = BLUE if active else GRAY
#     pygame.draw.rect(screen, color, rect)
#     font = pygame.font.SysFont(None, 28)
#     txt = font.render(text, True, WHITE)
#     screen.blit(txt, (rect.x + 10, rect.y + 8))

# Функция, реализующая рекурсивное построение треугольников
# def midpoint(p1, p2):
#     return ((p1[0]+p2[0])/2, (p1[1]+p2[1])/2)

# def drawTriangle(screen, A, B, C, depth):
#     if depth == 0:
#         pygame.draw.polygon(screen, BLACK, [A, B, C], 0)
#     else:
#         m12 = midpoint(A, B)
#         m23 = midpoint(B, C)
#         m31 = midpoint(C, A)
#         drawTriangle(screen, A, m12, m31, depth-1)
#         drawTriangle(screen, m12, B, m23, depth-1)
#         drawTriangle(screen, m31, m23, C, depth-1)

# Функция, реализующая рекурсивное построение квадратов
# def drawSquare(surface, x, y, size, depth):
#     if depth == 0:
#         pygame.draw.rect(surface, BLACK, (x, y, size, size))
#     else:
#         new_size = size // 3
#         for i in range(3):
#             for j in range(3):
#                 if i == 1 and j == 1:  # пропускаем центр
#                     continue
#                 drawSquare(surface, x + i*new_size, y + j*new_size, new_size, depth-1)

#Объекты от класса UIElemet
slider_size = UIElement(pygame.Rect(50, HEIGHT - 100, 300, 5), 'slider', "Size", 100, 700, 400)
slider_depth = UIElement(pygame.Rect(50, HEIGHT - 50, 300, 5), 'slider', "Depth", 1, 8, 4)
button_triangle = UIElement(pygame.Rect(650, HEIGHT - 120, 150, 40), 'button', "Треугольник")
button_square = UIElement(pygame.Rect(650, HEIGHT - 70, 150, 40), 'button', "Квадрат")

#Объекты от класса SSquare и STriangle
triangle = STriangle((0,0), (0,0), (0,0))
square = SSquare(WIDTH/2-HEIGHT/3,WIDTH/2-HEIGHT/2, 0)

# Основной цикл
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        # обработка UI
        slider_size.handle_event(event)
        slider_depth.handle_event(event)
        button_triangle.handle_event(event)
        button_square.handle_event(event)

        # выбор режима через кнопки
        if button_triangle.active:
            mode = "triangle"
            button_square.active = False
        elif button_square.active:
            mode = "square"
            button_triangle.active = False

    screen.fill(WHITE)

    size_val = slider_size.value
    depth_val = slider_depth.value

    if mode == "triangle":
        height = int(size_val * 0.866)
        triangle.a = (WIDTH/2, 10)
        triangle.b = (WIDTH/2 - size_val/2, 10 + height)
        triangle.c = (WIDTH/2 + size_val/2, 10 + height)
        triangle.drawTriangle(screen, depth_val)
    else:
        square.a = WIDTH//2 - size_val//2
        square.b = 50
        square.size = size_val
        square.drawSquare(screen, depth_val)

    # отрисовка UI
    slider_size.draw(screen)
    slider_depth.draw(screen)
    button_triangle.draw(screen)
    button_square.draw(screen)

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
