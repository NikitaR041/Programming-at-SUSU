import psycopg2
from config import host, user, password, db_name, port 

# Шаблон по созданию и отправке SQL запросов

try: #Различные запросы 
    #Подключение к базе данных 
    connection = psycopg2.connect(
        host = host,
        user = user,
        password = password,
        dbname = db_name,
        port = port
    )
    #Для работы с базой данных - нужен курсор 
    # cursor = connection.cursor()
    with connection.cursor() as cursor:
        cursor.execute(
            "SELECT version();"
        ) 
        print(f"Server version: {cursor.fetchone()}")

except Exception as ex: # Вызов ошибок
    print("[INFO] Error while with PostgreSQL", ex)
finally: #Завершение подключения к базе данных
    if 'connection':
        print("[INFO] PostgreSQL connection closed")
