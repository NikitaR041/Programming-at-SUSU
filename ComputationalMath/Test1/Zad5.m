x = -10:0.1:10;
y = -10:0.1:10;
[X, Y] = meshgrid(x, y);

Z = -1*exp(-1*y.^2).*(1 - X) + Y + sin(pi*X);

figure;
surf(X, Y, Z);
shading interp;
colormap jet;

title('График функции: z = (1 - 2x) + y + sin(x)', 'FontSize', 14);
xlabel('X', 'FontSize', 14);
ylabel('Y', 'FontSize', 14);
zlabel('Z', 'FontSize', 14);
colorbar;
grid on;
box on;