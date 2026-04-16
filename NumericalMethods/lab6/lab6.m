% Функция из условия
f = @(x, y) (x + y);

% Аналитически вычисленная функция 
f_accuracy = @(x) (-x - 1 + 3 .* exp(x-1)); 

% Количество узлов n = 10 с шагом h = 0.1, граница решений [1;2]
a = 1;
b = 2;
n = 10;
h = 0.1;

% Генерация значений в списке x и y
x = a:h:b;
y = zeros(size(x));
y(1) = 1;

% Проходка по методу Эйлера
for i = 1:n
    y(i+1) = y(i) + h*f(x(i), y(i));
end

fprintf('Значения х');
disp(x);
fprintf('Значения y');
disp(y);
fprintf('Значение интеграла решенная аналитическим способом %.4f\n\n', f_accuracy(2));

% График функции из вычисленных значений x и y
plot(x, y, 'b-', 'LineWidth', 1.5);
grid on;
title("График функции");
xlabel('x');
ylabel('y');

% Погрешности вычисления 
y_analytical = f_accuracy(x);
Delta = abs(y_analytical - y);
delta = Delta ./ y_analytical * 100;

fprintf('Погрешности между методом Эйлера и аналитическим решением:\n');
for i = 1:length(x)
    fprintf('x=%.1f, y=%.4f, f_accuracy=%.4f, абсолютная погрешность=%.4e, относительная погрешность=%.2f%%\n', ...
        x(i), y(i), y_analytical(i), Delta(i), delta(i));
end