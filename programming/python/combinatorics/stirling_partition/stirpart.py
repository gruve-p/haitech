#!/usr/bin/env python

#how many ways to partition [n] into k cells
#each cell are mutex and their union is [n]
def stirling(n,k):
    if n==k:
        return 1
    elif k==0 or k>n:
        return 0
    else:
        return k*stirling(n-1,k) + stirling(n-1,k-1)

#number of surjective mappings from n-set to k-set
def mapn2k(n,k):
    return factorial(k)*stirling(n,k)