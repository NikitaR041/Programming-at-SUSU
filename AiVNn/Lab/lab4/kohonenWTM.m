%% пример работы сети Кохонена
% зададим множество двумерных объектов (точек) и разобъем его на
% кластеры (используя стратегию WTM)
clear; clc; close all;

%% задаем множество объектов
noise=0.05;
N=20; % число объектов в кластере
% центры кластеров
xc1=0.2; yc1=0.2;
xc2=0.8; yc2=0.5;
xc3=0.2; yc3=0.8;

x1=xc1+noise*randn(N,1); y1=yc1+noise*randn(N,1);
x2=xc2+noise*randn(N,1); y2=yc2+noise*randn(N,1);
x3=xc3+noise*randn(N,1); y3=yc3+noise*randn(N,1);

% "свалим" все в кучу
x=[x1; x2; x3];
y=[y1; y2; y3];

% построим множество с которым будем работать
figure(1)
plot(x,y,'o');
axis([0 1 0 1])
% видно, что оно очевидным образом распадается на 3 класса

%% L1xL2 сетка нейронов Кохонена
L1=5; L2=5;
X=0:1/(L1-1):1; Y=0:1/(L2-1):1; % (X,Y) - это веса нейронов W!
% ее визуализация (начальное положение нейронов)
figure(2)
hold on
for i=1:L1
    for j=1:L2
        W(i,j,1)=X(i);
        W(i,j,2)=Y(j);
        plot(W(i,j,1),W(i,j,2),'ob');
    end
end
axis([0 1 0 1])


%% обучение WTM
NW=zeros(L1,L2); % тут будет число побед нейронов
rho=0.1;
etta=0.2; % шаг обучения
Niter=500; % количество эпох
%figure(4)
%axis([0 1 0 1])
%hold on
for s=1:Niter
    l=randperm(3*N); % случайно выбираем объект
    for k=1:3*N
        for i=1:L1
            for j=1:L2
                A(i,j)=(W(i,j,1)-x(l(k)))^2+(W(i,j,2)-y(l(k)))^2;
            end
        end
        [M,I] = min(A(:)); % находим нейрон-победитель
        [r,c] = ind2sub(size(A),I);
        NW(r,c)=NW(r,c)+1;
        % находим шаг для ВСЕХ нейронов
        for ii=1:L1
            for jj=1:L2
                eta(ii,jj)=etta*rho^(abs(ii-r)+abs(jj-c));
            end
        end
        % меняем веса (сдвигаем ВСЕ нейроны в сторону объекта)
        for ii=1:L1
            for jj=1:L2
                V=[W(ii,jj,1) W(ii,jj,2)]+eta(ii,jj)*([x(l(k)) y(l(k))]-[W(ii,jj,1) W(ii,jj,2)]);
                W(ii,jj,1)=V(1); W(ii,jj,2)=V(2);
                %h=plot(V(1), V(2),'o');
                %set(h);
                %pause(0.001);
            end
        end
    end
end

% визуализация конечного положения нейронов
figure(3)
hold on
for i=1:L1
    for j=1:L2
        plot(W(i,j,1),W(i,j,2),'ob');
        axis([0 1 0 1])
    end
end
NW'
