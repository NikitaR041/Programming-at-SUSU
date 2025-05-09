package MyFactoryEmulator;

/*
Интерфейс SupplierFactory необходим для класса Supplier, который является обобщенным классом по созданию поставщиков
    объектов класса Body, Accessory и Motor
*/
public interface SupplierFactory<T> {
    T create();
}
