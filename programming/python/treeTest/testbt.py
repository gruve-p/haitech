#!/usr/bin/env python

import sys,timeit
PYPY = hasattr(sys, 'pypy_version_info')

#import pickle

from random import randint, shuffle

from bintrees import BinaryTree, AVLTree, RBTree

#searching for 200 keys
def testSearchBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
mytree=BinaryTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
for i in range(200):
    mytree.get(randint(0,TSIZE*10),9999)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 100) / 100
    #print 'testing BT searchx200,ts =',tsize
    #print "%.6f ms/run" % (rtime)
    print tsize,rtime

def testSearchAVLT(tsize):
    setup = """\
from bintrees import AVLTree
from random import randint,sample
mytree=AVLTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
for i in range(200):
    mytree.get(randint(0,TSIZE*10),9999)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 100) / 100
    print tsize,rtime

def testSearchRBT(tsize):
    setup = """\
from bintrees import RBTree
from random import randint,sample
mytree=RBTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
for i in range(200):
    mytree.get(randint(0,TSIZE*10),9999)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 100) / 100
    print tsize,rtime

def testInsertBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
mytree=BinaryTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
insData=[(randint(0,TSIZE*10), randint(0,TSIZE*10)) for i in range(100)]
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
mytree.update(insData)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    bTime=float(t.timeit(number = 1)*1000)
    return bTime

def runTestInsertBT(tsize,times):
    rtime=0.0
    # testInsertBT(tsize)
    for i in range(times):
        rtime+=testInsertBT(tsize)
    rtime=float(rtime/times)
    #print 'testing BT insertx200,ts =',tsize
    #print "%.6f ms/run"  % rtime
    print tsize,rtime

def testInsertAVLT(tsize):
    setup = """\
from bintrees import AVLTree
from random import randint,sample
mytree=AVLTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
insData=[(randint(0,TSIZE*10), randint(0,TSIZE*10)) for i in range(100)]
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
mytree.update(insData)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    avlTime=float(t.timeit(number = 1)*1000)
    return avlTime
    

def runTestInsertAVLT(tsize,times):
    rtime=0.0
    testInsertAVLT(tsize)
    for i in range(times):
        rtime+=testInsertAVLT(tsize)
    rtime=float(rtime/times)
    #print 'testing AVLT insertx200,ts =',tsize
    #print "%.6f ms/run"  % rtime
    print tsize,rtime

def testInsertRBT(tsize):
    setup = """\
from bintrees import RBTree
from random import randint,sample
mytree=RBTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
insData=[(randint(0,TSIZE*10), randint(0,TSIZE*10)) for i in range(100)]
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
mytree.update(insData)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    runTime=float(t.timeit(number = 1)*1000)
    return runTime    

def runTestInsertRBT(tsize,times):
    rtime=0.0
    for i in range(times):
        rtime=rtime+testInsertRBT(tsize)
    rtime=float(rtime/times)
    #print 'testing RBT insertx200,ts =',tsize
    #print "%.6f ms/run"  % rtime
    print tsize,rtime

def testCopyBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
mytree=BinaryTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
newtree=mytree.copy()
    """
    t = timeit.Timer(stmt=test, setup=setup)
    print 'testing copy,ts =',tsize
    print "%.2f ms/run" % (1000 * t.timeit(number = 100) / 100)

def testDeleteBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
mytree=BinaryTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
keystodel=sample(keys, 100)
mytree.update(mydata)
""" % tsize
    test = """\
for kd in keystodel:
    del mytree[kd]
    """
    t = timeit.Timer(stmt=test, setup=setup)
    deltime = t.timeit(number = 1) * 1000
    return float(deltime)

def runTestDeleteBT(tsize,times):
    rtime=0.0
    for ii in range(times):
        rtime+=testDeleteBT(tsize)
    rtime=float(rtime/times)
    #print 'test deletex200 bt,ts =',tsize
    #print "%.6f ms/run" % rtime
    print tsize,rtime

def testDeleteAVLT(tsize):
    setup = """\
from bintrees import AVLTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
keystodel=sample(keys, 100)
mytree = AVLTree()
mytree.update(mydata)
""" % tsize
    test = """\
for kd in keystodel:
    mytree.pop(kd)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    #del mytree[kd]
    deltime = t.timeit(number = 1) * 1000
    return float(deltime)

def runTestDeleteAVLT(tsize,times):
    rtime=0.0
    for ii in range(times):
        rtime+=testDeleteAVLT(tsize)
    rtime=float(rtime/times)
    print tsize,rtime

def testADeleteRBT(tsize):
    from bintrees import RBTree
    from time import time
    from random import randint,sample
    TSIZE=tsize
    keys=sample(range(TSIZE*10), TSIZE)
    values=[0]*TSIZE
    mydata=list(zip(keys, values))
    keystodel=sample(keys, 100);valdel=[0]*100
    datadel=list(zip(keystodel, valdel))
    mytree = RBTree()
    mytree.update(mydata)

    avgtime=0.0;times=100
    for ii in range(times):
        startTime=time()
        for kd in keystodel:
            #mytree.pop(kd)
            del mytree[kd]
        avgtime+=(time()-startTime)
        mytree.update(datadel)
    avgtime=avgtime*1000.0/times
    print tsize,float(avgtime)
    return avgtime
    
def testDeleteRBT(tsize):
    setup = """\
from bintrees import RBTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
keystodel=sample(keys, 100)
mytree = RBTree()
mytree.update(mydata)
""" % tsize
    test = """\
for kd in keystodel:
    mytree.pop(kd)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    #del mytree[kd]
    deltime = t.timeit(number = 1) * 1000
    return float(deltime)
    
def runTestDeleteRBT(tsize,times):
    rtime=0.0
    for ii in range(times):
        rtime+=testDeleteRBT(tsize)
    rtime=float(rtime/times)
    print tsize,rtime
    
def testGetKeysBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
mytree=BinaryTree()
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree.update(mydata)
"""
    setup=setup % (tsize)
    test = """\
for i in range(500):
    mytree.keys(reverse=True)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    print 'testing allkeysx500,ts =',tsize
    print "%.2f ms/run" % (1000 * t.timeit(number = 100) / 100)

#this should fail bc of recursion depth
def testSortedKeyBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
TSIZE=%d
keys=[k for k in range(TSIZE)]
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
""" % tsize
    test = """\
mytree=BinaryTree()
mytree.update(mydata)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testBuildBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
""" % tsize
    test = """\
mytree=BinaryTree()
mytree.update(mydata)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testCopyBT(tsize):
    setup = """\
from bintrees import BinaryTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree=BinaryTree()
mytree.update(mydata)
""" % tsize
    test = """\
cptree=mytree.copy()
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

#verify if avl can easily balance itself
def testSortedKeyAVLT(tsize):
    setup = """\
from bintrees import AVLTree
from random import randint,sample
TSIZE=%d
keys=[k for k in range(TSIZE)]
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
""" % tsize
    test = """\
mytree=AVLTree()
mytree.update(mydata)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testBuildAVLT(tsize):
    setup = """\
from bintrees import AVLTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
""" % tsize
    test = """\
mytree=AVLTree()
mytree.update(mydata)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testCopyAVLT(tsize):
    setup = """\
from bintrees import AVLTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree=AVLTree()
mytree.update(mydata)
""" % tsize
    test = """\
cptree=mytree.copy()
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testSortedKeyRBT(tsize):
    setup = """\
from bintrees import RBTree
from random import randint,sample
TSIZE=%d
keys=[k for k in range(TSIZE)]
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
""" % tsize
    test = """\
mytree=RBTree()
mytree.update(mydata)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testBuildRBT(tsize):
    setup = """\
from bintrees import RBTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
""" % tsize
    test = """\
mytree=RBTree()
mytree.update(mydata)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testCopyRBT(tsize):
    setup = """\
from bintrees import RBTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
mytree=RBTree()
mytree.update(mydata)
""" % tsize
    test = """\
cptree=mytree.copy()
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def testInsertSameKeyRBT(tsize):
    setup = """\
from bintrees import FastRBTree
from random import randint,sample
TSIZE=%d
keys=sample(range(TSIZE*10), TSIZE)
values=[randint(0,TSIZE*10) for r in range(TSIZE)]
mydata=list(zip(keys, values))
iddata=sample(mydata, 111)
mytree=FastRBTree()
mytree.update(mydata)
""" % tsize
    test = """\
mytree.update(iddata)
print 'lenoftree',len(mytree)
    """
    t = timeit.Timer(stmt=test, setup=setup)
    rtime=1000 * t.timeit(number = 1) / 1
    print tsize,rtime

def genkeys():
    TSIZE=2^15
	tkeys=sample(range(TSIZE*10), TSIZE)
    skeys=sample(tkeys,100)
    import cPickle
	cPickle.dump(tkeys, open('tkeys.txt', 'wb'))
	cPickle.dump(tkeys, open('skeys.txt', 'wb'))

if __name__ == '__main__':
    mini,maxi=2**10,2**16
    ########test searching
    # print 'BTSearch';sys.stdout.flush();
    # for i in range(mini,maxi,(maxi-mini)/128):
        # testSearchBT(i)
    # print 'AVLTSearch'
    # for i in range(mini,maxi,(maxi-mini)/128):
        # testSearchAVLT(i)
    # print 'RBTSearch'
    # for i in range(mini,maxi,(maxi-mini)/128):
        # testSearchRBT(i)
    
    ########test insert
    # print 'BTInsert';sys.stdout.flush();
    # testInsertBT(mini)
    # for i in range(mini,maxi,(maxi-mini)/128):
        # runTestInsertBT(i,100)
    # print 'AVLTInsert';testInsertAVLT(mini)
    # for i in range(mini,maxi,(maxi-mini)/128):
        # runTestInsertAVLT(i,100)
    # print 'RBTInsert';testInsertRBT(mini)
    # for i in range(mini,maxi,(maxi-mini)/128):
        # runTestInsertRBT(i,100)
    ########test delete
    # print 'BTDelete';testDeleteBT(mini)
    # for i in range(mini,maxi,(maxi-mini)/128):
        # runTestDeleteBT(i,100)
    # print 'AVLTDelete';testDeleteAVLT(mini)
    for i in range(mini,maxi,(maxi-mini)/128):
        runTestDeleteAVLT(i,30)
    # print 'RBTDelete'
    # testDeleteRBT(mini)
    # for i in range(mini,maxi,(maxi-mini)/128):
        # runTestDeleteRBT(i,30)
    #####RBTDelete logscale
    # testDeleteRBT(mini);nbase=pow(2,float(1)/4);imin=10*4;imax=20*4
    # for i in range(imin,imax):
        # runTestDeleteRBT(int(nbase**i),10)
    #####new method to test RBTDel
    # for i in range(mini,maxi,(maxi-mini)/128):
        # testADeleteRBT(i)
    
    # print 'BTBuild'
    # for i in range(2**mini,2**maxi,(2**maxi-2**mini)/40):
        # testInsertSameKeyRBT(i)
    #print 'BTBuild'
    #for i in range(mini,maxi):
        #testBuildBT(2**i)
    #print 'AVLTBuild'
    #for i in range(mini,maxi):
        #testBuildAVLT(2**i)
    # print 'RBTBuild'
    # for i in range(mini,maxi):
        # testBuildRBT(2**i)
    # print 'BTSortedKey'
    # for i in range(mini,maxi):
        # testSortedKeyBT(2**i)
    # print 'BTCopy'
    # for i in range(mini,maxi):
        # testCopyBT(2**i)
    # print 'AVLTCopy'
    # for i in range(mini,maxi):
        # testCopyAVLT(2**i)
    # print 'RBTCopy'
    # for i in range(mini,maxi):
        # testCopyRBT(2**i)
    # print 'AVLTSortedKey'
    # for i in range(mini,maxi):
        # testSortedKeyAVLT(2**i)
    # print 'RBTSortedKey'
    # 