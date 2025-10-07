function y = f6(x)   
    if x < -pi/2
        y = (2/pi) * x + 1;
    elseif x < pi/2
        y = sin(2 * x);
    else
        y = (2 * x) / pi - 1;
    end
end