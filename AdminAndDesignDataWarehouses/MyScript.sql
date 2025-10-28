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
	name_mt VARCHAR(30) NOT NULL,
	country VARCHAR(30)
);
-- Фирма
CREATE TABLE company (
	company_id SERIAL PRIMARY KEY,
	name_company VARCHAR(30) NOT NULL,
	address VARCHAR(30) NOT NULL
);
-- Комплектующие
CREATE TABLE accessories (
	accessories_id SERIAL PRIMARY KEY,
	manufacture_id INTEGER NOT NULL REFERENCES manufacture(manufacture_id) ON DELETE RESTRICT,
	company_id INTEGER NOT NULL REFERENCES company(company_id) ON DELETE RESTRICT,
	name_item VARCHAR(30) NOT NULL,
	price myPriceType NOT NULL,
	type_item VARCHAR(30) NOT NULL
);
-- Значение характеристик
CREATE TABLE value_characteristic (
	accessories_id INTEGER NOT NULL REFERENCES accessories(accessories_id) ON UPDATE CASCADE,
	characteristic_id INTEGER NOT NULL REFERENCES characteristic(characteristic_id) ON UPDATE CASCADE,
	val INTEGER NOT NULL,
	PRIMARY KEY (accessories_id, characteristic_id)
);

-- Характеристика
CREATE TABLE characteristic (
	characteristic_id SERIAL PRIMARY KEY,
	name_charact VARCHAR(30) NOT NULL UNIQUE,
	unit_measure VARCHAR(30) NOT NULL 
);

-- Чек
CREATE TABLE cheque (
	cheque_id SERIAL PRIMARY KEY,
	shopper_id INTEGER NOT NULL REFERENCES shopper(shopper_id) ON UPDATE CASCADE,
	date_sale DATE NOT NULL,
	sale_amount myPriceType NOT NULL
);
-- Компьютер
CREATE TABLE computer (
	computer_id SERIAL PRIMARY KEY,
	cheque_item_id INTEGER NOT NULL REFERENCES cheque_item(position_id) ON UPDATE CASCADE,
	name_comp VARCHAR(30) NOT NULL,
	price myPriceType NOT NULL,
	warranty_months VARCHAR(30) NOT NULL, --???????
	build_date DATE NOT NULL-- ????
);
-- Состав конфигураций
CREATE TABLE contant_config (
	computer_id INTEGER NOT NULL REFERENCES computer(computer_id) ON UPDATE CASCADE,
	accessories_id INTEGER NOT NULL REFERENCES accessories(accessories_id) ON UPDATE CASCADE,
	count_item myQTY NOT NULL, -- ??? здесь должен быть инкремент или нет?
	PRIMARY KEY (computer_id, accessories_id) 	
)
-- product_enum - это перечисление, нужно создать переменную 
-- Состав чека
CREATE TABLE cheque_item (
	position_id SERIAL PRIMARY KEY,
	cheque_id INTEGER NULL REFERENCES cheque(cheque_id) ON UPDATE CASCADE,
	computer_id INTEGER NULL REFERENCES computer(computer_id) ON UPDATE RESTRICT,
	accessories_id INTEGER NOT NULL REFERENCES accessories(accessories_id) ON UPDATE RESTRICT,
	product_kind product_enum NOT NULL, -- типы 'computer' or 'component'
	count_sale_item myQTY NOT NULL,
	price_at_sale myPriceType GENERATED ALWAYS AS (count_sale_item * price_at_sale) STORED, --Всегда вычисляемое
	-- Проверка XOR
	CONSTRAINT receipt_item_xor_check CHECK (
        (computer_id IS NOT NULL AND component_id IS NULL AND product_kind = 'computer')
        OR
        (accessories_id IS NOT NULL AND accessories_id IS NULL AND product_kind = 'component')
    )
);
-- Покупатель
CREATE TABLE shopper (
	shopper_id SERIAL PRIMARY KEY,
	fio VARCHAR(30) NOT NULL,
	fio_number VARCHAR(12) NOT NULL UNIQUE, 
	emal VARCHAR(30) NOT NULL UNIQUE
);