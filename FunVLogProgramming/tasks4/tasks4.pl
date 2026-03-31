%20a. Вернуть индекс первого вхождения значения в список.

get_index(X, L, I) :- get_index(X, L, 1, I).
get_index(X, [X|_], I, I).
get_index(X, [_|T], CurI, I) :- NextI is CurI + 1, get_index(X, T, NextI, I).

%get_index(3, [1,3,4,3], I).
%get_index(3, [3,1,2], I).
%get_index(0, [1,2,3], I).
%get_index(X, [1,2,3], I).
%get_index(X, [1,2,3], 2).

%20b. Вернуть максимальное значение в списке чисел и индекс его первого вхождения.

get_max([H|T], Max, I) :- get_max(T, H, 1, 1, Max, I).
get_max([], Max, _, MaxI, Max, MaxI).
get_max([H|T], CurMax, CurI, MaxI, Max, I) :- H > CurMax, NewI is CurI + 1, get_max(T, H, NewI, NewI, Max, I).
get_max([H|T], CurMax, CurI, MaxI, Max, I) :- H =< CurMax, NewI is CurI + 1, get_max(T, CurMax, NewI, MaxI, Max, I).
    
%get_max([1,5,3,2], Max, I).
%get_max([7,2,9,4], Max, I).
%get_max([1,5,3,5,2], Max, I).
%get_max([4,4,4,4], Max, I).
%get_max([-5,-2,-10], Max, I).
%get_max([42], Max, I).
%get_max([], Max, I).