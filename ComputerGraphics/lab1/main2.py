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

# Треугольник Сперанского (иначе квадрат Сперанского)
mode = "triangle"

#Объекты от класса UIElemet
slider_size = UIElement(pygame.Rect(50, HEIGHT - 100, 300, 5),
                         'slider', "Size", 100, 700, 400)
slider_depth = UIElement(pygame.Rect(50, HEIGHT - 50, 300, 5),
                          'slider', "Depth", 1, 8, 4)
button_triangle = UIElement(pygame.Rect(650, HEIGHT - 120, 150, 40),
                             'button', "Треугольник")
button_square = UIElement(pygame.Rect(650, HEIGHT - 70, 150, 40),
                           'button', "Квадрат")

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
