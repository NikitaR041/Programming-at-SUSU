"""
Время должно быть представлено в форме hh:mm:ss, где hh - число из двух цифр от 00 до 23, mm и ss - числа из двух цифр от 00 до 59.
Ввод содержит одну или более строк длиной не более 100 символов.
Для каждой строки ввода вывести YES, если строка является записью времени, иначе вывести NO.

Пример ввода
00:00:01
0:00:01
01/12/21
23:00:00
Time is 01:00:50

Пример вывода
YES
NO
NO
YES
NO
"""

import re
import sys

# txt = sys.stdin.read()
# lines = txt.splitlines()

# for i in lines:
#     if re.fullmatch(r"(?:[01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]", i):
#         print("YES")
#     else:
#         print("NO")

"""
Шестнадцатеричное число должно начинаться с цифры, далее следует ноль или более цифр или латинских букв от A до F в любом регистре.
Ввод содержит одну или более строк длиной не более 100 символов.
Для каждой строки ввода вывести YES, если строка является шестнадцатеричным числом, иначе вывести NO.

Пример ввода
0A
A
HEX
12
1aF

Пример вывода
YES
NO
NO
YES
YES
"""

# txt = sys.stdin.read()
# lines = txt.splitlines()

# for i in lines:
#     if re.fullmatch(r"\d[0-9a-fA-F]*", i):
#         print("YES")
#     else:
#         print("NO")

"""
Алфавит марсианского языка состоит из строчных латинских букв. Буквам a, e, i, o, u, y соответствуют гласные звуки, остальным – согласные.
В результате опроса марсиан выяснилось, что им трудно произносить слова, в которых присутствуют два или более гласных звука подряд. Марсианскими лингвистами было принято решение: во всех словах, где есть два или более гласных звука подряд, оставить только последний из них.
Марсиане просят написать программу, переводящую слова из старого в новый форматы.
Например, если старое слово имело вид eeaaeeuinfaormaaiatoyuaoics, то новое слово будет таким: informatics.
Формат входного файла
Во входном файле содержится марсианское слово старого формата.
Формат выходного файла
Выходной файл должен содержать марсианское слово нового формата.
Ограничения
Длина слова находится в диапазоне от 1 до 100 символов.

Пример ввода 1
eeaaeeuinfaormaaiatoyuaoics
Пример вывода 1
informatics

Пример ввода 2
aeeaaayyaaauaaiaaiaacm
Пример вывода 2
acm

Пример ввода 3
bzzt
Пример вывода 3
bzzt
"""

# txt = input()
# match = re.sub(r"([aeiouy]){2,}", r"\0", txt)
# print(match)

"""
Список в формате JSON содержит целые числа. Часть чисел закомментирована с помощью // и /* */
Ввод содержит один список в формате JSON.
Вывести два целых числа – количество и сумму чисел в списке, без закомментированных.

Пример ввода
[12,-5,101,
 4, // 17,
 23, 0, /*4, 18,*/ 1
]

Пример вывода
7 136
"""

# txt = sys.stdin.read()
# pattern1 = re.sub(r"/\*.*?\*/", "", txt, flags=re.DOTALL)
# pattern2 = re.sub(r"//.*", "", pattern1)

# m = []
# for i in re.findall(r"-?\d+", pattern2):
#     m.append(int(i))
# print(len(m), sum(m))

"""
You have decided that PGP encryption is not strong enough for your email. You have decided to use Pig Latin encryption.
Input and Output
You are to write a program that will take in an arbitrary number of lines of text and output it in Pig Latin. Each line of text will contain one or more words. A "word" is defined as a consecutive sequence of letters (upper and/or lower case). Words should be converted to Pig Latin according to the following rules (non-words should be output exactly as they appear in the input):
1. Words that begin with a vowel (a, e, i, o, or u, and the capital versions of these) should just have the string "ay" (not including the quotes) appended to it. For example, "apple" becomes "appleay".
2. Words that begin with a consonant (any letter than is not A, a, E, e, I, i, O, o, U or u) should have the first consonant removed and appended to the end of the word, and then appending "ay" as well. For example, "hello" becomes "ellohay".
3. Do not change the case of any letter.
Sample Input
This is the input.

Sample Output
hisTay isay hetay inputay.
"""

# def my_f(match):
#     elem = match.group(0)
#     if re.match(r"^[AaEeIiOoUu]", elem):
#         return elem + "ay"
#     else:
#         return elem[1:] + elem[0] + "ay"

# txt = sys.stdin.read()
# res = re.sub(r"[a-zA-Z]+", my_f, txt)
# print(res, end="")

"""
Главный бюрократ компании "Планетарная экспресс-доставка" Гермес Конрад после написания очередного отчета или распоряжения обязательно подсчитывает количество слов и чисел в документе, так как владелец компании, профессор Х.Дж.Фарнсворт, не любит лишних слов, а любит только числа. Напишите программу, которая поможет Гермесу подсчитать количество слов и чисел в документе.
Во входном файле содержится от 1 до 100 строк длиной не более 80 символов. Словом или числом будем называть непрерывную последовательность печатных символов. При этом число в отличие от слова содержит одну или более цифр от 0 до 9. Слова и числа в документе разделены последовательностями пробелов, табуляций и переходов на новую строку.
В выходной файл вывести количество слов и чисел в документе в виде "2 word(s), 1 number(s)".

Пример ввода
                REPORT
In 1st quarter the margin was $20.02.

Вывод для примера
6 word(s), 2 number(s)
"""

txt = sys.stdin.read()
lines = txt.split()
n, w = 0, 0
obj =  re.compile(r"[0-9]")
for s in lines:
    if obj.search(s):
        n += 1
    else:
        w += 1

print(f"{w} word(s), {n} number(s)")
