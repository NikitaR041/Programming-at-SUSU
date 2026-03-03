%Интерполирование функции по равномерным узлам и Чебышева
%f(x) = exp(2*x+1) - sin(2*x+5) - 15
%интервал [-4; 4]

%Интервалы и кол-во узлов
a = -2;
b = 10;
node1 = 5;
node2 = 12;

%Cоздаем искусственные узлы и прогнём по функции
x1 = linspace(a,b, 100);
f = @(x) (exp(2*x+1) - sin(2*x+5) - 15);
y1 = f(x1);%таблица значений

% --- Равномерные узлы ---
x_node1 = linspace(a,b,node1);
y_node1 = f(x_node1);

x_node2 = linspace(a,b,node2);
y_node2 = f(x_node2);

% Коэффициенты Лангранжа
langrande_node1 = lagrange(x_node1, y_node1);
langrande_node2 = lagrange(x_node2, y_node2);

poly_node1 = polyval(langrande_node1, x1);
poly_node2 = polyval(langrande_node2, x1);

err_node1 = max(abs(poly_node1 - y1));
err_node2 = max(abs(poly_node2 - y1));

% --- Чебышевские узлы ---
cheb = @(a,b,m) 0.5*(a+b) + 0.5*(b-a)*cos(((2*(1:m)-1)/(2*m))*pi);

x_node1_m_cheb = cheb(a,b,node1);
y_node1_m_cheb = f(x_node1_m_cheb);

x_node2_b_cheb = cheb(a,b,node2);
y_node2_b_cheb = f(x_node2_b_cheb);

langrande_cheb_node1 = lagrange(x_node1_m_cheb, y_node1_m_cheb(:));
langrande_cheb_node2 = lagrange(x_node2_b_cheb,   y_node2_b_cheb(:));

poly_cheb_node1 = polyval(langrande_cheb_node1, x1);
poly_cheb_node2 = polyval(langrande_cheb_node2,   x1);

err_cheb_node1 = max(abs(poly_cheb_node1 - y1));
err_cheb_node2 = max(abs(poly_cheb_node2 - y1));

fprintf('\n==================== РЕЗУЛЬТАТЫ ====================\n\n');

fprintf('\n=== Многочлены Лагранжа ===\n\n');

fprintf('--- Равномерные узлы (m = %d) ---\n', node1);
print_poly(langrande_node1); fprintf('\n');
fprintf('--- Равномерные узлы (m = %d) ---\n', node2);
print_poly(langrande_node2); fprintf('\n');

fprintf('--- Чебышевские узлы (m = %d) ---\n', node1);
print_poly(langrande_cheb_node1); fprintf('\n');
fprintf('--- Чебышевские узлы (m = %d) ---\n', node2);
print_poly(langrande_cheb_node2); fprintf('\n');

fprintf('Число узлов (малое) m = %d\n', node1);
fprintf('  Равномерные: max error = %.6e\n', err_node1);
fprintf('  Чебышёвские: max error = %.6e\n\n', err_cheb_node1);

fprintf('Число узлов (большое) m = %d\n', node2);
fprintf('  Равномерные: max error = %.6e\n', err_node2);
fprintf('  Чебышёвские: max error = %.6e\n\n', err_cheb_node2);

% Печать таблицы в стиле твоей картинки
fprintf('Таблица погрешностей (макс. отклонение на сетке):\n');
fprintf('-------------------------------------------------\n');
fprintf(' m | Равномерные узлы | Чебышёвские узлы\n');
fprintf('-------------------------------------------------\n');
fprintf('%2d |   %.6e   |   %.6e\n', node1, err_node1, err_cheb_node1);
fprintf('%2d |   %.6e   |   %.6e\n', node2,   err_node2,   err_cheb_node2);
fprintf('-------------------------------------------------\n\n');

% ==== Графики для node1 ====
figure;
subplot(2,2,1);
plot(x1, y1, 'k', 'LineWidth', 2); hold on;
plot(x1, poly_node1, 'r--', 'LineWidth', 1.5);
plot(x_node1, y_node1, 'ro', 'MarkerFaceColor', 'r');
title('Равномерные узлы, n = 5');
grid on;

subplot(2,2,2);
plot(x1, poly_node1 - y1, 'b', 'LineWidth', 1.5);
title('Ошибка для равномерных узлов, n = 5');
grid on;

subplot(2,2,3);
plot(x1, y1, 'k', 'LineWidth', 2); hold on;
plot(x1, poly_cheb_node1, 'm--', 'LineWidth', 1.5);
plot(x_node1_m_cheb, y_node1_m_cheb, 'mo', 'MarkerFaceColor', 'm');
title('Чебышевские узлы, n = 5');
grid on;

subplot(2,2,4);
plot(x1, poly_cheb_node1 - y1, 'g', 'LineWidth', 1.5);
title('Ошибка для узлов Чебышёва, n = 5');
grid on;

% ==== Графики для node2 ====
figure;
subplot(2,2,1);
plot(x1, y1, 'k', 'LineWidth', 2); hold on;
plot(x1, poly_node2, 'r--', 'LineWidth', 1.5);
plot(x_node2, y_node2, 'ro', 'MarkerFaceColor', 'r');
title('Равномерные узлы, n = 12');
grid on;

subplot(2,2,2);
plot(x1, poly_node2 - y1, 'b', 'LineWidth', 1.5);
title('Ошибка для равномерных узлов, n = 12');
grid on;

subplot(2,2,3);
plot(x1, y1, 'k', 'LineWidth', 2); hold on;
plot(x1, poly_cheb_node2, 'm--', 'LineWidth', 1.5);
plot(x_node2_b_cheb, y_node2_b_cheb, 'mo', 'MarkerFaceColor', 'm');
title('Чебышевские узлы, n = 12');
grid on;

subplot(2,2,4);
plot(x1, poly_cheb_node2 - y1, 'g', 'LineWidth', 1.5);
title('Ошибка для узлов Чебышёва, n = 12');
grid on;
