import numpy as np

# Узел квадрантного дерева
class QuadTreeNode:
    #Конструктор по умолчанию
    def __init__(self, x, y, width, height, value=None):
        self.x = x  # Начальная координата Х левого верхнего угла области 
        self.y = y  # Начальная координата Y левого верхнего угла области
        self.width = width  #Ширина облати 
        self.height = height#Высота области
        self.value = value  # None для смешанных, True/False для однородных
        self.children = []  # [NW, NE, SW, SE] - дочерние узлы
    
    def is_leaf(self):
        return len(self.children) == 0
    
# Класс для работы с квадрантным деревом
class QuadTree:
    #Конструктор по умолчанию
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.root = QuadTreeNode(0, 0, width, height, False)
    
    def build_from_array(self, array):
        """Построение дерева из массива"""
        self.root = self._build_tree(0, 0, self.width, self.height, array)
    
    #Метод - рекурсивное построение дерева
    def _build_tree(self, x, y, width, height, array):
        #Базовый случай рекурсии - пискель 1x1
        if width == 1 and height == 1:
            return QuadTreeNode(x, y, width, height, array[y, x])
        
        # Проверяем, однороден ли регион
        region = array[y:y+height, x:x+width]
        if np.all(region == region[0, 0]):
            return QuadTreeNode(x, y, width, height, bool(region[0, 0]))
        
        # Разделяем на 4 квадранты
        node = QuadTreeNode(x, y, width, height, None)
        half_w, half_h = width // 2, height // 2
        
        node.children = [
            self._build_tree(x, y, half_w, half_h, array),  # NW
            self._build_tree(x + half_w, y, width - half_w, half_h, array),  # NE
            self._build_tree(x, y + half_h, half_w, height - half_h, array),  # SW
            self._build_tree(x + half_w, y + half_h, width - half_w, 
                             height - half_h, array)  # SE
        ]
        
        return node
     
    def to_array(self):
        """Преобразование дерева обратно в массив"""
        array = np.zeros((self.height, self.width), dtype=bool)
        self._tree_to_array(self.root, array)
        return array
    
    # Метод, который восстанавливает изображение из узлов
    def _tree_to_array(self, node, array):
        if node.is_leaf():
            if node.value is not None:
                array[node.y:node.y+node.height, node.x:node.x+node.width] = node.value
        else:
            for child in node.children:
                self._tree_to_array(child, array)