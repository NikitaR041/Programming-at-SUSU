-- Здесь удаление всех таблиц, доменов и перечисления на случай того, если произошло изменение 
DROP TABLE IF EXISTS cheque_item CASCADE;
DROP TABLE IF EXISTS cheque CASCADE;
DROP TABLE IF EXISTS computer CASCADE;
DROP TABLE IF EXISTS contant_config CASCADE;
DROP TABLE IF EXISTS value_characteristic CASCADE;
DROP TABLE IF EXISTS characteristic CASCADE;
DROP TABLE IF EXISTS accessories CASCADE;
DROP TABLE IF EXISTS company CASCADE;
DROP TABLE IF EXISTS manufacture CASCADE;
DROP TABLE IF EXISTS shopper CASCADE;

DROP TYPE IF EXISTS product_enum CASCADE;
DROP DOMAIN IF EXISTS myPriceType CASCADE;
DROP DOMAIN IF EXISTS myQTY CASCADE;

-- Здесь должны быть прописаны домены и перечисления
CREATE TYPE product_enum AS ENUM ('computer', 'accessories');
CREATE DOMAIN myPriceType AS DECIMAL(12, 2) DEFAULT 0 CHECK(VALUE >= 0);
CREATE DOMAIN myQTY AS INTEGER DEFAULT 1 CHECK(VALUE >= 0);

-- Создание таблиц --
-- Производитель
CREATE TABLE manufacture (
	manufacture_id SERIAL PRIMARY KEY,
	name_mt VARCHAR(100) NOT NULL,
	country VARCHAR(100)
);
-- Фирма
CREATE TABLE company (
	company_id SERIAL PRIMARY KEY,
	name_company VARCHAR(100) NOT NULL,
	address VARCHAR(100) NOT NULL
);
-- Комплектующие
CREATE TABLE accessories (
	accessories_id SERIAL PRIMARY KEY,
	manufacture_id INTEGER NOT NULL REFERENCES manufacture(manufacture_id) ON DELETE RESTRICT,
	company_id INTEGER NOT NULL REFERENCES company(company_id) ON DELETE RESTRICT,
	name_item VARCHAR(100) NOT NULL,
	price myPriceType NOT NULL,
	type_item VARCHAR(100) NOT NULL,
	count_item myQTY NOT NULL
);

-- Характеристика
CREATE TABLE characteristic (
	characteristic_id SERIAL PRIMARY KEY,
	name_charact VARCHAR(100) NOT NULL UNIQUE,
	unit_measure VARCHAR(100) NOT NULL 
);

-- Значение характеристик
CREATE TABLE value_characteristic (
	accessories_id INTEGER NOT NULL REFERENCES accessories(accessories_id) ON DELETE RESTRICT,
	characteristic_id INTEGER NOT NULL REFERENCES characteristic(characteristic_id) ON DELETE RESTRICT,
	val INTEGER NOT NULL,
	PRIMARY KEY (accessories_id, characteristic_id)
);

-- Покупатель
CREATE TABLE shopper (
	shopper_id SERIAL PRIMARY KEY,
	fio VARCHAR(30) NOT NULL,
	fio_number VARCHAR(12) NOT NULL UNIQUE, 
	emal VARCHAR(30) NOT NULL UNIQUE
);

-- Чек
CREATE TABLE cheque (
	cheque_id SERIAL PRIMARY KEY,
	shopper_id INTEGER NOT NULL REFERENCES shopper(shopper_id) ON DELETE RESTRICT,
	date_sale DATE NOT NULL
);
-- Компьютер
CREATE TABLE computer (
	computer_id SERIAL PRIMARY KEY,
	name_comp VARCHAR(100) NOT NULL,
	price myPriceType NOT NULL,
	warranty_months INTEGER NOT NULL CHECK (warranty_months > 0), -- Гарантия : количество месяцев для гарантиB
	build_date DATE NOT NULL, -- Дата изготовления 
	count_item myQTY NOT NULL
);
-- Состав конфигураций
CREATE TABLE contant_config (
	computer_id INTEGER NOT NULL REFERENCES computer(computer_id) ON DELETE RESTRICT,
	accessories_id INTEGER NOT NULL REFERENCES accessories(accessories_id) ON DELETE RESTRICT,
	count_item myQTY NOT NULL,
	PRIMARY KEY (computer_id, accessories_id) 	
);
-- Состав чека
CREATE TABLE cheque_item (
	position_id SERIAL PRIMARY KEY,
	cheque_id INTEGER NOT NULL REFERENCES cheque(cheque_id) ON DELETE RESTRICT,
	computer_id INTEGER NULL REFERENCES computer(computer_id) ON DELETE RESTRICT,
	accessories_id INTEGER NULL REFERENCES accessories(accessories_id) ON DELETE RESTRICT,
	product_kind product_enum NOT NULL, -- типы 'computer' or 'accessories'
	count_sale_item myQTY NOT NULL, -- Количество проданных товаров данной позиции
	price_at_sale myPriceType NOT NULL, -- Цена за единицу товара в момент продажи
	-- Проверка XOR
	CONSTRAINT receipt_item_xor_check CHECK (
        (computer_id IS NOT NULL AND accessories_id  IS NULL AND product_kind = 'computer')
        OR
        (accessories_id IS NOT NULL AND computer_id  IS NULL AND product_kind = 'accessories') -- computer_id или accessories_id ?
    )
);

-- Триггерная функция: списание товара со склада при продаже
CREATE OR REPLACE FUNCTION sell_item_decrease_stock()
RETURNS TRIGGER
SECURITY DEFINER
SET search_path = public
AS $$
DECLARE
    current_qty INTEGER;
BEGIN
    -- Продажа комплектующего
    IF NEW.product_kind = 'accessories' THEN

        SELECT count_item
        INTO current_qty
        FROM accessories
        WHERE accessories_id = NEW.accessories_id
        FOR UPDATE;

        IF current_qty IS NULL THEN
            RAISE EXCEPTION 'Комплектующее (accessories_id=%) не найдено', NEW.accessories_id;
        END IF;

        IF NEW.count_sale_item <= 0 THEN
            RAISE EXCEPTION 'Количество продажи должно быть > 0';
        END IF;

        IF current_qty < NEW.count_sale_item THEN
            RAISE EXCEPTION 'Недостаточно комплектующих (id=%): на складе %, требуется %',
                NEW.accessories_id, current_qty, NEW.count_sale_item;
        END IF;

        UPDATE accessories
        SET count_item = count_item - NEW.count_sale_item
        WHERE accessories_id = NEW.accessories_id;

        RETURN NEW;
    END IF;

    -- Продажа компьютера
    IF NEW.product_kind = 'computer' THEN

        SELECT count_item
        INTO current_qty
        FROM computer
        WHERE computer_id = NEW.computer_id
        FOR UPDATE;

        IF current_qty IS NULL THEN
            RAISE EXCEPTION 'Компьютер (computer_id=%) не найден', NEW.computer_id;
        END IF;

        IF NEW.count_sale_item <= 0 THEN
            RAISE EXCEPTION 'Количество продажи должно быть > 0';
        END IF;

        IF current_qty < NEW.count_sale_item THEN
            RAISE EXCEPTION 'Недостаточно компьютеров (id=%): на складе %, требуется %',
                NEW.computer_id, current_qty, NEW.count_sale_item;
        END IF;

        UPDATE computer
        SET count_item = count_item - NEW.count_sale_item
        WHERE computer_id = NEW.computer_id;

        RETURN NEW;
    END IF;

    -- На всякий случай (по идее сюда не попадём из-за CHECK XOR)
    RAISE EXCEPTION 'Некорректный product_kind: %', NEW.product_kind;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_sell_item_decrease_stock ON cheque_item;

CREATE TRIGGER trg_sell_item_decrease_stock
BEFORE INSERT ON cheque_item
FOR EACH ROW
EXECUTE FUNCTION sell_item_decrease_stock();

-- Функция, возвращающее вычисленную сумму чека 
-- Нет поля отдельного суммы 
CREATE OR REPLACE FUNCTION get_cheque_total(p_cheque_id INTEGER)
RETURNS myPriceType AS $$
DECLARE
    total myPriceType;
BEGIN
    SELECT COALESCE(SUM(count_sale_item * price_at_sale), 0)
    INTO total
    FROM cheque_item
    WHERE cheque_id = p_cheque_id;

    RETURN total;
END;
$$ LANGUAGE plpgsql;
-- Пример использования
-- SELECT get_cheque_total(5);

-- Функция, возвращающее полную конфигурацию компьютера
CREATE OR REPLACE FUNCTION get_computer_configuration(p_computer_id INTEGER)
RETURNS TABLE(
    component_name VARCHAR,
    quantity INTEGER
) AS $$
BEGIN
    RETURN QUERY -- Возвращает таблицу
    SELECT a.name_item, cc.count_item
    FROM contant_config cc
    JOIN accessories a ON a.accessories_id = cc.accessories_id
    WHERE cc.computer_id = p_computer_id;
END;
$$ LANGUAGE plpgsql;
-- Пример использования:
-- SELECT * FROM get_computer_configuration(3);

