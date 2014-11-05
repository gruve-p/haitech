node(X) :- edge(X,Y).
node(Y) :- edge(X,Y).
1{start(X) : node(X)}1.
{in(U,V)} :- edge(U,V).
1{in(X,Y)}1 : node(X).
1{in(Y,X)}1 : node(X).
reached(Y) :- start(X), in(X,Y).
reached(Y) :- reached(X), in(X,Y).