%create directed pseudoforest
#const n=10.
#const k=10.

v(1..n).
k{e(U,V) : v(U;V), U!=V}.
:- e(U,V), e(V,U).
%cannot have more than one successor
:- e(U,V1), e(U,V2), V1!=V2.
#show e/2.