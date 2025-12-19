import psycopg2
from psycopg2 import sql
from psycopg2 import Error
from manager import execute_query
from datetime import date
from conf import DB_NAME, DB_ANALYST, DB_PASSWORD_ANALYST, DB_HOST, DB_PORT

CONFIG_ANALYST = {
    "dbname": DB_NAME,
    "user": DB_ANALYST,
    "password": DB_PASSWORD_ANALYST,
    "host": DB_HOST,
    "port": DB_PORT
}
#Возвращает сумму чека - вызывает метод get_cheque_total из базы данных
def get_cheque_total_amount(cheque_id: int) -> float:
    sql = "SELECT get_cheque_total(%s);"
    params = (cheque_id,)
    
    # Ожидаем одно значение (сумму)
    result = execute_query(sql, params=params, fetch_one=True, config=CONFIG_ANALYST)
    
    # Возвращаем первое значение из кортежа (сумма) или 0.0, если ошибка
    return float(result[0]) if result else 0.0

#Возвращает конфигурацию компьютера - вызывает метод get_computer_configuration из базы данных
def get_computer_config_report(computer_id: int) -> list:
    sql = "SELECT component_name, quantity FROM get_computer_configuration(%s);"
    params = (computer_id,)
    
    # Ожидаем множество строк (компоненты и их количество)
    result = execute_query(sql, params=params, fetch_all=True, config=CONFIG_ANALYST)
    
    # Возвращаем список кортежей
    return result if result else []

#Возвращает все фирмы - это странно
def get_all_companies() -> list:
    """
    Получает список всех фирм (простой SELECT).
    """
    sql = "SELECT company_id, name_company, address FROM company;"
    # Аналитик имеет SELECT на таблицу company
    result = execute_query(sql, fetch_all=True, config=CONFIG_ANALYST)
    return result if result else []