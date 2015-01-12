%%%solution
g(1..k).

%ship
s(X,Y) :- b(X,Y,_).
%blank square
bs(X,Y) :- g(X), g(Y), not s(X,Y).

{lh(X,Y)} :- bs(X,Y).
lb(X,Y1,X,Y) :- lh(X,Y), s(X,Y1).
lb(X1,Y,X,Y) :- lh(X,Y), s(X1,Y).

lbc(X,Y,Z) :- s(X,Y), Z=#count{A,B:lb(X,Y,A,B)}.
:- b(X,Y,Z), not lbc(X,Y,Z).

%adjacent
a(X1,Y1,X2,Y2) :- g(X1;Y1;X2;Y2), |X1-X2|+|Y1-Y2|==1.
a(X1,Y1,X2,Y2) :- g(X1;Y1;X2;Y2), |X1-X2|==1, |Y1-Y2|==1.
%no adjacent lh and ship
:- s(X1,Y1), lh(X2,Y2), a(X1,Y1,X2,Y2).
:- lh(X1,Y1), lh(X2,Y2), a(X1,Y1,X2,Y2).

#show lh/2.
