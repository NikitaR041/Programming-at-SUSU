% === Табличные данные (вставь свои точки!!!) ===
x = [-5,-4, -3, -2, 0, 1, 2, 3, 4, 5];
y = [13, 12, 9, 5, 4, 5, 6, 11, 14, 17];

% --- Суммы ---
S1 = sum(x);
S2 = sum(x.^2);
S3 = sum(x.^3);
S4 = sum(x.^4);
n  = length(x);

% --- Матрица T ---
T = [S4, S3, S2;
     S3, S2, S1;
     S2, S1, n];

disp('Матрица T:');
disp(T);

% --- Вектор D ---
S_y   = sum(y);
S_xy  = sum(x .* y);
S_x2y = sum((x.^2) .* y);

D = [S_x2y; S_xy; S_y];

% --- Решение системы ---
X = T \ D;
disp('Коэффициетны X = T/D:');
disp(X);

a2 = X(1);
a1 = X(2);
a0 = X(3);

% --- Стандартная форма ---
fprintf('\n=== Классический вид параболы ===\n');
fprintf("f(x) = %.4f*x^2 + %.4f*x + %.4f\n", a2, a1, a0);

% --- Значения модели ---
f_x = a2*x.^2 + a1*x + a0;

% --- Ошибки ---
err  = abs(sum((y - f_x)));       % сумма квадратов ошибок

fprintf('\n=== Ошибки ===\n');
fprintf("err = %.6f\n\n", err);

res = y - f_x;
SSE  = sum(res.^2);                  % сумма квадратов ошибок
RMSE = sqrt(mean(res.^2));           % среднеквадратичная ошибка
fprintf('Сумма квадратов ошибок (SSE) = %.6f\n', SSE);
fprintf('Среднеквадратичная ошибка (RMSE) = %.6f\n', RMSE);

% --- График ---
figure;
plot(x, y, 'bo', 'MarkerSize', 8, 'LineWidth', 2); hold on;

x_plot = linspace(min(x)-1, max(x)+1, 200);
y_plot = a2*x_plot.^2 + a1*x_plot + a0;

plot(x_plot, y_plot, 'r-', 'LineWidth', 2);
grid on;

title('Аппроксимация параболой');
xlabel('x');
ylabel('y');
legend('Исходные точки', 'Парабола', 'Location', 'best');