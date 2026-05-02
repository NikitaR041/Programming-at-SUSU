% Функции из условия
f = @(x, y) ((1 + sin(x+y)).^2 - x);
g = @(x, y) (30.*x.*(cos(7.*x)).^5 - y);

% Функция точного значения для 2 уравнения
Q = @(t) 30 .* t .* (cos(7.*t)).^5; 
f_accuracy = @(x) exp(-x) .* integral(@(t) exp(t) .* Q(t), 0, x);
 
% Начальные условия
f_a = 0;
f_b = 10;

g_a = 0;
g_b = 2;

% количество узлов для функций f и g и шаг
f_n = 30;
g_n = 100; %g_n > 50

f_h = (f_b - f_a) / f_n; 
g_h = (g_b - g_a) / g_n;

% Генерация значений в списке x и y для функции f
f_x = f_a:f_h:f_b;
f_y = zeros(size(f_x));
f_y(1) = -1;

% Генерация значений в списке x и y для функции g
g_x = g_a:g_h:g_b;
g_y = zeros(size(g_x));
g_y(1) = 0;

% Циклы метода Рунге-Кутты 4-го порядка для функций f и g
for i = 1:f_n
    k1 = f(f_x(i), f_y(i));
    k2 = f(f_x(i) + f_h/2, f_y(i) + f_h/2 * k1);
    k3 = f(f_x(i) + f_h/2, f_y(i) + f_h/2 * k2);
    k4 = f(f_x(i) + f_h, f_y(i) + f_h * k3);
    
    f_y(i+1) = f_y(i) + (f_h/6) * (k1 + 2*k2 + 2*k3 + k4);
end

for i = 1:g_n
    k1 = g(g_x(i), g_y(i));
    k2 = g(g_x(i) + g_h/2, g_y(i) + g_h/2 * k1);
    k3 = g(g_x(i) + g_h/2, g_y(i) + g_h/2 * k2);
    k4 = g(g_x(i) + g_h, g_y(i) + g_h * k3);
    
    g_y(i+1) = g_y(i) + (g_h/6) * (k1 + 2*k2 + 2*k3 + k4);
end

% Графики для функций f и g
figure;
plot(f_x, f_y, 'b-', 'LineWidth', 1.5);
grid on;
title('y'' = (1 + sin(x+y))^2 - x');
xlabel('x'); ylabel('y');

figure;
plot(g_x, g_y, 'b-', 'LineWidth', 1.5);
grid on;
title('y'' = 30x\cdotcos^5(7x) - y');
xlabel('x'); ylabel('y');

% Считаем точные значения функции g для каждой точки х
y_analytical = arrayfun(f_accuracy, g_x);
Delta = abs(y_analytical - g_y);

fprintf('Погрешности между методом Рунге-Кутты 4 порядка и аналитическим решением:\n');
for i = 1:length(g_x)
    fprintf('x=%.4f, y=%.4f, f_accuracy=%.4f, абсолютная погрешность=%.4e\n', ...
        g_x(i), g_y(i), y_analytical(i), Delta(i));
end

disp(' ');
fprintf('Решением методом Рунге-Кутты 4 порядка для функции y'' = (1 + sin(x+y))^2 - x\n');
fprintf('Значения f_х и f_y \n');
disp([f_x' f_y']);

fprintf('Решением методом Рунге-Кутты 4 порядка для функции y'' = 30x * cos^5(7x) - y\n');
fprintf('Значения g_х и g_y \n');
disp([g_x' g_y']);