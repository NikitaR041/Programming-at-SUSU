:- op(900, fx, select).
:- op(800, xfx, where).

define(адр_книга, ['ФИО'/30, email/20, дата_рожд/10]).
адр_книга('Иванов И.И.', 'a@a.com', '1/1/1980').
адр_книга('Петров П.П.', 'p@p.com', '2/2/1990').
адр_книга('Сидоров С.С.', 'a@a.com', '3/3/1985').

at_ind(1, [E|_], E).
at_ind(N, [_|T], E) :-
   at_ind(N1, T, E),
   N is N1 + 1.

select Table where Field = Val :-
   define(Table, Fields),
   at_ind(Ind, Fields, Field/_),
   length(Fields, Arity),
   length(Args, Arity),
   at_ind(Ind, Args, Val),
   Q =.. [Table|Args],
   call(Q),
   write(Q), nl,
   fail.

%?- select адр_книга where email = 'a@a.com'.
%адр_книга(Иванов И.И.,a@a.com,1/1/1980)
%адр_книга(Сидоров С.С.,a@a.com,3/3/1985)
%no
