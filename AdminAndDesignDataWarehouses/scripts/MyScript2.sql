------------------------ Создание ролей
-- Роль администратора — полный доступ
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_roles WHERE rolname = 'admin_role') THEN
        CREATE ROLE admin_role LOGIN PASSWORD 'admin123';
    END IF;
END $$;

-- Роль кассира — работа только с продажами
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_roles WHERE rolname = 'cashier_role') THEN
        CREATE ROLE cashier_role LOGIN PASSWORD 'cashier123';
    END IF;
END $$;

-- Роль склада — работа с комплектующими и характеристиками
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_roles WHERE rolname = 'warehouse_role') THEN
        CREATE ROLE warehouse_role LOGIN PASSWORD 'warehouse123';
    END IF;
END $$;

-- Роль аналитика — только чтение
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_roles WHERE rolname = 'analyst_role') THEN
        CREATE ROLE analyst_role LOGIN PASSWORD 'analyst123';
    END IF;
END $$;

-- Гость — минимальные права
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_roles WHERE rolname = 'guest_role') THEN
        CREATE ROLE guest_role LOGIN PASSWORD 'guest123';
    END IF;
END $$;

---------------- Права на схему и объекты
-- Администратор имеет полный доступ
GRANT ALL PRIVILEGES ON SCHEMA public TO admin_role;

-- Кассир не должен создавать таблицы
REVOKE CREATE ON SCHEMA public FROM cashier_role;
GRANT USAGE ON SCHEMA public TO cashier_role;

-- Склад не создаёт таблицы
REVOKE CREATE ON SCHEMA public FROM warehouse_role;
GRANT USAGE ON SCHEMA public TO warehouse_role;

-- Аналитик — только просмотр
GRANT USAGE ON SCHEMA public TO analyst_role;

-- Гость минимальные права
GRANT USAGE ON SCHEMA public TO guest_role;

--------------- Права на таблицы
------ Таблицы для кассира, он работает только с чеками
GRANT SELECT, INSERT, UPDATE ON cheque TO cashier_role;
GRANT SELECT, INSERT, UPDATE ON cheque_item TO cashier_role;

-- Кассир должен иметь возможность видеть компьютеры и комплектующие
GRANT SELECT ON computer TO cashier_role;
GRANT SELECT ON accessories TO cashier_role;

------ Таблицы для склада
-- Комлпектующие + характеристики
GRANT SELECT, INSERT, UPDATE, DELETE ON accessories TO warehouse_role;
GRANT SELECT, INSERT, UPDATE, DELETE ON characteristic TO warehouse_role;
GRANT SELECT, INSERT, UPDATE, DELETE ON value_characteristic TO warehouse_role;

-- Склад видит компьютеры, но не продаёт
GRANT SELECT ON computer TO warehouse_role;

-- Склад не работает с продажами
REVOKE ALL ON cheque FROM warehouse_role;
REVOKE ALL ON cheque_item FROM warehouse_role;


------- Таблицы для аналитика
GRANT SELECT ON manufacture, company, accessories, characteristic,
              value_characteristic, computer, contant_config,
              shopper, cheque, cheque_item
TO analyst_role;

------- Таблицы для гостя - только просмотр ограниченной информации
GRANT SELECT ON computer TO guest_role;
GRANT SELECT ON accessories TO guest_role;

------- Таблицы для администратора - полный доступ ко всем таблицам
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO admin_role;


---------- Права на последовательности - нужно ли ? 
GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO admin_role;
GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO cashier_role;
GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO warehouse_role;
GRANT SELECT ON ALL SEQUENCES IN SCHEMA public TO analyst_role;


---------- Права на функции
GRANT EXECUTE ON FUNCTION get_cheque_total(integer) TO cashier_role, analyst_role;
GRANT EXECUTE ON FUNCTION get_computer_configuration(integer) TO analyst_role, warehouse_role;

-- Админ всё может
GRANT EXECUTE ON ALL FUNCTIONS IN SCHEMA public TO admin_role;
