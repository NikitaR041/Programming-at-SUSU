function print_poly(coef)
    % coef: вектор коэффициентов [a_n ... a_1 a_0]
    n = length(coef);

    fprintf('\nP(x) = ');
    for k = 1:n
        a = coef(k);
        p = n - k; % степень

        if abs(a) < 1e-12
            continue; % пропускаем нулевые
        end

        % знак
        if k > 1
            if a >= 0
                fprintf(' + ');
            else
                fprintf(' - ');
                a = -a; % распечатали знак, теперь модуль
            end
        end

        % коэффициент
        if p == 0
            fprintf('%.6g', a);
        elseif p == 1
            fprintf('%.6g*x', a);
        else
            fprintf('%.6g*x^%d', a, p);
        end
    end

    fprintf('\n\n');
end
