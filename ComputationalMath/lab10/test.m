%Решение системы нелинейных уравнений методом методом Ньютона
%Система
%sin(x+y)-1.2x = 0.1
%x^2+y^2 = 1
%Найденные производные для Якобиана
%dfs1x = cos(x+y) - (6/5);
%dfs1y = cos(x+y);
%dfs2x = 2*x;
%dfs2y = 2*y;
%f1 = sin(x+y)-1.2*x - 0.1;
%f2 = x.^2+y.^2 - 1;

y1 = ezplot('sin(x+y)-1.2*x - 0.1');
set(y1, 'Color', 'b', 'LineWidth', 2);
hold on; 
y2 = ezplot('x.^2+y.^2 - 1');
set(y2, 'Color', 'b', 'LineWidth', 2);
grid on;
interval = {[-1; 0], [0; 1]};
eps = 0.0001;
for i = 1:length(interval)
    point = interval{i};
    iter = 0;
    while true
       f0 = [sin(point(1) + point(2)) - 1.2*point(1) - 0.1; 
                point(1).^2 + point(2).^2 - 1];
       Jac = [cos(point(1) + point(2)) - 1.2, cos(point(1) + point(2));
                            2*point(1), 2*point(2)];
       
       if abs(det(Jac)) < 1e-10
            fprintf('Матрица Якоби вырождена на итерации %d det = %.2e\n', iter);
            break;
       end
       x_new = point - (Jac\f0);
       point = x_new;
       iter = iter + 1;
       if (iter > 100)
           fprintf('Итераций превышает 100');
           break;
       end;
       if norm(Jac\f0, inf) < eps % Проверка точности
           fprintf("\nНачальная точки: [%g; %g]\n", interval{i}(1), interval{i}(2));
           fprintf("Решение: [%g; %g]\n", x_new(1), x_new(2));
           fprintf("Итераций: %d\n", iter);
           break;
       end;
    end;
end;