% main_solver.m
% Решение СЛАУ методами Якоби и Зейделя с точностью 0.0001

clc; clear; format long;

% Матрица A и вектор b
A = [ 3.910  0.129  0.283  0.107;
      0.217  4.691  0.279  0.237;
      0.201  0.372  2.987  0.421;
      0.531  0.196  0.236  5.032 ];

b = [0.395; 0.432; 0.127; 0.458];

eps = 1e-4;

% --- Метод Якоби ---
[x_jacobi, iter_j] = Lab9Jacobi(A, b, eps);

% --- Метод Зейделя ---
[x_seidel, iter_s] = Lab9Zeidel(A, b, eps);

% --- Вывод результатов ---
fprintf('Решение системы методами Якоби и Зейделя:\n\n');

fprintf('Метод Якоби:\n');
disp(x_jacobi);
fprintf('Количество итераций: %d\n\n', iter_j);

fprintf('Метод Зейделя:\n');
disp(x_seidel);
fprintf('Количество итераций: %d\n\n', iter_s);

% --- Метод Гаусса (точное решение встроенной функцией) ---
x_gauss = A \ b;
fprintf('Метод Гаусса (точное решение):\n');
disp(x_gauss);

% --- Проверка точности (погрешности) ---
err_jacobi = norm(x_gauss - x_jacobi, inf);
err_seidel = norm(x_gauss - x_seidel, inf);

fprintf('\nПогрешность метода Якоби относительно точного решения: %.6e\n', err_jacobi);
fprintf('Погрешность метода Зейделя относительно точного решения: %.6e\n\n', err_seidel);

% --- Сравнение ---
if iter_j > iter_s
    fprintf('Метод Зейделя сошёлся быстрее (%d < %d итераций)\n', iter_s, iter_j);
elseif iter_j < iter_s
    fprintf('Метод Якоби оказался быстрее (%d < %d итераций)\n', iter_j, iter_s);
else
    fprintf('Оба метода сошлись за одинаковое количество итераций (%d)\n', iter_j);
end
