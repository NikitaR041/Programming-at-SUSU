"""
Напишите программу на языке Python, которая будет рассчитывать частоту слов из текстового файла.
Вход: текстовый файл (https://drive.google.com/file/d/13AXtMaNQ8z2_80rq5kLsRX7HS5HpUwZ2/view?usp=sharing)
Выход: информацию о частоте встречаемости слов необходимо сохранить в виде словаря, затем записать в выходной файл по убыванию частоты.
"""
import string
import pymorphy3 
import pandas as pd
import nltk
nltk.download('stopwords')
from nltk.corpus import stopwords

'''
    Так как в тексте встречаются различные слова в разных формах, то
    приведем их к инфинитиву для упрощения вычислительной мощности
''' 
STOP_WORDS = set(stopwords.words('russian'))

morph = pymorphy3.MorphAnalyzer()

def in_infinitiv(word):
    try:
        return morph.parse(word)[0].normal_form
    except:
        return word

#Открытие файла
with open('Чехов_Вишнёвый_Сад.txt', "r", encoding="ANSI") as file:
    text = file.read()
    text = text.lower()
    spec_chars = string.punctuation + '«»\t—…’'
    text = "".join([symbol for symbol in text if symbol not in spec_chars and symbol not in string.digits])
    array_words = text.split()
    array_words = [in_infinitiv(word) for word in array_words] 
    array_words = [w for w in  array_words if w not in STOP_WORDS]
    
    slovar = dict()
    for elem in array_words:
        slovar[elem] = slovar.get(elem, 0) + 1
    sorted_words = sorted(slovar.items(), key=lambda x: x[1], reverse=True)
    # print("Топ-10 слов (по начальной форме):")
    # df = pd.DataFrame(sorted_words, columns=['Слово', 'Частота'])
    # print(df)

#Сохранение результата в файл
with open('example.txt', "w", encoding="utf-8") as file:
    for i, (word, count) in enumerate(sorted_words, 1):
        file.write(f"{i:3}. {word:20} {count:5}\n")
