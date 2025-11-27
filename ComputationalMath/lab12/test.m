%Интерполирование функции по равномерным узлам
%f(x) = 2*x^2 - cos(5x+3)
%интервал [-2; 10]

%Применим функцию для вычисления сразу двух узлов
function [A, err, x1, y1, y3, V] = interp_vander(f, a, b, nodes, x2, y2)
    x1 = linspace(a, b, nodes);
    y1 = f(x1');
    V = vander(x1); %Вадермонд
    A = V \ y1;       % коэффициенты многочлена
    y3 = polyval(A, x2);
    err = max(abs(y3 - y2));
end

%Интервалы и кол-во узлов
a = -2;
b = 10;
node1 = 5;
node2 = 12;

%Cоздаем искусственные узлы и прогнём по функции
f = @(x) (2*x.^2 - cos(5*x+3));
x2 = linspace(a, b, 100);%мелкая сетка для графика
y2 = f(x2);%вектор значений функции на этой сетке

% === Вычисление для малого числа узлов ===
[A1, err1, x_node1, y_node1, y1_node1, V1] = interp_vander(f, a, b, node1, x2, y2);
% === Вычисление для большого числа узлов ===
[A2, err2, x_node2, y_node2, y2_node2, V2] = interp_vander(f, a, b, node2, x2, y2);

fprintf("\n=== Малое кол-во узлов (%d) ===\n", node1);
disp('y1 = ');
%disp(y1_node1);
disp('V1 = ');
disp(V1);
disp('A1 = ');
disp(A1);
fprintf('Полиниом P1 = ');
print_poly(A1');
fprintf('Максимальное отклонение = %.4f\n', err1);

fprintf("\n=== Большое кол-во узлов (%d) ===\n", node2);
disp('y2 = ');
%disp(y2_node2);
disp('V2 = ');
disp(V2);
disp('A2 = ');
disp(A2);
fprintf('Полиниом P2 = ');
print_poly(A1');
fprintf('Максимальное отклонение = %.4f\n', err2);
% === Графики ===
figure;
plot(x2, y2, 'b', 'LineWidth', 2); hold on;
plot(x2, y1_node1, 'r--', 'LineWidth', 2);
plot(x2, y2_node2, 'g-.', 'LineWidth', 2);
plot(x_node1, y_node1, 'ro', 'MarkerFaceColor', 'r');
plot(x_node2, y_node2, 'go', 'MarkerFaceColor', 'g');
grid on;
legend('f(x)', 'P small', 'P big', 'Узлы small', 'Узлы big');
title('Интерполяция — функция и многочлены');

figure;
plot(x2, y1_node1 - y2, 'm', 'LineWidth', 2); hold on;
plot(x2, y2_node2 - y2, 'k', 'LineWidth', 2);
yline(0, 'k--');
grid on;
legend('Ошибка small', 'Ошибка big');
title('Ошибка интерполяции');
xlabel('x'); ylabel('Ошибка');

