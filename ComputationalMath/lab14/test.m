%xg = linspace(-3, 3, 400);
%f = @(x) x.^4 - 4*x.^2 + 2*x + 3;
%plot(xg, f(xg), 'b','LineWidth',2); grid on;
%title('График функции для снятия точек');
%xlabel('x'); ylabel('y');

% === Табличные данные (вставь свои точки!!!) ===
x = [-2.8, -2.2, 0, -1.0, -1.5, -0.5, 0.2, 1.3 2.4, 2.9];
y = [30.7, 4.2, 0, 4.0, -3.94, 1.0, 3.2, 1.7, 20.0, 45.4];

n = 4;                % степень многочлена
N = length(x);

% === Матрица Вандермонда V ===
V = zeros(N, n+1);
for i = 1:N
    for j = 1:n+1
        V(i,j) = x(i)^(n-j+1);
    end
end

% === Решение системы нормальных уравнений ===
a = (V' * V) \ (V' * y');

disp('Коэффициенты МНК:');
disp(a');
print_poly(a');

% === Сравнение с polyfit ===
a_pf = polyfit(x, y, n)';
disp('Коэффициенты polyfit():');
disp(a_pf);

% === Построение многочлена ===
p = @(xx) polyval(a', xx);

% === Оценка точности ===
res = y' - p(x);
sko = norm(res) / sqrt(N - 1);
[max_abs, idx] = max(abs(res));

fprintf("\nСреднеквадратичное отклонение: %.6f\n", sko);
fprintf("Максимальное отклонение: %.6f в точке x = %.3f\n\n", ...
        max_abs, x(idx));

% === График ===
xx = linspace(min(x), max(x), 500);

plot(x, y, 'ko', 'MarkerFaceColor','k'); hold on;
plot(xx, p(xx), 'r-', 'LineWidth',2);
plot(x(idx), y(idx), 'bp', 'MarkerSize', 14, 'MarkerFaceColor','b');
grid on;

title('Метод наименьших квадратов');
legend('Табличные точки', 'Многочлен МНК', 'Макс. отклонение');
xlabel('x'); ylabel('y');