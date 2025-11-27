%Интерполирование функции по равномерным узлам
%f(x) = exp(2*x+1) - sin(2*x+5) - 15
%интервал [-4; 4]

%Интервалы и кол-во узлов
a = -4;
b = 4;
node = 5; 
%Cоздаем искусственные узлы и прогнём по функции
x1 = linspace(a,b, node+1);
f = @(x) (exp(2*x+1) - sin(2*x+5) - 15);
y1 = f(x1');%таблица значений

%Создание сетки
x2 = linspace(a, b, 100);%мелкая сетка для графика
y2 = f(x2);%вектор значений функции на этой сетке
L = lagrange(x1, y1);

y3= polyval(L,x2);%вектор значений многочлена на этой сетке
err_small = max(abs(y3 - y2));%максимальное отклонение многочлена от функции

disp('y1 = ');
disp(y1);

disp('Коэффициенты Лангранжа = ');
disp(L');

fprintf('Максимальное отклонение = %.4f\n', err_small);
fprintf('Полиниом при помощи Лангражна P = ');
print_poly(L');

% === Графики ===
figure(1);
plot(x2, y2, 'b', 'LineWidth', 2); hold on;
plot(x2, y3, 'r--', 'LineWidth', 2);
plot(x1, y1, 'ko', 'MarkerFaceColor','k');
grid on;
title('Интерполяция многочленом Лагранжа');
legend('f(x)', 'L_n(x)', 'Узлы');
xlabel('x');

figure(2);
plot(x2, y3 - y2, 'm', 'LineWidth', 2); hold on;
yline(0, 'k--');
grid on;
title('Ошибка интерполяции f(x) - L_n(x)');
xlabel('x');
ylabel('Ошибка');