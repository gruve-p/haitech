%%%the program
vx(X) :- nb(X,Y,P).
vy(Y) :- nb(X,Y,P).
val(P) :- nb(X,Y,P).
mx(X) :- vx(X), not vx(X+1).
my(X) :- vy(X), not vy(X+1).
md(X*Y/2) :- mx(X), my(Y).
do(1..X) :- md(X).

2{dm(X,Y,D) : vx(X),vy(Y)}2 :- do(D).
1{dm(X,Y,D) : do(D)}1 :- vx(X), vy(Y).

%dc(X,Y) all possible combinations
%dc(X,Y) :- val(X;Y), X<=Y.

%define adjacency
adj(X1,Y1,X2,Y2) :- vx(X1;X2), vy(Y1;Y2), |X1-X2|+|Y1-Y2|=1.
%same piece must be adj
:- dm(X1,Y1,D), dm(X2,Y2,D), |X1-X2|+|Y1-Y2|>0, not adj(X1,Y1,X2,Y2).

%no identical domino
cd(D,V1+V2,V1*V2) :- dm(X1,Y1,D), dm(X2,Y2,D), |X1-X2|+|Y1-Y2|>0, nb(X1,Y1,V1), nb(X2,Y2,V2).
:- cd(D1,S1,P1), cd(D2,S2,P2), D1!=D2, S1=S2,P1=P2.

%dt(X+Y,X*Y) :- val(X;Y), X<=Y.
%1{cd(D,S,P) : do(D)}1 :- dt(S,P).



%#show cd/3.
%#show dt/2.
#show dm/3.