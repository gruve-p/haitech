%%%the program
grid(1..k).
%there are some tower
{tower(X,Y): grid(X),grid(Y)}k*k.
%tower not in sentinel place
:- tower(X,Y), num(X,Y,P).

%(X2,Y2) seen from (X1,Y1) if
%in line
%inline(X1,Y1,X1,Y2) :- num(X1,Y1,P), grid(Y2), Y1!=Y2.
%inline(X1,Y1,X2,Y1) :- num(X1,Y1,P), grid(X2), X1!=X2.

%must see if inline and not blocked
%see(X1,Y1,X2,Y2) :- inline(X1,Y1,X2,Y2), not blocked(X1,Y1,X2,Y2), not tower(X2,Y2).
%sentinels can see
P{see(X,Y,X2,Y2) : grid(X2;Y2)}P :- num(X,Y,P).
:- see(X1,Y1,X2,Y2), tower(X2,Y2).
:- see(X1,Y1,X2,Y2), X1!=X2, Y1!=Y2.
:- see(X1,Y1,X2,Y2), blocked(X1,Y1,X2,Y2).
%%blocked(X1,Y1,X2,Y2), cannot see(X2,Y2) from (X1,Y1)
%blocked on col
blocked(X1,Y1,X1,Y2) :- num(X1,Y1,P), tower(X1,Y3), (Y3-Y1)*(Y3-Y2)<0,grid(Y2).
%blocked on row
blocked(X1,Y1,X2,Y1) :- num(X1,Y1,P), tower(X3,Y1), (X3-X1)*(X3-X2)<0, grid(X2).

%%must be seen if not blocked
vrange(X1,Y1,X1,Y2) :- grid(X1;Y1;Y2), Y2!=Y1.
vrange(X1,Y1,X2,Y1) :- grid(X1;Y1;X2), X2!=X1.
vrange(X,Y,X,Y) :- grid(X;Y).
see(X1,Y1,X2,Y2) :- vrange(X1,Y1,X2,Y2), not blocked(X1,Y1,X2,Y2), not tower(X2,Y2).

see(X,Y,X,Y) :- num(X,Y,P).
%tower not adj
:- tower(X1,Y1), tower(X2,Y2), |X1-X2|+|Y1-Y2|=1.



%park must be contiguous
reachable(X1,Y1,X2,Y2) :- not tower(X1,Y1), not tower(X2,Y2), |X1-X2| + |Y1-Y2| =1, grid(X1;Y1;X2;Y2).
reachable(X1,Y1,X2,Y2) :- reachable(X1,Y1,X3,Y3), reachable(X3,Y3,X2,Y2).
reachable(X1,Y1,X2,Y2) :- grid(X1;Y1;X2;Y2), not tower(X1,Y1), not tower(X2,Y2).


#show tower/2.
