f = @(x) x.^2 .* cos(x/4);

a = 2;
b = 3;

n = 10;
x = linspace(a, b, n);
y = f(x);

%интерполяционный многочлен
P = lagrange(x, y);

%интеграл от многочлена
P_int = polyint(P);
I_lagr = polyval(P_int, b) - polyval(P_int, a);

%Результат значение
F = @(x) (4*x.^2.*sin(x/4) + 32*x.*cos(x/4) - 128*sin(x/4));
I_exact = F(b) - F(a);

%погрешность
delta = abs(I_exact - I_lagr);

fprintf('Интеграл методом Лагранжа = %.10f\n', I_lagr);
fprintf('Точное значение           = %.10f\n', I_exact);
fprintf('Абсолютная погрешность    = %.2e\n\n', delta);

poly = linspace(a, b, 400);
figure;
plot(poly, f(poly), 'k', 'LineWidth', 2); hold on;
plot(poly, polyval(P, poly), 'r--', 'LineWidth', 2);
plot(x, y, 'ro', 'MarkerFaceColor','r');
grid on;
legend('f(x)', 'P_n(x)', 'Узлы');
title('Интегрирование методом Лагранжа');
xlabel('x'); ylabel('y');
