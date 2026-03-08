% Пределы интегрирования a,b
a = 0;
b = 1;
f = @(x) (3*x - 2)./((x + 5).*(3*x.^2 - 7*x + 8));

% Вычислим точный интеграл I_точное - это полученный результат
I_accuracy = - 17/118 * log(6/5) - 17/236 * log(2) + (79*sqrt(47)/5546)*(atan(7/sqrt(47)) - atan(1/sqrt(47))); 
fprintf("Точность: %.4f\n", I_accuracy);

I_accuracy1 = integral(f, a, b);
fprintf("Точность при помощи ф-ии integral: %.4f\n\n", I_accuracy1);

% График
x_plot = linspace(a, b, 1000);
figure;
plot(x_plot, f(x_plot), 'LineWidth', 1.5);
grid on;
title("График фуункции");
xlabel('x');
ylabel('y = f(x)');

%Задаем кол-во промежутков, шаг обучения и узлы разбиения 
n = 200;
h = (b - a) / n;
node = linspace(a, b, n+1);

% Квадратурные методы (формулы)
Left_rectangle = h*sum(f(node(1:end-1)));
fprintf("Левые прямоугольники: %.4f\n", Left_rectangle);
Right_rectangle = h*sum(f(node(2:end)));
fprintf("Правые треугольники %.4f\n", Right_rectangle);
Center_rectangle = h*sum(f((node(1:end-1) + node(2:end)) / 2));
fprintf("Центральные прямоугольники %.4f\n", Center_rectangle);
Trapezoid = (Left_rectangle + Right_rectangle) / 2;
fprintf("Метод трапеции: %.4f\n\n", Trapezoid);

%Оценка погрешностей и пересчитать для h/2, т.е. 2n = 2 * n
n2 = 2 * n;
h = (b - a) / n2;
node_2 = linspace(a, b, n2 + 1);

%Квадратурные методы в смысле 2n:
Left_rectangle_1 = h*sum(f(node_2(1:end-1)));
fprintf("Левые прямоугольники (в смысле 2n): %.4f\n", Left_rectangle_1);
Right_rectangle_1 = h*sum(f(node_2(2:end)));
fprintf("Правые треугольники (в смысле 2n): %.4f\n", Right_rectangle_1);
Center_rectangle_1 = h * sum( f( (node_2(1:end-1) + node_2(2:end)) / 2 ) );
fprintf("Центральные прямоугольники (в смысле 2n): %.4f\n", Center_rectangle_1);
Trapezoid_1 = (Left_rectangle_1 + Right_rectangle_1) / 2;
fprintf("Метод трапеции (в смысле 2n): %.4f\n\n", Trapezoid_1);

% Оценка погрешности:
R_Left_Rectangle = abs(Left_rectangle_1 - Left_rectangle);
fprintf("Погрешность Рунге левых прямоугольников: %.10f\n", R_Left_Rectangle);
R_Right_Rectangle = abs(Right_rectangle_1 - Right_rectangle);
fprintf("Погрешность Рунге правых прямоугольников: %.10f\n", R_Right_Rectangle);
R_Center_Rectangle = abs((Center_rectangle_1 - Center_rectangle)/3);
fprintf("Погрешность Рунге центральных прямоугольников: %.10f\n", R_Center_Rectangle);
R_Trapezoid = abs((Trapezoid_1 - Trapezoid)/3);
fprintf("Погрешность Рунге трапеций: %.10f\n\n", R_Trapezoid);

% Уточняющий интеграл: результат интеграла по методам + Рунге по всем метод
Clarify_L_rectangle = Left_rectangle_1 + R_Left_Rectangle;
fprintf("Уточняющий интеграл левых прямоугольников: %.10f\n", Clarify_L_rectangle);
Clarify_R_rectangle = Right_rectangle_1 + R_Right_Rectangle;
fprintf("Уточняющий интеграл правых прямоугольников: %.10f\n", Clarify_R_rectangle);
Clarify_Center_rectangle = Center_rectangle_1 + R_Center_Rectangle;
fprintf("Уточняющий интеграл центральных прямоугольников: %.10f\n", Clarify_Center_rectangle);
Clarify_Trapezoid = Trapezoid_1 + R_Trapezoid;
fprintf("Уточняющий интеграл трапеций: %.10f\n\n", Clarify_Trapezoid);

% Сравнение погрешностей: |фактическое (через integral) - I_уточняющее|
fin1 = abs(I_accuracy1 - Clarify_L_rectangle);
fprintf("Фактический итеграл для левых прямоугольников: %.10f\n", fin1);
fin2 = abs(I_accuracy1 - Clarify_R_rectangle);
fprintf("Фактический итеграл для правых прямоугольников: %.10f\n", fin2);
fin3 = abs(I_accuracy1 - Clarify_Center_rectangle);
fprintf("Фактический итеграл для центральных прямоугольников: %.20f\n", fin3);
fin4 = abs(I_accuracy1 - Clarify_Trapezoid);
fprintf("Фактический итеграл для трапеций: %.10f\n\n", fin4);
