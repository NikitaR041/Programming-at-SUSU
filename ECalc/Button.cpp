#include <iostream>
#include "Button.h"
#include "Math_for_calc.h"
#include "Button_processing.h"
#include "graphics.h"

//��������� ������, � ������� �������� ����������, ����������, �������� � ����
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

//������������, ������� ����� ��� ����������� ���� ������ (������������ � switch)
enum type {
    BINARY_OP, //�������� �������������� ������� ��� �������������� ��������
    UNARY_OP, //������� �������������� ������� 
    PARENTHESIS, //������
    DIGIT, //�����
    CONSTANT, //���������
    EDITION, //�������� ������ ��� ������������ ��������
    RESULT, //���������� ����������
    DEGRAD //������� �� ���� DEG � RAG (� �������� | �� ��������� DEG)
};

//��������� ������
struct Button but[N] = { {0, 80, 89, 169, 3, "buttons\\DEGRAD.bmp", "", "DEGRAD", DEGRAD}, {90, 80, 179, 169, 3, "buttons\\mod.bmp", "V", "MOD", BINARY_OP}, {180, 80, 269, 169, 0, "buttons\\CE.bmp", "", "CE", EDITION}, {270, 80, 359, 169, 0, "buttons\\DELETE.bmp", "", "delete", EDITION}, {360, 80, 449, 169, 0, "buttons\\(.bmp", "(", "(", PARENTHESIS}, {450, 80, 539, 169, 0,"buttons\\).bmp", ")", ")", PARENTHESIS}, {540, 80, 629, 169, 0,"buttons\\e.bmp", "e", "2,718281828459045", CONSTANT}, {630, 80, 719, 169, 3,"buttons\\exp.bmp", "W", "exp", UNARY_OP}, {720, 80, 810, 169, 3,"buttons\\del1.bmp", "X", "1/", UNARY_OP} ,
                        {0, 170, 89, 259, 1, "buttons\\+.bmp", "+", "+", BINARY_OP}, {90, 170, 179, 259, 0, "buttons\\1.bmp", "1", "1", DIGIT}, {180, 170, 269, 259, 0, "buttons\\2.bmp", "2", "2", DIGIT}, {270, 170, 359, 259, 0, "buttons\\3.bmp", "3", "3", DIGIT}, {360, 170, 449, 259, 3, "buttons\\sqrt2.bmp", "A", "sqrt2", UNARY_OP}, {450, 170, 539, 259, 3, "buttons\\sqrt.bmp", "B", "sqrt", BINARY_OP}, {540, 170, 629, 259, 3, "buttons\\x2.bmp", "C", "^2", UNARY_OP}, {630, 170, 719, 259, 3, "buttons\\xn.bmp", "D", "^", BINARY_OP}, {720, 170, 810, 259, 3, "buttons\\x!.bmp", "E", "fact", UNARY_OP},
                        {0, 260, 89, 349, 1, "buttons\\-.bmp", "-", "-", BINARY_OP}, {90, 260, 179, 349, 0, "buttons\\4.bmp", "4", "4", DIGIT}, {180, 260, 269, 349, 0, "buttons\\5.bmp", "5", "5", DIGIT}, {270, 260, 359, 349, 0, "buttons\\6.bmp", "6", "6", DIGIT}, {360, 260, 449, 349, 3, "buttons\\log2.bmp", "F", "log2", UNARY_OP}, {450, 260, 539, 349, 3, "buttons\\logn.bmp", "G", "log", BINARY_OP}, {540, 260, 629, 349, 3, "buttons\\ln.bmp", "H", "ln", UNARY_OP}, {630, 260, 719, 349, 3, "buttons\\lg.bmp", "I", "lg", UNARY_OP}, {720, 260, 810, 349, 3, "buttons\\10n.bmp", "K", "10^", UNARY_OP},
                        {0, 350, 89, 439, 2, "buttons\\del.bmp", "/", "/", BINARY_OP}, {90, 350, 179, 439, 0, "buttons\\7.bmp", "7", "7", DIGIT}, {180, 350, 269, 439, 0, "buttons\\8.bmp", "8", "8", DIGIT}, {270, 350, 359, 439, 0, "buttons\\9.bmp", "9", "9", DIGIT}, {360, 350, 449, 439, 3, "buttons\\sin.bmp", "L", "sin", UNARY_OP}, {450, 350, 539, 439, 3, "buttons\\cos.bmp", "M", "cos", UNARY_OP}, {540, 350, 629, 439, 3, "buttons\\tg.bmp", "N", "tg", UNARY_OP}, {630, 350, 719, 439, 3, "buttons\\ctg.bmp", "O", "ctg", UNARY_OP}, {720, 350, 810, 439, 0, "buttons\\pi.bmp", "pi", "3,14159265358979323846", CONSTANT},
                        {0, 440, 89, 530, 2, "buttons\\X.bmp", "*",  "*", BINARY_OP}, {90, 440, 179, 530, 0, "buttons\\=.bmp", "=", "=", RESULT}, {180, 440, 269, 530, 0, "buttons\\0.bmp", "0", "0", DIGIT}, {270, 440, 359, 530, 0, "buttons\\point.bmp", ",", "point", DIGIT}, {360, 440, 449, 530, 3, "buttons\\arcsin.bmp", "P", "arcsin", UNARY_OP}, {450, 440, 539, 530, 3, "buttons\\arccos.bmp", "Q", "arccos", UNARY_OP}, {540, 440, 629, 530, 3, "buttons\\arctg.bmp", "R", "arctg", UNARY_OP}, {630, 440, 719, 530, 3, "buttons\\arcctg.bmp", "S", "arcctg", UNARY_OP}, {720, 440, 810, 530, 3, "buttons\\modulx.bmp", "T", "abs", UNARY_OP}};

int priority; //����� ��� ����������� ���������� � ����� 
int priority_skb_o; //���������� ���������� �������� ������
int check_skb_z = false; //��������, ��� ������������ ����� �� �������� ������
int is_break_one = false; //��� ���������� �������� �����
int special_skb = false; // �������� �� ��, ��� ������������ ���������� �������� ��� ��������� ���.�������
int use_arith = false; // ������ �� ������������� �����-���� ���������� ��� �������� �������
int is_check_constant = false; //�������� �� ��, ��� ������������ ����� �� ���������
int is_check_del = false; //�������� �� ��������� ���� �����
int is_check_deg_rag = false; //�������� �� ������ �� DEG � RAG � �������� (�� ��������� DEG)
int is_finish = false; //��������, ��� ������ ������ =
int is_check_error = false; // ��������, ���� �������������� ������� ���� ������
int is_check_binary = false; //��������, ��� ������������ ���������� �������� ��������
int intermediate_result = false; //��������, ��� � ������� ��������� ����������
char is_check_binary_symb; //��������, ����� ���� ������ �������� �������

double num_1 = 0, num_2 = 0;
//���������� ���� � ������, � ����� ����� ������� ������ �� ��� double, ��� � ����������� ����� ���������� � ���������� ����� ��� ���������� � ����
std::string num_str{}; 

//��� ������� �������� �� ��������� �������� � ���
void draw_buts() {    
    setcolor(LIGHTGRAY);
    for (int i = 0; i < 45; i++) {
        but[i].bmp = loadBMP(but[i].name);
         if (but[i].bmp == nullptr) {
            std::cout << "������ �������� �����������: " << but[i].name << "\n";
            closegraph();
            return; 
         }
        putimage(but[i].x1, but[i].y1, but[i].bmp, COPY_PUT);
        rectangle(but[i].x1, but[i].y1, but[i].x2, but[i].y2);
    }
}

void clear_global_obj(){
    priority = 0; //����� ��� ����������� ���������� � ����� 
    priority_skb_o = 0; //���������� ���������� �������� ������
    check_skb_z = false; //��������, ��� ������������ ����� �� �������� ������
    is_break_one = true; //��� ���������� �������� �����
    use_arith = false; // ������ �� ������������� �����-���� ���������� ��� �������� �������
    special_skb = false; // �������� �� ��, ��� ������������ ���������� �������� ��� ��������� ���.�������
    is_check_constant = false; //���� ��������� ����� ���������, �� ������ ������
    is_check_del = false; //�������� �� ��������� ���� �����
    is_finish = false; //��������, ��� ������ ������ =
    is_check_error = false; // ��������, ���� �������������� ������� ���� ������
    is_check_binary = false; //��������, ��� ������������ ���������� �������� ��������
    intermediate_result = false; //��������, ��� � ������� ��������� ����������
    //���������� ��� �������� �������
    num_1 = 0; 
    num_2 = 0;
}

//�������� ���� ������
void clear_the_input(my_stack& m, stack_char& b) {
    //������� ���� ������
    while (stack_isempty(&b) == false || stack_isempty(&m) == false) {
        if (stack_isempty(&m) == false) {
            stack_pop(&m);
        }
        else if (stack_isempty(&b) == false) {
            stack_pop(&b);
        }
    }
}

//�������� ������, '�����' ������ � ���� ���������� ������ ����� ������� ��� �� ���������� ����
void clear_bufer(int* mass, int* jndex, int* count_mass) {
    //-----������� ������-----
    mass[(*jndex)] = 0;
    mass[(*jndex) + 1] = 0;
    *count_mass = 0;
    //-----������� ������-----
}

//������ �� DEG � RAG � ��������
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

//������� �� �������� ���������� ����������
void clear_interim_solution() {
    //������ ������ ������������� ��� �������� �����
    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 35, 810, 70);
    //���������� �� ����� �����
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(10, 35, num_str.c_str());
}

//������� �� ������ ����� '-' �� '+' ��� ���.����. abs
void draw_template_abs(std::string& output_result ){
    int s2 = 0;
    s2 = output_result.length();
    output_result.erase(s2 - 1);
    output_result += '+';
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//��������� ������� ��� ������ �������
void draw_template(std::string& output_result, int index, double num) {
   if (but[index].type_str == "^2"){
      output_result += '(' + std::to_string(num) + ')' + but[index].type_str;
   } else{
      output_result += but[index].type_str + '(' + std::to_string(num) + ')';
   }
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//��������� ������� ��� �������� �������
void draw_temlate_buniary(std::string& output_result, int index, double num_1_param) {
    output_result += std::to_string(num_1_param) + but[index].type_str;    
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//� ���� ������� �������������� ��� ������
void about_but(int* mass, int* count_mass, std::string& output_result, std::string& result_str, my_stack& m, stack_char& b) {
    if (mass[0] == 0 && mass[1] == 0) {
        return;
    }
    for (int i = 0; i < N; i++) { //���������� �� ���������
        //��� ���������� �������� �����
        if (is_break_one == true) {
            is_break_one = false;
            break;
        }
        for (int j = 0; j < (*count_mass); j += 2) { //���������� �� ������� ��� "������"
           //�������� �� � � �������� �� Y
            if ((but[i].x1 <= mass[j] && mass[j] <= but[i].x2) && (but[i].y1 <= mass[j + 1] && mass[j + 1] <= but[i].y2)) {
                
                switch (but[i].type) {
                case BINARY_OP: {
                    use_arith = true; // �������������� ����������
                    is_check_constant = false; //���� ��������� ����� ���������, �� ������ ������
                    check_skb_z = false;
                    clear_bufer(mass, &j, count_mass); // ������� �����
                    
                    //���� ������������ ����� �� �������� �������, ��
                    //���� ������������ ����� ����� �� �������� �������������� �������, ��
                    if (num_str != "" && num_1 == 0 && num_2 == 0 && (but[i].type_str == "MOD" || but[i].type_str == "^" || but[i].type_str == "sqrt" || but[i].type_str == "log")) {
                        is_check_binary = true;
                        is_check_binary_symb = but[i].symb[0]; // �������� ����������� ������ ���.���.�������
                        num_1 = std::stod(num_str);
                        num_str.clear();
                        draw_temlate_buniary(output_result, i, num_1); // ��������� ��������� �� ������
                        is_break_one = true;
                        break; 
                    }
                    else if (num_str != "" && is_check_binary == true && (but[i].symb[0] == '+' || but[i].symb[0] == '-' || but[i].symb[0] == '*' || but[i].symb[0] == '/')) {
                        num_2 = std::stod(num_str);
                        out_expression_str(output_result, num_str); //���������� ����� 
                        out_expression(output_result, but[i].symb[0]); // ���������� ���� 
                        num_str.clear();
                        switch_binary_func(is_check_binary_symb, num_1, num_2, &is_check_error, output_result, m); //����������� ���.�������
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
                        outtextxy(10, 35, std::to_string(stack_top(&m)).c_str()); //������� ����� � �������� �������������� ���������� 
                        is_break_one = true;
                        is_check_binary = false;
                        break; 
                    }
                    //���� �� ����� �����, �� ���������� ���
                    else if (num_str == "" && (but[i].type_str == "MOD" || but[i].type_str == "^" || but[i].type_str == "sqrt" || but[i].type_str == "log")) {
                        is_break_one = true;
                        break;
                    }

                    //���� ������������ ����� ����� �� �������������� ����, �� ������ �� ������, ������ ��������� �� ������������ �����
                    //&& check_skb_z == false -> use_arith ??
                    if (num_str == ""  && intermediate_result == false && stack_isempty(&m) == false  && stack_isempty(&b) == false) {
                        is_break_one = true;
                        break; //�������� ������
                    }

                    //���� ������������ ���������� ����� ������ �����, ������� �������� � ������� ����, �� ����������
                    //output_result.length() == 0
                    //&& check_skb_z == false -> use_arith ??
                    if (num_str == "" && intermediate_result == false && (but[i].symb[0] == '+' || but[i].symb[0] == '*' || but[i].symb[0] == '/')) {
                        is_break_one = true;
                    }
                    //���� ������������ � ������ ������ ����� �� ���� '-' | result_out == ""
                    //&& check_skb_z == false -> use_arith ??
                    else if (output_result.length() == 0 && num_str == "" && but[i].symb[0] == '-' ) {
                        is_break_one = true;
                        out_expression(output_result, '0'); //���������� ����� 0
                        out_expression(output_result, but[i].symb[0]); // �� ��������� ������� �������������� ���� �� ���������� ����
                        
                        arith_switch(but[i].symb[0], &priority, b); //������� ���������� ����� �������������� � �����
                        switch_arith_push(but[i].symb[0], b); //����� ������� � ���� � �����, ��� �� ��������� � �����
                    }
                    //�����, ������������ ���������� ���� �����, � ����� ����...
                    else {
                        //������ �� ����, ������ ������� ��� �� ������
                        out_expression_str(output_result, num_str); //������� ������� �����
                        savestr(num_str, m); // ����� �������� �����
                        out_expression(output_result, but[i].symb[0]); //����� ������� ����

                        //���������� ��������� ���������, ���� 5-4*,4-3-, 4-2+, 4-1/ . -> ?
                        if (stack_top(&b) == '-' && (but[i].symb[0] == '+' || but[i].symb[0] == '-' || but[i].symb[0] == '*' || but[i].symb[0] == '/')) { // ��������� ��� ���� ������
                            delete_sub(&priority, m, b);
                        }

                        //����� ��������� �� ������� ��������������� � ����� � ������� �������������� ������!
                        //� if ��������� ��� �� ������ �������������� ���� ��� ���
                        if (stack_isempty(&b) == true) {
                            is_break_one = true;
                            arith_switch(but[i].symb[0], &priority, b);
                            switch_arith_push(but[i].symb[0], b);

                        }//� else if ���������, ��� ��� ���� ������� �����-�� ��������� � ���, ��� � ����� ��������������� ����� ���� ����� � ������� ��������������� �����, ���� ������
                        else if (priority == but[i].priority || priority > but[i].priority) {
                            while (priority == but[i].priority || priority > but[i].priority) {
                                //������� "�������" ���� ����� � ���� � ������� �� ������� ����
                                merging_two_numbers(&priority, m, b, output_result);
                            }
                            is_break_one = true;
                            //����� ����� ���� ������� (1)-(2)
                            arith_switch(but[i].symb[0], &priority, b);
                            switch_arith_push(but[i].symb[0], b); // �������� � ����� ������,������, ����� �������� ����� ���� � �������������� ����
                            
                            //����� ������ �������� ������������� ����������
                            //������ ������ ������������� ��� �������� �����
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(10, 35, 810, 70);
                            out_result(num_str, m); //����� �� ������ �������� ����� � num_str, ������� ����� �������

                        }//� else ���������, ��� ������ ��� ������� �� ������, �� ������� � ����
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
                    //�������� �� ��, ��� ���� ������������ ����������� abs
                    if (but[i].type_str == "abs" && stack_top(&b) == '-') {
                        draw_template_abs(output_result);
                        delete_sub_unary(&priority, b);
                        //draw_buts();
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                        break;
                    }//����� ������������ ���������� ������ �������������� ����
                    else if (but[i].type_str == "abs" && (stack_top(&b) == '+' || stack_top(&b) == '*' || stack_top(&b) == '/')) {
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                        break;
                    }
                    //���� ������� ������������ �� ����������� ������, � ����� �������� ������� ��������, �� �� ��������� ����������� ����� 0
                    //������� ����������, ���� ������������ ����� ���������� ������� ��������
                    if (stack_isempty(&m) == true && (num_str.length() == 0 || num_str[0] == '0')) {
                        switch_unary_func(but[i].symb[0], num, &is_check_error, &is_check_deg_rag, output_result, m);
                        if (is_check_error == true) {
                            is_break_one = true;
                            clear_bufer(mass, &j, count_mass);
                            break;
                        }
                        draw_template(output_result, i, num); //������ ������
                        delete_expression(num_str, m);
                        check_skb_z = true;
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                    }
                    //���������� ������, ����� ������������ ����� ������ �����, �� ����������� �� ����� �����
                    //��������, 8 + "sin" -> 8 + sin(8) - ���� �������� ���
                    else if (output_result.length() != 0 && num_str == "") {
                        //����� ���������� ����� �� ������ � ������������ ����� ����� ������. �� ����� �����, �� ���������� ��� �������
                        if (stack_isempty(&b) == true) {
                            cleardevice();
                            draw_buts();
                            output_result.clear();
                        }
                        num = stack_top(&m); //������� �� ����� ����� � �������� � �������� ��������� � ������� ����
                        stack_pop(&m);//������� �����

                        switch_unary_func(but[i].symb[0], num,&is_check_error, &is_check_deg_rag, output_result, m);
                        if (is_check_error == true) {
                            is_break_one = true;
                            clear_bufer(mass, &j, count_mass);
                            break;
                        }
                        draw_template(output_result, i, num); //������ ������
                        delete_expression(num_str, m);
                        check_skb_z = true;
                        is_break_one = true;
                        clear_bufer(mass, &j, count_mass);
                    }
                    //����� ��� ���������
                    else {
                        savestr(num_str, m); //��������� ����� � ����
                        draw_template(output_result, i, stack_top(&m)); // ������ ������
                        num = stack_top(&m); //������� �� ����� ����� � �������� � �������� ��������� � ������� ����
                        stack_pop(&m);//������� �����
                        //����������� ������� �� ��������� ������
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
                    //�������� ����������, ���� 5(2+2), * ��� / ? ����� 5-(2+1) ��� 3+(1+2), ����� ����� �������� �� ������ ?
                    //���� ���� �������������� ����� ����� ��������, ��
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
                        //������ ���������� ������, ������������� ������ �� ����� �� ������������� ������
                        if (priority_skb_o > 0) {
                            //��������� �����, � ����� ������
                            out_expression_str(output_result, num_str);
                            out_expression(output_result, but[i].symb[0]);
                            savestr(num_str, m);
                            is_singular(m, b, &priority, &priority_skb_o, output_result);

                            //������ ������ ������������� ��� �������� �����
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(10, 35, 810, 70);
                            out_result(result_str, m); //����� �� ������ �������� ����� � num_str, ������� ����� �������
                            result_str.clear(); // ������� 
                            
                            //� ���� �������� ��� ������ �� �����, �� ���������� ��� � ������ ������������� �� ���������
                            if (stack_top(&b) == '(' || stack_top(&b) == '+' || stack_top(&b) == '-' || stack_top(&b) == '*' || stack_top(&b) == '/' || stack_isempty(&b) == true) {
                                //������� �����
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
                    //��������� ������, ����� ������������ �� ������ �����
                    if (result_str[0] == '0') result_str.clear();
                    if (use_arith == true) { 
                        use_arith = false;
                        num_str.clear();
                    }
                    //���������� ������, ����� ������������ ����� �� ���� =
                    if (is_finish == true) {
                        is_finish = false;
                       
                       //������ ������ ������������� ��� �������� �����
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(5, 5, 810, 70);
                       
                        clear_the_input(m, b);
                        num_str.clear();
                        result_str.clear();
                        output_result.clear();
                    }

                    //�������� ����� ���������� ���� � ��� string
                    is_break_one = true;
                    clear_bufer(mass, &j, count_mass);
                    //����������� num_str ������!
                    num_str = num_str + but[i].symb[0];
                    clear_interim_solution();
                    break;
                }
                case CONSTANT: {
                    if (is_check_constant == false) {
                        is_check_constant = true;
                        //���������� ����������� �����, � ����� ������
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
                            output_result.clear(); //������� ������
                            num_str = result_str; //�������� num_str �����
                            result_str.clear(); //������� ����� �� �������
                            is_finish = false;
                        }
                        else if (num_str != "") {
                            num_str.erase(num_str.length() - 1);
                        }
                        cleardevice();
                        draw_buts();
                        //������ ���������� ����� ��������
                        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
                        outtextxy(10, 35, num_str.c_str());
                        replace_deg_rag(&is_check_deg_rag);
                    }
                    is_break_one = true;
                    break;
                }
                case RESULT: {
                    //���� ������������ ���� 5+, 5^ -> ������ ��� ����� ���������
                    if (num_str == "" && check_skb_z == false) {
                        is_break_one = true;
                        break;
                    }
                    
                    if (priority_skb_o > 0) {
                        cleardevice();
                        out_error(output_result, "�� ������ ���������� �������� � �������� ������!");
                        draw_buts();
                        replace_deg_rag(&is_check_deg_rag);
                        is_break_one = true;
                        break;
                    }
                    is_finish = true;
                    check_skb_z = false;
                    clear_bufer(mass, &j, count_mass);

                    //� if e��� ������������ ������ �� ����, � �������� �� '='
                    if (num_str == "" && output_result.length() == 0) {
                        is_break_one = true;
                    }
                    //����� ���� ���, ��� ������������ ����� ������ �� 2+, � ����� ���������� 2+2
                    //((((5+4)+3)*2)/1)+2 -> � ����� 22 + 2, ������� ����� ��������� 
                    else if (stack_isempty(&b) == false) {
                        is_check_binary = false; // �������� ��� ���.�������
                        is_break_one = true;
                        out_expression_str(output_result, num_str); // ��������� � ���������
                        out_expression(output_result, '='); // ��������� ���� =
                        savestr(num_str, m);
                        while (stack_isempty(&b) == false) {
                            operation_result(stack_top(&b), output_result, &is_check_del, m, b);
                        }
                        //����� ������ ���������� �������� ���������
                        //������ ������ ������������� ��� �������� �����
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(10, 35, 810, 70);
                        out_result(result_str, m);
                        replace_deg_rag(&is_check_deg_rag);
                    }
                    //(4+(5+(6*(4/2)))) -> � ����� ��������� 21, �� � �������������� ����� ������ ���
                    else if(stack_isempty(&b) == true){
                        is_break_one = true;
                        
                        out_expression_str(output_result, num_str); // ��������� � ���������
                        out_expression(output_result, '='); // ��������� ���� =
                        if (is_check_binary == true) {
                            is_check_binary = false; // �������� ��� ���.�������
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
