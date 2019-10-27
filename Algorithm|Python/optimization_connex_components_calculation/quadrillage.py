"""
quadrillage (cases et bandes)
"""
from math import sqrt

class Case:
    """
    une case contient une liste de Points et les indices de ses voisins liés
    une case appartient a une bande horizontale et verticale
    une case est censée appartenir à une fenetre et avoir deux indices i et j
        partant de 0 qui désignent la place de la case dans le repere classique
        (i vers la droite et j vers le haut)

    for example:

    -create an empty case
    
    my_case = Case()

    -ajouter un Point dans la case

    my_point = Point([2,5])
    my_case.add_point(my_point)
    
    -calculer ses voisins liés (doit être fait après que tout les points de la fenetre soient dans les cases)

    my_case.fill_neighbors()
    """
    def __init__(self):
        self.nb_points = 0
        self.mat_position = [ [False,False], [False,False]]
                                        # si mat_position[0][1] est vrai il y a un point dans
                                        # le coin en haut à gauche de la case
        self.ind_linked_neighbors = []
        self.nb_neighbors = 0
        self.diag_bas = self.diag_haut = self.diag_droite = self.diag_gauche = False
        self.bas = self.haut = self.droite = self.gauche = False

    def add_point(self,x_point,y_point,distance_lim,pas):
        self.nb_points+=1
        i_case = int(x_point//pas)
        j_case = int(y_point//pas)

        distance_lim_diag=distance_lim/(2*sqrt(2))
        
        self.diag_gauche = x_point-i_case*pas-distance_lim_diag < 1e-14
        self.diag_droite = x_point-(i_case+1)*pas+distance_lim_diag > 1e-14

        self.diag_bas = y_point-j_case*pas-distance_lim_diag < 1e-14
        self.diag_haut = y_point-(j_case+1)*pas+distance_lim_diag > 1e-14
        
        #tried to optimize calculs by reusing the diag ones

        self.gauche = not ( not(self.diag_gauche) and (x_point-i_case*pas-distance_lim > 1e-14))
        self.droite = not(not(self.diag_droite) and (x_point-(i_case+1)*pas+distance_lim < 1e-14))
        
        self.bas = not(not(self.diag_bas) and (y_point-j_case*pas-distance_lim > 1e-14))
        self.haut = not(not(self.diag_haut) and (y_point-(j_case+1)*pas+distance_lim < 1e-14))
        
    def add_linked_neighbor(self, ind_linked_neighbor):
        self.ind_linked_neighbors.append(ind_linked_neighbor)
        self.nb_neighbors += 1
