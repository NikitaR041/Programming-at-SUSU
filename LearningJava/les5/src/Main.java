/*
Лабораторная работа 5. Контейнеры, IO потоки, классы Object и String
Написать программу, которая будет принимать в качестве аргумента имя текстового файла, и выводить CSV файл с колонками:
1.	Слово.
2.	Частота.
3.	Частота (в %).

CSV файл должен быть упорядочен по убыванию частоты, то есть самые частые слова должны идти в начале.
Разделителями считать все символы кроме букв и цифр.

Рекомендации:
•  Использовать класс java.lang.StringBuilder для построения слов.
•  Для чтения из файла удобно использовать: java.io.InputStreamReader, например:
Reader reader = null;
try
{
reader = new InputStreamReader(new FileInputStream("FILE NAME"));
		//read the data here
}
catch (IOException e)
{
	System.err.println("Error while reading file: " + e.getLocalizedMessage());
}
finally
{
	if (null != reader)
	{
		try
		{
			reader.close();
		}
		catch (IOException e)
		{
			e.printStackTrace(System.err);
		}
	}
}
• Для определения класса символа использовать метод Character.isLetterOrDigit.
Для хранения статистики в памяти можно использовать одну из реализаций интерфейса java.util.Set, который должен будет хранить объекты специального класса.
Данный класс должен содержать слово и счётчик.
В случае использования java.util.HashSet класс также должен реализовать методы equals, hashCode.

Теоретические сведения:
Контейнеры стандартной библиотеки расположены в пакете java.util. IO классы (потоки ввода-вывода) располагаются в пакете java.io.
Основные интерфейсы:
1.	Set – множество без дубликатов и без доступа по индексу.
2.	Map – множество пар ключ-значение, где ключи не повторяются.
Их основные реализации:
1.	HashMap, HashSet — реализации на основе функции hashCode.
2.	TreeMap, TreeSet – реализация на основе бинарного дерева.
Ключи (элементы) должны реализовывать интерфейс Comporable, иначе необходимо передавать в контейнер при его создании объект, реализующий интерфейс Comparator.
Хранимые в данных контейнерах данные упорядочены.
Лучшее время поиска, но большее накладные расходы на вставку, чем на основе функции hashCode.
*/

/*
    Лайфхаки
    Использование:
    1)Чтобы поделить текст на слова, используй string[] и split(regex), где regex - регулярное выражение
    2)Чтобы из текста убрать лишние знаки препинания, используй regex
 */
import javax.swing.*;
import java.io.*; // Использование всех методов из класса потока ввода-вывода
import java.util.ArrayList;
import java.util.*;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.lang.StringBuilder;
import java.util.regex.*;

public class Main {
    public static void main(String[] args) {
        Map<String, Integer> MyMap = new HashMap<>();
        List<Map.Entry<String, Integer>> pairList = new ArrayList<>();
        StringBuilder strBuffer1 = new StringBuilder();
        String strBuffer2;
        Reader reader = null;

        try {
            reader = new InputStreamReader(new FileInputStream("example.txt"), "UTF-8"); // Указываем кодировку UTF-8
            int index;
            while ((index = reader.read()) != -1) {
                strBuffer1.append((char) index);
            }

            // Очищаем текст от знаков препинания и лишних пробелов
            strBuffer2 = strBuffer1.toString().replaceAll("[^\\p{L}\\p{N}\\s]+", "").replaceAll("\\s+", " ").trim();
            String[] words = strBuffer2.split("\\s+");

            // Подсчет частоты слов
            for (String word : words) {
                MyMap.put(word, MyMap.getOrDefault(word, 0) + 1);
            }

            // Перенос данных в список и сортировка по убыванию
            pairList.addAll(MyMap.entrySet());
            pairList.sort(Comparator.comparing(Map.Entry<String, Integer>::getValue).reversed());

            // Общее количество слов
            int totalWords = words.length;

            // Записываем в CSV с использованием try-with-resources
            try (BufferedWriter writer = new BufferedWriter(new FileWriter("ExampleOut.csv", false))) {
                writer.write("Слово,Частота,Частота(%)\n");

                for (Map.Entry<String, Integer> entry : pairList) {
                    String word = entry.getKey();
                    int frequency = entry.getValue();
                    double percentage = (double) frequency / totalWords * 100;
                    writer.write(String.format("%s,%d,%.2f%%\n", word, frequency, percentage));
                }

                System.out.println("Файл ExampleOut.csv успешно создан!");
            } catch (IOException e) {
                System.err.println("Ошибка при записи в файл: " + e.getMessage());
            }

        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getLocalizedMessage());
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace(System.err);
                }
            }
        }
    }
}
