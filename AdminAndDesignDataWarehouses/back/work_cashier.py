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

#... другие функции для кассира