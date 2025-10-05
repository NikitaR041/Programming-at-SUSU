import pygame 
import numpy as np
import sys
from QuadTree import QuadTree, QuadTreeNode
from enum import Enum
import struct
import os

# Форматы хранения бинарных изображений
class StorageFormat(Enum):
    RLE = 1  # Код длин серий
    QUADTREE = 2  # Дерево квадрантов

class BinaryImageEditor:
    #Конструктор по умолчанию 
    def __init__(self, width=800, height=700):
        pygame.init()
        self.width = width #Ширина окна
        self.height = height #Высота окна
        self.screen = pygame.display.set_mode((width, height)) #Настройка окна
        pygame.display.set_caption("Binary Image Editor") #Название окна
        
        # Параметры изображения
        self.image_size = 32  # Размер бинарного изображения
        self.cell_size = 15   # Размер ячейки в реальном размере
        self.zoom_scale = 4   # Масштаб увеличения
        
        # Создаем пустое бинарное изображение
        self.image_data = np.zeros((self.image_size, self.image_size), dtype=bool)
        
        # Области отображения
        self.real_view_rect = pygame.Rect(50, 50, self.image_size * self.cell_size, self.image_size * self.cell_size)
        self.zoom_view_rect = pygame.Rect(550, 50, self.image_size * self.zoom_scale, self.image_size * self.zoom_scale)
        
        # Формат хранения
        self.storage_format = StorageFormat.RLE
        self.quadtree = QuadTree(self.image_size, self.image_size)

        # Цвета
        self.colors = {
            'background': (240, 240, 240),
            'grid': (200, 200, 200),
            'pixel_on': (0, 0, 0),
            'pixel_off': (255, 255, 255),
            'ui_bg': (220, 220, 220),
            'ui_border': (150, 150, 150)
        }
        
        # Шрифт
        self.font = pygame.font.SysFont('Arial', 14)

    #Метод отрисовки отображения области 
    def draw_image_view(self, rect, scale, title):
        # Рисуем фон
        pygame.draw.rect(self.screen, self.colors['pixel_off'], rect)
        pygame.draw.rect(self.screen, self.colors['grid'], rect, 1)
        
        # Рисуем сетку
        for i in range(self.image_size + 1):
            # Вертикальные линии
            pygame.draw.line(self.screen, self.colors['grid'],
                            (rect.x + i * scale, rect.y),
                            (rect.x + i * scale, rect.y + rect.height), 1)
            # Горизонтальные линии
            pygame.draw.line(self.screen, self.colors['grid'],
                            (rect.x, rect.y + i * scale),
                            (rect.x + rect.width, rect.y + i * scale), 1)     
        # Рисуем пиксели
        for y in range(self.image_size):
            for x in range(self.image_size):
                if self.image_data[y, x]:
                    pixel_rect = pygame.Rect(
                        rect.x + x * scale + 1,
                        rect.y + y * scale + 1,
                        scale - 1,
                        scale - 1
                    )
                    pygame.draw.rect(self.screen, self.colors['pixel_on'], pixel_rect)
        # Рисуем заголовок
        title_surface = self.font.render(title, True, (0, 0, 0))
        self.screen.blit(title_surface, (rect.x, rect.y - 20))

    #Отрисовка интерфейса (кнопки, инструкции, сетки)
    def draw_ui(self):
        # Панель информации
        info_rect = pygame.Rect(50, 550, 700, 80)
        pygame.draw.rect(self.screen, self.colors['ui_bg'], info_rect)
        pygame.draw.rect(self.screen, self.colors['ui_border'], info_rect, 1)
        
        # Информация о формате хранения
        format_text = f"Storage Format: {self.storage_format.name}"
        format_surface = self.font.render(format_text, True, (0, 0, 0))
        self.screen.blit(format_surface, (info_rect.x + 10, info_rect.y + 10))

        # Инструкции
        instructions = [
            "Left Click: Draw pixel",
            "Right Click: Erase pixel",
            "Ctrl+S: Save image",
            "Ctrl+O: Load image",
            "E: Export to PNG",
            "1: Use RLE format",
            "2: Use Quadtree format"
        ]
        
        count = 0
        shift_x = info_rect.x
        shift_y = info_rect.y
        for i, instruction in enumerate(instructions):
            if count % 2 == 0 and count != 0:
                shift_x += info_rect.x + 80
                shift_y = info_rect.y - (i * 15)
            text_surface = self.font.render(instruction, True, (0, 0, 0))
            self.screen.blit(text_surface, (shift_x + 10, shift_y + 30 + i * 15))
            count += 1
            

    # Обработчик событий 
    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            
            elif event.type == pygame.MOUSEBUTTONDOWN:
                self.handle_click(event.pos, event.button)
            
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_s and pygame.key.get_mods() & pygame.KMOD_CTRL:
                    self.save_image()
                elif event.key == pygame.K_o and pygame.key.get_mods() & pygame.KMOD_CTRL:
                    self.load_image()
                elif event.key == pygame.K_e:
                    self.export_image()
                elif event.key == pygame.K_1:
                    self.storage_format = StorageFormat.RLE
                elif event.key == pygame.K_2:
                    self.storage_format = StorageFormat.QUADTREE
        return True
    
    # Обработчик нажатия мышью
    def handle_click(self, pos, button):
        # Проверяем клик в области реального размера
        if self.real_view_rect.collidepoint(pos):
            x = (pos[0] - self.real_view_rect.x) // self.cell_size
            y = (pos[1] - self.real_view_rect.y) // self.cell_size
            
            if 0 <= x < self.image_size and 0 <= y < self.image_size:
                if button == 1:  # Левая кнопка - включить пиксель
                    self.image_data[y, x] = True
                elif button == 3:  # Правая кнопка - выключить пиксель
                    self.image_data[y, x] = False
        # Проверяем клик в области увеличения
        elif self.zoom_view_rect.collidepoint(pos):
            x = (pos[0] - self.zoom_view_rect.x) // self.zoom_scale
            y = (pos[1] - self.zoom_view_rect.y) // self.zoom_scale
            
            if 0 <= x < self.image_size and 0 <= y < self.image_size:
                if button == 1:
                    self.image_data[y, x] = True
                elif button == 3:
                    self.image_data[y, x] = False
    # Метод отрисовки элементов интерфейса
    def draw(self):
        self.screen.fill(self.colors['background'])
        
        # Рисуем изображение в реальном размере
        self.draw_image_view(self.real_view_rect, self.cell_size, "Real Size")
        
        # Рисуем увеличенное изображение
        self.draw_image_view(self.zoom_view_rect, self.zoom_scale, "Zoom View")
        
        # Рисуем UI элементы
        self.draw_ui()
        
        pygame.display.flip()

    # Запуск приложения 
    def run(self):
        clock = pygame.time.Clock()
        running = True
        
        while running:
            running = self.handle_events()
            self.draw()
            clock.tick(60)
        
        pygame.quit()
        sys.exit()

    # .... Алгоритм RLE - сжатия/расжатия изображения ....
    def encode_rle(self):
        """Кодирование в RLE формат"""
        flattened = self.image_data.flatten()
        encoded = []
        current_value = flattened[0]
        count = 1
        
        for i in range(1, len(flattened)):
            if flattened[i] == current_value:
                count += 1
            else:
                encoded.append((current_value, count))
                current_value = flattened[i]
                count = 1
        
        encoded.append((current_value, count))
        return encoded
    
    def decode_rle(self, encoded, width, height):
        """Декодирование из RLE формата"""
        total_pixels = width * height
        decoded = []
        
        for value, count in encoded:
            decoded.extend([value] * count)
        
        # Обрезаем до нужного размера на случай ошибок
        decoded = decoded[:total_pixels]
        
        # Преобразуем обратно в 2D массив
        return np.array(decoded, dtype=bool).reshape((height, width))
    
    # .... .... .... .... .... .... .... .... ....

    # Способы сохранения файла в собственный формат
    def save_image(self):
        """Сохранение в собственный формат"""
        filename = "image.bin"
        
        try:
            with open(filename, 'wb') as f:
                # Заголовок: размер изображения и формат хранения
                f.write(struct.pack('III', self.image_size, self.image_size, self.storage_format.value))
                
                if self.storage_format == StorageFormat.RLE:
                    encoded = self.encode_rle()
                    # Записываем количество пар
                    f.write(struct.pack('I', len(encoded)))
                    
                    for value, count in encoded:
                        f.write(struct.pack('?I', value, count))
                
                elif self.storage_format == StorageFormat.QUADTREE:
                    self.quadtree.build_from_array(self.image_data)
                    self._save_quadtree(f, self.quadtree.root)
            print(f"Сохранение изображения: {filename}")
        except Exception as e:
            print(f"Ошибка сохранения изображения : {e}")
    
    def _save_quadtree(self, f, node):
        """Рекурсивное сохранение квадрантного дерева"""
        # Сохраняем тип узла и координаты
        is_leaf = node.is_leaf()
        f.write(struct.pack('?IIII', is_leaf, node.x, node.y, node.width, node.height))
        
        if is_leaf:
            f.write(struct.pack('?', node.value if node.value is not None else False))
        else:
            for child in node.children:
                self._save_quadtree(f, child)
    # .... .... .... .... .... .... .... .... ....

    # Способы загрузки изображения из локального компьютера
    def load_image(self):
        """Загрузка из собственного формата"""
        filename = "image.bin"
        
        if not os.path.exists(filename):
            print(f"Файл {filename} не найден")
            return
        
        try:
            with open(filename, 'rb') as f:
                # Читаем заголовок
                width, height, format_value = struct.unpack('III', f.read(12))
                self.storage_format = StorageFormat(format_value)
                
                if self.storage_format == StorageFormat.RLE:
                    num_pairs = struct.unpack('I', f.read(4))[0]
                    encoded = []

                    for _ in range(num_pairs):
                        value, count = struct.unpack('?I', f.read(5))
                        encoded.append((value, count))
                    
                    self.image_data = self.decode_rle(encoded, width, height)
                
                elif self.storage_format == StorageFormat.QUADTREE:
                    self.quadtree = QuadTree(width, height)
                    self.quadtree.root = self._load_quadtree(f)
                    self.image_data = self.quadtree.to_array()
            
            print(f"Загрузка изображения: {filename}")
        
        except Exception as e:
            print(f"Ошибка загрузки изображения: {e}")

    def _load_quadtree(self, f):
        """Рекурсивная загрузка квадрантного дерева"""
        is_leaf, x, y, width, height = struct.unpack('?IIII', f.read(17))
        node = QuadTreeNode(x, y, width, height)
        
        if is_leaf:
            node.value = struct.unpack('?', f.read(1))[0]
        else:
            node.children = [
                self._load_quadtree(f),  # NW
                self._load_quadtree(f),  # NE
                self._load_quadtree(f),  # SW
                self._load_quadtree(f)   # SE
            ]
        
        return node
    # .... .... .... .... .... .... .... .... ....

    #Способы экспорта изображения
    def export_image(self):
        """Экспорт в PNG формат"""
        try:
            # Создаем поверхность для экспорта
            export_surface = pygame.Surface((self.image_size, self.image_size))
            
            # Заполняем пиксели
            for y in range(self.image_size):
                for x in range(self.image_size):
                    color = (0, 0, 0) if self.image_data[y, x] else (255, 255, 255)
                    export_surface.set_at((x, y), color)
            
            # Сохраняем как PNG
            pygame.image.save(export_surface, "exported_image.png")
            print("Изображение экспортирована в формате exported_image.png")
        
        except Exception as e:
            print(f"Ошибка экспорта изображения: {e}")