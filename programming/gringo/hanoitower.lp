#const m=8.
peg(a;b;c).
disk(1..3).
init_on(1..3,a).
goal_on(1..3,c).
%maximum number of moves
moves(m).
%for every turn T, move disk D to peg P. Only one move
1{move(D,P,T) : disk(D), peg(P)}1 :- moves(M),T=1..M.
%disk D is moved at time T
move(D,T) :- move(D,_,T).
%disk D is on peg P
on(D,P,0) :- init_on(D,P).
on(D,P,T) :- move(D,P,T).
%if not moved just stay, when it reaches m moves will terminate
on(D,P,T+1) :- on(D,P,T), not move(D,T+1), not moves(T).
%if disk D is on peg P, any disk from 1 to D-1, cannot be moved from P
blocked(D1,P,T+1) :- on(D,P,T), D1<D, disk(D1), not moves(T).
%if move disk D, it must not be blocked
:- move(D,P,T), blocked(D,_,T).
%at final turn things must be same as goal
:- goal_on(D,P), not on(D,P,M), moves(M).
%each disk is on only one peg, at every turn
:- 1{on(D,P,T) : peg(P)}1, disk(D), moves(M), T=1..M.
#show move/3.