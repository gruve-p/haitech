%%%
#const k=8.
#const n=3.
tree(1,5).
tree(2,1).
tree(2,7).
tree(3,1).
tree(3,3).
tree(3,6).
tree(5,8).
tree(6,1).
tree(6,6).
tree(6,7).
tree(7,5).
tree(8,7).

g(1..k).
free(X,Y) :- g(X;Y), not tree(X,Y).
adj(X1,Y1,X2,Y2) :- g(X1;Y1;X2;Y2), |X1-X2|+|Y1-Y2|=1.
adj(X1,Y1,X2,Y2) :- g(X1;Y1;X2;Y2), |X1-X2|=1, |Y1-Y2|=1.
n{tent(X,Y) : free(X,Y)}n.

hastree(X,Y) :- tent(X,Y), adj(X,Y,X1,Y1), tree(X1,Y1).
:- tent(X,Y), not hastree(X,Y).
:- tent(X1,Y1), tent(X2,Y2), adj(X1,Y1,X2,Y2).

#show tent/2.