from qtpy.QtCore import QObject, Signal
import numpy as np
from PIL import Image


class BinaryImage(QObject):
    changed = Signal()


    def __init__(self, width=64, height=64):
        super().__init__()
        self.width = width
        self.height = height
        # Храним как numpy.ndarray dtype=np.uint8 со значениями 0/1
        self.pixels = np.zeros((height, width), dtype=np.uint8)

    def set_size(self, width, height):
        new = np.zeros((height, width), dtype=np.uint8)
        h = min(height, self.height)
        w = min(width, self.width)
        new[:h, :w] = self.pixels[:h, :w]
        self.pixels = new
        self.width = width
        self.height = height
        self.changed.emit()


    def get_pixel(self, x, y):
      return int(self.pixels[y, x])


    def set_pixel(self, x, y, val):
        if 0 <= x < self.width and 0 <= y < self.height:
            self.pixels[y, x] = 1 if val else 0
            self.changed.emit()

    def fill(self, val):
        self.pixels[:, :] = 1 if val else 0
        self.changed.emit()


    def invert(self):
        self.pixels = 1 - self.pixels
        self.changed.emit()


    def flood_fill(self, x, y, val):
        # Непротяжённая реализация BFS/DFS для заливки
        target = self.get_pixel(x, y)
        if target == val:
            return
        h, w = self.height, self.width
        stack = [(x, y)]
        while stack:
            cx, cy = stack.pop()
            if cx < 0 or cy < 0 or cx >= w or cy >= h:
                continue
            if self.pixels[cy, cx] != target:
                continue
            self.pixels[cy, cx] = val
            stack.append((cx+1, cy))
            stack.append((cx-1, cy))
            stack.append((cx, cy+1))
            stack.append((cx, cy-1))
        self.changed.emit()

    # Экспорт в PNG через Pillow
    def export_png(self, path):
        # преобразуем 0->255 (white), 1->0 (black) для наглядности
        array = (1 - self.pixels) * 255
        img = Image.fromarray(array.astype('uint8'), mode='L')
        img.save(path)

# Загрузка/сохранение собственного формата реализованы в formats.py