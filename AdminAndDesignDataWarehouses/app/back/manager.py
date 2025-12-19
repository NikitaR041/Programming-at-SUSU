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
    dbname = config.get("dbname", "UNKNOWN")
    
    try:
        connection = psycopg2.connect(**config)
        with connection.cursor() as cursor:
            # Логирование для визуализации работы
            # Выполняется запрос
            print(f"\n---[USER: {user}] A request is being executed ---")
            print(f"   SQL: {sql_query.strip()}")
            if params:
                print(f"Param: {params}")

            cursor.execute(sql_query, params)
            
            # Обработка результатов
            if fetch_one:
                result = cursor.fetchone()
                print(f"Received 1 line.")
            elif fetch_all:
                result = cursor.fetchall()
                print(f"Received {len(result)} lines.")
            else:
                connection.commit()
                result = cursor.rowcount
                print(f"Successfully modified/added {result} lines.")

            return result

    except psycopg2.Error as e:
        if connection:
            connection.rollback()
        print(f"Ошибка {user}: {e}")
        print(f"ERROR DB {dbname}: {e}")
        return None
        
    finally:
        if connection:
            connection.close()

# Теперь все другие модули будут вызывать только эту функцию.