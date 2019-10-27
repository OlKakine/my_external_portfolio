#! /usr/bin/env python3

def g_prime(primes):
    """return prime number given a list of already found primes"""
    if primes==[]:
        primes=[3]
    yield 2
    for prime in primes:
        yield prime

    i=primes[-1]+2

    while True:
        is_prime=True
        for prime in primes:
            if i%prime==0:
                is_prime=False
                break
        if is_prime:
            primes+=[i]
            yield i
        i+=2

n=10001
primes=g_prime([])
for i in range(n-1):
    next(primes)
print(next(primes))
