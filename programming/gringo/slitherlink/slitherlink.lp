%%%the program
grid(1..k).
gridx(0..k+1).

%adjacent
adj(X,Y,A,B) :- |X-A|+|Y-B|=1, gridx(X;Y;A;B).


%some cells are painted
1{paint(X,Y) : grid(X;Y)}.
:- paint(X,Y), not grid(X).
:- paint(X,Y), not grid(Y).

%if cell not painted, and has number P
%P of its neighbor must be painted
P{paint(X1,Y1): adj(X,Y,X1,Y1)}P :- num(X,Y,P), not paint(X,Y).
%if cell is painted and has number P
%4-P of its neighbor must be painted
4-P{paint(X1,Y1) : adj(X,Y,X1,Y1)}4-P:- num(X,Y,P), paint(X,Y).

%painted cells continuous
adjp(X,Y,A,B) :- adj(X,Y,A,B), paint(X,Y), paint(A,B).
reachp(X,Y,A,B) :- adjp(X,Y,A,B).
reachp(X1,Y1,X3,Y3) :- reachp(X1,Y1,X2,Y2), reachp(X2,Y2,X3,Y3).
:- paint(X,Y), paint(A,B), not reachp(X,Y,A,B).

%all nonpaint also connected
np(X,Y) :- gridx(X;Y), not paint(X,Y).
adjn(X,Y,A,B) :- adj(X,Y,A,B), np(X,Y), np(A,B).
reachn(X,Y,A,B) :- adjn(X,Y,A,B).
reachn(X1,Y1,X3,Y3) :- reachn(X1,Y1,X2,Y2), reachn(X2,Y2,X3,Y3).
:- np(X,Y), np(A,B), not reachn(X,Y,A,B).

%%%for debug
%rr(A,B) :- reachn(2,4,A,B).
%counter(X,Y,A,B) :- np(X,Y), np(A,B), not reachn(X,Y,A,B).

%no cell has 4 borders
:- 4{paint(X1,Y1) : adj(X,Y,X1,Y1)}4, not paint(X,Y), grid(X;Y).
%path cannot cross
:- paint(X,Y), paint(X+1,Y-1), not paint(X,Y-1), not paint(X+1,Y).
:- paint(X,Y), paint(X+1,Y+1), not paint(X,Y+1), not paint(X+1,Y).


#show paint/2.
%#show counter/4.
%#show rr/2.