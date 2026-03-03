# ui.py
import tkinter as tk
from tkinter import ttk, messagebox

from db import get_connection

class LoginWindow(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Авторизация")
        self.geometry("360x200")
        self.resizable(False, False)

        # Чтобы русские сообщения в консоль не были кракозябрами (часто помогает)
        try:
            import sys
            sys.stdout.reconfigure(encoding="utf-8")
            sys.stderr.reconfigure(encoding="utf-8")
        except Exception:
            pass

        self.username_var = tk.StringVar(value="seller_role")
        self.password_var = tk.StringVar()

        frm = ttk.Frame(self, padding=14)
        frm.pack(fill="both", expand=True)

        ttk.Label(frm, text="Логин (роль Postgres):").grid(row=0, column=0, sticky="w")
        ttk.Entry(frm, textvariable=self.username_var).grid(row=1, column=0, sticky="ew", pady=(4, 10))

        ttk.Label(frm, text="Пароль:").grid(row=2, column=0, sticky="w")
        pwd = ttk.Entry(frm, textvariable=self.password_var, show="•")
        pwd.grid(row=3, column=0, sticky="ew", pady=(4, 12))
        pwd.bind("<Return>", lambda e: self.try_login())

        btns = ttk.Frame(frm)
        btns.grid(row=4, column=0, sticky="e")

        ttk.Button(btns, text="Войти", command=self.try_login).pack(side="right")
        ttk.Button(btns, text="Выход", command=self.destroy).pack(side="right", padx=(0, 8))

        frm.columnconfigure(0, weight=1)

    def try_login(self):
        user = self.username_var.get().strip()
        pwd = self.password_var.get()

        if not user or not pwd:
            messagebox.showwarning("Вход", "Введите логин и пароль.")
            return

        try:
            conn = get_connection(user=user, password=pwd)

            # Быстрая проверка, что соединение живое
            with conn.cursor() as cur:
                cur.execute("SELECT current_user;")
                current_user = cur.fetchone()[0]

            # Прячем окно входа и открываем главное
            self.withdraw()
            MainWindow(parent=self, conn=conn, current_user=current_user)

        except Exception as ex:
            # Здесь может быть: неправильный пароль, нет прав, БД не запущена и т.п.
            messagebox.showerror("Ошибка входа", f"Не удалось подключиться к БД.\n\n{ex}")

from services import (
    get_accessories, get_computers, create_cheque,
    sell_accessory, sell_computer, get_cheque_total, get_cheque_items,
    create_accessory, update_accessory, delete_accessory, get_accessories_full,
    get_computers_full, create_computer, update_computer, delete_computer
)


class MainWindow(tk.Toplevel):
    def __init__(self, parent: tk.Tk, conn, current_user: str):
        super().__init__(parent)
        self.parent = parent
        self.conn = conn
        self.current_user = current_user

        self.title(f"Пульс цен — {current_user}")
        self.geometry("900x520")
        # center_window(self)

        self.protocol("WM_DELETE_WINDOW", self.on_close)

        # Layout: left menu + right content
        root = ttk.Frame(self, padding=10)
        root.pack(fill="both", expand=True)

        self.menu = ttk.Frame(root)
        self.menu.pack(side="left", fill="y")

        self.content = ttk.Frame(root)
        self.content.pack(side="left", fill="both", expand=True, padx=(12, 0))

        ttk.Label(self.menu, text=f"Роль: {current_user}").pack(anchor="w", pady=(0, 10))
        ttk.Button(self.menu, text="Продажа", command=self.open_sale_screen).pack(fill="x", pady=3)

        # Кнопки только для админа
        if current_user == "admin_role":
            ttk.Separator(self.menu).pack(fill="x", pady=8)
            ttk.Label(self.menu, text="Администрирование").pack(anchor="w", pady=(0, 6))
            ttk.Button(self.menu, text="Комплектующие", command=self.open_accessories_crud).pack(fill="x", pady=3)
            ttk.Button(self.menu, text="Компьютеры", command=self.open_computers_crud).pack(fill="x", pady=3)

        ttk.Separator(self.menu).pack(fill="x", pady=10)
        ttk.Button(self.menu, text="Выйти", command=self.logout).pack(fill="x", pady=3)

        # стартовый экран
        self.open_sale_screen()

    def clear_content(self):
        for w in self.content.winfo_children():
            w.destroy()

    # ui.py - внутри MainWindow
    def open_accessories_crud(self):
        self.clear_content()
        AccessoriesCrudScreen(self.content, self.conn)

    def open_computers_crud(self):
        self.clear_content()
        ComputersCrudScreen(self.content, self.conn)

    def open_sale_screen(self):
        self.clear_content()
        SaleScreen(self.content, self.conn)

    def logout(self):
        try:
            self.conn.close()
        except Exception:
            pass
        self.destroy()
        self.parent.deiconify()

    def on_close(self):
        self.logout()


class SaleScreen(ttk.Frame):
    def __init__(self, parent, conn):
        super().__init__(parent)
        self.conn = conn
        self.pack(fill="both", expand=True)

        self.cheque_id = None

        # --- верх: создание чека ---
        top = ttk.LabelFrame(self, text="Чек", padding=10)
        top.pack(fill="x")

        self.shopper_id_var = tk.StringVar()
        ttk.Label(top, text="shopper_id:").grid(row=0, column=0, sticky="w")
        ttk.Entry(top, textvariable=self.shopper_id_var, width=12).grid(row=0, column=1, sticky="w", padx=(6, 12))

        ttk.Button(top, text="Создать чек", command=self.create_new_cheque).grid(row=0, column=2, sticky="w")

        self.cheque_label = ttk.Label(top, text="Чек не создан")
        self.cheque_label.grid(row=0, column=3, sticky="w", padx=(12, 0))

        top.columnconfigure(4, weight=1)

        # --- середина: добавление позиции ---
        mid = ttk.LabelFrame(self, text="Добавить позицию", padding=10)
        mid.pack(fill="x", pady=(10, 0))

        self.kind_var = tk.StringVar(value="accessories")
        ttk.Radiobutton(mid, text="Комплектующее", variable=self.kind_var, value="accessories",
                        command=self.reload_items).grid(row=0, column=0, sticky="w")
        ttk.Radiobutton(mid, text="Компьютер", variable=self.kind_var, value="computer",
                        command=self.reload_items).grid(row=0, column=1, sticky="w", padx=(12, 0))

        ttk.Label(mid, text="Товар:").grid(row=1, column=0, sticky="w", pady=(10, 0))
        self.item_combo = ttk.Combobox(mid, state="readonly", width=50)
        self.item_combo.grid(row=1, column=1, columnspan=3, sticky="we", pady=(10, 0))
        self.item_combo.bind("<<ComboboxSelected>>", lambda e: self.fill_price_from_selected())

        ttk.Label(mid, text="Кол-во:").grid(row=2, column=0, sticky="w", pady=(10, 0))
        self.qty_var = tk.StringVar(value="1")
        ttk.Entry(mid, textvariable=self.qty_var, width=10).grid(row=2, column=1, sticky="w", pady=(10, 0))

        ttk.Label(mid, text="Цена (на момент продажи):").grid(row=2, column=2, sticky="w", padx=(12, 0), pady=(10, 0))
        self.price_var = tk.StringVar()
        ttk.Entry(mid, textvariable=self.price_var, width=12).grid(row=2, column=3, sticky="w", pady=(10, 0))

        ttk.Button(mid, text="Добавить в чек", command=self.add_item).grid(row=3, column=3, sticky="e", pady=(12, 0))

        mid.columnconfigure(1, weight=1)

        # --- низ: позиции и сумма ---
        bottom = ttk.Frame(self)
        bottom.pack(fill="both", expand=True, pady=(10, 0))

        self.total_label = ttk.Label(bottom, text="Сумма: 0")
        self.total_label.pack(anchor="w")

        cols = ("id", "kind", "name", "qty", "price", "sum")
        self.tree = ttk.Treeview(bottom, columns=cols, show="headings", height=12)
        for c, t, w in [
            ("id", "ID", 60),
            ("kind", "Тип", 110),
            ("name", "Товар", 360),
            ("qty", "Кол-во", 80),
            ("price", "Цена", 110),
            ("sum", "Сумма", 110),
        ]:
            self.tree.heading(c, text=t)
            self.tree.column(c, width=w, anchor="w")
        self.tree.pack(fill="both", expand=True)

        # загрузка списка по умолчанию
        self.items_cache = []   # список кортежей из БД
        self.reload_items()

    def create_new_cheque(self):
        try:
            shopper_id = int(self.shopper_id_var.get().strip())
            self.cheque_id = create_cheque(self.conn, shopper_id)
            self.cheque_label.config(text=f"cheque_id = {self.cheque_id}")
            self.refresh_positions()
        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка", f"Не удалось создать чек.\n\n{ex}")

    def reload_items(self):
        """
        Перезагружаем товары в зависимости от выбранного типа.
        """
        try:
            if self.kind_var.get() == "accessories":
                self.items_cache = get_accessories(self.conn)  # (id, name, price, count_item)
                values = [f"{r[0]} — {r[1]} (цена: {r[2]}, остаток: {r[3]})" for r in self.items_cache]
            else:
                self.items_cache = get_computers(self.conn)    # (id, name, price, count_item)
                values = [f"{r[0]} — {r[1]} (цена: {r[2]}, остаток: {r[3]})" for r in self.items_cache]

            self.item_combo["values"] = values
            if values:
                self.item_combo.current(0)
                self.fill_price_from_selected()
        except Exception as ex:
            messagebox.showerror("Ошибка", str(ex))

    def fill_price_from_selected(self):
        """
        Подставляем цену выбранного товара в поле price_at_sale (можно менять вручную).
        """
        idx = self.item_combo.current()
        if idx < 0 or idx >= len(self.items_cache):
            return
        price = self.items_cache[idx][2]
        self.price_var.set(str(price))

    def add_item(self):
        if not self.cheque_id:
            messagebox.showwarning("Продажа", "Сначала создайте чек.")
            return

        try:
            idx = self.item_combo.current()
            if idx < 0:
                messagebox.showwarning("Продажа", "Выберите товар.")
                return

            item_id = int(self.items_cache[idx][0])
            qty = int(self.qty_var.get().strip())
            price = float(self.price_var.get().strip().replace(",", "."))

            if qty <= 0:
                messagebox.showwarning("Продажа", "Количество должно быть > 0.")
                return

            # Вставка позиции запускает ТВОЙ триггер списания со склада
            if self.kind_var.get() == "accessories":
                sell_accessory(self.conn, self.cheque_id, item_id, qty, price)
            else:
                sell_computer(self.conn, self.cheque_id, item_id, qty, price)

            self.refresh_positions()
            # чтобы в комбобоксе обновились остатки
            self.reload_items()

        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка продажи", str(ex))

    def refresh_positions(self):
        """
        Обновить таблицу позиций и сумму.
        """
        if not self.cheque_id:
            self.total_label.config(text="Сумма: 0")
            for i in self.tree.get_children():
                self.tree.delete(i)
            return

        try:
            rows = get_cheque_items(self.conn, self.cheque_id)
            for i in self.tree.get_children():
                self.tree.delete(i)

            for r in rows:
                # (position_id, product_kind, item_name, qty, price, line_total)
                self.tree.insert("", "end", values=r)

            total = get_cheque_total(self.conn, self.cheque_id)
            self.total_label.config(text=f"Сумма: {total}")

        except Exception as ex:
            messagebox.showerror("Ошибка", str(ex))

# ui.py (добавь)
class AccessoryDialog(tk.Toplevel):
    def __init__(self, parent, title: str, initial=None):
        super().__init__(parent)
        self.title(title)
        self.resizable(False, False)

        self.result = None  # сюда вернём данные, если нажали OK

        frm = ttk.Frame(self, padding=12)
        frm.pack(fill="both", expand=True)

        # initial: (manufacture_id, company_id, name_item, price, type_item, count_item)
        m_id = "" if initial is None else str(initial[0])
        c_id = "" if initial is None else str(initial[1])
        name = "" if initial is None else str(initial[2])
        price = "" if initial is None else str(initial[3])
        t_item = "" if initial is None else str(initial[4])
        qty = "1" if initial is None else str(initial[5])

        self.manufacture_var = tk.StringVar(value=m_id)
        self.company_var = tk.StringVar(value=c_id)
        self.name_var = tk.StringVar(value=name)
        self.price_var = tk.StringVar(value=price)
        self.type_var = tk.StringVar(value=t_item)
        self.qty_var = tk.StringVar(value=qty)

        def add_row(r, label, var):
            ttk.Label(frm, text=label).grid(row=r, column=0, sticky="w", pady=4)
            ttk.Entry(frm, textvariable=var, width=35).grid(row=r, column=1, sticky="ew", pady=4)

        add_row(0, "manufacture_id:", self.manufacture_var)
        add_row(1, "company_id:", self.company_var)
        add_row(2, "name_item:", self.name_var)
        add_row(3, "price:", self.price_var)
        add_row(4, "type_item:", self.type_var)
        add_row(5, "count_item:", self.qty_var)

        btns = ttk.Frame(frm)
        btns.grid(row=6, column=0, columnspan=2, sticky="e", pady=(10, 0))

        ttk.Button(btns, text="Отмена", command=self.on_cancel).pack(side="right")
        ttk.Button(btns, text="OK", command=self.on_ok).pack(side="right", padx=(0, 8))

        frm.columnconfigure(1, weight=1)

        self.transient(parent)
        self.grab_set()
        self.wait_visibility()
        self.focus()

    def on_ok(self):
        try:
            manufacture_id = int(self.manufacture_var.get().strip())
            company_id = int(self.company_var.get().strip())
            name_item = self.name_var.get().strip()
            type_item = self.type_var.get().strip()

            if not name_item:
                messagebox.showwarning("Проверка", "name_item не может быть пустым.")
                return
            if not type_item:
                messagebox.showwarning("Проверка", "type_item не может быть пустым.")
                return

            price = float(self.price_var.get().strip().replace(",", "."))
            count_item = int(self.qty_var.get().strip())
            if count_item < 0:
                messagebox.showwarning("Проверка", "count_item не может быть отрицательным.")
                return

            self.result = (manufacture_id, company_id, name_item, price, type_item, count_item)
            self.destroy()
        except Exception as ex:
            messagebox.showerror("Ошибка ввода", str(ex))

    def on_cancel(self):
        self.result = None
        self.destroy()

class AccessoriesCrudScreen(ttk.Frame):
    def __init__(self, parent, conn):
        super().__init__(parent)
        self.conn = conn
        self.pack(fill="both", expand=True)

        from services import get_accessories_full, create_accessory, update_accessory, delete_accessory
        self.get_accessories_full = get_accessories_full
        self.create_accessory = create_accessory
        self.update_accessory = update_accessory
        self.delete_accessory = delete_accessory

        top = ttk.Frame(self)
        top.pack(fill="x")

        ttk.Label(top, text="Комплектующие", font=("Segoe UI", 12, "bold")).pack(side="left")

        btns = ttk.Frame(top)
        btns.pack(side="right")
        ttk.Button(btns, text="Обновить", command=self.reload).pack(side="right", padx=4)
        ttk.Button(btns, text="Удалить", command=self.delete_selected).pack(side="right", padx=4)
        ttk.Button(btns, text="Изменить", command=self.edit_selected).pack(side="right", padx=4)
        ttk.Button(btns, text="Добавить", command=self.add_new).pack(side="right", padx=4)

        cols = ("id", "man", "comp", "name", "price", "type", "qty")
        self.tree = ttk.Treeview(self, columns=cols, show="headings", height=16)
        headings = {
            "id": "ID",
            "man": "manufacture_id",
            "comp": "company_id",
            "name": "name_item",
            "price": "price",
            "type": "type_item",
            "qty": "count_item",
        }
        widths = {"id": 60, "man": 120, "comp": 110, "name": 260, "price": 100, "type": 140, "qty": 90}

        for c in cols:
            self.tree.heading(c, text=headings[c])
            self.tree.column(c, width=widths[c], anchor="w")

        self.tree.pack(fill="both", expand=True, pady=(10, 0))
        self.tree.bind("<Double-1>", lambda e: self.edit_selected())

        self.reload()

    def reload(self):
        try:
            rows = self.get_accessories_full(self.conn)
            for i in self.tree.get_children():
                self.tree.delete(i)
            for r in rows:
                # r = (id, manufacture_id, company_id, name_item, price, type_item, count_item)
                self.tree.insert("", "end", values=r)
        except Exception as ex:
            messagebox.showerror("Ошибка", str(ex))

    def get_selected(self):
        sel = self.tree.selection()
        if not sel:
            return None
        return self.tree.item(sel[0], "values")

    def add_new(self):
        print("ADD NEW clicked")
        dlg = AccessoryDialog(self, "Добавить комплектующее", initial=None)
        self.wait_window(dlg)
        print("Dialog result:", dlg.result)
        if dlg.result is None:
            return
        try:
            manufacture_id, company_id, name_item, price, type_item, count_item = dlg.result
            self.create_accessory(self.conn, manufacture_id, company_id, name_item, price, type_item, count_item)
            self.reload()
        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка добавления", str(ex))

    def edit_selected(self):
        selected = self.get_selected()
        if selected is None:
            messagebox.showwarning("Изменить", "Сначала выберите строку.")
            return

        # selected строки из Treeview приходят как строки
        accessories_id = int(selected[0])
        initial = (int(selected[1]), int(selected[2]), selected[3], float(selected[4]), selected[5], int(selected[6]))

        dlg = AccessoryDialog(self, f"Изменить комплектующее ID={accessories_id}", initial=initial)
        self.wait_window(dlg)

        if dlg.result is None:
            return

        try:
            manufacture_id, company_id, name_item, price, type_item, count_item = dlg.result
            self.update_accessory(self.conn, accessories_id, manufacture_id, company_id, name_item, price, type_item, count_item)
            self.reload()
        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка изменения", str(ex))

    def delete_selected(self):
        selected = self.get_selected()
        if selected is None:
            messagebox.showwarning("Удалить", "Сначала выберите строку.")
            return

        accessories_id = int(selected[0])
        if not messagebox.askyesno("Подтверждение", f"Удалить комплектующее ID={accessories_id}?"):
            return

        try:
            self.delete_accessory(self.conn, accessories_id)
            self.reload()
        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка удаления", str(ex))

# ui.py (добавь рядом с AccessoryDialog)

class ComputerDialog(tk.Toplevel):
    def __init__(self, parent, title: str, initial=None):
        super().__init__(parent)
        self.title(title)
        self.resizable(False, False)
        self.result = None

        frm = ttk.Frame(self, padding=12)
        frm.pack(fill="both", expand=True)

        # initial: (name_comp, price, warranty_months, build_date, count_item)
        name = "" if initial is None else str(initial[0])
        price = "" if initial is None else str(initial[1])
        warranty = "12" if initial is None else str(initial[2])
        build_date = "" if initial is None else str(initial[3])  # ожидаем YYYY-MM-DD
        qty = "1" if initial is None else str(initial[4])

        self.name_var = tk.StringVar(value=name)
        self.price_var = tk.StringVar(value=price)
        self.warranty_var = tk.StringVar(value=warranty)
        self.build_date_var = tk.StringVar(value=build_date)
        self.qty_var = tk.StringVar(value=qty)

        def add_row(r, label, var, hint=None):
            ttk.Label(frm, text=label).grid(row=r, column=0, sticky="w", pady=4)
            ttk.Entry(frm, textvariable=var, width=35).grid(row=r, column=1, sticky="ew", pady=4)
            if hint:
                ttk.Label(frm, text=hint).grid(row=r, column=2, sticky="w", padx=(10, 0))

        add_row(0, "name_comp:", self.name_var)
        add_row(1, "price:", self.price_var)
        add_row(2, "warranty_months:", self.warranty_var)
        add_row(3, "build_date:", self.build_date_var, hint="формат: YYYY-MM-DD")
        add_row(4, "count_item:", self.qty_var)

        btns = ttk.Frame(frm)
        btns.grid(row=5, column=0, columnspan=3, sticky="e", pady=(10, 0))
        ttk.Button(btns, text="Отмена", command=self.on_cancel).pack(side="right")
        ttk.Button(btns, text="OK", command=self.on_ok).pack(side="right", padx=(0, 8))

        frm.columnconfigure(1, weight=1)

        self.transient(parent)
        self.grab_set()
        self.wait_visibility()
        self.focus()

    def on_ok(self):
        try:
            name_comp = self.name_var.get().strip()
            if not name_comp:
                messagebox.showwarning("Проверка", "name_comp не может быть пустым.")
                return

            price = float(self.price_var.get().strip().replace(",", "."))
            warranty_months = int(self.warranty_var.get().strip())
            if warranty_months <= 0:
                messagebox.showwarning("Проверка", "warranty_months должен быть > 0.")
                return

            build_date = self.build_date_var.get().strip()
            # Не валидируем жёстко, пусть Postgres проверит дату (так проще для курсовой)
            if not build_date:
                messagebox.showwarning("Проверка", "build_date обязателен (YYYY-MM-DD).")
                return

            count_item = int(self.qty_var.get().strip())
            if count_item < 0:
                messagebox.showwarning("Проверка", "count_item не может быть отрицательным.")
                return

            self.result = (name_comp, price, warranty_months, build_date, count_item)
            self.destroy()
        except Exception as ex:
            messagebox.showerror("Ошибка ввода", str(ex))

    def on_cancel(self):
        self.result = None
        self.destroy()

# ui.py (добавь)

class ComputersCrudScreen(ttk.Frame):
    def __init__(self, parent, conn):
        super().__init__(parent)
        self.conn = conn
        self.pack(fill="both", expand=True)

        from services import get_computers_full, create_computer, update_computer, delete_computer
        self.get_computers_full = get_computers_full
        self.create_computer = create_computer
        self.update_computer = update_computer
        self.delete_computer = delete_computer

        top = ttk.Frame(self)
        top.pack(fill="x")

        ttk.Label(top, text="Компьютеры", font=("Segoe UI", 12, "bold")).pack(side="left")

        btns = ttk.Frame(top)
        btns.pack(side="right")
        ttk.Button(btns, text="Обновить", command=self.reload).pack(side="right", padx=4)
        ttk.Button(btns, text="Удалить", command=self.delete_selected).pack(side="right", padx=4)
        ttk.Button(btns, text="Изменить", command=self.edit_selected).pack(side="right", padx=4)
        ttk.Button(btns, text="Добавить", command=self.add_new).pack(side="right", padx=4)

        cols = ("id", "name", "price", "warranty", "build_date", "qty")
        self.tree = ttk.Treeview(self, columns=cols, show="headings", height=16)

        headings = {
            "id": "ID",
            "name": "name_comp",
            "price": "price",
            "warranty": "warranty_months",
            "build_date": "build_date",
            "qty": "count_item",
        }
        widths = {"id": 60, "name": 280, "price": 100, "warranty": 140, "build_date": 120, "qty": 100}

        for c in cols:
            self.tree.heading(c, text=headings[c])
            self.tree.column(c, width=widths[c], anchor="w")

        self.tree.pack(fill="both", expand=True, pady=(10, 0))
        self.tree.bind("<Double-1>", lambda e: self.edit_selected())

        self.reload()

    def reload(self):
        try:
            rows = self.get_computers_full(self.conn)
            for i in self.tree.get_children():
                self.tree.delete(i)
            for r in rows:
                # r = (computer_id, name_comp, price, warranty_months, build_date, count_item)
                self.tree.insert("", "end", values=r)
        except Exception as ex:
            messagebox.showerror("Ошибка", str(ex))

    def get_selected(self):
        sel = self.tree.selection()
        if not sel:
            return None
        return self.tree.item(sel[0], "values")

    def add_new(self):
        print("ADD NEW clicked")
        dlg = ComputerDialog(self, "Добавить компьютер", initial=None)
        self.wait_window(dlg)
        print("Dialog result:", dlg.result)
        if dlg.result is None:
            return
        try:
            name_comp, price, warranty_months, build_date, count_item = dlg.result
            self.create_computer(self.conn, name_comp, price, warranty_months, build_date, count_item)
            self.reload()
        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка добавления", str(ex))

    def edit_selected(self):
        selected = self.get_selected()
        if selected is None:
            messagebox.showwarning("Изменить", "Сначала выберите строку.")
            return

        computer_id = int(selected[0])
        initial = (selected[1], float(selected[2]), int(selected[3]), str(selected[4]), int(selected[5]))

        dlg = ComputerDialog(self, f"Изменить компьютер ID={computer_id}", initial=initial)
        self.wait_window(dlg)
        
        if dlg.result is None:
            return

        try:
            name_comp, price, warranty_months, build_date, count_item = dlg.result
            self.update_computer(self.conn, computer_id, name_comp, price, warranty_months, build_date, count_item)
            self.reload()
        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка изменения", str(ex))

    def delete_selected(self):
        selected = self.get_selected()
        if selected is None:
            messagebox.showwarning("Удалить", "Сначала выберите строку.")
            return

        computer_id = int(selected[0])
        if not messagebox.askyesno("Подтверждение", f"Удалить компьютер ID={computer_id}?"):
            return

        try:
            self.delete_computer(self.conn, computer_id)
            self.reload()
        except Exception as ex:
            try:
                self.conn.rollback()
            except Exception:
                pass
            messagebox.showerror("Ошибка удаления", str(ex))
