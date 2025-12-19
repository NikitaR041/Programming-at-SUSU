import tkinter as tk
from tkinter import ttk
from manager import execute_query


def open_guest_window(config):
    root = tk.Tk()
    root.title("Гость — просмотр компьютеров")
    root.geometry("1200x800")

    tk.Label(root, text=f"Пользователь: {config['user']}", font=("Arial", 10)).pack(pady=5)
    tk.Label(root, text="Список компьютеров", font=("Arial", 14)).pack(pady=10)

    columns = ("computer_id", "name_comp", "price", "warranty_months", "build_date")
    table = ttk.Treeview(root, columns=columns, show="headings")

    table.heading("computer_id", text="ID")
    table.heading("name_comp", text="Название")
    table.heading("price", text="Цена")
    table.heading("warranty_months", text="Гарантия")
    table.heading("build_date", text="Дата сборки")

    table.pack(expand=True, fill="both")

    load_computers(table, config)

    root.mainloop()


def load_computers(table, config):
    sql = "SELECT computer_id, name_comp, price, warranty_months, build_date FROM computer;"
    rows = execute_query(sql, fetch_all=True, config=config)
    print("Результат:", rows)  # <--- здесь увидим что вернулось

    if rows:
        for row in rows:
            table.insert("", tk.END, values=row)
