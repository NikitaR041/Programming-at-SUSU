import psycopg2
from psycopg2 import sql
from psycopg2 import Error
from conf import DB_NAME, DB_USER, DB_PASSWORD, DB_HOST, DB_PORT

CONFIG_DEFAULT = {
    "dbname": DB_NAME,
    "user": DB_USER,
    "password": DB_PASSWORD,
    "host": DB_HOST,
    "port": DB_PORT
}

def execute_query(sql_query, params=None, fetch_one=False, fetch_all=False, config=CONFIG_DEFAULT):
    """Универсальная функция для выполнения SQL-запросов."""
    connection = None
    user = config.get("user", "UNKNOWN")
    
    try:
        connection = psycopg2.connect(**config)
        with connection.cursor() as cursor:
            # Логирование для визуализации работы
            print(f"\n---[USER: {user}] Выполняется запрос ---")
            print(f"   SQL: {sql_query.strip()}")
            if params:
                print(f"Параметры: {params}")

            cursor.execute(sql_query, params)
            
            # Обработка результатов
            if fetch_one:
                result = cursor.fetchone()
                print(f"Получено 1 строка.")
            elif fetch_all:
                result = cursor.fetchall()
                print(f"Получено {len(result)} строк.")
            else:
                connection.commit()
                result = cursor.rowcount
                print(f"Успешно изменено/добавлено {result} строк.")

            return result

    except psycopg2.Error as e:
        if connection:
            connection.rollback()
        print(f"ОШИБКА БД для {user}: {e}")
        return None
        
    finally:
        if connection:
            connection.close()

# Теперь все другие модули будут вызывать только эту функцию.