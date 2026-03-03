-- 1) Создаём роли (если их ещё нет)
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_roles WHERE rolname = 'admin_role') THEN
        CREATE ROLE admin_role LOGIN PASSWORD 'admin123';
    END IF;

    IF NOT EXISTS (SELECT 1 FROM pg_roles WHERE rolname = 'seller_role') THEN
        CREATE ROLE seller_role LOGIN PASSWORD 'seller123';
    END IF;
END $$;

-- 2) Админ: базово "всё можно" в public
GRANT USAGE, CREATE ON SCHEMA public TO admin_role;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO admin_role;
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO admin_role;
GRANT EXECUTE ON ALL FUNCTIONS IN SCHEMA public TO admin_role;

-- 3) Продавец: только продажа + просмотр ассортимента
GRANT USAGE ON SCHEMA public TO seller_role;

-- смотреть ассортимент
GRANT SELECT ON computer, accessories TO seller_role;

-- оформлять чек и позиции чека
GRANT SELECT, INSERT ON cheque TO seller_role;
GRANT SELECT, INSERT ON cheque_item TO seller_role;

-- чтобы INSERT в SERIAL работал (позиции/чеки)
GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO seller_role;

-- 4) Продавцу запрещаем менять склад напрямую (важно)
REVOKE INSERT, UPDATE, DELETE ON computer FROM seller_role;
REVOKE INSERT, UPDATE, DELETE ON accessories FROM seller_role;

-- (оставляем SELECT, который выдали выше)
GRANT SELECT ON computer, accessories TO seller_role;

-- 5) Делает функцию "служебной": владельцем функции назначаем админа
ALTER FUNCTION sell_item_decrease_stock() OWNER TO admin_role;

-- 6) Продавцу не нужно вызывать функцию вручную, но на всякий случай можно запретить
REVOKE EXECUTE ON FUNCTION sell_item_decrease_stock() FROM PUBLIC;
REVOKE EXECUTE ON FUNCTION sell_item_decrease_stock() FROM seller_role;
