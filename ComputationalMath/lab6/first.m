% Уравнение arctg(x-1) + 3x - 2 = 0
% 1. Построение графика для визуального отделения корней
x = -1 : 0.01 : 2;  % Расширенный диапазон для лучшего обзора
y = atan(x-1) + 3*x - 2;

figure;
plot(x, y, 'b-', 'LineWidth', 2);
hold on;

% Ось OX
plot(x, zeros(size(x)), 'k-', 'LineWidth', 1.5);

% 2. Поиск корня
f = @(x) atan(x-1) + 3*x - 2;
result = fzero(f, [0, 1]);

% 3. Отметка корня на графике
plot(result, 0, 'ro', 'MarkerSize', 10, ...
     'MarkerFaceColor', 'red', 'MarkerEdgeColor', 'black');

grid on;

title('График функции: y = arctg(x-1) + 3x - 2', ...
      'FontSize', 14, 'FontWeight', 'bold');
xlabel('x', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('y', 'FontSize', 12, 'FontWeight', 'bold');

% 5. Добавление информативной легенды и аннотаций
legend('y = arctg(x-1) + 3x - 2', 'Ось OX (y=0)', ...
       'Точка пересечения с осью OX', ...
       'Location', 'northwest');

% Аннотация с координатами корня
annotation('textbox', [0.15, 0.15, 0.2, 0.1], 'String', ...
           sprintf('Корень:\nx = %.6f', result), ...
           'FontSize', 11, 'BackgroundColor', 'white', ...
           'EdgeColor', 'black');

hold off;

% 6. Вывод результатов
fprintf('РЕЗУЛЬТАТЫ АНАЛИЗА:\n');
fprintf('===================\n');
fprintf('Уравнение: arctg(x-1) + 3x - 2 = 0\n');
fprintf('Найденный корень: x = %.6f\n', result);
fprintf('Значение функции в корне: f(%.6f) = %.2e\n', result, f(result));
fprintf('Визуальный анализ графика подтверждает наличие одного корня\n');
fprintf('на интервале [0, 1], где функция меняет знак.\n');