# services.py

def get_accessories(conn):
    with conn.cursor() as cur:
        cur.execute("""
            SELECT accessories_id, name_item, price, count_item
            FROM accessories
            ORDER BY accessories_id
        """)
        return cur.fetchall()


def get_computers(conn):
    with conn.cursor() as cur:
        cur.execute("""
            SELECT computer_id, name_comp, price, count_item
            FROM computer
            ORDER BY computer_id
        """)
        return cur.fetchall()


def create_cheque(conn, shopper_id: int):
    with conn.cursor() as cur:
        cur.execute("""
            INSERT INTO cheque (shopper_id, date_sale)
            VALUES (%s, CURRENT_DATE)
            RETURNING cheque_id
        """, (shopper_id,))
        cheque_id = cur.fetchone()[0]
    conn.commit()
    return cheque_id


def sell_accessory(conn, cheque_id: int, accessories_id: int, qty: int, price: float):
    with conn.cursor() as cur:
        cur.execute("""
            INSERT INTO cheque_item
            (cheque_id, accessories_id, product_kind, count_sale_item, price_at_sale)
            VALUES (%s, %s, 'accessories', %s, %s)
        """, (cheque_id, accessories_id, qty, price))
    conn.commit()


def sell_computer(conn, cheque_id: int, computer_id: int, qty: int, price: float):
    with conn.cursor() as cur:
        cur.execute("""
            INSERT INTO cheque_item
            (cheque_id, computer_id, product_kind, count_sale_item, price_at_sale)
            VALUES (%s, %s, 'computer', %s, %s)
        """, (cheque_id, computer_id, qty, price))
    conn.commit()


def get_cheque_total(conn, cheque_id: int):
    with conn.cursor() as cur:
        cur.execute("SELECT get_cheque_total(%s);", (cheque_id,))
        return cur.fetchone()[0]


def get_cheque_items(conn, cheque_id: int):
    """
    Возвращает позиции чека с названием товара (аксессуар/компьютер).
    """
    with conn.cursor() as cur:
        cur.execute("""
            SELECT
                ci.position_id,
                ci.product_kind,
                COALESCE(a.name_item, c.name_comp) AS item_name,
                ci.count_sale_item,
                ci.price_at_sale,
                (ci.count_sale_item * ci.price_at_sale) AS line_total
            FROM cheque_item ci
            LEFT JOIN accessories a ON a.accessories_id = ci.accessories_id
            LEFT JOIN computer c ON c.computer_id = ci.computer_id
            WHERE ci.cheque_id = %s
            ORDER BY ci.position_id
        """, (cheque_id,))
        return cur.fetchall()


# ------------------
# Ниже расписана система CRUD для таблицы accessories

#Функция обработки создания записи в таблице accessories
def create_accessory(conn, manufacture_id: int, company_id: int, name_item: str,
                     price, type_item: str, count_item: int):
    with conn.cursor() as cur:
        cur.execute("""
            INSERT INTO accessories (manufacture_id, company_id, name_item, price, type_item, count_item)
            VALUES (%s, %s, %s, %s, %s, %s)
            RETURNING accessories_id
        """, (manufacture_id, company_id, name_item, price, type_item, count_item))
        new_id = cur.fetchone()[0]
    conn.commit()
    return new_id

#Функция обработки обновления записи в таблице accessories
def update_accessory(conn, accessories_id: int, manufacture_id: int, company_id: int, name_item: str,
                     price, type_item: str, count_item: int):
    with conn.cursor() as cur:
        cur.execute("""
            UPDATE accessories
            SET manufacture_id=%s,
                company_id=%s,
                name_item=%s,
                price=%s,
                type_item=%s,
                count_item=%s
            WHERE accessories_id=%s
        """, (manufacture_id, company_id, name_item, price, type_item, count_item, accessories_id))
    conn.commit()

#Функция обработки удаления записи в таблице accessories
def delete_accessory(conn, accessories_id: int):
    with conn.cursor() as cur:
        cur.execute("DELETE FROM accessories WHERE accessories_id=%s", (accessories_id,))
    conn.commit()

#Функция получения всех записей из таблицы accessories с полным набором полей
def get_accessories_full(conn):
    """
    Для админ-таблицы: показываем больше полей.
    """
    with conn.cursor() as cur:
        cur.execute("""
            SELECT accessories_id, manufacture_id, company_id, name_item, price, type_item, count_item
            FROM accessories
            ORDER BY accessories_id
        """)
        return cur.fetchall()

# Ниже расписана система CRUD для таблицы computer

def get_computers_full(conn):
    with conn.cursor() as cur:
        cur.execute("""
            SELECT computer_id, name_comp, price, warranty_months, build_date, count_item
            FROM computer
            ORDER BY computer_id
        """)
        return cur.fetchall()


def create_computer(conn, name_comp: str, price, warranty_months: int, build_date, count_item: int):
    with conn.cursor() as cur:
        cur.execute("""
            INSERT INTO computer (name_comp, price, warranty_months, build_date, count_item)
            VALUES (%s, %s, %s, %s, %s)
            RETURNING computer_id
        """, (name_comp, price, warranty_months, build_date, count_item))
        new_id = cur.fetchone()[0]
    conn.commit()
    return new_id


def update_computer(conn, computer_id: int, name_comp: str, price, warranty_months: int, build_date, count_item: int):
    with conn.cursor() as cur:
        cur.execute("""
            UPDATE computer
            SET name_comp=%s,
                price=%s,
                warranty_months=%s,
                build_date=%s,
                count_item=%s
            WHERE computer_id=%s
        """, (name_comp, price, warranty_months, build_date, count_item, computer_id))
    conn.commit()


def delete_computer(conn, computer_id: int):
    with conn.cursor() as cur:
        cur.execute("DELETE FROM computer WHERE computer_id=%s", (computer_id,))
    conn.commit()