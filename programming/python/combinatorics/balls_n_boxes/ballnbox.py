#!/usr/bin/env python

def intpart(n,k):
    if n==k:
        return 1
    elif n<1 or k<1:
        return 0
    else:
        return intpart(n-1,k-1)+intpart(n-k,k)

def ksub(n,k):
    if k<=0 or k==n:
        return 1
    elif k<0 or n<0 or k>n:
        return 1
    else:
        return (ksub(n-1,k-1)+ksub(n-1,k))

#######how many ways to put n balls into k boxes
#both balls and boxes unlabeled
#box can hold any balls
def uBalluBoxa(n,k):
    sum=0
    for i in xrange(1,k+1):
        sum+=intpart(n,j)
    return n
#both balls and boxes unlabeled
#injective: each box cannot hold more than 1 ball
def uBalluBoxi(n,k):
    if n<=k: return 1
    else: return 0
#both balls and boxes unlabeled
#surjective: each box has at least one ball
def uBalluBoxs(n,k):
    return intpart(n,k)
#balls unlabeled, boxes labeled
#box can hold any balls
def uBalllBoxa(n,k):
    return ksub(n+k-1,k-1)
#balls unlabeled, boxes labeled
#injective: each box cannot hold more than 1 ball
def uBalllBoxi(n,k):
    return ksub(k,n)
#balls unlabeled, boxes labeled
#surjective: each box has at least one ball
def uBalllBoxs(n,k):
    return ksub(n-1,k-1)