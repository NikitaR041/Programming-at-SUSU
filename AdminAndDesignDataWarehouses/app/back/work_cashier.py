import psycopg2
from psycopg2 import sql
from psycopg2 import Error
from manager import execute_query
from datetime import date
from conf import DB_NAME, DB_CASHIER, DB_PASSWORD_CASHIER, DB_HOST, DB_PORT

CONFIG_CASHIER = {
    "dbname": DB_NAME,
    "user": DB_CASHIER,
    "password": DB_PASSWORD_CASHIER,
    "host": DB_HOST,
    "port": DB_PORT
}

def create_new_cheque(shopper_id):
    """Создает новый чек под ролью Кассира."""
    sql = "INSERT INTO cheque (shopper_id, date_sale) VALUES (%s, %s) RETURNING cheque_id;"
    params = (shopper_id, date.today())
    
    # ПЕРЕДАЧА КОНФИГУРАЦИИ: Здесь мы явно указываем, какую конфигурацию использовать
    result = execute_query(sql, params=params, fetch_one=True, config=CONFIG_CASHIER)
    
    return result[0] if result else None

def create_new_cheque(shopper_id):
    """
    Создаёт новый чек.
    Возвращает cheque_id.
    """
    sql = """
        INSERT INTO cheque (shopper_id, date_sale)
        VALUES (%s, %s)
        RETURNING cheque_id;
    """
    params = (shopper_id, date.today())

    result = execute_query(
        sql, params=params, fetch_one=True, config=CONFIG_CASHIER
    )

    return result[0] if result else None

def add_cheque_item(
    cheque_id,
    product_kind,
    count_sale_item,
    price_at_sale,
    computer_id=None,
    accessories_id=None
):
    """
    Добавляет позицию в чек.
    product_kind: 'computer' | 'accessories'
    """
    sql = """
        INSERT INTO cheque_item (
            cheque_id,
            computer_id,
            accessories_id,
            product_kind,
            count_sale_item,
            price_at_sale
        )
        VALUES (%s, %s, %s, %s, %s, %s);
    """

    params = (
        cheque_id,
        computer_id,
        accessories_id,
        product_kind,
        count_sale_item,
        price_at_sale
    )

    return execute_query(sql, params=params, config=CONFIG_CASHIER)

def get_cheque_items(cheque_id):
    """
    Возвращает список позиций чека.
    """
    sql = """
        SELECT
            position_id,
            product_kind,
            computer_id,
            accessories_id,
            count_sale_item,
            price_at_sale
        FROM cheque_item
        WHERE cheque_id = %s;
    """

    return execute_query(
        sql, params=(cheque_id,), fetch_all=True, config=CONFIG_CASHIER
    )

def get_cheque_total(cheque_id):
    """
    Возвращает итоговую сумму чека.
    """
    sql = "SELECT get_cheque_total(%s);"

    result = execute_query(
        sql, params=(cheque_id,), fetch_one=True, config=CONFIG_CASHIER
    )

    return result[0] if result else 0

def get_computers():
    """
    Список всех компьютеров (только чтение).
    """
    sql = """
        SELECT computer_id, name_comp, price, warranty_months
        FROM computer;
    """

    return execute_query(sql, fetch_all=True, config=CONFIG_CASHIER)

def get_accessories():
    """
    Список комплектующих (только чтение).
    """
    sql = """
        SELECT accessories_id, name_item, price, type_item
        FROM accessories;
    """

    return execute_query(sql, fetch_all=True, config=CONFIG_CASHIER)
