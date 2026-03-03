f = @(x) x.^2 .* cos(x/4);

a = 2;
b = 3;
n = 10;

% Узлы Чебышёва
cheb = @(a,b,n) 0.5*(a+b) + 0.5*(b-a)*cos((2*(1:n)-1)/(2*n)*pi);

x_cheb = cheb(a, b, n);
y_cheb = f(x_cheb);

% Интерполяционный многочлен Лагранжа
P_cheb = lagrange(x_cheb, y_cheb);

% Интеграл от многочлена
P_int = polyint(P_cheb);
I_cheb = polyval(P_int, b) - polyval(P_int, a);

% Точное значение
F = @(x) (4*x.^2.*sin(x/4) + 32*x.*cos(x/4) - 128*sin(x/4) );

I_exact = F(b) - F(a);

% Погрешность
delta = abs(I_exact - I_cheb);

fprintf('Интеграл по узлам Чебышёва = %.10f\n', I_cheb);
fprintf('Точное значение           = %.10f\n', I_exact);
fprintf('Абсолютная погрешность    = %.2e\n\n', delta);

% График
xx = linspace(a, b, 400);

figure;
plot(xx, f(xx), 'k', 'LineWidth', 2); hold on;
plot(xx, polyval(P_cheb, xx), 'm--', 'LineWidth', 2);
plot(x_cheb, y_cheb, 'mo', 'MarkerFaceColor','m');
grid on;
legend('f(x)', 'P_n(x) (Чебышёв)', 'Узлы Чебышёва');
title('Интегрирование по узлам Чебышёва');
xlabel('x'); ylabel('y');
