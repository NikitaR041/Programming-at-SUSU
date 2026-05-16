%Начальные условия
a = 0.4; b = 3;
% Кол-во узлов, шаг, узлы
n = 100;
h = (b - a) / n;
x = linspace(a, b, n+1);
%x = a:h:b;

% Коэффициенты системы (A*y_{i-1} + C*y_i + B*y_{i+1} = F)
A = zeros(1, n+1); 
B = zeros(1, n+1); 
C = zeros(1, n+1); 
F = zeros(1, n+1);

for i = 2:n
    xi = x(i);
    A(i) = 1/h^2 + 0.5*xi/(2*h);
    C(i) = 1 - 2/h^2;
    B(i) = 1/h^2 - 0.5*xi/(2*h);
    F(i) = 2;
end

% Коэффициенты у краевых условий
k1 = 2 + 1/h; mu1 = -1/h; phi1 = 4.2742;
k2 = 1;       mu2 = 0;    phi2 = 2;

% Метод прогонки
alpha = zeros(1, n+1);
beta = zeros(1, n+1);

alpha(1) = -mu1 / k1;
beta(1) = phi1 / k1;

for i = 2:n
    denom = A(i) * alpha(i-1) + C(i);
    alpha(i) = -B(i) / denom;
    beta(i) = (F(i) - A(i) * beta(i-1)) / denom;
end

% Обратный ход 
y = zeros(1, n+1);
y(n+1) = (phi2 - mu2 * beta(n)) / (k2 + mu2 * alpha(n));

for i = n:-1:1
    y(i) = alpha(i) * y(i+1) + beta(i);
end

fprintf('Таблица значений для пар (x, y)\n'); 
for i = 1:n+1 
fprintf('%4d %10.4f %14.6f\n', i, x(i), y(i)); 
end 

plot(x, y, 'b-o', 'LineWidth', 1.5, 'MarkerSize', 2);
grid on; xlabel('x'); ylabel('y');
title('Решение краевой задачи методом прогонки');