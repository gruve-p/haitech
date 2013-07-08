#!/usr/bin/env python

#permutation k-cycles
#the number of permutation of [n]
#with exactly k cycles
#example one permutation of [6] is
#(1,3,5)(2,4)(4)

def pkc(n,k):
    result=0
    if n==k and n>=0:
        result=1
    elif (n>=1 and k==0) or k>n or n<1:
        result=0
    else:
        result=(n-1)*pkc(n-1,k)+pkc(n-1,k-1)

    return result

#stirling number of the first kind
#signed
def stir1k(n,k):
    return ((-1)**(n-k))*pkc(n,k)

#recursive
def stir1kRecur(n,k):
    if n==k and n>=0: return 1
    elif (n>=1 and k==0) or k>n or n<1: return 0
    else:
        return (1-n)*stir1kRecur(n-1,k) + stir1kRecur(n-1,k-1)