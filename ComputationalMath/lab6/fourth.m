%Уравнение: x^2 - 20*sin(x)
f = @(x) x.^2 - 20*sin(x);

x1 = [-1, 1];
x2 = [2.5, 3];
r1 = fzero(f, x1);
r2 = fzero(f, x2);
fprintf('Корни уравнения:\n');
fprintf('x1 = %.6f\n', r1);
fprintf('x2 = %.6f\n', r2);
%fprintf('x3 = %.6f\n', r3);

% Построение графика
x = -6:0.01:6;
y = f(x);

figure;
plot(x, y, 'b-', 'LineWidth', 2);
hold on;
plot(x, zeros(size(x)), 'k-');
plot([r1, r2], [0, 0], 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'red');
grid on;
title('x^2 - 20·sin(x) = 0');
xlabel('x');
ylabel('f(x)');
legend('f(x)', 'Ось X', 'Корни', 'Location', 'northwest');