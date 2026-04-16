function dz_central_field
    % ==== Дано по условию ====
    G = 6.67430e-11;
    M = 2e30;
    R = 7e8;
    mu = G * M;   % гравитационный параметр

    fprintf('Движение в центральном поле сил\n');
    fprintf('--------------------------------\n');
    level = input('Введите уровень задания (1 или 2): ');

    switch level
        case 1
            % Уровень 1: заданы x0, y0, vx0, vy0
            x0  = input('x0  = ');
            y0  = input('y0  = ');
            vx0 = input('vx0 = ');
            vy0 = input('vy0 = ');
            solveLevel1(x0, y0, vx0, vy0, mu, R);

        case 2
            % Уровень 2: заданы r0 и v0, скорость перпендикулярна радиусу
            r0 = input('r0 = ');
            v0 = input('v0 = ');
            solveLevel2(r0, v0, mu, R);

        otherwise
            error('Нужно ввести 1 или 2.');
    end
end

% ============================================================
%                 УРОВЕНЬ 1
% ============================================================
function solveLevel1(x0, y0, vx0, vy0, mu, R)
    rvec = [x0; y0];
    vvec = [vx0; vy0];

    r0 = norm(rvec);
    v0 = norm(vvec);

    if r0 <= R
        fprintf('\nКорабль уже внутри звезды — столкновение уже произошло.\n');
        plotStarAndPoint(R, x0, y0);
        return;
    end

    % Удельный момент импульса h = r x v (в плоскости)
    h = x0 * vy0 - y0 * vx0;

    % Удельная энергия
    eps = 0.5 * v0^2 - mu / r0;

    % Тип траектории по энергии
    tol = 1e-12;
    if eps < -tol
        orbitType = 'эллипс';
    elseif abs(eps) <= tol
        orbitType = 'парабола';
    else
        orbitType = 'гипербола';
    end

    fprintf('\n----- Уровень 1 -----\n');
    fprintf('r0 = %.6e м\n', r0);
    fprintf('v0 = %.6e м/с\n', v0);
    fprintf('h  = %.6e\n', h);
    fprintf('eps= %.6e Дж/кг\n', eps);
    fprintf('Тип траектории: %s\n', orbitType);

    % Почти радиальное движение
    if abs(h) < 1e-14
        fprintf('Почти радиальное движение (h ~ 0).\n');
        radialMotionPlot(rvec, vvec, mu, R);
        return;
    end

    % Вектор эксцентриситета
    evec = ( (v0^2 - mu / r0) * rvec - dot(rvec, vvec) * vvec ) / mu;
    e = norm(evec);
    p = h^2 / mu;
    omega = atan2(evec(2), evec(1));  % аргумент перицентра
    theta0 = atan2(y0, x0);

    fprintf('e  = %.6e\n', e);
    fprintf('p  = %.6e м\n', p);

    % Проверка возможного столкновения
    [collision, thetaHit] = firstFutureCollision(theta0, omega, e, p, R, sign(h));

    if collision
        fprintf('Столкновение со звездой возможно. Строим траекторию до удара.\n');
        theta = linspace(theta0, thetaHit, 2000);
    else
        fprintf('Столкновения со звездой не будет.\n');

        % Для показа строим всю кривую
        if e < 1 - 1e-10
            theta = linspace(0, 2*pi, 3000);     % эллипс
        elseif abs(e - 1) <= 1e-10
            theta = omega + linspace(-pi + 1e-3, pi - 1e-3, 3000); % парабола
        else
            nuMax = acos(-1 / e) - 1e-3;        % гипербола
            theta = omega + linspace(-nuMax, nuMax, 3000);
        end
    end

    % Уравнение орбиты
    r = p ./ (1 + e * cos(theta - omega));

    % На всякий случай уберём точки за пределами разумной области
    valid = isfinite(r) & (r > 0);
    r = r(valid);
    theta = theta(valid);

    % Проекция координат
    x = r .* cos(theta);
    y = r .* sin(theta);

    % ==== График ====
    figure; hold on; grid on; axis equal;
    t = linspace(0, 2*pi, 600);
    plot(R*cos(t), R*sin(t), 'r--', 'LineWidth', 1.8);
    plot(x, y, 'b', 'LineWidth', 2);
    plot(0, 0, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 6);
    plot(x0, y0, 'mo', 'MarkerFaceColor', 'm', 'MarkerSize', 8);

    xlabel('x, м');
    ylabel('y, м');
    title(['Уровень 1: ', orbitType]);
    legend('Звезда', 'Траектория', 'Центр', 'Старт', 'Location', 'best');
end

% ============================================================
%                 УРОВЕНЬ 2
% ============================================================
function solveLevel2(r0, v0, mu, R)
    % Удобно взять старт на оси x:
    % r(0) = (r0, 0), v(0) = (0, v0)
    x0 = r0; 
    y0 = 0;
    vx0 = 0;
    vy0 = v0;

    if r0 <= R
        fprintf('\nКорабль уже внутри звезды — столкновение уже произошло.\n');
        plotStarAndPoint(R, x0, y0);
        return;
    end

    vc = sqrt(mu / r0);           % 1 космическая скорость
    eps = 0.5 * v0^2 - mu / r0;   % удельная энергия
    h = r0 * v0;                  % |r x v|, т.к. скорость перпендикулярна радиусу

    % Эксцентриситет для касательного старта
    e = abs(r0 * v0^2 / mu - 1);
    p = h^2 / mu;

    fprintf('\n----- Уровень 2 -----\n');
    fprintf('r0 = %.6e м\n', r0);
    fprintf('v0 = %.6e м/с\n', v0);
    fprintf('v_кр = %.6e м/с\n', vc);
    fprintf('eps  = %.6e Дж/кг\n', eps);
    fprintf('e    = %.6e\n', e);
    fprintf('p    = %.6e м\n', p);

    tol = 1e-12;
    if abs(v0 - vc) < tol
        orbitType = 'окружность';
        fprintf('Тип траектории: окружность\n');
        fprintf('Столкновения не будет, если r0 > R.\n');
        collision = false;
    elseif eps < -tol
        orbitType = 'эллипс';
        fprintf('Тип траектории: эллипс\n');

        % Для касательного старта:
        % если v0 < vc, начальная точка — апоцентр, потом радиус уменьшается;
        % если v0 > vc, начальная точка — перицентр, дальше радиус только растёт.
        if v0 < vc
            rp = p / (1 + e); % минимальный радиус
            if rp <= R
                collision = true;
                fprintf('Минимальный радиус rp = %.6e м <= R.\n', rp);
                fprintf('Столкновение со звездой будет.\n');
            else
                collision = false;
                fprintf('rp = %.6e м > R, столкновения не будет.\n', rp);
            end
        else
            collision = false;
            fprintf('Начальная точка — перицентр, дальше радиус растёт.\n');
            fprintf('Столкновения не будет.\n');
        end
    elseif abs(eps) <= tol
        orbitType = 'парабола';
        fprintf('Тип траектории: парабола\n');
        collision = (r0 <= R);
        fprintf('После старта радиус только увеличивается, столкновения не будет.\n');
    else
        orbitType = 'гипербола';
        fprintf('Тип траектории: гипербола\n');
        collision = false;
        fprintf('После перицентра радиус только растёт, столкновения не будет.\n');
    end

    % Построение траектории
    if strcmp(orbitType, 'окружность')
        theta = linspace(0, 2*pi, 2000);
        r = r0 * ones(size(theta));
    else
        omega = atan2(0, evecSign(v0, vc)); %#ok<NASGU>
        % В нашем выбранном старте при v0<vc перицентр направлен влево,
        % при v0>vc — вправо. Удобно просто использовать общее уравнение через
        % стартовые координаты, как в уровне 1.
        rvec = [x0; y0];
        vvec = [vx0; vy0];
        evec2 = ( (v0^2 - mu / r0) * rvec - dot(rvec, vvec) * vvec ) / mu;
        omega = atan2(evec2(2), evec2(1));

        theta0 = atan2(y0, x0);

        if collision
            [~, thetaHit] = firstFutureCollision(theta0, omega, e, p, R, sign(h));
            theta = linspace(theta0, thetaHit, 2000);
        else
            if e < 1 - 1e-10
                theta = linspace(0, 2*pi, 3000);
            elseif abs(e - 1) <= 1e-10
                theta = omega + linspace(-pi + 1e-3, pi - 1e-3, 3000);
            else
                nuMax = acos(-1 / e) - 1e-3;
                theta = omega + linspace(-nuMax, nuMax, 3000);
            end
        end

        r = p ./ (1 + e * cos(theta - omega));
    end

    valid = isfinite(r) & (r > 0);
    r = r(valid);
    theta = theta(valid);

    x = r .* cos(theta);
    y = r .* sin(theta);

    figure; hold on; grid on; axis equal;
    t = linspace(0, 2*pi, 600);
    plot(R*cos(t), R*sin(t), 'r--', 'LineWidth', 1.8);
    plot(x, y, 'b', 'LineWidth', 2);
    plot(0, 0, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 6);
    plot(x0, y0, 'mo', 'MarkerFaceColor', 'm', 'MarkerSize', 8);

    xlabel('x, м');
    ylabel('y, м');
    title(['Уровень 2: ', orbitType]);
    legend('Звезда', 'Траектория', 'Центр', 'Старт', 'Location', 'best');
end

% ============================================================
%         Поиск ближайшего будущего пересечения r = R
% ============================================================
function [hit, thetaHit] = firstFutureCollision(theta0, omega, e, p, R, dirSign)
    hit = false;
    thetaHit = NaN;

    if e < 1e-12
        return; % круг не пересекает радиус R, если уже не внутри
    end

    c = (p / R - 1) / e;

    if abs(c) > 1
        return; % пересечения нет
    end

    alpha = acos(max(-1, min(1, c)));
    cand = omega + [alpha, -alpha];

    % Добавим несколько оборотов для правильного выбора "впереди по времени"
    cand = cand(:); % делаем столбец 2x1
    shifts = 2*pi*(-2:2); % 1x5
    
    cand = cand + shifts; % автоматическое расширение (MATLAB R2016b+)
    cand = cand(:); % обратно в вектор

    bestDelta = inf;

    for k = 1:numel(cand)
        th = cand(k);
        if dirSign > 0
            d = mod(th - theta0, 2*pi);
        else
            d = mod(theta0 - th, 2*pi);
        end

        if d > 1e-10 && d < bestDelta
            bestDelta = d;
        end
    end

    if isfinite(bestDelta)
        hit = true;
        if dirSign > 0
            thetaHit = theta0 + bestDelta;
        else
            thetaHit = theta0 - bestDelta;
        end
    end
end

% ============================================================
%                 Радиальное движение (h ~ 0)
% ============================================================
function radialMotionPlot(rvec, vvec, mu, R)
    r0 = norm(rvec);
    u = rvec / r0;  % единичный вектор вдоль линии движения
    vr0 = dot(rvec, vvec) / r0; % радиальная скорость

    eps = 0.5 * dot(vvec, vvec) - mu / r0;

    fprintf('Радиальная скорость vr0 = %.6e м/с\n', vr0);

    if vr0 < 0
        % Идём к центру
        s = linspace(r0, R, 1000);
        fprintf('Движение сразу к звезде: строим от r0 до R.\n');
    else
        % Сначала наружу, если энергия отрицательна — будет возврат
        if eps < 0
            rturn = -mu / eps;  % точка разворота
            fprintf('Есть точка разворота rturn = %.6e м\n', rturn);
            s1 = linspace(r0, rturn, 800);
            s2 = linspace(rturn, R, 800);
            s = [s1, s2];
            fprintf('Столкновение со звездой будет после разворота.\n');
        else
            fprintf('Улетает без столкновения.\n');
            s = linspace(r0, r0 + 2*R, 1000);
        end
    end

    x = s * u(1);
    y = s * u(2);

    figure; hold on; grid on; axis equal;
    t = linspace(0, 2*pi, 600);
    plot(R*cos(t), R*sin(t), 'r--', 'LineWidth', 1.8);
    plot(x, y, 'b', 'LineWidth', 2);
    plot(0, 0, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 6);
    plot(rvec(1), rvec(2), 'mo', 'MarkerFaceColor', 'm', 'MarkerSize', 8);

    xlabel('x, м');
    ylabel('y, м');
    title('Радиальное движение');
    legend('Звезда', 'Траектория', 'Центр', 'Старт', 'Location', 'best');
end

% ============================================================
%                 Вспомогательный рисунок
% ============================================================
function plotStarAndPoint(R, x0, y0)
    figure; hold on; grid on; axis equal;
    t = linspace(0, 2*pi, 600);
    plot(R*cos(t), R*sin(t), 'r--', 'LineWidth', 1.8);
    plot(0, 0, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 6);
    plot(x0, y0, 'mo', 'MarkerFaceColor', 'm', 'MarkerSize', 8);
    xlabel('x, м'); ylabel('y, м');
    title('Корабль уже внутри звезды');
    legend('Звезда', 'Центр', 'Точка', 'Location', 'best');
end

% ============================================================
%    Заглушка: знак для канонического evec в уровне 2
% ============================================================
function s = evecSign(v0, vc)
    if v0 < vc
        s = -1;
    else
        s = 1;
    end
end