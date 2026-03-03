%Задаем диапазон
x = -5:0.1:5;
y = (pi.^x).*(2*x+1).*sin(3*x);

figure;
plot(x,y,'r-', 'LineWidth',1.5);
xline(0, 'k-');
yline(0, 'k-');

title('График функции y = pi^x*(3*x+1)*sin(2*x)', 'FontSize', 14);

xlabel('x', 'LineWidth', 12);
ylabel('y', 'LineWidth', 12);

grid on;
set(gca, 'GridLineStyle', '--', 'GridAlpha', 0.7);