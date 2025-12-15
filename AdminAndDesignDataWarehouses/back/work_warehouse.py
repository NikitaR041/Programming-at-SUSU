import psycopg2
from psycopg2 import sql
from psycopg2 import Error
from manager import execute_query
from conf import DB_NAME, DB_HOST, DB_PORT, DB_WAREHOUSE, DB_PASSWORD_WAREHOUSE

CONFIG_WAREHOUSE = {
    "dbname": DB_NAME,
    "user": DB_WAREHOUSE,
    "password": DB_PASSWORD_WAREHOUSE,
    "host": DB_HOST,
    "port": DB_PORT
} 

def create_new_accessory(manufacture_id: int, company_id: int, name_item: str, price: float, type_item: str) -> int:
    """
    Добавляет новый комплектующий в таблицу accessories.
    Склад имеет права INSERT.
    """
    sql = """
    INSERT INTO accessories (manufacture_id, company_id, name_item, price, type_item)
    VALUES (%s, %s, %s, %s, %s) 
    RETURNING accessories_id;
    """
    params = (manufacture_id, company_id, name_item, price, type_item)
    
    result = execute_query(sql, params=params, fetch_one=True, config=CONFIG_WAREHOUSE)
    
    return result[0] if result else None

def update_accessory_price(accessories_id: int, new_price: float) -> int:
    """
    Обновляет цену комплектующего.
    Склад имеет права UPDATE.
    """
    sql = "UPDATE accessories SET price = %s WHERE accessories_id = %s;"
    params = (new_price, accessories_id)
    
    # Возвращает количество измененных строк (0 или 1)
    return execute_query(sql, params=params, config=CONFIG_WAREHOUSE) 

def delete_accessory(accessories_id: int) -> int:
    """
    Удаляет комплектующее.
    Склад имеет права DELETE.
    """
    sql = "DELETE FROM accessories WHERE accessories_id = %s;"
    params = (accessories_id,)
    
    # Возвращает количество измененных строк (0 или 1)
    return execute_query(sql, params=params, config=CONFIG_WAREHOUSE)