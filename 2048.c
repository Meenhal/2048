#include <stdio.h> 
#include <stdlib.h> /* pour rand et srand */
#include <time.h> /* pour time */

/* Constante symbolique utilisée pour générer un nouveau bloc aléatoire sur la grille */
#define RANDOM_MAX 4 

/* Initialise le jeu et l'interface*/
void initialiser_jeu(int tab[4][4]);

/* Ajoute un bloc dans un endroit aléatoire de la grille qui n'est pas occupé par un autre bloc */
void nouveau_bloc(int tab[4][4]);

/* Affiche la grille dans le terminale */
void afficher_grille(int tab[4][4]); 

/* Déplace tous les blocs vers le haut et renvoie le score gagné grâce au déplacement */
int mouvement_haut(int tab[4][4]); 

/* Déplace tous les blocs vers le bas et renvoie le score gagné grâce au déplacement */
int mouvement_bas(int tab[4][4]);

/* Déplace tous les blocs vers la gauche et renvoie le score gagné grâce au déplacement */
int mouvement_gauche(int tab[4][4]);

/* Déplace tous les blocs vers la droite et renvoie le score gagné grâce au déplacement */
int mouvement_droite(int tab[4][4]);

/* Demande l'entrée d'un caractère à l'utilisateur pour l'associer à un des déplacements */
int mouvement(int tab[4][4]);


int main()
{   
    /* On définit la taille de la grille qui est de 4 x 4 */
    int grille[4][4]; 
    
    /* On initialise le score à 0 */
    int score = 0; 
    int i, j, verif_espace = 0, verif_victoire = 0;
    
    initialiser_jeu(grille);

    /* Le jeu s'arrête une fois que le bloc "2048" apparait sur la grille ou bien qu'il n'y a plus d'espace dans celle-ci */
    while (score < 2048) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (grille[i][j] == 0) {
                    verif_espace += 1;
                }
                if (grille[i][j] == 2048) {
                    verif_victoire += 1;
                }
            }
        }
        if (verif_victoire > 0) {
            printf("Bravo !! Vous avez terminé le jeu avec un score de : %d\n", score);
            return 0;
        }  
        if (verif_espace > 0) {
            score += mouvement(grille);
            printf("Votre score actuel est de : %d\n", score);
            verif_espace = 0;
        } else {
            printf("Il n'y a plus d'espace dans la grille, vous avez perdu avec un score finale de : %d\n", score);
            return 0;
        }
    }  
}

void initialiser_jeu(int tab[4][4])
{
    /* initialise le générateur de nombres aléatoires */
    srand(time(NULL));

    int i, j;
    char c;
    
    /* On remplit le tableau avec des 0 */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tab[i][j] = 0;
        }
    }
    
    printf("\nBienvenue sur 2048 !\n\n");
    printf("Voici les touches à utiliser pour y jouer :\n");
    printf("z = Tout envoyer vers le haut\n");
    printf("q = Tout envoyer vers la gauche\n");
    printf("s = Tout envoyer vers le bas\n");
    printf("d = Tout envoyer vers la droite\n\n");
    printf("Entrez n'importe quel caractère, puis appuiyez sur la touche \"entrer\" pour lancer le jeu.\n\n");
    scanf(" %c", &c);
    
    /* On place les 2 premiers chiffres obligatoires */
    nouveau_bloc(tab);
    nouveau_bloc(tab);
    
    /* On dessine la grille à partir du tableau */
    printf("Très bien, le jeu est lancé !\n\n");
    afficher_grille(tab);
}

void afficher_grille(int tab[4][4])
{
    int i, j;
    
    /* On affiche le tableau de sorte à créer une grille */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("|  %d  ", tab[i][j]);
        }
        printf("|\n\n");
    }
}

void nouveau_bloc(int tab[4][4]) 
{    
    /* On définit aléatoirement le bloc à placer (soit 2, soit 4) */
    int temp = rand() % 2;
    int new_bloc = 0;
    if (temp == 0) {
        new_bloc = 2;
    } else { 
        new_bloc = 4;
    }
    
    /* On cherche des coordonnées aléatoires dans la grille */
	int i = rand() % RANDOM_MAX;
    int j = rand() % RANDOM_MAX;
    
    /* S'il y a déjà un bloc à ces coordonnées, on en cherche une nouvelle jusqu'à en trouver une qui est vide */
    while (tab[i][j] != 0) {
        i = rand() % RANDOM_MAX;
        j = rand() % RANDOM_MAX;
    }

    /* On place le bloc aux coordonnées vides */
    tab[i][j] = new_bloc;
}

int mouvement_haut(int tab[4][4]) 
{
    int temptab[4][4];
    int score = 0;
    int i, j, k = 0, l = 0, m = 0, n = 0;

    /* On crée une copie du tableau original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
           temptab[i][j] = 0;
        }
    }

    /* Déplacement des blocs vers le haut */
    for (i = 0; i < 4; i++) {
        if (tab[i][0] != 0) {
            temptab[k][0] = tab[i][0];
            tab[i][0] = 0;
            k += 1;
        }
        if (tab[i][1] != 0) {
            temptab[l][1] = tab[i][1];
            tab[i][1] = 0;
            l += 1;
        }
        if (tab[i][2] != 0) {
            temptab[m][2] = tab[i][2];
            tab[i][2] = 0;
            m += 1;
        }
        if (tab[i][3] != 0) {
            temptab[n][3] = tab[i][3];
            tab[i][3] = 0;
            n += 1;
        }
    }

    /* Addition des blocs identiques */
    for (j = 0; j < 4; j++) {
        if (temptab[0][j] == temptab[1][j]) {
            temptab[0][j] += temptab[1][j];
            score += temptab[0][j];
            temptab[1][j] =  temptab[2][j];
            temptab[2][j] =  temptab[3][j];
            temptab[3][j] = 0;
        } else if (temptab[1][j] == temptab[2][j]) {
            temptab[1][j] += temptab[2][j];
            score += temptab[1][j];
            temptab[2][j] =  temptab[3][j];
            temptab[3][j] = 0;
        } else if (temptab[2][j] == temptab[3][j]) {
            temptab[2][j] += temptab[3][j];
            score += temptab[2][j];
            temptab[3][j] = 0; 
        }
    }
    
    /* On recopie le deuxième tableau dans l'original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tab[i][j] = temptab[i][j];
        }
    }

    /* On renvoie le score obtenue avec ce déplacement */
    return score;
}

int mouvement_bas(int tab[4][4]) 
{
    int temptab[4][4];
    int score = 0;
    int i, j, k = 3, l = 3, m = 3, n = 3;

    /* On crée une copie du tableau original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
           temptab[i][j] = 0;
        }
    }

    /* Déplacement des blocs vers le bas */
    for (i = 3; i >= 0; i--) {
        if (tab[i][0] != 0) {
            temptab[k][0] = tab[i][0];
            tab[i][0] = 0;
            k -= 1;
        }
        if (tab[i][1] != 0) {
            temptab[l][1] = tab[i][1];
            tab[i][1] = 0;
            l -= 1;
        }
        if (tab[i][2] != 0) {
            temptab[m][2] = tab[i][2];
            tab[i][2] = 0;
            m -= 1;
        }
        if (tab[i][3] != 0) {
            temptab[n][3] = tab[i][3];
            tab[i][3] = 0;
            n -= 1;
        }
    }

    /* Addition des blocs identiques */
    for (j = 0; j < 4; j++) { 
        if (temptab[3][j] == temptab[2][j]) {
            temptab[3][j] += temptab[2][j];
            score += temptab[3][j];
            temptab[2][j] = temptab[1][j];
            temptab[1][j] = temptab[0][j];
            temptab[0][j] = 0;
        } else if (temptab[2][j] == temptab[1][j]) {
            temptab[2][j] += temptab[1][j];
            score += temptab[2][j];
            temptab[1][j] = temptab[0][j];
            temptab[0][j] = 0;
        } else if (temptab[1][j] == temptab[0][j]) {
            temptab[1][j] += temptab[0][j];
            score += temptab[1][j];
            temptab[0][j] = 0;
        }
    }

    /* On recopie le deuxième tableau dans l'original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tab[i][j] = temptab[i][j];
        }
    }

    /* On renvoie le score obtenue avec ce déplacement */
    return score;
}

int mouvement_gauche(int tab[4][4]) 
{
    int temptab[4][4];
    int score = 0;
    int i, j, k = 0;

    /* On crée une copie du tableau original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
           temptab[i][j] = 0;
        }
    }

    /* Déplacement des blocs vers la gauche */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (tab[i][j] != 0) {
                temptab[i][k] = tab[i][j];
                k += 1;
            }
        }
        k = 0;
    }

    /* Addition des blocs identiques */
    for (i = 0; i < 4; i++) {
        if (temptab[i][0] == temptab[i][1]) {
            temptab[i][0] += temptab[i][1];
            score += temptab[i][0];
            temptab[i][1] = temptab[i][2];
            temptab[i][2] = temptab[i][3];
            temptab[i][3] = 0;
        } else if (temptab[i][1] == temptab[i][2]) {
            temptab[i][1] += temptab[i][2];
            score += temptab[i][1];
            temptab[i][2] = temptab[i][3];
            temptab[i][3] = 0;
        } else if (temptab[i][2] == temptab[i][3]) {
            temptab[i][2] += temptab[i][3];
            score += temptab[i][2];
            temptab[i][3] = 0;
        }
    }

    /* On recopie le deuxième tableau dans l'original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tab[i][j] = temptab[i][j];
        }
    }

    /* On renvoie le score obtenue avec ce déplacement */
    return score;
}

int mouvement_droite(int tab[4][4]) 
{
    int temptab[4][4];
    int score = 0;
    int i, j, k = 3;

    /* On crée une copie du tableau original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
           temptab[i][j] = 0;
        }
    }

    /* Déplacement des blocs vers la gauche */
    for (i = 0; i < 4; i++) {
        for (j = 3; j >= 0; j--) {
            if (tab[i][j] != 0) {
                temptab[i][k] = tab[i][j];
                k -= 1;
            }
        }
        k = 3;
    }

    /* Addition des blocs identiques */
    for (i = 0; i < 4; i++) {
        if (temptab[i][3] == temptab[i][2]) {
            temptab[i][3] += temptab[i][2];
            score += temptab[i][3];
            temptab[i][2] = temptab[i][1];
            temptab[i][1] = temptab[i][0];
            temptab[i][0] = 0;
        } else if (temptab[i][2] == temptab[i][1]) {
            temptab[i][2] += temptab[i][1];
            score += temptab[i][2];
            temptab[i][1] = temptab[i][0];
            temptab[i][0] = 0;
        } else if (temptab[i][1] == temptab[i][0]) {
            temptab[i][1] += temptab[i][0];
            score += temptab[i][1];
            temptab[i][0] = 0;
        }
    }

    /* On recopie le deuxième tableau dans l'original */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tab[i][j] = temptab[i][j];
        }
    }

    /* On renvoie le score obtenue avec ce déplacement */
    return score;
}

int mouvement(int tab[4][4]) 
{
    char c;
    int score = 0;

    printf("Entrez un caractère correspondant à un déplacement, les caractères valides sont : z,q,s,d.\n");
    scanf(" %c", &c);
 
    /* On associe un caractère à chaque mouvement, puis on rajoute un nouveau bloc aléatoirement dans la grille et on affiche celle-ci */
    if (c == 'z') {
        score += mouvement_haut(tab);
        nouveau_bloc(tab);
        afficher_grille(tab);
    } else if (c == 'q') {
        score += mouvement_gauche(tab);
        nouveau_bloc(tab);
        afficher_grille(tab);
    } else if (c == 's') {
        score += mouvement_bas(tab);
        nouveau_bloc(tab);
        afficher_grille(tab);
    } else if (c == 'd') {
        score += mouvement_droite(tab);
        nouveau_bloc(tab);
        afficher_grille(tab);
    } else {
        printf("Caractère invalide.\n\n");
    }
    
    /* On renvoie le score obtenu avec ce déplacement, 0 si le caractère est invalide */
    return score;
}

