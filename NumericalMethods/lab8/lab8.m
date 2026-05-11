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
y_list = [0.3 0.5 0.6 0.8 1.0 1.2 1.4]; x0 = 2;

figure; hold on; grid on;
for y0_elem = y_list
    [~, X_loop] = ode45(@f, t, [x0 y0_elem]);
    plot(X_loop(:,1), X_loop(:,2), 'Color', [205 145 158]/255); 
end


