/****************************************************************************************************************************/
/*																															*/
/*  Ce programme est un ensemble de sous-programmes qui ont pour but d'effectué divers traitement et analyse d'image		*/
/*																															*/
/*																															*/
/*	Methode:	Selon le choix de l'utilisateur le programme principale appel la fonction qui lui est associer.				*/
/*				On a une chaine de caractère qui va contenir le nom de l'image à traiter, et une commande systeme			*/
/*				qui va afficher les fichier bmp dans le repertoire courant. Selon le choix de traiment le nom de l'image	*/
/*				sera passé en argument du sous programme choisie															*/
/*																															*/
/*																															*/
/*	Résultat obtenu: 	Les sous-programmes fonctionnent tous.																*/
/*						Le sous-programme Etiqueter ne fonctionne pas sur les images avec trop de formes la pile n'est pas  */	
/*						assez grande. De plus le bruit est détecter comme une forme.										*/
/*																															*/
/*	Visual Studio 2022																										*/
/*	22 septembre 2023								édité le 03 Fevrier 2025												*/
/*	BERNARD Alexy																											*/
/****************************************************************************************************************************/


//Résultats obtenus : Les sous-programmes fonctionnent tous.


#include "BERNARD_TD_Image.h"
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<conio.h>



void main()
{
	int Choix = -1;
	char img[20];
	struct fichierimage* fichier = NULL;
	struct fichierimage* fichier_1 = NULL;

	//Affiche les fichier .bmp du répertoire courant
	system("dir *.bmp");

	printf("\tNom de l'image a utiliser (sans .bmp): ");
	scanf("%s", img);
	strcat(img, ".bmp");
	printf("%s",img);
	
	printf("\n");
		

	
	do{		
			fichier = charger(img);
			printf("\n\n");
			printf("* * * * * * * * * * Menu * * * * * * * * * *\n");
			printf("\t0. Effectuer une binarisation.\n");
			printf("\t1. Appliquer un effet niveau de gris.\n");
			printf("\t2. Appliquer un effet miroir.\n");
			printf("\t3. Appliquer un effet sym%ctrique.\n", 130);
			printf("\t4. Pivoter l'image.\n");
			printf("\t8. Transformation monochromatique.\n");
			printf("\t9. Inversion des couleurs.\n");
			printf("\t11. Effectuer une r%cduction.\n", 130);
			printf("\t12. Effectuer un agrandissement.\n");
			printf("\t13. Affichage d'histogramme.\n");
			printf("\t14. Appliquer un filtre n%cgatif.\n", 130);
			printf("\t15. Modifier la luminosit%c de l'image.\n", 130);
			printf("\t17. Convolution.\n");
			printf("\t23. (tp) Superpostion.\n");
			printf("\t22. Filtre moyenneur.\n");
			printf("\t25. (tp) Egalisation d'histogramme.\n");
			printf("\t26. (tp) Ettiqueter.\n");
			printf("\t27. (tp) Calculer l'aire d'une formes.\n");
			printf("\t-1. Quitter\n");
			printf("\n\n");
			printf("* * * * * Choisissez une action * * * * * *\n");
			printf("\t");
			scanf_s("%d", &Choix);
			printf("\n");

			

			switch (Choix) 
			{	
				case 0 : 
					Binarisation(fichier);
					break;

				case 1 : 
					Niveau_Gris(fichier);
					break; 

				case 2 :					
					Miroir(fichier);
					break;

				case 3 :					
					Symetrie(fichier);
					break;

				case 4 :
					Pivot(fichier);
					break;

				case 5 :
					
					break;

				case 6 :

					break;

				case 7 : 
					
					break;

				case 8 : 
					Monochrome(fichier);
					break;

				case 9 :
					Inversion(fichier);
					break;

				case 10 : 
					
					break;

				case 11 : 
					Reduction(fichier);
					break;

				case 12 :
					Agrandissement(fichier);
					break;

				case 13 :
					Histogramme(fichier);
					break;

				case 14:
					Negatif(fichier);
					break;

				case 15:
					Luminosite(fichier);
					break;

				case 17:
					Convolution(fichier);
					break;

				case 22:
					Filtre_Moy(fichier);
					break;

				case 23:
					Superposition(fichier);
					break;
				
				case 25:
					Egalisation_Histogramme(fichier);
					break;

				case 26:
					Etiqueter(fichier);
					break;

				case 27:
					Moments(fichier);
					break;

				default:
					Choix = -1;
					printf("fermeture");
					break;
			}
	}while (Choix >= 0);
	char command[256];
	snprintf(command, sizeof(command), "start %s", img);
	system(command);
}