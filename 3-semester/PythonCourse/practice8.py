#Задание 1
# Базовый класс «СТУДЕНТ» описывает следующие данные о студентах университета: ФИО, номер группы. 
# Производный класс «СТУДЕНТ ОБЩЕСТВЕННИК» содержит следующие элементы: общественная работа, процент надбавки к стипендии. 
# Производный класс «СТУДЕНТ СПОРТСМЕН» содержит следующие элементы: вид спорта. 
# Организовать ввод/вывод информации о студентах. 

#Родительский класс
class Student():
    def __init__(self, surname, name, fathername, group):
        self._surname = surname
        self._name = name
        self._fathername = fathername
        self._group = group

    @property
    def surname(self):
        print(f"Ваша фамилия: {self._surname}")
    
    @property
    def name(self):
        print(f"Ваше имя: {self._name}")
    
    @property
    def fathername(self):
        print(f"Ваше отчество: {self._fathername}")
        
    @property
    def group(self):
        print(f"Ваша группа: {self._group}")

    @group.setter
    def group(self, new_group):
        self._group = new_group
        print(f"Вам присовили новую группу: {self._group}")

    #Полиморфизм
    def getSay(self):
        print(f"Привет я Студент! Меня зовут {self._name}! Я из группы {self._group}")

#Дочерний класс от родительского класса Student
class SocialStudent(Student):
    def __init__(self,surname, name, fathername, group, work, uppdatemoney):
        super().__init__(surname, name, fathername, group)
        self._work = work
        self._uppdatemoney = uppdatemoney

    @property
    def work(self):
        print(f"Я работаю в сфере {self._work}")

    @property
    def uppdatemoney(self):
        print(f"На данный момент наша процентная надбавка к стипендии {self._uppdatemoney}")

    @uppdatemoney.setter
    def uppdatemoney(self, new_uppdatemoney):
        if(self._uppdatemoney < new_uppdatemoney):
            self._uppdatemoney = new_uppdatemoney
            print(f"Я увеличил процентную надбавку к стипендии! Ура! Теперь она составляет {self._uppdatemoney}")
        else:
            self._uppdatemoney = new_uppdatemoney
            print(f"Я понизил процентную надбавку к стипендии! О нет! Теперь она составляет {self._uppdatemoney}")

    #Полиморфизм
    def getSay(self):
        print(f"Привет я Студент общественник! Меня зовут {self._name}!")

#Дочерний класс от родительского класса Student
class AthleteStudent(Student):
    def __init__(self, surname, name, fathername, group, sport):
        super().__init__(surname, name, fathername, group)
        self._sport = sport
    
    @property
    def sport(self):
        print(f"Привет! Меня зовут {self._name}! Я занимаюсь {self._sport}")

    @sport.setter
    def sport(self, new_sport):
        self._sport = new_sport
        print(f"Теперь мне нравится заниматься {self._sport}")
    
    #Полиморфизм
    def getSay(self):
        print(f"Привет я Студент спортсмен! Меня зовут {self._name}! И я люблю заниматься {self._sport}")

#Создаем экземляры
obj1 = Student("Романов", "Роман", "Романович", "ET212")
obj2 = SocialStudent("Никитов", "Никита", "Никитич", "ЕТ412", "СММ", 0.15)
obj3 = AthleteStudent("Максимов", "Максим", "Максимович", "ЕТ112", "баскетбол")

#Геттеры
obj1.surname
obj2.name
obj3.fathername

#Сеттеры
obj3.group = "ET312"
obj2.uppdatemoney = 0.25

#Вызов полиморфиза метода getSay
obj1.getSay()
obj2.getSay()
obj3.getSay()

#Задание 2
# Базовый класс «АВТОБУСНЫЙ РЕЙС» описывает следующие данные элементы: номер рейса, пункт назначения, цена билета, дата и время отправления, дата и время прибытия на конечный пункт. 
# Производный класс «РЕЙС-ЭКСПРЕСС» содержит следующие данные: процентная надбавка на цену билета. 
# Производный класс «МЕЖДУНАРОДНЫЙ РЕЙС» содержит следующие данные: страна. 
# Организовать ввод/вывод данных о рейсах. 
# Вывести информацию о рейсах, позволяющих добраться до указанного пункта. 

class BusTrip():
    def __init__(self, numbertrip=None, pointplace=None, cost=None, departuretime=None, arrivaltime=None):
        self._numbertrip = numbertrip
        self._pointplace = pointplace
        self._cost = cost
        self._departuretime = departuretime
        self._arrivaltime = arrivaltime
    
    #Функция по выводу данных
    def printTrip(self):
        #По идеи достаточно одного условия на проверку номера рейса
        if(self._numbertrip is None):
            print("Извините, но рейс пустой! Можете забронировать новый рейс!")
        else:
            print(f"Вот ваш теущий рейс: {self._numbertrip}\n{self._pointplace}\n{self._cost}\n{self._departuretime}\n{self._arrivaltime}\n")

    #Функция по вводу данных о рейсах
    def inputTrip(self, newnumbertrip, newpointplace, newcost, newdepraturetime, newarrivaltime):
        self._numbertrip = newnumbertrip
        self._pointplace = newpointplace
        self._cost = newcost
        self._departuretime = newdepraturetime
        self._arrivaltime = newarrivaltime
        print(f"Ваши данные о поездке изменились: {self._numbertrip}\n{self._pointplace}\n{self._cost}\n{self._departuretime}\n{self._arrivaltime}\n")

class ExpressBusTrip(BusTrip):
    def __init__(self, numbertrip=None, pointplace=None, cost=None, departuretime=None, arrivaltime=None, uppdatemoney=None):
        super().__init__(numbertrip, pointplace, cost, departuretime, arrivaltime)
        self._uppdatemoney = uppdatemoney
    
    #Функция по выводу данных
    def printTrip(self):
        #По идеи достаточно одного условия на проверку номера рейса
        if(self._numbertrip is None):
            print("Извините, но рейс пустой! Можете забронировать новый рейс!")
        else:
            print(f"Вот ваш теущий рейс c учетом процентной надбавкой на цену билета: {self._numbertrip}\n{self._pointplace}\n{(self._cost)*(self._uppdatemoney)}\n{self._departuretime}\n{self._arrivaltime}\n{self._uppdatemoney}\n")
    
    #Функция по вводу данных о рейсах
    def inputTrip(self, newnumbertrip, newpointplace, newcost, newdepraturetime, newarrivaltime, newuppdatemoney):
        self._numbertrip = newnumbertrip
        self._pointplace = newpointplace
        self._cost = newcost
        self._departuretime = newdepraturetime
        self._arrivaltime = newarrivaltime
        self._uppdatemoney = newuppdatemoney
        print(f"Ваши данные о поездке изменились: {self._numbertrip}\n{self._pointplace}\n{self._cost}\n{self._departuretime}\n{self._arrivaltime}\n{self._uppdatemoney}")
    
class InternationalBusTrip(ExpressBusTrip):
    def __init__(self, numbertrip=None, pointplace=None, cost=None, departuretime=None, arrivaltime=None, uppdatemoney=None, country=None):
        super().__init__(numbertrip, pointplace, cost, departuretime, arrivaltime, uppdatemoney)
        self._country = country
    
    #Функция по выводу данных
    def printTrip(self):
        #По идеи достаточно одного условия на проверку номера рейса
        if(self._numbertrip is None):
            print("Извините, но ваш международный рейс пустой! Можете забронировать новый международный рейс!")
        else:
            print(f"Вот ваш теущий международный рейс: {self._numbertrip}\n{self._pointplace}\n{(self._cost)*(self._uppdatemoney)}\n{self._departuretime}\n{self._arrivaltime}\n{self._uppdatemoney}\n{self._country}\n")
    
    #Функция по вводу данных о рейсах
    def inputTrip(self, newnumbertrip, newpointplace, newcost, newdepraturetime, newarrivaltime, newuppdatemoney, newcountry):
        self._numbertrip = newnumbertrip
        self._pointplace = newpointplace
        self._cost = newcost
        self._departuretime = newdepraturetime
        self._arrivaltime = newarrivaltime
        self._uppdatemoney = newuppdatemoney
        self._country = newcountry
        print(f"Ваши данные о поездке изменились: {self._numbertrip}\n{self._pointplace}\n{self._cost}\n{self._departuretime}\n{self._arrivaltime}\n{self._uppdatemoney}\n{self._country}")

#Создаем экземпляры классов без ввода аргументов
ObjBusTrip1 = BusTrip()
ObjBusTrip2 = ExpressBusTrip()
ObjBusTrip3 = InternationalBusTrip()

#Пробуем полиморфизм
ObjBusTrip1.inputTrip("123", "Moscow", 12500, "01.01.2024|15:30", "03.01.2024|09:00")
ObjBusTrip1.printTrip()

#Здесь цена 12000 без учета надбавки за экспресс перевозки
ObjBusTrip2.inputTrip("321", "St`Peterburg", 12000, "05.12.2024|08:30", "05.12.2024|11:00", 0.25)
#Здесь в выводе 12000*0.25 с учетом надбавки за экспресс перевозки
ObjBusTrip2.printTrip()

ObjBusTrip3.inputTrip("213", "Novosibirsk", 15000, "05.05.2024|16:55", "08.05.2024|09:00", 0.25, "Russia")
ObjBusTrip3.printTrip()

#Задание 3
# Базовый класс «ПРЕПОДАВАТЕЛЬ» описывает данные: ФИО преподавателя, должность, кафедра. 
# Производный класс «КУРАТОР» содержит следующие данные: название курируемой группы, номер курса. 
# Производный класс «НАУЧНЫЙ РУКОВОДИТЕЛЬ» содержит следующие данные: тема, ФИО студента. 
# Организовать ввод/вывод данных о преподавателе. 
# Вывести список преподавателей для указанной кафедры. 
# Учтите, что один и тот же сотрудник может быть одновременно и куратором и руководить научной работой нескольких студентов, а может не быть ни тем, ни другим.

#Родительский класс
class Teacher():
    def __init__(self, FIO, post, department):
        self._FIO = FIO
        self._post = post
        self._department = department

    #Пробуем переопределить __str__ для форматирования вывода
    def __str__(self):
        return f"ФИО: {self._FIO}, Должность: {self._post}, Кафедра: {self._department}"
    
    @property
    def department(self):
        return self._department

#Дочерний класс от родительского класса Teacher
class Tutor(Teacher):
    def __init__(self, FIO, post, department, namegroup, coursenumber):
        super().__init__(FIO, post, department)
        self._namegroup = namegroup
        self._coursenumber = coursenumber

    def __str__(self):
        return super().__str__()+f", Название группы: {self._namegroup}, Номер курса {self._coursenumber}"

#Дочерний класс от родительского класса Teacher   
class ScientificSupervisor(Teacher):
    def __init__(self, FIO, post, department, topic, FIOstudent):
        super().__init__(FIO, post, department)
        self._topic = topic
        self._FIOstudent = FIOstudent

    def __str__(self):
        return super().__str__()+f", Название темы {self._topic}, ФИО студента {self._FIOstudent}"

# Функция для фильтрации преподавателей по кафедре
def filter_teachers_by_department(teachers, department_name):
    return [teacher for teacher in teachers if teacher.department == department_name]
    
#Список сотдруников вуза
teachers = [
    Teacher("Макбукович К.К", "Профессор", "ИЕТН"),
    Tutor("Зайцев А.И", "Старший куратор", "ВШЭКН", "КЭ-233", 2),
    ScientificSupervisor("Дегтярёв П.И", "Научный руководитель", "ИЕТН", "Алгоритмы и структуры данных", "Ишаков Ю.Ю"),
]

# Вывод всех преподавателей
print("Все преподаватели:")
for teacher in teachers:
    print(teacher)

# Вывод преподавателей указанной кафедры
department_to_filter = "ИЕТН"
print(f"\nПреподаватели кафедры {department_to_filter}:")
filtered_teachers = filter_teachers_by_department(teachers, department_to_filter)
for teacher in filtered_teachers:
    print(teacher)
