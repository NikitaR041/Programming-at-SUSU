#include <iostream>
#include "Button.h"
#include "Math_for_calc.h"
#include "Button_processing.h"
#include "graphics.h"

//Структура кнопки, в которой хранятся координаты, приоритеты, названия и типы
struct Button {
    int x1;
    int y1;
    int x2;
    int y2;
    int priority; 
    char name[20];
    char symb[20];
    std::string type_str;
    int type;
    IMAGE* bmp;
};

//Перечисление, которая нужна для определение типа кнопки (Используется в switch)
enum type {
    BINARY_OP, //Бинарные математические функции или арифметические операции
    UNARY_OP, //Унарные математические функции 
    PARENTHESIS, //Скобки
    DIGIT, //Цифры
    CONSTANT, //Константы
    EDITION, //Очищение экрана или посимвольное удаление
    RESULT, //Вычисление результата
    DEGRAD //Перевод из типа DEG в RAG (и наоборот | по умолчанию DEG)
};

//Структура кнопки
struct Button but[N] = { {0, 80, 89, 169, 3, "buttons\\DEGRAD.bmp", "", "DEGRAD", DEGRAD}, {90, 80, 179, 169, 3, "buttons\\mod.bmp", "V", "MOD", BINARY_OP}, {180, 80, 269, 169, 0, "buttons\\CE.bmp", "", "CE", EDITION}, {270, 80, 359, 169, 0, "buttons\\DELETE.bmp", "", "delete", EDITION}, {360, 80, 449, 169, 0, "buttons\\(.bmp", "(", "(", PARENTHESIS}, {450, 80, 539, 169, 0,"buttons\\).bmp", ")", ")", PARENTHESIS}, {540, 80, 629, 169, 0,"buttons\\e.bmp", "e", "2,718281828459045", CONSTANT}, {630, 80, 719, 169, 3,"buttons\\exp.bmp", "W", "exp", UNARY_OP}, {720, 80, 810, 169, 3,"buttons\\del1.bmp", "X", "1/", UNARY_OP} ,
                        {0, 170, 89, 259, 1, "buttons\\+.bmp", "+", "+", BINARY_OP}, {90, 170, 179, 259, 0, "buttons\\1.bmp", "1", "1", DIGIT}, {180, 170, 269, 259, 0, "buttons\\2.bmp", "2", "2", DIGIT}, {270, 170, 359, 259, 0, "buttons\\3.bmp", "3", "3", DIGIT}, {360, 170, 449, 259, 3, "buttons\\sqrt2.bmp", "A", "sqrt2", UNARY_OP}, {450, 170, 539, 259, 3, "buttons\\sqrt.bmp", "B", "sqrt", BINARY_OP}, {540, 170, 629, 259, 3, "buttons\\x2.bmp", "C", "^2", UNARY_OP}, {630, 170, 719, 259, 3, "buttons\\xn.bmp", "D", "^", BINARY_OP}, {720, 170, 810, 259, 3, "buttons\\x!.bmp", "E", "fact", UNARY_OP},
                        {0, 260, 89, 349, 1, "buttons\\-.bmp", "-", "-", BINARY_OP}, {90, 260, 179, 349, 0, "buttons\\4.bmp", "4", "4", DIGIT}, {180, 260, 269, 349, 0, "buttons\\5.bmp", "5", "5", DIGIT}, {270, 260, 359, 349, 0, "buttons\\6.bmp", "6", "6", DIGIT}, {360, 260, 449, 349, 3, "buttons\\log2.bmp", "F", "log2", UNARY_OP}, {450, 260, 539, 349, 3, "buttons\\logn.bmp", "G", "log", BINARY_OP}, {540, 260, 629, 349, 3, "buttons\\ln.bmp", "H", "ln", UNARY_OP}, {630, 260, 719, 349, 3, "buttons\\lg.bmp", "I", "lg", UNARY_OP}, {720, 260, 810, 349, 3, "buttons\\10n.bmp", "K", "10^", UNARY_OP},
                        {0, 350, 89, 439, 2, "buttons\\del.bmp", "/", "/", BINARY_OP}, {90, 350, 179, 439, 0, "buttons\\7.bmp", "7", "7", DIGIT}, {180, 350, 269, 439, 0, "buttons\\8.bmp", "8", "8", DIGIT}, {270, 350, 359, 439, 0, "buttons\\9.bmp", "9", "9", DIGIT}, {360, 350, 449, 439, 3, "buttons\\sin.bmp", "L", "sin", UNARY_OP}, {450, 350, 539, 439, 3, "buttons\\cos.bmp", "M", "cos", UNARY_OP}, {540, 350, 629, 439, 3, "buttons\\tg.bmp", "N", "tg", UNARY_OP}, {630, 350, 719, 439, 3, "buttons\\ctg.bmp", "O", "ctg", UNARY_OP}, {720, 350, 810, 439, 0, "buttons\\pi.bmp", "pi", "3,14159265358979323846", CONSTANT},
                        {0, 440, 89, 530, 2, "buttons\\X.bmp", "*",  "*", BINARY_OP}, {90, 440, 179, 530, 0, "buttons\\=.bmp", "=", "=", RESULT}, {180, 440, 269, 530, 0, "buttons\\0.bmp", "0", "0", DIGIT}, {270, 440, 359, 530, 0, "buttons\\point.bmp", ",", "point", DIGIT}, {360, 440, 449, 530, 3, "buttons\\arcsin.bmp", "P", "arcsin", UNARY_OP}, {450, 440, 539, 530, 3, "buttons\\arccos.bmp", "Q", "arccos", UNARY_OP}, {540, 440, 629, 530, 3, "buttons\\arctg.bmp", "R", "arctg", UNARY_OP}, {630, 440, 719, 530, 3, "buttons\\arcctg.bmp", "S", "arcctg", UNARY_OP}, {720, 440, 810, 530, 3, "buttons\\modulx.bmp", "T", "abs", UNARY_OP}};

int priority; //Нужен для запоминания приоритета у знака 
int priority_skb_o; //Запоминает количество открытых скобок
int check_skb_z = false; //Проверка, что пользователь нажал на закрытую скобку
int is_break_one = false; //Для завершения внешнего цикла
int special_skb = false; // Проверка на то, что пользователь пользуется скобками при включении мат.функций
int use_arith = false; // Запрет на использование какой-либо арифметики для бинарных функций
int is_check_constant = false; //Проверка на то, что пользователь нажал на константу
int is_check_del = false; //Проверка на делимость двух чисел
int is_check_deg_rag = false; //Проверка на замену из DEG в RAG и наоборот (По умолчанию DEG)
int is_finish = false; //Проверка, что нажата кнопка =
int is_check_error = false; // Проверка, если математическая функция дала ошибку
int is_check_binary = false; //Проверка, что пользователь пользуется бинарной функцией
int intermediate_result = false; //Проверка, что в скобках произошло вычисление
char is_check_binary_symb; //Проверка, какая была нажата бинарная функция

double num_1 = 0, num_2 = 0;
//Накопление цифр в строке, а затем явным образом меняем на тип double, что в последствии можно обработать в дальнейшем число или сохранение в стек
std::string num_str{}; 

//Это функция отвечает за отрисовку картинок и все
void draw_buts() {    
    setcolor(LIGHTGRAY);
    for (int i = 0; i < 45; i++) {
        but[i].bmp = loadBMP(but[i].name);
         if (but[i].bmp == nullptr) {
            std::cout << "Ошибка загрузки изображения: " << but[i].name << "\n";
            closegraph();
            return; 
         }
        putimage(but[i].x1, but[i].y1, but[i].bmp, COPY_PUT);
        rectangle(but[i].x1, but[i].y1, but[i].x2, but[i].y2);
    }
}

void clear_global_obj(){
    priority = 0; //Нужен для запоминания приоритета у знака 
    priority_skb_o = 0; //Запоминает количество открытых скобок
    check_skb_z = false; //Проверка, что пользователь нажал на закрытую скобку
    is_break_one = true; //Для завершения внешнего цикла
    use_arith = false; // Запрет на использование какой-либо арифметики для бинарных функций
    special_skb = false; // Проверка на то, что пользователь пользуется скобками при включении мат.функций
    is_check_constant = false; //Если объявляли ранее константу, то уберем флажок
    is_check_del = false; //Проверка на делимость двух чисел
    is_finish = false; //Проверка, что нажата кнопка =
    is_check_error = false; // Проверка, если математическая функция дала ошибку
    is_check_binary = false; //Проверка, что пользователь пользуется бинарной функцией
    intermediate_result = false; //Проверка, что в скобках произошло вычисление
    //Переменные для бинарной функции
    num_1 = 0; 
    num_2 = 0;
}

//Очищение двух стеков
void clear_the_input(my_stack& m, stack_char& b) {
    //Очистка двух стеков
    while (stack_isempty(&b) == false || stack_isempty(&m) == false) {
        if (stack_isempty(&m) == false) {
            stack_pop(&m);
        }
        else if (stack_isempty(&b) == false) {
            stack_pop(&b);
        }
    }
}

//Очищение буфера, 'буфер' хранит в себе координаты кнопки после нажатия ЛКМ на диалоговое окно
void clear_bufer(int* mass, int* jndex, int* count_mass) {
    //-----Очищает память-----
    mass[(*jndex)] = 0;
    mass[(*jndex) + 1] = 0;
    *count_mass = 0;
    //-----Очищает память-----
}

//Замена из DEG в RAG и наоборот
void replace_deg_rag(int* is_check_deg_rad_param) {
    if (*is_check_deg_rad_param == false) {
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
        outtextxy(15, 114, "DEG"); 
        outtextxy(15, 114, "DEG"); 
    }
    else if (*is_check_deg_rad_param == true) {
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
        outtextxy(15, 114, "RAD");
    }
}

//Функция по удаление временного вычисления
void clear_interim_solution() {
    //Делаем черный прямоугольник для удаление числа
    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 35, 810, 70);
    //Показываем на экран цифры
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(10, 35, num_str.c_str());
}

//Функция по замене знака '-' на '+' для мат.функ. abs
void draw_template_abs(std::string& output_result ){
    int s2 = 0;
    s2 = output_result.length();
    output_result.erase(s2 - 1);
    output_result += '+';
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//Рисование шаблона для унарнх функций
void draw_template(std::string& output_result, int index, double num) {
   if (but[index].type_str == "^2"){
      output_result += '(' + std::to_string(num) + ')' + but[index].type_str;
   } else{
      output_result += but[index].type_str + '(' + std::to_string(num) + ')';
   }
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//Рисования шаблона для бинарных функций
void draw_temlate_buniary(std::string& output_result, int index, double num_1_param) {
    output_result += std::to_string(num_1_param) + but[index].type_str;    
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//В этой функции обрабатывается тип кнопки
void about_but(int* mass, int* count_mass, std::string& output_result, std::string& result_str, my_stack& m, stack_char& b) {
    if (mass[0] == 0 && mass[1] == 0) {
        return;
    }
    for (int i = 0; i < N; i++) { //Проходимся по структуре
        //Для завершения внешнего цикла
        if (is_break_one == true) {
            is_break_one = false;
            break;
        }
        for (int j = 0; j < (*count_mass); j += 2) { //Проходимся по массиву пар "кнопок"
           //Проверка по Х и проверка по Y
            if ((but[i].x1 <= mass[j] && mass[j] <= but[i].x2) && (but[i].y1 <= mass[j + 1] && mass[j + 1] <= but[i].y2)) {
                
                switch (but[i].type) {
                case BINARY_OP: {
                    use_arith = true; // Использовалось аримфетика
                    is_check_constant = false; //Если объявляли ранее константу, то уберем флажок
                    check_skb_z = false;
                    clear_bufer(mass, &j, count_mass); // Очищаем буфер
                    
                    //Если пользователь нажал на бинарную функцию, то
                    //Если пользователь сразу нажал на бинарную математическую функцию, то
                    if (num_str != "" && num_1 == 0 && num_2 == 0 && (but[i].type_str == "MOD" || but[i].type_str == "^" || but[i].type_str == "sqrt" || but[i].type_str == "log")) {
                        is_check_binary = true;
                        is_check_binary_symb = but[i].symb[0]; // передаем специальный символ бин.мат.функции
                        num_1 = std::stod(num_str);
                        num_str.clear();
                        draw_temlate_buniary(output_result, i, num_1); // Отображем выражение на экране
                        is_break_one = true;
                        break; 
                    }
                    else if (num_str != "" && is_check_binary == true && (but[i].symb[0] == '+' || but[i].symb[0] == '-' || but[i].symb[0] == '*' || but[i].symb[0] == '/')) {
                        num_2 = std::stod(num_str);
                        out_expression_str(output_result, num_str); //Отображаем число 
                        out_expression(output_result, but[i].symb[0]); // Отображаем знак 
                        num_str.clear();
                        switch_binary_func(is_check_binary_symb, num_1, num_2, &is_check_error, output_result, m); //Определение бин.функции
                        if (is_check_error == true) {
                            is_break_one = true;
                            clear_bufer(mass, &j, count_mass);
                            break;
                        }
                        arith_switch(but[i].symb[0], &priority, b);
                        switch_arith_push(but[i].symb[0], b);
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(10, 35, 810, 70);
                        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
                        outtextxy(10, 35, std::to_string(stack_top(&m)).c_str()); //Достаем число в качестве промежуточного вычисления 
                        is_break_one = true;
                        is_check_binary = false;
                        break; 
                    }
                    //Если не ввели число, то пропускаем ход
                    else if (num_str == "" && (but[i].type_str == "MOD" || but[i].type_str == "^" || but[i].type_str == "sqrt" || but[i].type_str == "log")) {
                        is_break_one = true;
                        break;
                    }

                    //Если пользователь опять нажал на арифметический знак, то ничего не делаем, должно поступить от пользователя число
                    //&& check_skb_z == false -> use_arith ??
                    if (num_str == ""  && intermediate_result == false && stack_isempty(&m) == false  && stack_isempty(&b) == false) {
                        is_break_one = true;
                        break; //Досрочно уходим
                    }

                    //Если пользователь изначально хочет ввести знаки, которые написаны в условии ниже, то пропускаем
                    //output_result.length() == 0
                    //&& check_skb_z == false -> use_arith ??
                    if (num_str == "" && intermediate_result == false && (but[i].symb[0] == '+' || but[i].symb[0] == '*' || but[i].symb[0] == '/')) {
                        is_break_one = true;
                    }
                    //Если пользователь с самого начала нажал на знак '-' | result_out == ""
                    //&& check_skb_z == false -> use_arith ??
                    else if (output_result.length() == 0 && num_str == "" && but[i].symb[0] == '-' ) {
                        is_break_one = true;
                        out_expression(output_result, '0'); //Показываем число 0
                        out_expression(output_result, but[i].symb[0]); // По символьно выводим арифметический знак на диалоговое окно
                        
                        arith_switch(but[i].symb[0], &priority, b); //Сначала рассмотрим какая приоритетность у знака
                        switch_arith_push(but[i].symb[0], b); //Затем заносим в стек и знаем, что за приоритет у знака
                    }
                    //Иначе, пользователь изначально ввел число, а потом знак...
                    else {
                        //Нажали на знак, значит покажем это на экране
                        out_expression_str(output_result, num_str); //Сначала покажем число
                        savestr(num_str, m); // Затем сохраним число
                        out_expression(output_result, but[i].symb[0]); //Потом покажем знак

                        //Рассмотрим изменение выражения, если 5-4*,4-3-, 4-2+, 4-1/ . -> ?
                        if (stack_top(&b) == '-' && (but[i].symb[0] == '+' || but[i].symb[0] == '-' || but[i].symb[0] == '*' || but[i].symb[0] == '/')) { // Проверить вот этот случай
                            delete_sub(&priority, m, b);
                        }

                        //Затем проверяем на порядок приоритетностей в стеке с текущим арифметическим знаком!
                        //В if проверяем был ли пустой арифметический стек или нет
                        if (stack_isempty(&b) == true) {
                            is_break_one = true;
                            arith_switch(but[i].symb[0], &priority, b);
                            switch_arith_push(but[i].symb[0], b);

                        }//в else if ожидается, что уже было введено какое-то выражение и так, что в стеке приоритнетность знака либо равна с текущим приоритетностью знака, либо больше
                        else if (priority == but[i].priority || priority > but[i].priority) {
                            while (priority == but[i].priority || priority > but[i].priority) {
                                //Процесс "слияние" двух чисел в одно и уменьше на единицу знак
                                merging_two_numbers(&priority, m, b, output_result);
                            }
                            is_break_one = true;
                            //Затем новый знак заносим (1)-(2)
                            arith_switch(but[i].symb[0], &priority, b);
                            switch_arith_push(but[i].symb[0], b); // Проверка в цикле прошла,значит, можно заносить новый знак в арифметический стек
                            
                            //Здесь должны показать промежуточное вычисление
                            //Делаем черный прямоугольник для удаление числа
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(10, 35, 810, 70);
                            out_result(num_str, m); //Здесь мы заного добавили число в num_str, который ранее очищали

                        }//в else ожидается, что первые два условия не прошли, то заносим в стек
                        else {
                            is_break_one = true;
                            arith_switch(but[i].symb[0], &priority, b);
                            switch_arith_push(but[i].symb[0], b);
                        }
                    }
                    break;
                }
                case UNARY_OP: {
                    double num = 0;
                    //Проверка на то, что если пользователь использовал abs
                    if (but[i].type_str == "abs" && stack_top(&b) == '-') {
                        draw_template_abs(output_result);
                        delete_sub_unary(&priority, b);
                        //draw_buts();
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                        break;
                    }//Иначе пользователь используем другой арифметический знак
                    else if (but[i].type_str == "abs" && (stack_top(&b) == '+' || stack_top(&b) == '*' || stack_top(&b) == '/')) {
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                        break;
                    }
                    //Если вначале пользователь не пользовался числом, а сразу применил унарную операцию, то по умолчанию использовал число 0
                    //Условие необходимо, если пользователь сразу использует унарную операцию
                    if (stack_isempty(&m) == true && (num_str.length() == 0 || num_str[0] == '0')) {
                        switch_unary_func(but[i].symb[0], num, &is_check_error, &is_check_deg_rag, output_result, m);
                        if (is_check_error == true) {
                            is_break_one = true;
                            clear_bufer(mass, &j, count_mass);
                            break;
                        }
                        draw_template(output_result, i, num); //Рисуем шаблон
                        delete_expression(num_str, m);
                        check_skb_z = true;
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                    }
                    //Обработаем случай, когда пользователь забыл ввести число, то вытаскиваем из стека число
                    //Например, 8 + "sin" -> 8 + sin(8) - итог выглядит так
                    else if (output_result.length() != 0 && num_str == "") {
                        //Когда появляется ответ на экране и пользователь хочет найти функци. от этого числа, то выолняется это условие
                        if (stack_isempty(&b) == true) {
                            cleardevice();
                            draw_buts();
                            output_result.clear();
                        }
                        num = stack_top(&m); //Достаем из стека число и передаем в качестве аргумента в функцию ниже
                        stack_pop(&m);//Удаляем число

                        switch_unary_func(but[i].symb[0], num,&is_check_error, &is_check_deg_rag, output_result, m);
                        if (is_check_error == true) {
                            is_break_one = true;
                            clear_bufer(mass, &j, count_mass);
                            break;
                        }
                        draw_template(output_result, i, num); //рисуем шаблон
                        delete_expression(num_str, m);
                        check_skb_z = true;
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                    }
                    //Иначе все нормально
                    else {
                        savestr(num_str, m); //Сохраняем число в стек
                        draw_template(output_result, i, stack_top(&m)); // рисуем шаблон
                        num = stack_top(&m); //Достаем из стека число и передаем в качестве аргумента в функцию ниже
                        stack_pop(&m);//Удаляем число
                        //Объявляется функция по обработке кнопки
                        switch_unary_func(but[i].symb[0], num,&is_check_error, &is_check_deg_rag, output_result, m);
                        if (is_check_error == true) {
                            is_break_one = true;
                            clear_bufer(mass, &j, count_mass);
                            break;
                        }
                        delete_expression(num_str, m);
                        check_skb_z = true;
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                    }
                    replace_deg_rag(&is_check_deg_rag);
                    break;
                }
                case PARENTHESIS: {
                    //Распишем исключение, если 5(2+2), * или / ? Также 5-(2+1) или 3+(1+2), какое число умножать на скобку ?
                    //Если есть арифметические знаки перед скобками, то
                    if (but[i].symb[0] == '(') {
                        out_expression(output_result, but[i].symb[0]);
                        priority = 0;
                        priority_skb_o += 1;
                        arith_switch(but[i].symb[0], &priority, b);
                        switch_arith_push(but[i].symb[0], b);
                        clear_bufer(mass, &j, count_mass);
                        is_break_one = true;
                    }
                    else if (but[i].symb[0] == ')') {
                        intermediate_result = true;
                        check_skb_z = true;
                        //Должны обработать случай, полльзователь ниразу не нажал на открывающуюся скобку
                        if (priority_skb_o > 0) {
                            //Отобразим число, а затем скобку
                            out_expression_str(output_result, num_str);
                            out_expression(output_result, but[i].symb[0]);
                            savestr(num_str, m);
                            is_singular(m, b, &priority, &priority_skb_o, output_result);

                            //Делаем черный прямоугольник для удаление числа
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(10, 35, 810, 70);
                            out_result(result_str, m); //Здесь мы заного добавили число в num_str, который ранее очищали
                            result_str.clear(); // Очищаем 
                            
                            //А если осталось ещё скобка из стека, то пропускаем ход и дальше рассматриваем на выражение
                            if (stack_top(&b) == '(' || stack_top(&b) == '+' || stack_top(&b) == '-' || stack_top(&b) == '*' || stack_top(&b) == '/' || stack_isempty(&b) == true) {
                                //Очищаем буфер
                                clear_bufer(mass, &j, count_mass);
                                is_break_one = true;
                                break;
                            }
                        }
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                    }
                    break;
                }
                case DIGIT: { 
                    //Обработка случая, когда пользователь не вводил число
                    if (result_str[0] == '0') result_str.clear();
                    if (use_arith == true) { 
                        use_arith = false;
                        num_str.clear();
                    }
                    //Обработаем случай, когда пользователь нажал на знак =
                    if (is_finish == true) {
                        is_finish = false;
                       
                       //Делаем черный прямоугольник для удаление числа
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(5, 5, 810, 70);
                       
                        clear_the_input(m, b);
                        num_str.clear();
                        result_str.clear();
                        output_result.clear();
                    }

                    //Основная часть сохранения цифр в тип string
                    is_break_one = true;
                    clear_bufer(mass, &j, count_mass);
                    //Обязательно num_str пустой!
                    num_str = num_str + but[i].symb[0];
                    clear_interim_solution();
                    break;
                }
                case CONSTANT: {
                    if (is_check_constant == false) {
                        is_check_constant = true;
                        //Показываем константное число, а потом стерем
                        num_str = but[i].type_str;
                        clear_interim_solution();
                    }
                    is_break_one = true;
                    clear_bufer(mass, &j, count_mass);
                    break;
                }
                case EDITION: {
                    clear_bufer(mass, &j, count_mass);
                    if (but[i].type_str == "CE" && (output_result.length() != 0 || result_str.length() != 0 || num_str.length() != 0)) {
                        clear_global_obj();
                        clear_the_input(m, b);
                        output_result.clear();
                        result_str.clear();
                        num_str.clear();
                        cleardevice();
                        draw_buts();
                        replace_deg_rag(&is_check_deg_rag);
                    }
                    else if (but[i].type_str == "delete") {
                        if (result_str != "" && is_finish == true) {
                            output_result.clear(); //Очищаем пример
                            num_str = result_str; //Передаем num_str число
                            result_str.clear(); //Очищаем ответ из массива
                            is_finish = false;
                        }
                        else if (num_str != "") {
                            num_str.erase(num_str.length() - 1);
                        }
                        cleardevice();
                        draw_buts();
                        //Задаем конкретное место удаления
                        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
                        outtextxy(10, 35, num_str.c_str());
                        replace_deg_rag(&is_check_deg_rag);
                    }
                    is_break_one = true;
                    break;
                }
                case RESULT: {
                    //ЕСли пользователь ввел 5+, 5^ -> нельзя так будет вычислить
                    if (num_str == "" && check_skb_z == false) {
                        is_break_one = true;
                        break;
                    }
                    
                    if (priority_skb_o > 0) {
                        cleardevice();
                        out_error(output_result, "Не равное количество открытых и закрытых скобок!");
                        draw_buts();
                        replace_deg_rag(&is_check_deg_rag);
                        is_break_one = true;
                        break;
                    }
                    is_finish = true;
                    check_skb_z = false;
                    clear_bufer(mass, &j, count_mass);

                    //В if eсли пользователь ничего не ввел, а нажимает на '='
                    if (num_str == "" && output_result.length() == 0) {
                        is_break_one = true;
                    }
                    //Может быть так, что пользователь нажал только на 2+, а нужно польностью 2+2
                    //((((5+4)+3)*2)/1)+2 -> в итоге 22 + 2, которое нужно посчитать 
                    else if (stack_isempty(&b) == false) {
                        is_check_binary = false; // Забываем про мат.функцию
                        is_break_one = true;
                        out_expression_str(output_result, num_str); // Добавляем в выражение
                        out_expression(output_result, '='); // Добавляем знак =
                        savestr(num_str, m);
                        while (stack_isempty(&b) == false) {
                            operation_result(stack_top(&b), output_result, &is_check_del, m, b);
                        }
                        //Здесь должны польностью показать результат
                        //Делаем черный прямоугольник для удаление числа
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(10, 35, 810, 70);
                        out_result(result_str, m);
                        replace_deg_rag(&is_check_deg_rag);
                    }
                    //(4+(5+(6*(4/2)))) -> в итоге получится 21, но в арифметическом стеке ничего нет
                    else if(stack_isempty(&b) == true){
                        is_break_one = true;
                        
                        out_expression_str(output_result, num_str); // Добавляем в выражение
                        out_expression(output_result, '='); // Добавляем знак =
                        if (is_check_binary == true) {
                            is_check_binary = false; // Забываем про мат.функцию
                            switch_binary_func(is_check_binary_symb, num_1, std::stod(num_str), &is_check_error, output_result, m);
                            if (is_check_error == true) {
                                is_break_one = true;
                                clear_bufer(mass, &j, count_mass);
                                break;
                            }
                        }
                        else {
                            savestr(num_str, m);
                        }
                        draw_buts();
                        bar(10, 35, 810, 70);
                        out_result(result_str, m);
                        replace_deg_rag(&is_check_deg_rag);
                    }
                    break;
                }
                case DEGRAD:{
                    if (is_check_deg_rag == false) {
                        is_check_deg_rag = true;
                        replace_deg_rag(&is_check_deg_rag);
                        clear_bufer(mass, &j, count_mass);
                        is_break_one = true;
                    }
                    else {
                        is_check_deg_rag = false;
                        replace_deg_rag(&is_check_deg_rag);
                        clear_bufer(mass, &j, count_mass);
                        is_break_one = true;
                    }
                    break;
                    }
                }  
            }else{
                continue;
            }
        }
    }
}
