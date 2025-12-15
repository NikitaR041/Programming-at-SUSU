from manager import execute_query
from conf import DB_NAME, DB_HOST, DB_PORT, DB_ADMIN, DB_PASSWORD_ADMIN

ADMIN_CONFIG = {
    'dbname': DB_NAME,
    'user': DB_ADMIN,
    'password': DB_PASSWORD_ADMIN,
    'host': DB_HOST,
    'port': DB_PORT
}

def create_new_user(username, password):
    # Опасная функция, доступна только Админу
    sql = f"CREATE ROLE {username} LOGIN PASSWORD '{password}';"
    # Обратите внимание: здесь мы не используем %s, так как это команда DDL/DCL
    return execute_query(sql, config=ADMIN_CONFIG)