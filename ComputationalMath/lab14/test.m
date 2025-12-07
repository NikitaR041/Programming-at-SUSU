%xg = linspace(-3, 3, 400);
%f = @(x) x.^4 - 4*x.^2 + 2*x + 3;
%plot(xg, f(xg), 'b','LineWidth',2); grid on;
%title('График функции для снятия точек');
%xlabel('x'); ylabel('y');

% === Табличные данные (вставь свои точки!!!) ===
x = [-3, -3, -2, 0, 1, 2, 3];
y = [12, 9, 2, 1, 2, 10, 13];

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

% --- Вектор D ---
S_y   = sum(y);
S_xy  = sum(x .* y);
S_x2y = sum((x.^2) .* y);

D = [S_x2y; S_xy; S_y];

% --- Решение системы ---
X = T \ D;
a2 = X(1);
a1 = X(2);
a0 = X(3);

% --- Стандартная форма ---
fprintf('\n=== Классический вид параболы ===\n');
fprintf("f(x) = %.4f*x^2 + %.4f*x + %.4f\n", a2, a1, a0);

% --- Новый вид параболы ---
A = a2;                   
x0 = -a1 / (2*a2);        
B = A*x0^2 + a1*x0 + a0;  

fprintf('\n=== Новый (вершинный) вид ===\n');
fprintf("f(x) = %.4f * (x - %.4f)^2 + %.4f\n", A, x0, B);

% --- Значения модели ---
f_x = a2*x.^2 + a1*x + a0;

% --- Ошибки ---
err_sq  = abs(sum((y - f_x)));       % сумма квадратов ошибок

fprintf('\n=== Ошибки ===\n');
fprintf("|SUM( (y_i - f(x_i))|) = %.6f\n\n", err_sq);

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
