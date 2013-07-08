#!/usr/bin/env python

#binomial coefficient
def ksub(n,k):
    if k<=0 or k==n:
        return 1
    elif k<0 or n<0 or k>n:
        return 1
    else:
        return (ksub(n-1,k-1)+ksub(n-1,k))

#how many ways to partition [n] into k cells
#each cell are mutex and their union is [n]
def stirling(n,k):
    if n==k:
        return 1
    elif k==0 or k>n:
        return 0
    else:
        return k*stirling(n-1,k) + stirling(n-1,k-1)

#bell number
#how many way to parition [n]
#into any number of cells
def bell(n):
    bn=1
    if n>1:
        bn=0
        for j in range(0,n+1):
            bn=bn+stirling(n,j)
    return bn
#bell recursive formula
def bellRecur(n):
    sum=0
    if n==0 or n==1: return 1
    for i in xrange(1,n+1):
        sum+= ksub(n-1,i-1)*bellRecur(n-i)
    return sum
