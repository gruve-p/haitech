%%%pigeons
#const n=5.
#const m=4.

p(1..m).
h(1..n).


%%%a
1{a(X,Z) : h(Z)}1 :- p(X).
:- a(X,Y), a(Z,Y), X<Z.

#show a/2.
%#show g/1.
