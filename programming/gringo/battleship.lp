%%%the details%%%
%p23

%row and col
col(1,3).
col(2,1).
col(3,5).
col(4,2).
col(5,5).
col(6,2).
col(7,2).
col(8,5).

row(1,4).
row(2,1).
row(3,6).
row(4,1).
row(5,2).
row(6,5).
row(7,2).
row(8,4).


sn(11,5).
%%%the program%%%
%default ships
sn(1,4).
sn(2,3).
sn(3,3).
sn(4,2).
sn(5,2).
sn(6,2).
sn(7,1).
sn(8,1).
sn(9,1).
sn(10,1).

grid(X) :- col(X,P).
{sh(X,Y,N) : sn(N,S)}1 :- grid(X;Y).
S{sh(X,Y,N) : grid(X;Y)}S :- sn(N,S).
%for the ship shape
hs(X,Y) :- hss(X,Y,S).
%circle
1{sh(X,Y,N) : sn(N,1)}1 :- hss(X,Y,ci).
%square
%north
hs(X,Y-1) :- hss(X,Y,no).
:- hss(X,Y,no), sh(X-1,Y,N).
:- hss(X,Y,no), sh(X+1,Y,N).
:- hss(X,Y,no), sh(X,Y+1,N).
%south
hs(X,Y+1) :- hss(X,Y,so).
:- hss(X,Y,so), sh(X-1,Y,N).
:- hss(X,Y,so), sh(X+1,Y,N).
:- hss(X,Y,so), sh(X,Y-1,N).
%east
hs(X-1,Y) :- hss(X,Y,ea).
:- hss(X,Y,ea), sh(X,Y-1,N).
:- hss(X,Y,ea), sh(X,Y+1,N).
:- hss(X,Y,ea), sh(X+1,Y,N).
%west
hs(X+1,Y) :- hss(X,Y,we).
:- hss(X,Y,we), sh(X,Y-1,N).
:- hss(X,Y,we), sh(X,Y+1,N).
:- hss(X,Y,we), sh(X-1,Y,N).



hs(X,Y) :- sh(X,Y,N).
1{sh(X,Y,N) : sn(N,S)}1 :- hs(X,Y).
%define neighborhod
nb(X1,Y1,X2,Y2) :- grid(X1;X2;Y1;Y2), |X1-X2|+|Y1-Y2|=1.
nb(X1,Y1,X2,Y2) :- grid(X1;X2;Y1;Y2), |X1-X2|=1,|Y1-Y2|=1.
%diff ship cannot touch
:- sh(X1,Y1,N1), sh(X2,Y2,N2), N1!=N2, nb(X1,Y1,X2,Y2).
%number of ship pcs on row and col
P{sh(X,Y,N) : grid(X), sn(N,S)}P :- row(Y,P).
P{sh(X,Y,N) : grid(Y), sn(N,S)}P :- col(X,P).
%ship adj
sad(X1,Y1,X2,Y2) :- sh(X1,Y1,N), sh(X2,Y2,N), |X1-X2|+|Y1-Y2|=1.
sr(X1,Y1,X2,Y2) :- sad(X1,Y1,X2,Y2).
sr(X1,Y1,X3,Y3) :- sr(X1,Y1,X2,Y2), sr(X2,Y2,X3,Y3).
:- sh(X1,Y1,N), sh(X2,Y2,N), not sr(X1,Y1,X2,Y2), |X1-X2|+|Y1-Y2|>0.
%ship in one line
:- sh(X1,Y1,N), sh(X2,Y2,N), X1!=X2, Y1!=Y2.

#show sh/3.
