%Уравнение: (x-2)^2*2^x = 1

f = @(x) (x-2).^2 .* 2.^x - 1;

%Интервалы для каждой точки
x1 = [-6.5, -5.5];
x2 = [1, 1.5];
x3 = [2, 2.5];
r1 = fzero(f, x1);
r2 = fzero(f, x2);
r3 = fzero(f, x3);
disp(r1);
disp(r2);
disp(r3);

% Строим график на широком интервале
x = -5:0.1:5;
y = f(x);

figure;
plot(x, y, 'b-', 'LineWidth', 2);
hold on;
plot(x, zeros(size(x)), 'k-', 'LineWidth', 1); % Ось X
grid on;
title('График функции: (x-2)^2 ⋅ 2^x - 1 = 0', 'FontSize', 14);
xlabel('x', 'FontSize', 12);
ylabel('f(x)', 'FontSize', 12);

% Отмечаем действительные корни
plot(real_roots, zeros(size(real_roots)), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'red');
legend('f(x)', 'Ось X', 'Корни', 'Location', 'northwest');