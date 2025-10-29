from upemtk import *
from time import sleep
from random import randint

# dimensions du jeu
taille_case = 15
largeur_plateau = 40  # en nombre de cases
hauteur_plateau = 30  # en nombre de cases


def case_vers_pixel(case):
    """
    Fonction recevant les coordonnées d'une case du plateau sous la 
    forme d'un couple d'entiers (ligne, colonne) et renvoyant les 
    coordonnées du pixel se trouvant au centre de cette case. Ce calcul 
    prend en compte la taille de chaque case, donnée par la variable 
    globale taille_case.
    """
    i, j = case
    return (i + .5) * taille_case, (j + .5) * taille_case


def affiche_pommes(pommes):#fonction qui permet d'afficher les pommes
    for pomme in pommes:
        x, y = case_vers_pixel(pomme)
        cercle(x, y, taille_case/2,
                couleur='darkred', remplissage='red')
        rectangle(x-2, y-taille_case*.4, x+2, y-taille_case*.7,
                 couleur='darkgreen', remplissage='darkgreen')
def affiche_pommes_poi(pommes_poi):
    for poison in pommes_poi :
        x,y = case_vers_pixel(poison)
        cercle(x, y, taille_case/2,
                couleur='darkred', remplissage='darkred')
        rectangle(x-2, y-taille_case*.4, x+2, y-taille_case*.7,
                 couleur='darkgreen', remplissage='darkgreen')

def affiche_serpent(serpent,serpent_2):#fonction qui perment d'afficher le serpent
    for corps in serpent:
        x, y = case_vers_pixel(corps)
        cercle(x, y, taille_case/2 + 1,
               couleur='darkgreen', remplissage='green')
    for corps in serpent_2 : 
        x , y = case_vers_pixel(corps)
        cercle(x, y, taille_case/2 + 1,
               couleur='orange', remplissage='yellow')

def affiche_obstacle(obstacles):# fonction qui perment d'afficher les obstacles
     for obstacle in obstacles:
        x, y = case_vers_pixel(obstacle)
        rectangle(x - 7, y - 7, x + 7, y + 7, couleur='black', remplissage='black')


def change_direction(direction, ancienne_dir, touche):#direction serpent
   
    if touche =='z':
        # flèche haut pressée
        direction = (0, -1)
    elif touche == 's':
        direction = (0, 1)
    elif touche == 'd':
        direction = (1, 0)
    elif touche == 'q':
        direction = (-1, 0)
    if direction[0] == -(ancienne_dir[0]) and direction[1] == -(ancienne_dir[1]):
        direction = ancienne_dir
    return direction

def change_direction_2(direction_2, ancienne_dir_2, touche):#direction serpent joueur2
   
    if touche == 'Up':
        # flèche haut pressée
        direction_2 = (0, -1)
    elif touche == 'Down':
        direction_2 = (0, 1)
    elif touche == 'Right':
        direction_2 = (1, 0)
    elif touche == 'Left':
        direction_2 = (-1, 0)
    if direction_2[0] == -(ancienne_dir_2[0]) and direction_2[1] == -(ancienne_dir_2[1]):
        direction_2 = ancienne_dir_2
    return direction_2

def mouvement_serpent(serpent, direction):
    return [[serpent[0][0]+direction[0], serpent[0][1]+direction[1]]]

def mouvement_serpent_2(serpent_2, direction_2):
    return [[serpent_2[0][0]+direction_2[0], serpent_2[0][1]+direction_2[1]]]

def bordure(serpent):#delimite les contours de la fenetre
    if serpent[0][1] < 1 or serpent[0][1] > hauteur_plateau or serpent[0][0] < 0 or serpent[0][0] > largeur_plateau :  # si le serpent sort de la grille de jeu la fenetre se fermes
        return False
    return True

def ajoute_pomme(pommes, cpt_pommes, serpent,obstacles):#affichage de pommes tous les 30 frame et ce qui ce passe quand le serpent pas sur la pommes
    if cpt_pommes == 40:
        pomme_x = randint(0, largeur_plateau - 1)
        pomme_y = randint(1, hauteur_plateau - 1)
        while([pomme_x, pomme_y] in serpent) or ([pomme_x, pomme_y] in obstacles) :
            pomme_x = randint(1, largeur_plateau - 1)
            pomme_y = randint(1, hauteur_plateau - 1)
        pommes.append([pomme_x, pomme_y])
        cpt_pommes = 0
    cpt_pommes += 1
    return pommes, cpt_pommes

def ajoute_poi(poisons,cpt_poi,serpent,obstacles):
    if cpt_poi == 90 :
        poi_x = randint(1,largeur_plateau-1)
        poi_y = randint(1,hauteur_plateau-1)
        while([poi_x,poi_y] in serpent) or ([poi_x,poi_y] in obstacles) :
            poi_x = randint(1,largeur_plateau)
            poi_y = randint(1,hauteur_plateau)
        poisons.append([poi_x,poi_y])
        cpt_poi = 0
    cpt_poi += 1 
    return poisons,cpt_poi 

def grandir_serpent(serpent, serpent_2, queue, pommes, score):# permet que le serpent grandi
    if serpent[0] in pommes:
        pommes.pop(pommes.index(serpent[0]))
        score += 1
        serpent.append(queue)
    if serpent_2[0] in pommes:
        pommes.pop(pommes.index(serpent_2[0]))
        score += 1
        serpent_2.append(queue)
    return pommes, score
def perte_serpent(serpent,queue,pommes_poi,score,jouer):
    if len(serpent) > 1 : 
        if serpent[0] in pommes_poi :
            pommes_poi.pop(pommes_poi.index(serpent[0]))
            score -= 1
            serpent.pop()
    elif len(serpent) == 1 :
        if serpent[0] in pommes_poi : 
            jouer = False 
    return pommes_poi,serpent,score ,jouer 

def ajoute_obstacle(obstacles, cpt_obstacles): #ajout d'un obstacle tous les 60 frame
    if cpt_obstacles == 60:
        obstacle_x = randint(0, largeur_plateau - 1)
        obstacle_y = randint(1, hauteur_plateau)
        while ([obstacle_x, obstacle_y] in serpent):
            obstacle_x = randint(0, largeur_plateau - 1)
            obstacle_y = randint(1, hauteur_plateau)
        obstacles.append([obstacle_x, obstacle_y])
        cpt_obstacles = 0
    cpt_obstacles += 1
    return obstacles, cpt_obstacles

def corps_suittete(serpent): #faire en sorte que le corps suive la tête du serpent
    serpent = mouvement_serpent(serpent, direction) + serpent
    serpent.pop(len(serpent)-1)
    return serpent
def corps_suittete_2(serpent_2):
    serpent_2 = mouvement_serpent_2(serpent_2, direction_2) + serpent_2
    serpent_2.pop(len(serpent_2)-1)
    return serpent_2

def se_mange(serpent=[1], serpent_2=[1]):#fonction au cas ou le serpent se mange lui même
    if serpent.count(serpent[0]) > 1:
        return False
    elif serpent_2.count(serpent_2[0]) > 1:
        return False
    return True

def colision(serpent, serpent_2):
    if serpent.count(serpent_2[0]) == 1:
        return False
    elif serpent_2.count(serpent[0]) == 1:
        return False

# programme principal
if __name__ == "__main__":

    # initialisation du jeu
    framerate = 10  # taux de rafraîchissement du jeu en images/s
    direction = (0, 0)  # direction initiale du serpent
    direction_2 = (0, 0)
    ancienne_dir = (0, 0)
    ancienne_dir_2 = (0, 0)
    pommes = [] # liste des coordonnées des cases contenant des pommes
    obstacles = []# liste des coordonnées des cases contenant des obstacles
    serpent = [[5, 10]]
    serpent_2 = [[35,10]] # liste des coordonnées de cases adjacentes décrivant le serpent
    poisons = [] # liste des coordonnées des pommes empoisonnées 
    cpt_pommes = 40
    cpt_obstacles = 60
    cpt_poi = 0
    score = 0
    cree_fenetre(taille_case * (largeur_plateau),
                 taille_case * (hauteur_plateau))

    # boucle principale
    jouer = True
    while jouer:
        # affichage des objets
        efface_tout()
        texte(450, 0, " score="+str(score), couleur="red", taille=15) # texte qui affiche le score dans la fenetre
        pommes, cpt_pommes = ajoute_pomme(pommes, cpt_pommes, serpent,obstacles)
        obstacles, cpt_obstacles = ajoute_obstacle(obstacles, cpt_obstacles)
        pommes_poi , cpt_poi = ajoute_poi(poisons,cpt_poi,serpent,obstacles)
       # framerate= accelere(framerate,score)
        if(direction == (0, 0)):
            cpt_pommes = 0
            cpt_obstacles = 0
            texte((largeur_plateau*taille_case)/2, (hauteur_plateau*taille_case)/4, ('Appuyez sur la fenêtre puis une touche directionel pour commencer pour commencer'), couleur='black', ancrage='center', taille=12, tag='')
        affiche_pommes_poi(poisons)
        affiche_pommes(pommes) 
        affiche_serpent(serpent,serpent_2)
        affiche_obstacle(obstacles)
        #accelere(framerate,score)
        mise_a_jour()

        # gestion des événements
        ev = donne_ev()
        ty = type_ev(ev)
        if ty == 'Quitte':
            jouer = False
        elif ty == 'Touche':
            print(touche(ev))
            direction = change_direction(direction, ancienne_dir, touche(ev))#si on appuis sur une touche qui commande l'inverse de la direction du serpent le serpent va continuer dans la direction qu'il avait
            direction_2 = change_direction_2(direction_2, ancienne_dir_2, touche(ev))
            if direction != ancienne_dir:
                ancienne_dir = direction
            if direction_2 != ancienne_dir_2:
                ancienne_dir_2 = direction_2
        #if (bordure(serpent) and se_mange(serpent) and not (serpent[0] in obstacles)) == False:
        if bordure(serpent) == False or bordure(serpent_2) == False :    
            jouer = False
        elif se_mange(serpent) == False or se_mange(serpent_2) == False :
            jouer = False
        elif (serpent[0] in obstacles) == True or (serpent_2[0] in obstacles) == True:
            jouer = False
        elif colision(serpent, serpent_2) == False:
            jouer = False
            
        queue = serpent[len(serpent)-1]#queue du serpent
        pommes, score = grandir_serpent(serpent, serpent_2, queue, pommes, score)
        pommes_poi,serpent,score,jouer = perte_serpent(serpent,queue,pommes_poi,score,jouer)
        serpent = corps_suittete(serpent)# la sueue suit la tete
        serpent_2 = corps_suittete_2(serpent_2)

        # attente avant rafraîchissement
        sleep(1/framerate)
    efface_tout()
    texte((largeur_plateau*taille_case)/2, (hauteur_plateau*taille_case)/2,('Dommage','votre','score','est','de', score), couleur='black', ancrage='center', taille=20, tag='')
    mise_a_jour()
    attend_fermeture()