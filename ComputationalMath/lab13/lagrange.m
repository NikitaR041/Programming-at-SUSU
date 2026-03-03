function coef = lagrange(x, y)
    % Численный многочлен Лагранжа
    n = length(x);
    coef = 0;

    for k = 1:n
        % Базисный полином L_k(x)
        Lk = 1;

        for j = 1:n
            if j ~= k
                % полиномиальное умножение
                Lk = conv(Lk, [1 -x(j)]) / (x(k) - x(j));
            end
        end

        % Добавляем вклад y(k)*Lk(x)
        coef = coef + y(k) * Lk;
    end
end
