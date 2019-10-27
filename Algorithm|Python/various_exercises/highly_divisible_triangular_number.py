#! /usr/bin/env python3

def g_triangular_nbs():
    i=1
    triangular_nb=i
    while True:
        yield triangular_nb
        i+=1
        triangular_nb+=i

def highly_divisible_triangular_nb(nb_min_divisors):
    for triangular_nb in g_triangular_nbs():
        nb_factors=2
        for factor in range(2,triangular_nb>>1):
            if triangular_nb%factor==0:
                nb_factors+=1
        if nb_factors>=nb_min_divisors:
            return triangular_nb

print(highly_divisible_triangular_nb(500))
