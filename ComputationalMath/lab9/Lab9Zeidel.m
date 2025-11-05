function [x, iter] = Lab9Zeidel(A, B, eps)
% SEIDEL_METHOD — Решение системы Ax = b методом Зейделя
% Вход:
%   A   — матрица коэффициентов
%   b   — вектор правых частей
%   eps — требуемая точность
% Выход:
%   x   — найденный вектор решений
%   iter — количество итераций

n = length(B);
x = zeros(n, 1);
iter = 0;

while true
    iter = iter + 1;
    x_old = x;

    for i = 1:n
        s1 = A(i,1:i-1) * x(1:i-1);
        s2 = A(i,i+1:end) * x_old(i+1:end);
        x(i) = (B(i) - s1 - s2) / A(i,i);
    end

    % проверка на точность
    if norm(x - x_old, inf) < eps
        break;
    end
end
end