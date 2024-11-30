#Задание 1
# Базовый класс «СТУДЕНТ» описывает следующие данные о студентах университета: ФИО, номер группы. 
# Производный класс «СТУДЕНТ ОБЩЕСТВЕННИК» содержит следующие элементы: общественная работа, процент надбавки к стипендии. 
# Производный класс «СТУДЕНТ СПОРТСМЕН» содержит следующие элементы: вид спорта. 
# Организовать ввод/вывод информации о студентах. 

#Родительский класс
# class Student():
#     def __init__(self, surname, name, fathername, group):
#         self._surname = surname
#         self._name = name
#         self._fathername = fathername
#         self._group = group

#     @property
#     def surname(self):
#         print(f"Ваша фамилия: {self._surname}")
    
#     @property
#     def name(self):
#         print(f"Ваше имя: {self._name}")
    
#     @property
#     def fathername(self):
#         print(f"Ваше отчество: {self._fathername}")
        
#     @property
#     def group(self):
#         print(f"Ваша группа: {self._group}")

#     @group.setter
#     def group(self, new_group):
#         self._group = new_group
#         print(f"Вам присовили новую группу: {self._group}")

#     #Полиморфизм
#     def getSay(self):
#         print(f"Привет я Студент! Меня зовут {self._name}! Я из группы {self._group}")

# #Дочерний класс от родительского класса Student
# class SocialStudent(Student):
#     def __init__(self,surname, name, fathername, group, work, uppdatemoney):
#         super().__init__(surname, name, fathername, group)
#         self._work = work
#         self._uppdatemoney = uppdatemoney

#     @property
#     def work(self):
#         print(f"Я работаю в сфере {self._work}")

#     @property
#     def uppdatemoney(self):
#         print(f"На данный момент наша процентная надбавка к стипендии {self._uppdatemoney}")

#     @uppdatemoney.setter
#     def uppdatemoney(self, new_uppdatemoney):
#         if(self._uppdatemoney < new_uppdatemoney):
#             self._uppdatemoney = new_uppdatemoney
#             print(f"Я увеличил процентную надбавку к стипендии! Ура! Теперь она составляет {self._uppdatemoney}")
#         else:
#             self._uppdatemoney = new_uppdatemoney
#             print(f"Я понизил процентную надбавку к стипендии! О нет! Теперь она составляет {self._uppdatemoney}")

#     #Полиморфизм
#     def getSay(self):
#         print(f"Привет я Студент общественник! Меня зовут {self._name}!")

# #Дочерний класс от родительского класса Student
# class AthleteStudent(Student):
#     def __init__(self, surname, name, fathername, group, sport):
#         super().__init__(surname, name, fathername, group)
#         self._sport = sport
    
#     @property
#     def sport(self):
#         print(f"Привет! Меня зовут {self._name}! Я занимаюсь {self._sport}")

#     @sport.setter
#     def sport(self, new_sport):
#         self._sport = new_sport
#         print(f"Теперь мне нравится заниматься {self._sport}")
    
#     #Полиморфизм
#     def getSay(self):
#         print(f"Привет я Студент спортсмен! Меня зовут {self._name}! И я люблю заниматься {self._sport}")

# #Создаем экземляры
# obj1 = Student("Романов", "Роман", "Романович", "ET212")
# obj2 = SocialStudent("Никитов", "Никита", "Никитич", "ЕТ412", "СММ", 0.15)
# obj3 = AthleteStudent("Максимов", "Максим", "Максимович", "ЕТ112", "баскетбол")

# #Геттеры
# obj1.surname
# obj2.name
# obj3.fathername

# #Сеттеры
# obj3.group = "ET312"
# obj2.uppdatemoney = 0.25

# #Вызов полиморфиза метода getSay
# obj1.getSay()
# obj2.getSay()
# obj3.getSay()

#Задание 2
# Базовый класс «АВТОБУСНЫЙ РЕЙС» описывает следующие данные элементы: номер рейса, пункт назначения, цена билета, дата и время отправления, дата и время прибытия на конечный пункт. 
# Производный класс «РЕЙС-ЭКСПРЕСС» содержит следующие данные: процентная надбавка на цену билета. 
# Производный класс «МЕЖДУНАРОДНЫЙ РЕЙС» содержит следующие данные: страна. 
# Организовать ввод/вывод данных о рейсах. 
# Вывести информацию о рейсах, позволяющих добраться до указанного пункта. 