def g_prime(n,primes):
    """return every prime number below n>3 given a list of already found primes"""
    if primes==[]:
        primes=[3]
        
    for i in filter(lambda x: x%2!=0, range(primes[-1]+1,n+1)):
        is_prime=True
        for prime in primes:
            if i%prime==0:
                is_prime=False
                break
        if is_prime:
            primes+=[i]
    print(sum(primes)+2)

n=2*10**6

marked=[0]*n
value = 3
s = 2
while value < n:
    if marked[value] == 0:
        s += value
        i = value
        while i < n:
            marked[i] = 1
            i += value
    value += 2
print(s)
