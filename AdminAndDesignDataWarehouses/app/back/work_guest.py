from manager import execute_query
from conf import DB_NAME, DB_HOST, DB_PORT, DB_GUEST, DB_PASSWORD_GUEST

GUEST_CONFIG = {
    'dbname': DB_NAME,
    'user': DB_GUEST,
    'password': DB_PASSWORD_GUEST,
    'host': DB_HOST,
    'port': DB_PORT
}

def get_public_computers_list() -> list:
    """Получает список компьютеров для каталога (разрешено Гостю)."""
    sql = "SELECT computer_id, name_comp, price FROM computer ORDER BY computer_id LIMIT 3;"
    return execute_query(sql, fetch_all=True, config=GUEST_CONFIG)

def attempt_to_get_cheque_data():
    """Попытка Гостя получить финансовые данные (должна завершиться ошибкой)."""
    # Гость не имеет SELECT на таблицу cheque
    sql = "SELECT * FROM cheque LIMIT 1;"
    print("   -> Попытка получить данные из таблицы 'cheque'...")
    return execute_query(sql, fetch_all=True, config=GUEST_CONFIG)