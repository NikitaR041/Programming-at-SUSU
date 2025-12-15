# import psycopg2
# from psycopg2 import sql
# from psycopg2 import Error
# from conf import dbname, user, password, host, port 

import work_cashier
import work_analyst
import work_warehouse
import work_guest
import random

def main():
    # Генерируем уникальный ID для тестового аксессуара, чтобы избежать конфликтов
    test_acc_id = 100 + random.randint(1, 1000)

    print("ДЕМОНСТРАЦИЯ РАБОТЫ СЕРВЕРНОЙ ЧАСТИ")
    

    # ====================================================================
    # 1. ДЕМОНСТРАЦИЯ: РОЛЬ ГОСТЯ (Публичное чтение)
    # ====================================================================
    print("\n--- 1 РОЛЬ ГОСТЯ: Чтение каталога (SELECT на computer) ---")
    computers = work_guest.get_public_computers_list()
    if computers:
        print(f"Список компьютеров (ID | Имя | Цена): {computers[0]}...")
    else:
        print("Ошибка: Гость не смог прочитать данные (проверьте права).")

    # Тест безопасности: Гость не должен видеть финансовые данные
    print("\n ТЕСТ БЕЗОПАСНОСТИ: Попытка Гостя прочитать чеки ---")
    work_guest.attempt_to_get_cheque_data() # Ожидаем ошибку в консоли от db_manager.py!
    print("   (Ожидалась ошибка 'permission denied' в логах выше.)")

    # ====================================================================
    # 2. ДЕМОНСТРАЦИЯ: РОЛЬ КАССИРА (Создание транзакции)
    # ====================================================================
    print("--- 2 РОЛЬ КАССИРА: Создание Чека (INSERT) ---")
    # Создаем новый чек
    new_cheque_id = work_cashier.create_new_cheque(shopper_id=1)
    
    if new_cheque_id:
        print(f"Создан новый ЧЕК №{new_cheque_id}. (Произошел commit)")
        
        # Добавляем позицию в чек (компьютер ID 5, цена 55000)
        work_cashier.add_product_to_cheque(new_cheque_id, 'computer', 5, 1, 55000.00)
        # Добавляем позицию в чек (аксессуар ID 10, цена 1500, 2 шт.)
        work_cashier.add_product_to_cheque(new_cheque_id, 'accessories', 10, 2, 1500.00)
        print("Позиции добавлены. (Произошли commits)")
    else:
        print("Критическая ошибка: Кассир не смог создать чек.")
        return

    # ====================================================================
    # 3. ДЕМОНСТРАЦИЯ: РОЛЬ СКЛАДА (CRUD на инвентаре)
    # ====================================================================
    print("--- 3 РОЛЬ СКЛАДА: Управление Инвентарем (UPDATE) ---")
    
    # Сценарий: Склад обновляет цену на существующий товар (ID 10)
    OLD_PRICE = 1500.00
    NEW_PRICE = 1650.00
    
    print(f"   Склад обновляет цену аксессуара ID 10 (было {OLD_PRICE} стало {NEW_PRICE})")
    rows_updated = work_warehouse.update_accessory_price(10, NEW_PRICE)
    
    if rows_updated > 0:
        print(f"Успех: Цена аксессуара ID 10 обновлена. (Произошел commit)")
    else:
        print("Ошибка: Склад не смог обновить цену (проверьте права/наличие товара).")

    # ====================================================================
    # 4. ДЕМОНСТРАЦИЯ: РОЛЬ АНАЛИТИКА (Отчетность)
    # ====================================================================
    print("--- 4 РОЛЬ АНАЛИТИКА: Отчеты и Функции (EXECUTE) ---")

    # Расчет суммы созданного чека (должно быть: 55000 + 2*1500 = 58000.00)
    total = work_analyst.get_cheque_total_amount(new_cheque_id)
    print(f"Сумма ЧЕКА №{new_cheque_id} (расчет функцией): {total:.2f}")

    # Получение конфигурации компьютера
    config = work_analyst.get_computer_config_report(computer_id=5)
    print(f"Конфигурация Компьютера ID 5:")
    for name, qty in config:
        print(f"     - {name}: {qty} шт.")
    print("Аналитик успешно выполнил оба отчета.")
    print("   Демонстрация завершена. Проверьте логи для всех SQL-запросов и результатов.")


if __name__ == "__main__":
    main()

