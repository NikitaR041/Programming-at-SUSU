import tkinter as tk
from tkinter import ttk, messagebox
import psycopg2
from psycopg2 import Error

# Модуль для выполнения запросов
from manager import execute_query 

class WarehouseApp(tk.Tk):
    # Принимаем конфиг для подключения
    def __init__(self, user_config):
        super().__init__()
        self.db_config = user_config
        self.title(f"Склад (Пользователь: {self.db_config['user']})")
        self.geometry("1400x800")
        
        self.notebook = ttk.Notebook(self)
        self.notebook.pack(expand=True, fill='both', padx=10, pady=10)
        
        # Создание вкладок
        self.create_accessories_tab()
        self.create_characteristics_tab()

    def create_accessories_tab(self):
        # --- ФУНКЦИОНАЛ УПРАВЛЕНИЯ КОМПЛЕКТУЮЩИМИ (CRUD) ---
        frame = ttk.Frame(self.notebook)
        self.notebook.add(frame, text='Комплектующие и запасы')
        
        # Здесь будет таблица для accessories
        tk.Label(frame, text="Управление Комплектующими", font=('Arial', 14)).pack(pady=10)
        self.tree_accessories = self.setup_accessories_tree(frame)
        self.tree_accessories.pack(fill='both', expand=True)

        # Здесь будут кнопки CRUD (Добавить, Изменить, Удалить, Обновить)
        self.load_accessories()
        
    def setup_accessories_tree(self, parent):
        columns = ("id", "manufacturer", "company", "name", "price", "type")
        tree = ttk.Treeview(parent, columns=columns, show="headings")
        # Настройка заголовков (headings)
        # ...
        return tree

    def load_accessories(self):
        # Запрос для отображения полных данных (нужно объединение с manufacture и company)
        sql = """
        SELECT a.accessories_id, m.name_mt, c.name_company, a.name_item, a.price, a.type_item
        FROM accessories a
        JOIN manufacture m ON m.manufacture_id = a.manufacture_id
        JOIN company c ON c.company_id = a.company_id;
        """
        rows = execute_query(sql, fetch_all=True, config=self.db_config)
        
        # Обновление таблицы
        # ...

    def create_characteristics_tab(self):
        # --- ФУНКЦИОНАЛ УПРАВЛЕНИЯ ХАРАКТЕРИСТИКАМИ (VALUE_CHARACTERISTIC) ---
        frame = ttk.Frame(self.notebook)
        self.notebook.add(frame, text='Характеристики')
        
        # Здесь будет логика для управления characteristic и value_characteristic
        tk.Label(frame, text="Управление Характеристиками Комплектующих", font=('Arial', 14)).pack(pady=10)
        # ...
        pass


# Для запуска
# app = WarehouseApp(user_config)
# app.mainloop()