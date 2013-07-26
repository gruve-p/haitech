#!/usr/bin/env python

#solve n queens problem with lp_solve

#create lp file
#./nqueens.py > nqueens.lp
#solve with lp_solve
#lp_solve nqueens.lp

def queeni(n):
    return 'q'+str(n)

def qdiff(a,b):
    return 'd_'+str(a)+'_'+str(b)

def ne(a,b):
    return 'ne_'+str(a)+'_'+str(b)
	
def se(a,b):
    return 'se_'+str(a)+'_'+str(b)

def declare(n):
    mystr='int '
    for i in xrange(1,n+1):
        mystr+=queeni(i)
        if i<n: mystr+=','
    mystr+=';'
    print mystr
    mystr='bin '
    for i in xrange(1,n+1):
        for j in xrange(i+1,n+1):
            mystr += (qdiff(i,j)+','+ne(i,j)+','+se(i,j))
            if i!=(n-1) or j!=n: mystr+=','
    mystr+=';'
    print mystr

def qinit(n):
    # objective='min: '
    # for i in xrange(1,n+1):
        # objective+=queeni(i)
        # if i<n: objective+=' + '
    # objective+=';'
    # objective='min: q1;'
    objective='min: d_1_2;'
    # objective='min: ne_1_2;'
    # objective='min: se_1_2;'
    print objective
    for i in xrange(1,n+1):
        mystr='1 <= ' + queeni(i) +' <= '+str(n)+';'
        print mystr
    

def alldiff(n):
    for i in xrange(1,n+1):
        for j in xrange(i+1,n+1):
            mystr=queeni(i)+' - '+queeni(j)+' + '+str(n)+' * '+qdiff(i,j)+' >= 1;'
            print mystr
            mystr=queeni(i)+' - '+queeni(j)+' + '+str(n)+' * '+qdiff(i,j)+' <= '+str(n-1)+';'
            print mystr
            

def diagon(n):
    for i in xrange(1,n+1):
        for j in xrange(i+1,n+1):
            mystr=queeni(j)+' - '+queeni(i)+' + '+str(j-i+n)+' * '+ne(i,j)+' >= ' + str(j-i+1) +';'
            print mystr
            mystr=queeni(j)+' - '+queeni(i)+' + '+str(j-i+n)+' * '+ne(i,j)+' <= ' + str(n-1+2*j-2*i) +';'
            print mystr
            mystr=queeni(j)+' - '+queeni(i)+' + '+str(j-i+n)+' * '+se(i,j)+' >= ' + str(i-j+1) +';'
            print mystr
            mystr=queeni(j)+' - '+queeni(i)+' + '+str(j-i+n)+' * '+se(i,j)+' <= ' + str(n-1) +';'
            print mystr

def nqueen(n):
    qinit(n)
    alldiff(n)
    diagon(n)
    declare(n)

nqueen(9)