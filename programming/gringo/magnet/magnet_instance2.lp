%%%details of the map
%%problem13
%magnets positions
bloc(1..2,1,1).
bloc(3..4,1,2).
bloc(5..6,1,3).
bloc(7..8,1,4).
bloc(1,2..3,5).
bloc(2..3,2,6).
bloc(4..5,2,7).
bloc(6..7,2,8).
bloc(8,2..3,9).
bloc(2..3,3,10).
bloc(4..5,3,11).
bloc(6,3..4,12).
bloc(7,3..4,13).
bloc(1..2,4,14).
bloc(3..4,4,15).
bloc(5,4..5,16).
bloc(8,4..5,17).
bloc(1,5..6,18).
bloc(2..3,5,19).
bloc(4,5..6,20).
bloc(6..7,5,21).
bloc(2,6..7,22).
bloc(3,6..7,23).
bloc(5..6,6,24).
bloc(7..8,6,25).
bloc(1,7..8,26).
bloc(4,7..8,27).
bloc(5..6,7,28).
bloc(7,7..8,29).
bloc(8,7..8,30).

bloc(2..3,8,31).
bloc(5..6,8,32).

%row and col, plus and minus
rowp(1,2).
rowp(3,3).
rowp(5,1).
rowp(7,2).

rown(2,1).
rown(4,2).
rown(6,4).
rown(8,3).

colp(2,2).
colp(4,4).
colp(6,1).
colp(8,2).

coln(1,2).
coln(3,2).
coln(5,1).
coln(7,3).