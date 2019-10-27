#! /usr/bin/env python3

def is_palyndrome(n):
    """return true if n is a palyndrome integer"""
    str_n = str(n)
    for i in range(len(str_n)//2):
        if str_n[i]!=str_n[-1-i]:
            return False
    return True

def largest_palindrome_product(nb_factor,nb_digit):
    '''return the largest palindrome made from the product of nb_factor of nb_digit'''
    largest=0
    for a in range(999,900,-1):
        for b in range(999,900,-1):
            c=a*b
            if c>largest and is_palyndrome(c):
                largest=c
    print(largest)

largest_palindrome_product(0,0)
        
