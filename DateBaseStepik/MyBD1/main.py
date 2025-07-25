import psycopg2
from config import host, user, password, db_name, port 

# Шаблон по созданию и отправке SQL запросов
"""
Простая база данных
Сущности: Студенты, учебные предметы, задачи, результат выполения пользователя задачи
Характеристика:
1)Каждый студент хранит в себе логин, почту и пароль
2)Каждый предмет хранит в себе название учебного предмета
3)Каждая задача хранит в себе название задачи, описание и результат
4)Каждый результат хранит в себе внешние ключи от таблиц 'задачи' и 'студента'
Связи:
1) Каждый студент имеет множество учебных предметов (один ко многим)
2) Каждый учебный предмет имеет множество задач (один ко многим)
3) Каждый студент имеет множество результатов (один ко многим)
4) Каждая задача имеет множество резулатов (один ко многим)
"""
try: #Различные запросы 
    #Подключение к базе данных 
    connection = psycopg2.connect(
        host = host,
        user = user,
        password = password,
        dbname = db_name,
        port = port
    )
    # Делаем постоянным автокоммит (либо прописывать в каждом запросе)
    connection.autocommit = True

    #Для работы с базой данных - нужен курсор 
    # cursor = connection.cursor()
    with connection.cursor() as cursor:
        cursor.execute("SELECT version();")
        print(f"Server version: {cursor.fetchone()}")

    with connection.cursor() as cursor:
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS students (
                user_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                login VARCHAR(10) NOT NULL,
                email VARCHAR(20) NOT NULL,
                password VARCHAR(20) NOT NULL, 
                UNIQUE(email, password)
            );
            """
        ) 
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS objects (
                object_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                name VARCHAR(20) NOT NULL,
                user_id INT NULL,
                FOREIGN KEY (user_id) REFERENCES students (user_id)
            );
            """
        )
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS tasks (
                task_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                title VARCHAR(20) NOT NULL,
                description TEXT DEFAULT NULL,
                object_id INT NULL,
                FOREIGN KEY (object_id) REFERENCES objects (object_id)
            );
            """
        )
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS results (
                result_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                aresult SMALLINT NOT NULL,
                user_id INT NULL,
                task_id INT NULL,
                FOREIGN KEY (user_id) REFERENCES students (user_id),
                FOREIGN KEY (task_id) REFERENCES tasks (task_id)
            );
            """
        )
        print("[INFO] Table crated successfully")

except Exception as ex: # Вызов ошибок
    print("[INFO] Error while with PostgreSQL", ex)
finally: #Завершение подключения к базе данных
    if 'connection':
        print("[INFO] PostgreSQL connection closed")
