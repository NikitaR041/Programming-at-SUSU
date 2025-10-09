% Уравение arctg(x-1) + 3x - 2 = 0

%Смотрим график по диапазону [0.5;1] 
x = 0.5 : 0.1 : 1;
y = atan(x-1) + 3*x - 2;
plot(x,y)
grid on
title('y = arctg(x-1) + 3*x - 2')

%Поиск корня
f = @(x) atan(x-1) + 3*x - 2;
result = fzero(f, [0, 1]);
disp(result);