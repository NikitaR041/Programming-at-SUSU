function y = Lab5(~)
    x = 2:0.1:3;
    y = exp(x).*((x.^2).^(1/3)) - x - 1;
    plot(x, y, 'r-.', 'Marker', '*')
    grid on
    hold on
    
    x0 = 2.35;
    y0 = exp(x0).*((x0.^2).^(1/3)) - x0 - 1; 
   
    plot(x0, y0, 'g*', 'MarkerSize', 10)
    hold off
   
    y = y0; % Возвращаем значение y0
end