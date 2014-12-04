%%problem1
%magnets positions
bloc(1,1..2,1).
bloc(2..3,1,2).
bloc(4,1..2,3).
bloc(2..3,2,4).
bloc(1,3..4,5).
bloc(2,3..4,6).
bloc(3..4,3,7).
bloc(3..4,4,8).


%row and col, plus and minus
rowp(1,1).
rowp(2,1).
rowp(3,1).
rowp(4,2).

rown(1,2).
rown(2,0).
rown(3,1).
rown(4,2).

colp(1,1).
colp(2,1).
colp(3,2).
colp(4,1).

coln(1,1).
coln(2,2).
coln(3,0).
coln(4,2).