%%%pigeons
#const n=5.
#const m=4.

p(1..m).
h(1..n).


%%%a
1{a(X,Z) : h(Z)}1 :- p(X).
b(X-1,Y) :- a(X,Y), p(X-1).
b(X-1,Y) :- b(X,Y), p(X-1).
:- b(X,Y), a(X,Y).

#show a/2.
%#show g/1.
