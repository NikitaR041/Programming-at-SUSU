a = 0;
b = 10;
f = @(x) (x.*exp(-x)./(x+2));

% Вычислим точный интеграл I_точное при помощи встроенной функции integral
I_accuracy1 = integral(f, a, b);
fprintf("Точное при помощи функции integral: %.10f\n\n", I_accuracy1);

% График
x_plot = linspace(a, b, 1000);
figure;
plot(x_plot, f(x_plot), 'LineWidth', 1.5);
grid on;
title("График фуункции");
xlabel('x');
ylabel('y = f(x)');

% Узлы Гауса при n = 7
nodes_Gauss = [-0.9491079123 -0.7415311856 -0.4058451514 0 0.4058451514 0.7415311856 0.9491079123];

% Коэффициенты Гаусса n = 7
coef_Gauss = [0.1294849662 0.2797053915 0.3818300505 0.4179591837 0.3818300505 0.2797053915 0.1294849662];

% Перерасчет на исходном отрезке [0;30]
z = (b - a) ./ 2 .* nodes_Gauss + (a + b) ./ 2;

% Результат по Гауссу
result_Gauss = ((b - a) ./ 2) .* sum(coef_Gauss .* f(z));
fprintf("Результат по Гауссу: %.10f\n", result_Gauss);

% Погрешности 
fprintf("Погрешность между точным и Гауссу: %.10f\n", abs(I_accuracy1 - result_Gauss));