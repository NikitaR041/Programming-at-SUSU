import pygame

pygame.init()

# Окно
WIDTH, HEIGHT = 900, 700
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Слайдеры в Pygame")

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
BLUE = (50, 100, 200)

clock = pygame.time.Clock()
running = True

# Значение по умолчанию 
size = 400 # Длина треугольника
depth = 4 # Глубина рекурсии

# Параметры слайдеров
slider_width = 300
slider_height = 5
handle_radius = 12

# Объекты ползунков (позже их используем для вырисовки на экране)
slider1_rect = pygame.Rect(50, HEIGHT - 100, slider_width, slider_height)
slider2_rect = pygame.Rect(50, HEIGHT - 50, slider_width, slider_height)
 
dragging1 = False
dragging2 = False

def draw_slider(rect, value, min_val, max_val, label):
    """Рисуем слайдер и возвращаем позицию ручки"""
    # Рисуем прямоугольник - видимую полоску
    pygame.draw.rect(screen, GRAY, rect)
    # Рисуем и располагаем кружочек (курсор)
    # По умолчанию ползунок расположен по середине
    ratio = (value - min_val) / (max_val - min_val) # Значение [0;1]
    handle_x = rect.x + int(ratio * rect.width)
    # handle_x = rect.x + rect.width
    # handle_y = rect.y + rect.height // 2
    handle_y = rect.y
    pygame.draw.circle(screen, BLUE, (handle_x, handle_y), handle_radius)
    # Подпись
    font = pygame.font.SysFont(None, 24)
    txt = font.render(f"{label}: {value}", True, BLACK)
    screen.blit(txt, (rect.x + rect.width + 20, rect.y - 10))
    return pygame.Rect(handle_x - handle_radius, handle_y - handle_radius, handle_radius*2, handle_radius*2)

# Метод, который вычисляет новую длину треугольника по двум точкам
def midpoint(p1, p2):
    return ((p1[0]+p2[0])/2, (p1[1]+p2[1])/2)

def sierpinski_triangle(screen, A, B, C, depth):
    if depth == 0:
        pygame.draw.polygon(screen, BLACK, [A, B, C], 0)
    else:
        m12 = midpoint(A, B)
        m23 = midpoint(B, C)
        m31 = midpoint(C, A)
        sierpinski_triangle(screen, A, m12, m31, depth-1)
        sierpinski_triangle(screen, m12, B, m23, depth-1)
        sierpinski_triangle(screen, m31, m23, C, depth-1)

# Основной цикл
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.MOUSEBUTTONDOWN:
            if handle1.collidepoint(event.pos):
                dragging1 = True
            elif handle2.collidepoint(event.pos):
                dragging2 = True

        elif event.type == pygame.MOUSEBUTTONUP:
            dragging1 = dragging2 = False

        elif event.type == pygame.MOUSEMOTION:
            if dragging1:
                # Изменяем size
                rel_x = max(slider1_rect.left, min(event.pos[0], slider1_rect.right))
                ratio = (rel_x - slider1_rect.left) / slider1_rect.width
                size = int(100 + ratio * 600)  # от 100 до 700
            elif dragging2:
                # Изменяем depth
                rel_x = max(slider2_rect.left, min(event.pos[0], slider2_rect.right))
                ratio = (rel_x - slider2_rect.left) / slider2_rect.width
                depth = int(1 + ratio * 7)  # от 1 до 8

    screen.fill(WHITE)

    # Вершины треугольника под размер size
    height = int(size * 0.866)  # высота равностороннего
    A = (WIDTH/2, 10) # Вверхний угол
    B = (WIDTH/2 - size/2, 10+height) # Левый угол
    C = (WIDTH/2 + size/2,  10+height) # Правый угол

    # Рисуем треугольник
    sierpinski_triangle(screen, A, B, C, depth)

    # Слайдеры (возвращают прямоугольники ручек)
    handle1 = draw_slider(slider1_rect, size, 100, 700, "Size")
    handle2 = draw_slider(slider2_rect, depth, 1, 8, "Depth")

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
