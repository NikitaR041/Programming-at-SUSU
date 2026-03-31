%20a. Вернуть индекс первого вхождения значения в список.
get_index(X, [X|_], 1).
get_index(X, [_|T], Index) :- get_index(X, T, Index2), Index is Index2 + 1. 
%get_index(3, [1,3,4,3], I).
%get_index(3, [3,1,2], I).
%get_index(0, [1,2,3], I).
%get_index(X, [1,2,3], I).
%get_index(X, [1,2,3], 2).

%20b. Вернуть максимальное значение в списке чисел и индекс его первого вхождения.
%get_max([H|T], Max, I) :- get_max(T, H, 1, 1, Max, I).
%get_max([], Max, MaxI, _, Max, MaxI).
%get_max([H|T], CurMax, CurI, MaxI, Max, I) :- H > CurMax, NewI is CurI + 1, get_max(T, H, NewI, NewI, Max, I).
%get_max([H|T], CurMax, CurI, MaxI, Max, I) :- H =< CurMax, NewI is CurI + 1, get_max(T, CurMax, NewI, MaxI, Max, I).
   
% find_max_index(Список, МаксЗначение, Индекс)
find_max_index([H|T], Max, Index) :- 
    max_helper(T, H, 1, 1, Max, Index).

% max_helper(Хвост, ТекМакс, ТекМаксИндекс, ТекПозиция, ИтогМакс, ИтогИндекс)
max_helper([], Max, MaxIdx, _, Max, MaxIdx). % Конец списка — возвращаем накопленные значения.

% Случай 1: Нашли новый максимум
max_helper([H|T], CurMax, _, CurPos, Max, MaxIdx) :-
    H > CurMax, !,
    NewPos is CurPos + 1,
    max_helper(T, H, NewPos, NewPos, Max, MaxIdx).

% Случай 2: Текущий элемент не больше максимума
max_helper([_|T], CurMax, CurMaxIdx, CurPos, Max, MaxIdx) :-
    NewPos is CurPos + 1,
    max_helper(T, CurMax, CurMaxIdx, NewPos, Max, MaxIdx).

%get_max([1,5,3,2], Max, I).
%get_max([7,2,9,4], Max, I).
%get_max([1,5,3,5,2], Max, I).
%get_max([4,4,4,4], Max, I).
%get_max([-5,-2,-10], Max, I).
%get_max([42], Max, I).
%get_max([], Max, I).