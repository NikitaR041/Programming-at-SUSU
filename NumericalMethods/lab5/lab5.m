f = @(x) (x.*exp(-x)./(x+2));
g = @(x) x ./ (x + 2);

% Количество итераций для Гаусса-Лаггера: n = 4
n = 4; 

% График функции y(x)
x_plot = linspace(0, 10, 500);
figure;
plot(x_plot, f(x_plot), 'b-', 'LineWidth', 1.5);
grid on;
title("График функции");
xlabel('x');
ylabel('y = f(x)');

% График функции Гаусса-Лаггера g(x)
figure;
plot(x_plot, g(x_plot), 'r-', 'LineWidth', 1.5);
grid on;
title("График функции g(x) Гаусса-Лаггера");
xlabel('x');
ylabel('Гаусса-Лаггера g(x)');

x_nodes = [0.322548, 1.745761, 4.536620, 9.395071];
coef_gauss_lag = [0.603154, 0.357419, 0.0388879, 0.000539295];

I_Gaus_Lag = sum(coef_gauss_lag .* (x_nodes ./ (x_nodes + 2)));
fprintf("Результат при помощи Гаусса-Лаггера: %.10f\n\n", I_Gaus_Lag);

% Вычислим точный интеграл I_точное при помощи встроенной функции integral
I_accuracy = integral(@(x) x.*exp(-x)./(x+2), 0, Inf, 'AbsTol', 1e-12, 'RelTol', 1e-12);
fprintf("Точное при помощи функции integral: %.10f\n\n", I_accuracy);

% Погрешности 
fprintf("Погрешность между точным и Гауссу: %.10f\n", abs(I_accuracy - I_Gaus_Lag));