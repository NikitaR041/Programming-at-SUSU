%% решаем задачу регрессии с помощью двуслойной сети, обучение проводим по
% методу обратного распостранения ошибки
clear; clc; close all;

% функция
y=@(x) x.*cos(x)./10;
% возьмем N значений функции в качестве обучающей выборки
x=0:0.25:10;
y=y(x);
x=x./10;
N=length(x);

% для решения задачи выберем структуру сети n-H-M;
n=1; H=5; M=1;
w1=randn(n+1,H);
w2=randn(H+1,M);

% посчитаем первоначальное значение функционала качества
for k=1:N
    output(k)=NNFF(w1, w2, x(k));
    L(k)=(output(k)-y(k)).^2;
end
Q(1)=sum(L)/N;
%% учимся
Niter=3000;
lambda=0.01; % темп забывания
figure(1)
h=plot(x,y,'ob',x,output,'r', 'LineWidth',2);
p=0;
for j=1:Niter
    for k=1:N
        for s=1:1
        [w1new, w2new, Q1]=BackProp(w1,w2, x(k),y(k));
        Q(k+1+(j-1)*N)=(1-lambda)*Q(k+(j-1)*N)+lambda*Q1;
        w1=w1new;
        w2=w2new;
        end
     end
     p=p+1;
     if p == 10
         for k=1:N
             yNN(k)=NNFF(w1, w2, x(k));
         end
         p=0;
         delete(h)
         h=plot(x,y,'ob',x,yNN,'r','LineWidth',2);
         pause(0.0001);
     end
 end

figure(2)
plot(Q)

% чтобы увидеть процесс обучения будем строить кривую, которую нейронная
% сеть "подгоняет" под нужную нам и ошибку Функционала качества
