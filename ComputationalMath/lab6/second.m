%Уравнение: x^4 - 18*x^2 + 6 = 0
%Пересекается в двух точках

lambda = [1, 0, -18 , 0, 6];

x_roots = roots(lambda);

% Выводим только действительные корни
fprintf('Действительные корни уравнения:\n');
for i = 1:length(x_roots)
    if abs(imag(x_roots(i))) < 1e-4
        disp(real(x_roots(i)));
        %fprintf('x = %.6f\n', real(x_roots(i)));
    end
end

% Строим график
x = -5:0.01:5;
y = x.^4 - 18*x.^2 + 6;

figure;
plot(x, y, 'b-', 'LineWidth', 2);
hold on;
plot(x, zeros(size(x)), 'k-', 'LineWidth', 1);
grid on;
title('x^4 - 18x^2 + 6 = 0');
xlabel('x');
ylabel('f(x)');

% Отмечаем действительные корни
plot(x_roots, zeros(size(x_roots)), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'red');
legend('f(x)', 'Ось X', 'Корни', 'Location', 'northwest');