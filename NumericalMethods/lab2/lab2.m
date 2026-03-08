% Пределы интегрирования a,b
a = 2;
b = 3;
f = @(x) 1./((x.^3+3.*x.^2+3.*x+1).*sqrt(x.^2+2.*x-3));

% Вычислим точный интеграл I_точное при помощи встроенной функции integral
I_accuracy1 = integral(f, a, b);
fprintf("Точное при помощи функции integral: %.10f\n\n", I_accuracy1);

% График
x_plot = linspace(a, b, 1000);
figure;
plot(x_plot, f(x_plot), 'LineWidth', 1.5);
grid on;
title("График фуункции");
xlabel('x');
ylabel('y = f(x)');

%Задаем кол-во промежутков, шаг обучения и узлы разбиения 
n = 6;
h = (b - a) / n;
node = linspace(a, b, n+1);

% Квадратурные методы (формулы)
Left_rectangle = h*sum(f(node(1:end-1)));
Right_rectangle = h*sum(f(node(2:end)));
Trapezoid = (Left_rectangle + Right_rectangle) / 2;
fprintf("Метод трапеции: %.10f\n", Trapezoid);
Simpson_integral = h * (f(node(1)) + f(node(end)) + 4 * sum(f(node(2:2:end-1))) + 2 * sum(f(node(3:2:end-2)))) / 3;
fprintf("Метод Симпсона: %.10f\n\n", Simpson_integral);

%Оценка погрешностей и пересчитать для h/2, т.е. 2n = 2 * n
n2 = 2 * n;
h = (b - a) / n2;
node_2 = linspace(a, b, n2 + 1);

%Квадратурные методы в смысле 2n:
Left_rectangle_1 = h*sum(f(node_2(1:end-1)));
Right_rectangle_1 = h*sum(f(node_2(2:end)));
Trapezoid_1 = (Left_rectangle_1 + Right_rectangle_1) / 2;
fprintf("Метод трапеции (в смысле 2n): %.10f\n", Trapezoid_1);
Simpson_integral_1 = h * (f(node_2(1)) + f(node_2(end)) + 4 * sum(f(node_2(2:2:end-1))) + 2 * sum(f(node_2(3:2:end-2)))) / 3;
fprintf("Метод Симпсона (в смысле 2n): %.10f\n\n", Simpson_integral_1);


% Оценка погрешности:
R_Trapezoid = abs((Trapezoid_1 - Trapezoid)/3);
fprintf("Погрешность Рунге трапеций: %.20f\n", R_Trapezoid);
R_Simpson = abs((Simpson_integral_1 - Simpson_integral) / 15);
fprintf("Погрешность Рунге метод Симпсона: %.20f\n\n", R_Simpson);

% Уточняющий интеграл: результат интеграла по методам + Рунге по всем метод
Clarify_Trapezoid = Trapezoid_1 + R_Trapezoid;
fprintf("Уточняющий интеграл трапеций: %.20f\n", Clarify_Trapezoid);
Clarify_Simpson =  Simpson_integral_1 + R_Simpson;
fprintf("Уточняющий интеграл Симпсон: %.20f\n\n", Clarify_Simpson);

% Сравнение погрешностей: |фактическое (через integral) - I_уточняющее|
fin4 = abs(I_accuracy1 - Clarify_Trapezoid);
fprintf("Фактический итеграл для трапеций: %.20f\n\n", fin4);
fin5 = abs(I_accuracy1 - Clarify_Simpson);
fprintf("Фактический итеграл для Симпсона: %.20f\n\n", fin5);
