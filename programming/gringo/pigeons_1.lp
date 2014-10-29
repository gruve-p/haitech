%%%pigeons
%m pigeons, n holes
#const n=5.
#const m=4.

p(1..m).
h(1..n).



%%%one h per p
1{a(X,Z) : h(Z)}1 :- p(X).

%%%one p per h
{a(X,Y) : p(X)}1 :- h(Y).

#show a/2.
%#show g/1.
