#14.11.2024

#Zadanie 1
# Вам доступен текстовый файл ledger.txt с данными о продажах фирмы за месяц. 
# На каждой строке файла указано, сколько клиент заплатил за товар, в долларах (целое число). 
# Напишите программу для подсчета суммарной месячной выручки фирмы.

summa = 0
with open("ledger.txt", 'r') as myfile:
   for line in myfile:
       line = line.strip()  
       if line != '':  
           summa += int(line)
print(summa)

#Zadanie 2
#Откройте файл 1.txt и напишите программу по подсчету количества строк в файле, а затем и количества слов в нем.
count_line = 0
count_word = 0
words = list()
with open("1.txt", 'r') as myfile:
   while True:
       line = myfile.readline()
       if not line: break 
       count_line += 1
       words = line.split()
       count_word += len(words)

print(f"Количество строк: {count_line}, Количество слов: {count_word}")

#Zadanie 3
# Запишите в файл 1.txt любой стих С.А. Есенина
# Открываем файл для записи

with open("1Copy.txt", 'w', encoding="utf-8") as file:
    print("Введите текст для записи в файл. Введите 'STOP' для завершения ввода.")
    while True:
        line = input()
        if line == "STOP":  
            break
        file.write(line + "\n")  
print("Текст успешно записан в файл 1Copy.txt")

#Zadanie 5
#В имеющимся у вас файле 1.txt найдите самое длинное слово и выведите его на экран.
with open("1.txt", 'r', encoding="utf-8") as myfile:
    words = myfile.read().split()

print(max(words, key=len))

##Zadanie 4
##В имеющимся у вас файле 1.txt напишите программу по замене некоторых запрещенных слов звездочкой (*).
##Ваши запрещенные слова – это «мухи», «тучи», «листва».
##Вы можете как заменить эти слова одной звездочкой, так и заменить их тем количеством звезд, какая длина у слова.  

##with open("1.txt", 'r', encoding="utf-8") as myfile:
##    
