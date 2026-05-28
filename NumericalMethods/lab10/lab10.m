% Начальные условия
a = 0.4; b = 3;
yb = 2; c = 4.2742;

F = @(alpha) F_alpha(alpha, c, a, b, yb);

alpha0 = 1;
alph_o = fzero(F, alpha0);
fprintf('alpha = y(%.1f)  = %.6f\n', a, alph_o);
fprintf('y''(%.1f)        = %.6f\n', a, 2*alph_o - c);

% Задача Коши с найденным начальным условием
xsp = [a b];
z0  = [alph_o; 2*alph_o - c];
[x, z] = ode45(@syst, xsp, z0);
y = z(:,1);

fprintf('Проверка левого:  2*y(a)-y''(a) = %.6f  \n', 2*z(1,1) - z(1,2), c);
fprintf('Проверка правого: y(b) = %.6f \n', z(end,1), yb);

% График решения
figure;
plot(x, y, 'b-', 'LineWidth', 2);
hold on;
plot(b, yb, 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
grid on;
title('Метод пристрелки');
xlabel('x'); ylabel('y(x)');
legend('Решение y(x)', 'y(3) = 2', 'Location', 'best');

function dz = syst(x, z)
    dz = zeros(2,1);
    dz(1) = z(2);           
    dz(2) = 2 + 0.5*x*z(2) - z(1);      
end

function res = F_alpha(alph, c, a, b, yb)
    xsp = [a b];
    z0  = [alph; 2*alph - c];           
    [~, z] = ode45(@syst, xsp, z0);
    res = z(end,1) - yb;                
end
