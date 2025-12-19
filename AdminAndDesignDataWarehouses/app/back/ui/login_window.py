import sys
import tkinter as tk
from tkinter import messagebox
import psycopg2

from conf import DB_NAME, DB_HOST, DB_PORT

# Исправление кодировки консоли (чтобы не было вопросиков)
sys.stdout.reconfigure(encoding='utf-8')

class LoginWindow:
    def __init__(self, root):
        self.root = root
        self.root.title("Вход в систему")
        self.root.geometry("300x200")

        tk.Label(root, text="Логин").pack(pady=5)
        self.entry_login = tk.Entry(root)
        self.entry_login.pack()

        tk.Label(root, text="Пароль").pack(pady=5)
        self.entry_password = tk.Entry(root, show="*")
        self.entry_password.pack()

        tk.Button(root, text="Войти", command=self.login).pack(pady=15)

    def login(self):
        user = self.entry_login.get()
        password = self.entry_password.get()

        current_config = {
            "dbname": DB_NAME,
            "user": user,
            "password": password,
            "host": DB_HOST,
            "port": DB_PORT
        }
        try:
            conn = psycopg2.connect(**current_config)

            cursor = conn.cursor()
            cursor.execute("SELECT current_user;")
            role = cursor.fetchone()[0]

            conn.close()

            messagebox.showinfo("Успех", f"Вы вошли как: {role}")
            self.open_role_window(role, current_config)

        except psycopg2.Error as e:
            messagebox.showerror("Ошибка входа", str(e))

    def open_role_window(self, role, config):
        self.root.destroy()  # закрываем логин

        if role == "guest_role":
            from ui.guest_window import open_guest_window
            open_guest_window(config)
        elif role == "cashier_role":
            from ui.cashier_window import CashierApp
            app = CashierApp(user_config=config)
            app.mainloop()
        elif role == "warehouse_role":
            from ui.warehouse_window import WarehouseApp
            app = WarehouseApp(user_config=config)
            app.mainloop()
        else:
            messagebox.showinfo("Инфо", f"Окно для роли {role} пока не реализовано")
