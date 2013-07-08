#!/usr/bin/env python

#find number of derangement of [n]
#a derangement is a permutation of the elements of a set such that
#none of the elements appear in their original position.

def factorial(n):
    if n<2:
        return 1
    else:
        return n*factorial(n-1)

def derange(n):
    result=1;
    if n>0:
        result=0
        for i in range(0,n+1):
            result=result+((-1)**i)*1.0/factorial(i)
        result=result*factorial(n)
    return result