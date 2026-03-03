#Класс Треугольник Серпинского
import pygame

class STriangle :
    #Конструктор с параметрами
    def __init__(self, a, b, c, color=(0,0,0)):
        self.a = a
        self.b = b
        self.c = c
        self.color = color

    #Метод, который делит две стороны пополам    
    def midpoint(self, p1, p2) :
        return ((p1[0]+p2[0])/2, (p1[1]+p2[1])/2)

    #Основной вызов метода для рисования треугольника Серпинского
    def drawTriangle(self, screen, depth):
        self.drawRecursiveT(screen, self.a, self.b, self.c, depth)

    #Рекурсивный метод, который рождает новые треугольники
    def drawRecursiveT(self, screen, A, B, C, depth):
        if depth == 0:
            pygame.draw.polygon(screen, self.color, [A, B, C], 0)
        else:
            m12 = self.midpoint(A, B)
            m23 = self.midpoint(B, C)
            m31 = self.midpoint(C, A)
            self.drawRecursiveT(screen, A, m12, m31, depth-1)
            self.drawRecursiveT(screen, m12, B, m23, depth-1)
            self.drawRecursiveT(screen, m31, m23, C, depth-1)
    
