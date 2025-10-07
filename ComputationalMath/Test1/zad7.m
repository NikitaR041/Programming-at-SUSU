num = 9;
if num < 0
    fprintf('Факториал неопределен для отрицательных чисел\n');
elseif num == 0 || num == 1
    fprintf('%d! = 1\n', num);
else
    result = 1;
    for i = 2:num
        result = result * i;
    end
    fprintf('%d! = %d\n', num, result);
end