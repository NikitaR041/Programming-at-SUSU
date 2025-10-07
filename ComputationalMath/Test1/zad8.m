f = @(x) (2*x - 1).*cos(x) - 1;   
a = -pi;                           
b = pi;                            
n = 1000;                          

 % равномерное разбиение интервала
x = linspace(a, b, n);           
y = f(x);

res = [];                         

for i = 1:n-1
    %Проверка на смену знака
    if y(i) * y(i+1) < 0
        %Уточнение корня 
        r = fzero(f, [x(i), x(i+1)]);  
        res(end+1) = r;            
    end
end

res = unique(round(res, 6));

fprintf('Найдено %d корней:\n', length(res));
for k = 1:length(res)
    fprintf('x_%d = %.4f\n', k, res(k));
end
