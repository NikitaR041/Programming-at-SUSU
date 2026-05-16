:- op(900, fx, select).
:- op(850, xfx, from).

define(адр_книга, ['ФИО'/30, email/20, дата_рожд/10]).
адр_книга('Иванов И.И.', 'HelloWorld@a.com', '1/1/1980').
адр_книга('Акарлян В.В.', 'ПриветМир@p.com', '2/2/2000').
адр_книга('Зумеров З.З.', 'Hi@a.com', '3/3/1185').

at_ind(1, [Field/W|_], Field, W).
at_ind(N, [_|T], Field, W) :- 
   at_ind(N1, T, Field, W), 
   N is N1 + 1.

select SelectedFields from Table :-
   define(Table, AllFields),
   length(AllFields, Arity),
   length(Args, Arity),
   Q =.. [Table|Args],
   findall(Args, call(Q), AllRows), 
   print_rows(AllRows, SelectedFields, AllFields).

print_rows([], _, _).
print_rows([Row|Rest], Selected, Structure) :-
   print_row(Selected, Structure, Row),
   nl,
   print_rows(Rest, Selected, Structure).

print_row([], _, _).
print_row([F|Fs], Structure, RowArgs) :-
   at_ind(Ind, Structure, F, W),
   nth1(Ind, RowArgs, Val),
   write(Val),
   atom_length(Val, L), Pad is W - L, tab(Pad),
   print_row(Fs, Structure, RowArgs).
   
% select ['ФИО', email] from адр_книга.

% select [email, 'ФИО'] from адр_книга.

% select [email] from адр_книга.