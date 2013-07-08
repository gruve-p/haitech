#!/usr/bin/env python

#x^(_n)=x(x-1)...(x-n+1)
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