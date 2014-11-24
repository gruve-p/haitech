
%%%the program
grid(1..k).
%each number has P branches
P{branch(X,Y,X1,Y1) : grid(X1), grid(Y1)}P :- num(X,Y,P).
%:- branch(X,Y,X1,Y1), not num(X,Y,P), grid(X1;Y1).

%a cell can only be associated to one numcell
:- branch(A1,B1,X,Y), branch(A2,B2,X,Y), |A1-A2| + |B1-B2| >0.
%branch from a num must be on same col or row
:- branch(A,B,X,Y), A!=X, B!=Y.
%branch not on numcell
:- num(X,Y,P), branch(A,B,X,Y).
%brach must be continuous
:- branch(A,B,A,Y), Y>B, not branch(A,B,A,Y1), Y1>B,Y1<Y, grid(Y1).
:- branch(A,B,A,Y), Y<B, not branch(A,B,A,Y1), Y1<B,Y1>Y, grid(Y1).

:- branch(A,B,X,B), X>A, not branch(A,B,X1,B), X1>A,X1<X, grid(X1).
:- branch(A,B,X,B), X<A, not branch(A,B,X1,B), X1<A,X1>X, grid(X1).

#show branch/4.