function [x, iter] = Lab9Jacobi(A, B, eps)
% JACOBI_METHOD — Решение системы Ax = b методом Якоби
% Вход:
%   A   — матрица коэффициентов
%   B   — вектор правых частей
%   eps — требуемая точность
% Выход:
%   x   — найденный вектор решений
%   iter — количество итераций
n = length(B);
x = zeros(n, 1);      % начальное приближение (x0 = 0)
x_new = x;
iter = 0;

while true
    iter = iter + 1;
    for i = 1:n
        s = 0;
        for j = 1:n
            if j ~= i
                s = s + A(i,j) * x(j);
            end
        end
        x_new(i) = (B(i) - s) / A(i,i);
    end

    % проверка на точность
    if norm(x_new - x, inf) < eps
        break;
    end

    x = x_new;
end
end