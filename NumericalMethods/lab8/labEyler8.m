% Параметры
h = 0.01;            % Шаг (возьмем поменьше для точности)
t = 0:h:1.6;        % Вектор времени
n = length(t);      % Количество шагов

% Резервируем место под решения
x_euler = zeros(1, n);
y_euler = zeros(1, n);

% Начальные условия
x_euler(1) = 2;
y_euler(1) = 0.6;

% Цикл метода Эйлера
for i = 1:(n-1)
    % Считаем производные (правые части системы)
    dxdt = x_euler(i)^2 - y_euler(i)^2;
    dydt = 2 * x_euler(i) * y_euler(i);
    
    % Делаем шаг по формуле: новое = старое + шаг * производная
    x_euler(i+1) = x_euler(i) + h * dxdt;
    y_euler(i+1) = y_euler(i) + h * dydt;
end

% Рисуем результат
plot(t, x_euler, 'g--', 'DisplayName', 'Эйлер x(t)');
hold on;
plot(t, y_euler, 'm--', 'DisplayName', 'Эйлер y(t)');

for i = 1:length(x_euler)
    fprintf('x=%.1f, y=%.4f\n', ...
        x_euler(i), y_euler(i));
end