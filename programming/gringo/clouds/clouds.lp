%%%%%%%%%%%%%clouds%%%%%%%%%%%%%
%%%details%%%
%p12
ro(1,4).
ro(2,8).
ro(3,6).
ro(4,4).
ro(5,3).
ro(6,5).
ro(7,7).
ro(8,4).
ro(9,6).
ro(10,4).

co(1,4).
co(2,7).
co(3,5).
co(4,8).
co(5,3).
co(6,4).
co(7,7).
co(8,3).
co(9,5).
co(10,5).



%%%the program%%%
grid(X) :- co(X,P).
%number of cloud on row and col
P{cl(X,Y) : grid(X)}P :- ro(Y,P).
P{cl(X,Y) : grid(Y)}P :- co(X,P).

%cr(X,Y,X,Y) :- cl(X,Y).
ca(X1,Y1,X2,Y2) :-  cl(X1,Y1), cl(X2,Y2), |X1-X2|+|Y1-Y2|=1.
cr(X1,Y1,X2,Y2) :- ca(X1,Y1,X2,Y2).
cr(X1,Y1,X3,Y3) :- cr(X1,Y1,X2,Y2), cr(X2,Y2,X3,Y3).
4{cc(X1,Y1,X2,Y2) : cr(X1,Y1,X2,Y2)} :- cl(X1,Y1).
%%must be rect shape
cl(X3,Y1) :- cr(X1,Y1,X2,Y1), grid(X3), (X3-X1)*(X3-X2)<0.
cl(X1,Y3) :- cr(X1,Y1,X1,Y2), grid(Y3), (Y3-Y1)*(Y3-Y2)<0.
cl(X2,Y1) :- cr(X1,Y1,X2,Y2).
cl(X1,Y2) :- cr(X1,Y1,X2,Y2).

#show cl/2.