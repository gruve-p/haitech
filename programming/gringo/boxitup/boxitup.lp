%%%the program
grid(1..k).
label(L) :- num(X,Y,S,L).
bl(X,Y,L) :- num(X,Y,S,L).
bs(L,S) :- num(X,Y,S,L).
%every cell has label
1{bl(X,Y,L) : label(L)}1 :- grid(X;Y).
%quantity of every label
S{bl(X,Y,L) : grid(X;Y)}S :- bs(L,S).
%box continuity
bl(X3,Y,L1) :- bl(X1,Y,L1), bl(X2,Y,L1), grid(X3), (X3-X1)*(X3-X2)<0.
bl(X,Y3,L1) :- bl(X,Y1,L1), bl(X,Y2,L1), grid(Y3), (Y3-Y1)*(Y3-Y2)<0.

%adj(X1,Y1,X2,Y2) :- grid(X1;X2;Y1;Y2), |X1-X2|+|Y1-Y2|=1.
%ba(X1,Y1,X2,Y2) :- adj(X1,Y1,X2,Y2), bl(X1,Y1,L), bl(X2,Y2,L).
%br(X1,Y1,X2,Y2) :- ba(X1,Y1,X2,Y2).
%br(X1,Y1,X3,Y3) :- br(X1,Y1,X2,Y2), br(X2,Y2,X3,Y3).
%:- bl(X1,Y1,L), bl(X2,Y2,L), not br(X1,Y1,X2,Y2).

%rectangle condition
bl(X2,Y1,L) :- bl(X1,Y1,L), bl(X2,Y2,L).
bl(X1,Y2,L) :- bl(X1,Y1,L), bl(X2,Y2,L).

%%%just debug
bl1(X,Y) :- bl(X,Y,1).



#show bl/3.
%#show bl1/2.