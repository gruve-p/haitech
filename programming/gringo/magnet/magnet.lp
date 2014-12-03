%%%details of the map
%%%the program
val(0;1).
0{set(X,Y,V) : val(V)}1 :- grid(X), grid(Y).

grid(X) :- bloc(X,Y,P).
%:- set(X,Y,1), set(X,Y,0).

%if one is pos, the other is neg, in one bloc
set(X2,Y2,0) :- set(X1,Y1,1), |X1-X2|+|Y1-Y2|=1, bloc(X1,Y1,P), bloc(X2,Y2,P).

set(X2,Y2,1) :- set(X1,Y1,0), |X1-X2|+|Y1-Y2|=1, bloc(X1,Y1,P), bloc(X2,Y2,P).

%row and col rules
P{set(X,Y,1) : grid(X)}P :- rowp(Y,P).
P{set(X,Y,0) : grid(X)}P :- rown(Y,P).
P{set(X,Y,1) : grid(Y)}P :- colp(X,P).
P{set(X,Y,0) : grid(Y)}P :- coln(X,P).

%same sign cannot be adjacent
:- set(X1,Y1,S), set(X2,Y2,S), |X1-X2| + |Y1-Y2| =1.


#show set/3.
