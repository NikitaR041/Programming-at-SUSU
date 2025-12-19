import tkinter as tk
from tkinter import ttk, messagebox
import psycopg2
from tkinter import simpledialog
from psycopg2 import sql, Error

from conf import DB_NAME, DB_HOST, DB_PORT, DB_CASHIER, DB_PASSWORD_CASHIER

# # ====== Настройки подключения к базе ======
# CONFIG_CASHIER = {
#     'host': DB_HOST,
#     'database': DB_NAME,
#     'user': DB_CASHIER,
#     'password': DB_PASSWORD_CASHIER
# }

# ====== Основное окно ======
class CashierApp(tk.Tk):
    def __init__(self, user_config):
        super().__init__()
        self.db_config = user_config
        self.title("Кассовое окно")
        self.geometry("1200x800")
        
        # Списки товаров и аксессуаров
        self.products = []
        self.current_cheque_items = []

        # GUI компоненты
        self.create_widgets()
        self.load_products()

    def create_widgets(self):
        # --- Таблица товаров ---
        tk.Label(self, text="Товары и аксессуары").pack()
        self.tree_products = ttk.Treeview(self, columns=("id", "name", "price"), show='headings')
        self.tree_products.heading("id", text="ID")
        self.tree_products.heading("name", text="Название")
        self.tree_products.heading("price", text="Цена")
        self.tree_products.pack(fill=tk.X)

        # Кнопка добавления товара в чек
        tk.Button(self, text="Добавить в чек", command=self.add_to_cheque).pack(pady=5)

        # --- Таблица текущего чека ---
        tk.Label(self, text="Текущий чек").pack()
        self.tree_cheque = ttk.Treeview(self, columns=("id", "name", "price", "qty"), show='headings')
        self.tree_cheque.heading("id", text="ID")
        self.tree_cheque.heading("name", text="Название")
        self.tree_cheque.heading("price", text="Цена")
        self.tree_cheque.heading("qty", text="Кол-во")
        self.tree_cheque.pack(fill=tk.X)

        # Кнопки управления чеком
        frame = tk.Frame(self)
        frame.pack(pady=10)
        tk.Button(frame, text="Новый чек", command=self.new_cheque).grid(row=0, column=0, padx=5)
        tk.Button(frame, text="Сохранить чек", command=self.save_cheque).grid(row=0, column=1, padx=5)

    # ====== Загрузка товаров (только SELECT) ======
    def load_products(self):
        try:
            conn = psycopg2.connect(**self.db_config)
            cursor = conn.cursor()
            sql_query = """
                SELECT computer_id AS id, name_comp, price, 'computer' AS kind FROM computer 
                UNION ALL
                SELECT accessories_id AS id, name_item, price, 'accessories' AS kind FROM accessories 
                ORDER BY id;
                """
            cursor.execute(sql_query)
            self.products = cursor.fetchall()
            cursor.close()
            conn.close()

            # Очистка и заполнение таблицы
            for row in self.tree_products.get_children():
                self.tree_products.delete(row)
            for p in self.products:
                self.tree_products.insert("", tk.END, values=p)

        except Error as e:
            messagebox.showerror("Ошибка базы данных", str(e))

    # ====== Добавление товара в текущий чек ======
    def add_to_cheque(self):
        selected = self.tree_products.selection()
        if not selected:
            messagebox.showwarning("Выбор товара", "Выберите товар")
            return
        for item in selected:
            visible_values = self.tree_products.item(item, "values")
            product_id_str = visible_values[0] # ID приходит как строка

            # Находим полные данные (включая KIND) из self.products
            full_product_data = next((p for p in self.products if str(p[0]) == product_id_str), None)

            if full_product_data is None:
                 messagebox.showerror("Ошибка", "Не удалось найти тип товара.")
                 return
                 
            product_id, name, price, kind = full_product_data

            # Запрос количества
            qty = simpledialog.askinteger("Количество", f"Сколько '{name}' добавить?", minvalue=1, initialvalue=1) 
            if qty is not None and qty > 0: # Проверка на None, если пользователь нажал Отмена
                self.current_cheque_items.append((product_id, name, price, qty, kind)) 
                self.refresh_cheque()

    def refresh_cheque(self):
        for row in self.tree_cheque.get_children():
            self.tree_cheque.delete(row)
        for item in self.current_cheque_items:
            self.tree_cheque.insert("", tk.END, values=item)

    # ====== Новый чек ======
    def new_cheque(self):
        self.current_cheque_items.clear()
        self.refresh_cheque()

    # ====== Сохранение чека ======
    def save_cheque(self):
        if not self.current_cheque_items:
            messagebox.showwarning("Чек пуст", "Добавьте товары в чек")
            return
        try:
            conn = psycopg2.connect(**self.db_config)
            cursor = conn.cursor()
            
            # Создание записи в таблице cheque
            cursor.execute("INSERT INTO cheque DEFAULT VALUES RETURNING cheque_id;")
            cheque_id = cursor.fetchone()[0]

            # Добавление позиций в cheque_item
            for item in self.current_cheque_items:
                product_id, name, price, qty, kind = item
                computer_id = None
                accessories_id = None
                # Определяем, куда вставлять ID
                if kind == 'computer':
                    computer_id = product_id
                elif kind == 'accessories':
                    accessories_id = product_id
                else:
                    raise ValueError(f"Неизвестный тип товара: {kind}")
                
                sql_insert = """
                INSERT INTO cheque_item (cheque_id, computer_id, accessories_id, product_kind, count_sale_item, price_at_sale) 
                VALUES (%s, %s, %s, %s, %s, %s);
                """

                cursor.execute(
                    sql_insert,
                    (cheque_id, computer_id, accessories_id, kind, qty, price)
                )

            conn.commit()
            cursor.close()
            conn.close()

            messagebox.showinfo("Чек сохранён", f"Чек #{cheque_id} успешно сохранён")
            self.new_cheque()
        except Error as e:
            conn.rollback() # Не забываем про rollback
            messagebox.showerror("Ошибка базы данных", str(e))
            
        except ValueError as e:
            messagebox.showerror("Ошибка приложения", str(e))
            self.new_cheque()


if __name__ == "__main__":
    app = CashierApp()
    app.mainloop()
