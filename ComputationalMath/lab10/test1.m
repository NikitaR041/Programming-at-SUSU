%Решение системы нелинейных уравнений методом простой итерации
%Система
%sin(x+2) - y = 1.5 => y = sin(x+2) - 1.5
%x + cos(y-2) = 0.5 => x = -1*cos(y-2) + 0.5

y1 = ezplot('sin(x+2) - y - 1.5');
set(y1, 'Color', 'b', 'LineWidth', 2);
hold on; 
y2 = ezplot('x + cos(y-2) - 0.5');
set(y2, 'Color', 'b', 'LineWidth', 2);
grid on;

x0 = 1.0;
y0 = 1.0;

y = sin(x0 + 2) - 1.5;
x = -1*cos(y0 - 2) - 0.5;
e = 0.0001;
k = 1;
max_iter = 100;

while and(or(abs(x - x0) > e, abs(y - y0) > e), k < max_iter)
	x0 = x;
	y0 = y;
    y = sin(x0 + 2) - 1.5;
	x = -1*cos(y0 - 2) - 0.5;
	k = k + 1;
end

fprintf('Итераций: %d\n', k);
fprintf('x = %.6f\n', x);
fprintf('y = %.6f\n', y);