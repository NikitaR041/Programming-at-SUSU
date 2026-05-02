%Метод функции - система из условия
function F = f(t, X)
    F = [X(1)^2 - X(2)^2; 2*X(1)*X(2)];
end

%Начальные условия
x0 = [2 0.6];
t = [0 1.6];

[t, X] = ode45(@f, t, x0);

% График зависимостей x(t) и y(t)
figure; 
plot(t, X(:,1), 'g-', 'LineWidth', 2); hold on; 
plot(t, X(:,2), 'b-', 'LineWidth', 2); 
grid on; xlabel('t'); ylabel('x(t), y(t)'); 
legend('x(t)', 'y(t)'); title('Решение системы: x(t) и y(t)');

%Построение одной фазовой траектории
figure; 
plot(X(:,1), X(:,2), 'r', 'LineWidth', 2); 
grid on; xlabel('x'); ylabel('y'); 
title('Фазовая траектория (x0=2, y0=0.6)');

%Семейство траекторий
% Условие 1: x0 от -2 до 2, y0 = 0
% Условие 2: x0 = 2, y0 от -1.5 до 1

x_list = [-2 -1.5 -1 -0.5 0 0.5 1 1.5 2]; y0 = 0;
y_list = [-1.5 -1 -0.5 0 0.5 1]; x0 = 2;

figure; hold on; grid on;
for x0_elem = x_list
    [~, X_loop] = ode45(@f, t, [x0_elem y0]); % Короткое время 0.4
    plot(X_loop(:,1), X_loop(:,2), 'Color', [47 79 79]/255); 
end

for y0_elem = y_list
    [~, X_loop] = ode45(@f, t, [x0 y0_elem]); % Короткое время 0.4
    plot(X_loop(:,1), X_loop(:,2), 'Color', [205 145 158]/255); 
end


