#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<conio.h>

// structure d'entete du fichier
struct entete_fichier
       {
       char idformat[2];
       int taille_fichier;
       int reserve;
       int debut;
       };

// structure d'entete de l'image
struct entete_bmp
       {
       int taille_image;
       int largeur;
       int alignement;
       int hauteur;
       short plans;
       short profondeur;
       int compression;
       int taille_image_totale;
       int resolutionh;
       int resolutionv;
       int nbrcouleur;
       int nbrcouleuri;
       };

// structure d'un pixel
struct pixels
       {
       unsigned char b;
       unsigned char g;
       unsigned char r;
       };

// structure du fichier
struct fichierimage
       {
       struct entete_fichier entetefichier;
       struct entete_bmp entetebmp;
       struct pixels image[5000][5000];
       };

struct fichierimage *charger(char *nom)
{
FILE *f;
int i,j,k;
unsigned char zero;
unsigned char *buffer;
int position=0;
int longueur=0;
struct fichierimage *fichier=(struct fichierimage *)malloc(sizeof(struct fichierimage));

f=fopen(nom,"rb");
fseek(f,0,SEEK_END);
longueur=ftell(f);
fseek(f,0,SEEK_SET);
buffer=(unsigned char *)malloc(longueur*sizeof(unsigned char));
fread((unsigned char *)buffer,1,longueur,f);
fclose(f);

// lecture de l'entete du fichier

memcpy(&fichier->entetefichier.idformat,(buffer+position),2);
position+=2;
memcpy(&fichier->entetefichier.taille_fichier,(buffer+position),4);
position+=4;
memcpy(&fichier->entetefichier.reserve,(buffer+position),4);
position+=4;
memcpy(&fichier->entetefichier.debut,(buffer+position),4);
position+=4;

/*
printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
printf("reserve                  :%d\n",fichier->entetefichier.reserve);
printf("debut                    :%d\n",fichier->entetefichier.debut);
*/

// lecture de l'entete de l'image

memcpy(&fichier->entetebmp.taille_image,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.largeur,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.hauteur,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.plans,(buffer+position),2);
position+=2;
memcpy(&fichier->entetebmp.profondeur,(buffer+position),2);
position+=2;
memcpy(&fichier->entetebmp.compression,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.taille_image_totale,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.resolutionh,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.resolutionv,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.nbrcouleur,(buffer+position),4);
position+=4;
memcpy(&fichier->entetebmp.nbrcouleuri,(buffer+position),4);
position+=4;

/*
printf("taille image             :%d\n",fichier->entetebmp.taille_image);
printf("largeur                  :%d\n",fichier->entetebmp.largeur);
printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
printf("plans                    :%d\n",fichier->entetebmp.plans);
printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
printf("compression              :%d\n",fichier->entetebmp.compression);
printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
*/

if(fichier->entetebmp.plans!=1||fichier->entetebmp.profondeur!=24||fichier->entetebmp.compression!=0||fichier->entetebmp.nbrcouleur!=0||fichier->entetebmp.nbrcouleuri!=0)
{
printf("Impossible de charger l'image\n");
free(fichier);
free(buffer);
return 0;
}

// mise de l'image en memoire

for(i=fichier->entetebmp.hauteur-1;i>=0;i--)
{
for(j=0;j<fichier->entetebmp.largeur;j++)
                                {
                                memcpy(&fichier->image[i][j].b,(buffer+position),1);
                                position+=1;
                                memcpy(&fichier->image[i][j].g,(buffer+position),1);
                                position+=1;
                                memcpy(&fichier->image[i][j].r,(buffer+position),1);
                                position+=1;
                                }
for(k=0;k<fichier->entetebmp.largeur%4;k++)
                                           {
                                           memcpy(&zero,(buffer+position),1);
                                           position+=1;
                                           }
}

free(buffer);
return fichier;
}

int enregistrer(char *nom,struct fichierimage *fichier)
{
FILE *f;
int i,j,k;
unsigned char zero=(unsigned char)0;
unsigned char *buffer;
int position=0;
int longueur=14+fichier->entetefichier.taille_fichier;
buffer=(unsigned char *)malloc(longueur*sizeof(unsigned char));

// ecriture de l'entete du fichier

/*
printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
printf("reserve                  :%d\n",fichier->entetefichier.reserve);
printf("debut                    :%d\n",fichier->entetefichier.debut);
*/

memcpy((buffer+position),&fichier->entetefichier.idformat,2);
position+=2;
memcpy((buffer+position),&fichier->entetefichier.taille_fichier,4);
position+=4;
memcpy((buffer+position),&fichier->entetefichier.reserve,4);
position+=4;
memcpy((buffer+position),&fichier->entetefichier.debut,4);
position+=4;

// ecriture de l'entete de l'image

/*
printf("taille image             :%d\n",fichier->entetebmp.taille_image);
printf("largeur                  :%d\n",fichier->entetebmp.largeur);
printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
printf("plans                    :%d\n",fichier->entetebmp.plans);
printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
printf("compression              :%d\n",fichier->entetebmp.compression);
printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
*/

memcpy((buffer+position),&fichier->entetebmp.taille_image,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.largeur,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.hauteur,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.plans,2);
position+=2;
memcpy((buffer+position),&fichier->entetebmp.profondeur,2);
position+=2;
memcpy((buffer+position),&fichier->entetebmp.compression,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.taille_image_totale,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.resolutionh,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.resolutionv,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.nbrcouleur,4);
position+=4;
memcpy((buffer+position),&fichier->entetebmp.nbrcouleuri,4);
position+=4;

if(fichier->entetebmp.plans!=1||fichier->entetebmp.profondeur!=24||fichier->entetebmp.compression!=0||fichier->entetebmp.nbrcouleur!=0||fichier->entetebmp.nbrcouleuri!=0)
{
printf("Impossible d'enregistrer l'image\n");
free(buffer);
return 0;
}

for(i=fichier->entetebmp.hauteur-1;i>=0;i--)
{
for(j=0;j<fichier->entetebmp.largeur;j++)
                                {
                                memcpy((buffer+position),&fichier->image[i][j].b,1);
                                position+=1;
                                memcpy((buffer+position),&fichier->image[i][j].g,1);
                                position+=1;
                                memcpy((buffer+position),&fichier->image[i][j].r,1);
                                position+=1;
                                }
for(k=0;k<fichier->entetebmp.largeur%4;k++)
                                           {
                                           memcpy((buffer+position),&zero,1);
                                           position+=1;
                                           }
}

f=fopen(nom,"wb");
fwrite((unsigned char *)buffer,1,longueur,f);
fclose(f);
free(buffer);
return 1;
}

struct fichierimage *nouveau(int largeur,int hauteur)
{
int i,j;
struct fichierimage *fichier;
int longueur;

if(largeur>5000||hauteur>5000||largeur<=0||hauteur<=0)
	{
	return(NULL);
	}

longueur=14+40+3*largeur*hauteur+(largeur%4)*hauteur;
fichier=(struct fichierimage *)malloc(sizeof(struct fichierimage));

// ecriture de l'entete du fichier

fichier->entetefichier.idformat[0]='B';
fichier->entetefichier.idformat[1]='M';
fichier->entetefichier.taille_fichier=40+3*largeur*hauteur+(largeur%4)*hauteur;
fichier->entetefichier.reserve=0;
fichier->entetefichier.debut=54;

// ecriture de l'entete de l'image

fichier->entetebmp.taille_image=40;
fichier->entetebmp.largeur=largeur;
fichier->entetebmp.hauteur=hauteur;
fichier->entetebmp.plans=1;
fichier->entetebmp.profondeur=24;
fichier->entetebmp.compression=0;
fichier->entetebmp.taille_image_totale=40+3*largeur*hauteur+(largeur%4)*hauteur;
fichier->entetebmp.resolutionh=1;
fichier->entetebmp.resolutionv=1;
fichier->entetebmp.nbrcouleur=0;
fichier->entetebmp.nbrcouleuri=0;

// lecture de l'ente du fichier

/*
printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
printf("reserve                  :%d\n",fichier->entetefichier.reserve);
printf("debut                    :%d\n",fichier->entetefichier.debut);
*/

// lecture de l'ente de l'image

/*
printf("taille image             :%d\n",fichier->entetebmp.taille_image);
printf("largeur                  :%d\n",fichier->entetebmp.largeur);
printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
printf("plans                    :%d\n",fichier->entetebmp.plans);
printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
printf("compression              :%d\n",fichier->entetebmp.compression);
printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
*/

// mise de l'image en memoire

for(i=fichier->entetebmp.hauteur-1;i>=0;i--)
{
for(j=0;j<fichier->entetebmp.largeur;j++)
                                {
                                fichier->image[i][j].b=0;
                                fichier->image[i][j].g=0;
                                fichier->image[i][j].r=0;
                                }
}

return fichier;
}

// 0-
void Binarisation(struct fichierimage* fichier) {
	printf("\tBinarisation\n");
	int i, j, niv_gris, moy = 0;
	for (i = 0; i < fichier->entetebmp.hauteur; i++) {
		for (j = 0; j < (fichier->entetebmp.largeur); j++)
		{
			niv_gris = (fichier->image[i][j].r + fichier->image[i][j].g + fichier->image[i][j].b) / 3;
			moy += niv_gris;
		}
	}
	moy = moy / (fichier->entetebmp.hauteur * fichier->entetebmp.largeur);
	for (i = 0; i < fichier->entetebmp.hauteur; i++) {
		for (j = 0; j < (fichier->entetebmp.largeur); j++) {
			niv_gris = (fichier->image[i][j].r + fichier->image[i][j].g + fichier->image[i][j].b) / 3;
			if (niv_gris < moy) {
				fichier->image[i][j].r = 0;
				fichier->image[i][j].g = 0;
				fichier->image[i][j].b = 0;
			}
			else {
				fichier->image[i][j].r = 255;
				fichier->image[i][j].g = 255;
				fichier->image[i][j].b = 255;
			}
		}
	}
	enregistrer("rslt_binarisation.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_binarisation.bmp");
	system(command);



	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
	}

// 1-
void Niveau_Gris(struct fichierimage* fichier){
	int i, j, niv_gris;
	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < fichier->entetebmp.largeur; j++) {
			niv_gris = (fichier->image[i][j].r + fichier->image[i][j].g + fichier->image[i][j].b) / 3;
			fichier->image[i][j].r = niv_gris;
			fichier->image[i][j].g = niv_gris;
			fichier->image[i][j].b = niv_gris;
		}

	enregistrer("rslt_niveau_gris.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_niveau_gris.bmp");
	system(command);

	free(fichier);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 2-
void Miroir(struct fichierimage* fichier)
{
	int i, j;

	for (i = 0; i <= fichier->entetebmp.hauteur; i++)
		for (j = 0; j < fichier->entetebmp.largeur; j++)
		{
			fichier->image[i][j].r = fichier->image[i][fichier->entetebmp.largeur - j].r;
			fichier->image[i][j].g = fichier->image[i][fichier->entetebmp.largeur - j].g;
			fichier->image[i][j].b = fichier->image[i][fichier->entetebmp.largeur - j].b;
		}

	enregistrer("rslt_miroir.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_miroir.bmp");
	system(command);

	free(fichier);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 3-
void Symetrie(struct fichierimage* fichier)
{
	int i, j, h, l;
	h = fichier->entetebmp.hauteur;
	l = fichier->entetebmp.largeur;
	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < (fichier->entetebmp.largeur); j++) {
			fichier->image[i][j].r = fichier->image[h - i][j].r;
			fichier->image[i][j].g = fichier->image[h - i][j].g;
			fichier->image[i][j].b = fichier->image[h - i][j].b;
		}

	enregistrer("rslt_symetrie.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_symetrie.bmp");
	system(command);

	free(fichier);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}


// 4-
void Pivot(struct fichierimage* fichier)
{
	int i, j;
	int choix = 0;
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier_1 = NULL;
	fichier_1 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

	printf("\t1. Pivot gauche\n");
	printf("\t2. Pivot droit\n");
	printf("\t");
	scanf_s("%d", &choix);

	switch (choix)
	{
	case 1:
		for (i = 0; i < hauteur; i++)
			for (j = 0; j < largeur; j++)
			{
				fichier_1->image[largeur - j - 1][i].r = fichier->image[i][j].r;
				fichier_1->image[largeur - j - 1][i].g = fichier->image[i][j].g;
				fichier_1->image[largeur - j - 1][i].b = fichier->image[i][j].b;
			}
		break;

	case 2:
		for (i = 0; i < hauteur; i++)
			for (j = 0; j < largeur; j++)
			{
				fichier_1->image[j][hauteur - i - 1].r = fichier->image[i][j].r;
				fichier_1->image[j][hauteur - i - 1].g = fichier->image[i][j].g;
				fichier_1->image[j][hauteur - i - 1].b = fichier->image[i][j].b;
			}
		break;
	}


	enregistrer("rslt_pivot.bmp", fichier_1);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_pivot.bmp");
	system(command);

	free(fichier_1);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 8-
void Monochrome(struct fichierimage* fichier)
{
	int i, j;
	int choix = 0;

	printf("\t1. Rouge.\n");
	printf("\t2. Vert.\n");
	printf("\t3. Bleu.\n");

	printf("\t");
	scanf_s("%d", &choix);

	switch (choix)
	{
	case 1:
		for (i = 0; i < fichier->entetebmp.hauteur; i++)
			for (j = 0; j < (fichier->entetebmp.largeur); j++)
			{
				fichier->image[i][j].r = fichier->image[i][j].r;
				fichier->image[i][j].g = 0;
				fichier->image[i][j].b = 0;
			}
		break;

	case 2:
		for (i = 0; i < fichier->entetebmp.hauteur; i++)
			for (j = 0; j < (fichier->entetebmp.largeur); j++)
			{
				fichier->image[i][j].r = 0;
				fichier->image[i][j].g = fichier->image[i][j].g;
				fichier->image[i][j].b = 0;
			}
		break;

	case 3:
		for (i = 0; i < fichier->entetebmp.hauteur; i++)
			for (j = 0; j < (fichier->entetebmp.largeur); j++)
			{
				fichier->image[i][j].r = 0;
				fichier->image[i][j].g = 0;
				fichier->image[i][j].b = fichier->image[i][j].b;
			}
		break;
	}

	enregistrer("rslt_monochrome.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_monochrome.bmp");
	system(command);

	free(fichier);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 9-
void Inversion(struct fichierimage* fichier) {
	int i, j;

	// Rouge devient Bleu.
	// Vert devient Rouge.
	// Bleu devient Vert.


	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < (fichier->entetebmp.largeur); j++)
		{
			int save = fichier->image[i][j].r;
			int save_1 = fichier->image[i][j].g;
			fichier->image[i][j].r = fichier->image[i][j].b;
			fichier->image[i][j].g = save;
			fichier->image[i][j].b = save_1;
		}

	enregistrer("rslt_inversion.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_inversion.bmp");
	system(command);

	free(fichier);
}

// 11-
void Reduction(struct fichierimage* fichier)
{
	int i, j, k, l, red = 0;
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier_1 = NULL;
	printf_s("\tRatio de r%cductiont : ", 130);
	scanf_s("%d", &red);
	fichier_1 = nouveau(largeur / red, hauteur / red);

	for (i = 0; i <= hauteur; i++)
		for (j = 0; j <= largeur; j++)
		{
			fichier_1->image[i / red][j / red].r = fichier->image[i][j].r;
			fichier_1->image[i / red][j / red].g = fichier->image[i][j].g;
			fichier_1->image[i / red][j / red].b = fichier->image[i][j].b;

		}

	enregistrer("rslt_reduction.bmp", fichier_1);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_reduction.bmp");
	system(command);

	free(fichier_1);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 12-
void Agrandissement(struct fichierimage* fichier)
{
	int i, j, k, l, ag = 0;
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier_1 = NULL;
	printf_s("\tRatio d'agrandissement : ");
	scanf_s("%d", &ag);
	fichier_1 = nouveau(ag * largeur, ag * hauteur);

	for (i = 1; i < hauteur; i++)
		for (j = 1; j < largeur; j++)
		{
			for (k = ((ag * i) - 1); k <= (ag * i); k++)
				for (l = ((ag * j) - 1); l <= (ag * j); l++)
				{
					fichier_1->image[k][l].r = fichier->image[i][j].r;
					fichier_1->image[k][l].g = fichier->image[i][j].g;
					fichier_1->image[k][l].b = fichier->image[i][j].b;
				}
		}

	enregistrer("rslt_agrandissement.bmp", fichier_1);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_agrandissement.bmp");
	system(command);

	free(fichier_1);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 13-
Histogramme(struct fichierimage* fichier)
{
	int i, j, niv_gris;
	float C = 0.0;
	int	nbp = ((fichier->entetebmp.hauteur) * (fichier->entetebmp.largeur));
	float tab[257] = { 0.0 };
	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < (fichier->entetebmp.largeur); j++)
		{
			niv_gris = (fichier->image[i][j].r + fichier->image[i][j].g + fichier->image[i][j].b) / 3;
			tab[niv_gris] = tab[niv_gris] + 1;
		}

	for (i = 0; i < 256; i++) {
		printf(" [%d] ", i);
		printf(" [%f] ", tab[i]);
		printf(" \n ");

	}
	if (tab[0] > tab[255]) {
		return 1;
	}
	else {
		return 0;
	}
	
}

// 14-
void Negatif(struct fichierimage* fichier)
{
	int i, j;

	for (i = 0; i <= fichier->entetebmp.hauteur; i++)
		for (j = 0; j <= fichier->entetebmp.largeur; j++)
		{
			fichier->image[i][j].r = 255 - fichier->image[i][j].r;
			fichier->image[i][j].g = 255 - fichier->image[i][j].g;
			fichier->image[i][j].b = 255 - fichier->image[i][j].b;
		}

	enregistrer("rslt_negatif.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_negatif.bmp");
	system(command);

	free(fichier);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 15-
void Luminosite(struct fichierimage* fichier)
{
	int i, j;
	int lumi;
	printf("\tSaisissez la luminosite (entier positif/negatif) :");
	scanf("%d", &lumi);
	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < fichier->entetebmp.largeur; j++) {

			fichier->image[i][j].r = max(0, min(255, fichier->image[i][j].r + lumi));
			fichier->image[i][j].g = max(0, min(255, fichier->image[i][j].g + lumi));
			fichier->image[i][j].b = max(0, min(255, fichier->image[i][j].b + lumi));
		}

	enregistrer("rslt_lumin.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_lumin.bmp");
	system(command);

	free(fichier);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 17-
void Convolution(struct fichierimage* fichier)
{
	int i, j, k, l, r, g, b;

	float tab[3][3] = { {0,-1,0},
						{-1,5,-1},
						{0,-1,0} };

	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	float somr = 0.0;
	float somg = 0.0;
	float somb = 0.0;
	float moy = 0.0;
	int niv_gris = 0;
	struct fichierimage* fichier_1 = NULL;
	fichier_1 = nouveau(largeur, hauteur);

	for (i = 1; i < hauteur - 1; i++)
		for (j = 1; j < largeur - 1; j++)
		{

			for (k = -1; k <= 1; k++)
				for (l = -1; l <= 1; l++)
				{
					r = fichier->image[i + k][j + l].r;
					g = fichier->image[i + k][j + l].g;
					b = fichier->image[i + k][j + l].b;

					somr = somr + (r * tab[k + 1][l + 1]);
					somg = somg + (g * tab[k + 1][l + 1]);
					somb = somb + (b * tab[k + 1][l + 1]);
				}

			if (fichier->image[hauteur / 2][largeur / 2].r != fichier->image[hauteur / 2][largeur / 2].g)
			{
				if (somr > 255) { somr = 255; }
				if (somb > 255) { somb = 255; }
				if (somg > 255) { somg = 255; }

				if (somr < 0) { somr = 0; }
				if (somb < 0) { somb = 0; }
				if (somg < 0) { somg = 0; }
			}

			fichier_1->image[i][j].r = somr;
			fichier_1->image[i][j].g = somg;
			fichier_1->image[i][j].b = somb;
			somr = 0.0;
			somb = 0.0;
			somg = 0.0;

		}

	enregistrer("rslt_convolution.bmp", fichier_1);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_convolution.bmp");
	system(command);

	free(fichier_1);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 22-
void Filtre_Moy(struct fichierimage* fichier)
{
	int i, j, k, l, r, g, b;

	float tab[3][3] = { {1,1,1},
						{1,1,1},
						{1,1,1} };

	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	float somr = 0.0;
	float somg = 0.0;
	float somb = 0.0;
	float moy = 0.0;
	int niv_gris = 0;
	struct fichierimage* fichier_1 = NULL;
	fichier_1 = nouveau(largeur, hauteur);

	for (i = 1; i < hauteur - 1; i++)
		for (j = 1; j < largeur - 1; j++)
		{

			for (k = -1; k <= 1; k++)
				for (l = -1; l <= 1; l++)
				{
					r = fichier->image[i + k][j + l].r;
					g = fichier->image[i + k][j + l].g;
					b = fichier->image[i + k][j + l].b;

					somr = somr + (r * tab[k + 1][l + 1]);
					somg = somg + (g * tab[k + 1][l + 1]);
					somb = somb + (b * tab[k + 1][l + 1]);
				}


			fichier_1->image[i][j].r = somr / 9;
			fichier_1->image[i][j].g = somg / 9;
			fichier_1->image[i][j].b = somb / 9;
			somr = 0.0;
			somb = 0.0;
			somg = 0.0;

		}

	enregistrer("rslt_filtre_moy.bmp", fichier_1);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_filtre_moy.bmp");
	system(command);

	free(fichier_1);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

//23-
void Superposition(struct fichierimage* fichier)
{
	int i, j;
	struct fichierimage* fichier_1 = NULL;
	fichier_1 = charger("Paysage.bmp");

	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier_2 = NULL;
	fichier_2 = nouveau(largeur, hauteur);

	int dist;
	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < (fichier->entetebmp.largeur); j++)
		{
			//printf(" rouge_fichier: %d vert_fichier: %d bleu_fichier: %d ", fichier->image[i][j].r, fichier->image[i][j].g, fichier->image[i][j].b);
			//printf(" \trouge_fichier: %d vert_fichier: %d bleu_fichier: %d ", fichier_1->image[i][j].r, fichier_1->image[i][j].g , fichier_1->image[i][j].b);

			dist = sqrt(pow((fichier->image[i][j].r - fichier->image[i][j + 1].r), 2) + pow((fichier->image[i][j].g - fichier->image[i][j + 1].g), 2) + pow((fichier->image[i][j].b - fichier->image[i][j + 1].b), 2));
			//printf("distance : %d", dist);
			if (dist < 70 && fichier->image[i][j].b>150) {
				fichier_2->image[i][j].r = fichier_1->image[i][j].r;
				fichier_2->image[i][j].g = fichier_1->image[i][j].g;
				fichier_2->image[i][j].b = fichier_1->image[i][j].b;
			}
			else {
				fichier_2->image[i][j].r = fichier->image[i][j].r;
				fichier_2->image[i][j].g = fichier->image[i][j].g;
				fichier_2->image[i][j].b = fichier->image[i][j].b;
			}
		}
	enregistrer("rslt_superposition.bmp", fichier_2);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_superposition.bmp");
	system(command);

	free(fichier_2);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 25-
void Egalisation_Histogramme(struct fichierimage* fichier)
{
	int i, j, niv_gris;
	float C = 0.0;
	int	nbp = ((fichier->entetebmp.hauteur) * (fichier->entetebmp.largeur));
	float tab[257] = { 0.0 };

	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < (fichier->entetebmp.largeur); j++)
		{
			niv_gris = (fichier->image[i][j].r + fichier->image[i][j].g + fichier->image[i][j].b) / 3;
			tab[niv_gris] = tab[niv_gris] + 1;
		}

	for (i = 0; i < 256; i++)
	{
		tab[i] = tab[i] / nbp;
	}

	for (i = 0; i < 256; i++)
	{
		C = tab[i] + C;
		tab[i] = C;
	}

	for (i = 0; i < fichier->entetebmp.hauteur; i++)
		for (j = 0; j < (fichier->entetebmp.largeur); j++)
		{
			niv_gris = (tab[fichier->image[i][j].r] * 255);
			fichier->image[i][j].r = niv_gris;
			fichier->image[i][j].g = niv_gris;
			fichier->image[i][j].b = niv_gris;
		}

	enregistrer("rslt_egalisation_histogramme.bmp", fichier);

	char command[256];
	snprintf(command, sizeof(command), "start %s", "rslt_egalisation_histogramme.bmp");
	system(command);

	free(fichier);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 26-
void Etiqueter(struct fichierimage* fichier)
{	
	Binarisation(fichier);
	struct fichierimage* fichier_1 = charger("rslt_binarisation.bmp");
	//verifie si le fond est noir
	if (Histogramme(fichier_1))
	{	//Si oui inverse le noir avec du blanc
		printf("Negatif\n");
		Negatif(fichier_1);
		fichier_1 = charger("rslt_negatif.bmp");
	}
	printf("Etiquetage\n");
	int i, j;
	int nbLabel = 0;
	int hauteur = fichier_1->entetebmp.hauteur;
	int largeur = fichier_1->entetebmp.largeur;
	struct fichierimage* fichier_3 = NULL;
	fichier_3 = nouveau(largeur, hauteur);

	for (i = 1; i < hauteur - 1; i++) {
		for (j = 1; j < largeur - 1; j++) {
			if (fichier_1->image[i][j].r == 0) {
				nbLabel++;
				fichier_3->image[i][j].r = 10 * nbLabel;
				fichier_3->image[i][j].g = 10 * nbLabel;
				fichier_3->image[i][j].b = 10 * nbLabel;

				fichier_1->image[i][j].r = 255;
				fichier_1->image[i][j].g = 255;
				fichier_1->image[i][j].b = 255;

				//Pile pour stocker les pixels à visiter
				//Faire une pile dynamique serais mieux pour éviter les erreures d'espace saturer notament pour la cellules7
                int pile[300 * 300][2];
				int tete_pile = -1;

				// Ajouter le pixel actuel à la pile
				pile[++tete_pile][0] = i;
				pile[tete_pile][1] = j;

				while (tete_pile >= 0) {
					int x = pile[tete_pile][0];
					int y = pile[tete_pile--][1];

					// Voisin de droite
					if (fichier_1->image[x][y + 1].r == 0) {
						fichier_3->image[x][y + 1].r = 10 * nbLabel;
						fichier_3->image[x][y + 1].g = 10 * nbLabel;
						fichier_3->image[x][y + 1].b = 10 * nbLabel;
						fichier_1->image[x][y + 1].r = 255;
						fichier_1->image[x][y + 1].g = 255;
						fichier_1->image[x][y + 1].b = 255;
						pile[++tete_pile][0] = x;
						pile[tete_pile][1] = y + 1;
					}
					// Voisin du bas
					if (fichier_1->image[x + 1][y].r == 0) {
						fichier_3->image[x + 1][y].r = 10 * nbLabel;
						fichier_3->image[x + 1][y].g = 10 * nbLabel;
						fichier_3->image[x + 1][y].b = 10 * nbLabel;
						fichier_1->image[x + 1][y].r = 255;
						fichier_1->image[x + 1][y].g = 255;
						fichier_1->image[x + 1][y].b = 255;
						pile[++tete_pile][0] = x + 1;
						pile[tete_pile][1] = y;
					}
					// Voisin de gauche
					if (fichier_1->image[x][y - 1].r == 0) {
						fichier_3->image[x][y - 1].r = 10 * nbLabel;
						fichier_3->image[x][y - 1].g = 10 * nbLabel;
						fichier_3->image[x][y - 1].b = 10 * nbLabel;
						fichier_1->image[x][y - 1].r = 255;
						fichier_1->image[x][y - 1].g = 255;
						fichier_1->image[x][y - 1].b = 255;
						pile[++tete_pile][0] = x;
						pile[tete_pile][1] = y - 1;
					}
					// Voisin du haut
					if (fichier_1->image[x - 1][y].r == 0) {
						fichier_3->image[x - 1][y].r = 10 * nbLabel;
						fichier_3->image[x - 1][y].g = 10 * nbLabel;
						fichier_3->image[x - 1][y].b = 10 * nbLabel;
						fichier_1->image[x - 1][y].r = 255;
						fichier_1->image[x - 1][y].g = 255;
						fichier_1->image[x - 1][y].b = 255;
						pile[++tete_pile][0] = x - 1;
						pile[tete_pile][1] = y;
					}
				}
			}
		}
	}
	printf("Nombre d'objets : %d\n", nbLabel);
	enregistrer("etiqueter.bmp", fichier_3);

	//Calcule le périmètre et l'air d'un objet
	for (int lb = 1; lb <= nbLabel; lb++) {
		int perimetre = 0;
		int air = 0;
		for (i = 1; i < hauteur - 1; i++) {
			for (j = 1; j < largeur - 1; j++) {
				if (fichier_3->image[i][j].r == 10 * lb) {
					air++;
					if (fichier_3->image[i][j + 1].r == 0 || fichier_3->image[i + 1][j].r == 0 || fichier_3->image[i][j - 1].r == 0 || fichier_3->image[i - 1][j].r == 0) {
						perimetre++;
					}
				}
			}
		}
		printf("Objet %d : Perimetre : %d : Air : %d\n", lb, perimetre, air);
	}

	

	char command[256];
	snprintf(command, sizeof(command), "start %s", "etiqueter.bmp");
	system(command);
	
	free(fichier);
	free(fichier_1);

	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 27- Moments
void Moments(struct fichierimage* fichier)
{
	printf("\tMoments\n");
	int i, j, k, l;
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier_1 = NULL;
	Binarisation(fichier);
	fichier_1 = charger("rslt_binarisation.bmp");
	//Calcul des moments
	float m00 = 0.0, m10 = 0.0, m01 = 0.0, m11 = 0.0, m20 = 0.0, m02 = 0.0;
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			if (fichier_1->image[i][j].r == 0) { // Pixel noir
				m00 += 1;
				m10 += j;
				m01 += i;
				m11 += i * j;
				m20 += j * j;
				m02 += i * i;
			}
		}
	}
	printf("Aire m00: %f\n", m00);
	printf("m10: %f\n", m10);
	printf("m01: %f\n", m01);
	printf("m11: %f\n", m11);
	printf("m20: %f\n", m20);
	printf("m02: %f\n", m02);

	//Calcul du centre de gravite
	float x_bar = m10 / m00;
	float y_bar = m01 / m00;
	printf("Centre de gravite : \n");
	printf("x_bar: %f\n", x_bar);
	printf("y_bar: %f\n", y_bar);
	free(fichier_1);
	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}

// 28- Moments de Hu
void Moments_Hu(struct fichierimage* fichier)
{
	printf("\tMoments de Hu\n");
	int i, j, k, l;
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier_1 = NULL;
	fichier_1 = charger("rslt_binarisation.bmp");
	//Calcul des moments
	float m00 = 0.0, m10 = 0.0, m01 = 0.0, m11 = 0.0, m20 = 0.0, m02 = 0.0;
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			if (fichier_1->image[i][j].r == 0) { // Pixel noir
				m00 += 1;
				m10 += j;
				m01 += i;
				m11 += i * j;
				m20 += j * j;
				m02 += i * i;
			}
		}
	}
	//Calcul des moments centraux
	float x_bar = m10 / m00;
	float y_bar = m01 / m00;
	float mu20 = m20 - x_bar * m10;
	float mu02 = m02 - y_bar * m01;
	float mu11 = m11 - x_bar * m01;

	//Calcul des moments de Hu
	float hu1 = mu20 + mu02;
	float hu2 = pow(mu20 - mu02, 2) + 4 * pow(mu11, 2);
	printf("Hu1: %f\n", hu1);
	printf("Hu2: %f\n", hu2);

	//variation des moments de Hu en fonction de la rotation

	free(fichier_1);
	printf("\tOuvrez le dossier du projet afin d'y trouver votre image modifiee\n");
	printf("\n");
	printf("\t___________________________________________________________");
	printf("\n");
}
