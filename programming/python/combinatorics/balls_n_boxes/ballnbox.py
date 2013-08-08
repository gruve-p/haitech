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

def stirling(n,k):
    if n==k:
        return 1
    elif k==0 or k>n:
        return 0
    else:
        return k*stirling(n-1,k) + stirling(n-1,k-1)

def factorial(n):
    if n<2:
        return 1
    else:
        return n*factorial(n-1)

def pkc(n,k):
    result=0
    if n==k and n>=0:
        result=1
    elif (n>=1 and k==0) or k>n or n<1:
        result=0
    else:
        result=(n-1)*pkc(n-1,k)+pkc(n-1,k-1)

    return result

def sscn(n,k):
    return ((-1)**(n-k))*pkc(n,k)
	
def fallfact(x,n):
    result=0
    if n<0:
        return 0
    if n==0:
        return 1
    else:
        for k in range(0,n+1):
            result=result+sscn(n,k)*(x**k)
        return result

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

#balls labeled, boxes unlabeled
#box can hold any balls
def lBalluBoxa(n,k):
    sum=0
    for i in range(1,k+1):
        sum+=stirling(n,i)
    return sum
#balls labeled, boxes unlabeled
#injective: each box cannot hold more than 1 ball
def lBalluBoxi(n,k):
    if n<=k: return 1
    else: return 0
#balls labeled, boxes unlabeled
#surjective: each box has at least one ball
def lBalluBoxs(n,k):
    return stirling(n,k)
#balls labeled, boxes labeled
#box can hold any balls
def lBalllBoxa(n,k):
    return k**n
#balls labeled, boxes labeled
#injective: each box cannot hold more than 1 ball
def lBalllBoxi(n,k):
    return k**fallfact(n)
#balls labeled, boxes labeled
#surjective: each box has at least one ball
def lBalllBoxs(n,k):
    return factorial(k)*stirling(n,k)