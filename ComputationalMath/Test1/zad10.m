f = @(x) x + 3*log10(x) - 2;

% Параметры
a = 0.1;
b = 5;
epsilon = 1e-6;
max_iter = 100;

% Проверка условия
if f(a) * f(b) > 0
    error('Функция имеет одинаковый знак на концах интервала');
end

% Метод дихотомии
for iter = 1:max_iter
    c = (a + b) / 2;
    
    if abs(f(c)) < epsilon || (b - a) < epsilon
        break;
    end
    
    if f(a) * f(c) < 0
        b = c;
    else
        a = c;
    end
end

fprintf('Корень: x = %.8f\n', c);
fprintf('f(x) = %.2e\n', f(c));
fprintf('Итераций: %d\n', iter);