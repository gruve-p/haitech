#count number of partitions of non-neg int n
#into k nonzero parts
#example one partition of 8
#is (4,3,1)
def intpart(n,k):
    if n==k:
        return 1
    elif n<1 or k<1:
        return 0
    else:
        return intpart(n-1,k-1)+intpart(n-k,k)