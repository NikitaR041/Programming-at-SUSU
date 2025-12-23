import psycopg2
from psycopg2.extensions import connection

DB_HOST = "localhost"
DB_NAME = "MyCourseWork"  # поменяй на свою БД
DB_PORT = 5432

def get_connection(user: str, password: str) -> connection:
    """
    Подключение под введённой ролью (admin_role / seller_role).
    options задаёт client_encoding, чтобы русские ошибки не ломались.
    """
    return psycopg2.connect(
        host=DB_HOST,
        port=DB_PORT,
        dbname=DB_NAME,
        user=user,
        password=password,
        options="-c client_encoding=UTF8",
    )
