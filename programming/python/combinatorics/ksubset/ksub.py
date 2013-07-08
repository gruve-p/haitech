#!/usr/bin/env python

#find number of ksubset of [n]

def ksub(n,k):
    if k<=0 or k==n:
        return 1
    elif k<0 or n<0 or k>n:
        return 1
    else:
        return (ksub(n-1,k-1)+ksub(n-1,k))