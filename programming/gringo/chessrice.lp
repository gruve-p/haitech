rice(0,0,2).
rice(0,1,2).
rice(0,2,4).
rice(0,3,2).
rice(1,0,0).
rice(1,1,3).
rice(1,2,0).
rice(1,3,1).
rice(2,0,1).
rice(2,1,2).
rice(2,2,2).
rice(2,3,1).
rice(3,0,4).
rice(3,1,1).
rice(3,2,2).
rice(3,3,2).
vx(X) :- rice(X,Y,R).
vy(Y) :- rice(X,Y,R).
pos(0,0,0).
%move m+n-2 steps
#const t=6.
%vt(0..t).
vt(X+Y) :- vx(X), vy(Y).
pos(3,3,t).
get(0,R) :- rice(0,0,R).
1{pos(X,Y,T) : vx(X), vy(Y)}1:- vt(T).
:- pos(X,Y,T), T<t, not pos(X+1,Y,T+1), not pos(X,Y+1,T+1).
get(T+1,R1+R2) :- get(T,R1), pos(X,Y,T+1), rice(X,Y,R2).
#maximize { X@1: get(t,X) }.
#show get/2.