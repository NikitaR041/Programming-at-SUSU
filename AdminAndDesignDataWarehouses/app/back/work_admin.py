from manager import execute_query
from conf import DB_NAME, DB_HOST, DB_PORT, DB_ADMIN, DB_PASSWORD_ADMIN

ADMIN_CONFIG = {
    'dbname': DB_NAME,
    'user': DB_ADMIN,
    'password': DB_PASSWORD_ADMIN,
    'host': DB_HOST,
    'port': DB_PORT
}

# def create_new_user(username, password):
#     # Опасная функция, доступна только Админу
#     sql = f"CREATE ROLE {username} LOGIN PASSWORD '{password}';"
#     # Обратите внимание: здесь мы не используем %s, так как это команда DDL/DCL
#     return execute_query(sql, config=ADMIN_CONFIG)

# -----------------------
# КОМПЬЮТЕРЫ
# -----------------------

def get_all_computers():
    sql = """
        SELECT computer_id, name_comp, price, warranty_months, build_date
        FROM computer
        ORDER BY computer_id;
    """
    return execute_query(sql, fetch_all=True, config=ADMIN_CONFIG)


def add_computer(name, price, warranty_months, build_date):
    sql = """
        INSERT INTO computer (name_comp, price, warranty_months, build_date)
        VALUES (%s, %s, %s, %s);
    """
    return execute_query(
        sql,
        params=(name, price, warranty_months, build_date),
        config=ADMIN_CONFIG
    )


def delete_computer(computer_id):
    sql = """
        DELETE FROM computer
        WHERE computer_id = %s;
    """
    return execute_query(
        sql,
        params=(computer_id,),
        config=ADMIN_CONFIG
    )


# -----------------------
# КОМПЛЕКТУЮЩИЕ
# -----------------------

def get_all_accessories():
    sql = """
        SELECT accessories_id, name_item, price, type_item
        FROM accessories
        ORDER BY accessories_id;
    """
    return execute_query(sql, fetch_all=True, config=ADMIN_CONFIG)


def add_accessory(manufacture_id, company_id, name, price, type_item):
    sql = """
        INSERT INTO accessories (manufacture_id, company_id, name_item, price, type_item)
        VALUES (%s, %s, %s, %s, %s);
    """
    return execute_query(
        sql,
        params=(manufacture_id, company_id, name, price, type_item),
        config=ADMIN_CONFIG
    )


def delete_accessory(accessories_id):
    sql = """
        DELETE FROM accessories
        WHERE accessories_id = %s;
    """
    return execute_query(
        sql,
        params=(accessories_id,),
        config=ADMIN_CONFIG
    )