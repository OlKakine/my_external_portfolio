#! /usr/bin/env python3

from math import sqrt

def g_3or5(n):
    """return every number below n which is a multiple of 3 or 5 """
    i=1
    while i<n:
        if i%3==0 or i%5==0:
            yield i
        i+=1

def g_even_fibo(n):
    """return every even term below n>2 of the fibonacci sequence"""
    a,b=1,2
    yield 2
    i=0
    while b<=n:
        a,b=b,a+b
        if i==2:
            yield b
            i=-1
        i+=1

def g_prime(n,primes):
    """return every prime number below n>3 given a list of already found primes"""
    if primes==[]:
        primes=[3]
    yield 2
    for prime in primes:
        yield prime
        
    for i in filter(lambda x: x%2!=0, range(primes[-1]+1,n+1)):
        is_prime=True
        for prime in primes:
            if i%prime==0:
                is_prime=False
                break
        if is_prime:
            primes+=[i]
            yield i
            
n=600851475143
n=13195
max_prime=0
primes=[3]
while n!=1:
    for prime in g_prime(n,primes):
        if n%prime==0:
            n/=prime
            n=int(n)
            max_prime=prime
            break
print(max_prime)
