#!/usr/bin/env python3
"""
compute sizes of all connected components.
sort and display.
"""

"""
v1.3: added algorithms for plotting perf in main
      finished comments
      added experimental limits on entries
"""

from timeit import timeit
from sys import argv

from random import random
from math import log 

from geo.point import Point

from math import sqrt
from math import ceil

def load_instance(filename):
    """
    loads .pts file.
    returns distance limit and points.
    """
    with open(filename, "r") as instance_file:
        lines = iter(instance_file)
        distance = float(next(lines))
        points = [Point([float(f) for f in l.split(",")]) for l in lines]

    return distance, points

def init_fenetre(distance):
    """
    on cree une fenetre,sous forme de tableau 2D, constituée de cases dont 
    la diagonale est égale à la distance limite.

    on retourne le pas (la valeur du cote d'une case), le nb de cases et la fenetre
    """
    nb_cases = ceil(1/(distance/sqrt(2)))
    pas = distance/sqrt(2)

    fenetre = [[[] for _ in range(nb_cases)] for _ in range(nb_cases)]
    
    return pas,nb_cases,fenetre

def remplir_cases(fenetre,points,pas, s_explorable):
    """
    on recoit la fenetre vide, les points et un set vide (s_explorable).

    on remplit les points dans leurs case de la fenetre qui correspond.

    on ajoute dans le set les indices d'une case, des que la case est 
    non vide donc explorable.
    """
    for point in points:
        ind_i = int(point.coordinates[0]//pas)
        ind_j = int(point.coordinates[1]//pas)
        fenetre[ind_i][ind_j].append(point)
        
        s_explorable.add((ind_i, ind_j))

def linked(ind_case1, ind_case2, fenetre, distance_lim):
    """
    compare les points 2 a 2 until linked or not
    """
    for point1 in fenetre[ind_case1[0]][ind_case1[1]]:
        for point2 in fenetre[ind_case2[0]][ind_case2[1]]:
            if point1.distance_to(point2) <= distance_lim:
                return True

    return False

def explo(i,j,fenetre, distance_lim, s_explorable):
    """
    on recoit les indices d'une case de fenetre a explorer.

    on va donc explorer les case voisines (avec 2 cases d'ecart, sauf en diagonale) 
    qui sont liees (cad qui ont au moins 2 points lies) et explorable.

    avant d'appeler l'exploration d'une case, on la supprime du set des cases 
    explorables: on ne garde dans s_explorable que les cases explorables (non vides) 
    et non encore explorees.

    finalement on retourne le nombre de points total dans les cases voisines liees.
    """
    taille = 0

    s_to_be_explored = {(i+1,j), (i+1,j+1), (i+1,j-1), \
                        (i,j-1), (i,j+1), \
                        (i-1,j-1), (i-1,j), (i-1, j+1), \
                        (i+2,j), (i+2, j-1), (i+2,j+1), \
                        (i-2,j), (i-2, j+1), (i-2,j-1), \
                        (i,j+2), (i+1, j+2), (i-1,j+2), \
                        (i,j-2), (i+1, j-2), (i-1,j-2)}

    for ind_i, ind_j in s_to_be_explored:
        if (ind_i, ind_j) in s_explorable and \
           linked((i,j), (ind_i, ind_j), fenetre, distance_lim):
            
            s_explorable.remove((ind_i, ind_j))
            taille += len(fenetre[ind_i][ind_j]) + \
                explo(ind_i,ind_j,fenetre, distance_lim, s_explorable)

    return taille

def print_components_sizes(distance, points):
    """
    affichage des tailles triees de chaque composante
    """
    pas, nb_cases, fenetre = init_fenetre(distance)
    s_explorable= set()
    remplir_cases(fenetre,points,pas, s_explorable)

    tailles=[]
    while len(s_explorable) != 0:
        i,j = s_explorable.pop()
        tailles.append(len(fenetre[i][j])+ explo(i,j,fenetre, distance, s_explorable))                
    tailles = list(reversed(sorted(tailles)))
    print(tailles)

def main():
    """
    ne pas modifier: on charge une instance et on affiche les tailles
    """
    
    """ #programme donne pour le leaderboard
    for instance in argv[1:]:
        distance, points = load_instance(instance)
        print_components_sizes(distance, points)
    """

    #programme pour tester l'algo avec un nombre de points et une distance donnes
    
    #conditions sur les limites (dans le cas random):
    #on a seulement une borne sup (plus la distance est petite, moins on aura des points lies et donc on atteindra pas le max de recursion)

    #tests experimentaux
    #d=0.03 nb_points=1000 ok 0.008 10k ok 0.003 100k ok 0.0008 1M ok

    #conclusion: borne sup distance (tres approximatif) autour de 0.03 pour 1000
    #       et on peut la diviser par 10 quand on multiplie le nb de points par 100
    points, distance=[],0.008
    for _ in range(10000):
        points.append(Point([random(),random()]))
        

    print_components_sizes(distance,points)

    
    
    """ #programme pour plot la perf de l'algo, ne pas oublier d'enlever le print dans dans print_components_sizes
    x,y = [],[]
    for i in range(1,100):
        nb_points = 1000*i
        setup = '''
    
points, distance = [], 0.003
     
for _ in range({}):
    points.append(Point([random(),random()]))
'''.format(nb_points)

        x.append(nb_points*log(nb_points))
        y.append(timeit(setup = setup, \
                        stmt = 'print_components_sizes(distance,points)', \
                        globals=globals(), number = 1))

    import matplotlib.pyplot as plt
    plt.plot(x,y)
    
    plt.show()
    """
    
main()
