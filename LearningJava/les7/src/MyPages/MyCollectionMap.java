package MyPages;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyCollectionMap<T1 extends String, T2 extends Material> {
    private Map<T1, List<T2>> MyMap; //Поле мой словарь

    //Конструктор по умолчанию
    public MyCollectionMap(){ MyMap = new HashMap<>(); }

    //Добавление пары в словарь по ключу и значению
    // Добавление элемента в список по ключу
    public void addToMyMap(T1 key, T2 value) {
        // Если ключа нет — создаем новый список
        MyMap.computeIfAbsent(key, _ -> new ArrayList<>()).add(value);
    }
    //Удаление пары из словаря по ключу
    public void erasePairMyMap(T1 key){ MyMap.remove(key); }

    //Поиск пары в словаре по ключу - возвращает и удаляет пару из словаря
    public Map.Entry<T1, T2> getSearchInMyMap(T1 key) throws MyException {
        if (!MyMap.containsKey(key)) { throw new MyException("Неизвестный ключ!"); }
        T2 value = MyMap.get(key);
        Map.Entry<T1, T2> entry = Map.entry(key, value);
        MyMap.remove(key);
        return entry;
    }

    //Поиск пары в словаря по ключу - возвращает истинно или ложь
    public boolean isSearchInMyMap(T1 key){ return MyMap.containsKey(key); }

    //Проверка на пустоту словаря
    public boolean isEmptyMyMap(){ return MyMap.isEmpty(); }
}
