import pygame

class SSquare :
    #Конструктор с параметрами
    def __init__(self, x, y, size, color=(0,0,0)) :
        self.x = x
        self.y = y
        self.size = size
        self.color = color

    #Основной вызов метода для рисования квадрата Серпинского
    def drawSquare(self, screen, depth):
        self.drawRecursiveS(screen, self.x, self.y, self.size, depth)

    #Рекурсивный метод, который рождает новые квадраты
    def drawRecursiveS(self, screen, x, y, size, depth):
        if depth == 0:
            pygame.draw.rect(screen, self.color, (x, y, size, size))
        else:
            new_size = size // 3
            for i in range(3):
                for j in range(3):
                    if i == 1 and j == 1:  # пропускаем центр
                        continue
                    self.drawRecursiveS(screen, x + i*new_size, 
                                        y + j*new_size, new_size, depth-1)
