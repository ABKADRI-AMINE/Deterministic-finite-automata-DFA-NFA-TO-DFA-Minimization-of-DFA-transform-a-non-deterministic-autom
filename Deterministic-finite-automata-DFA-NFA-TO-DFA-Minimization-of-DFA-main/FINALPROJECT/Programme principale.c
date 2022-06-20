#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char TabContenueFichier[1000];
char TabAutomate[100][100][20];
char TabDeterministe[100][100][20]; 
char TabMinimisation[100][100][20]; 
char TabMinimisation_1[100][100][20];
char TabMinimisation_2[100][100][20];



char colonnecherchee;
char etatcourant;
char x;
char mot1[100], NomFiche[10];
char EtatIni[10][2], EtatFin[10][2];
char tochar[10], EtatFinDeterministe[10][2], EtatIniMini[10][2], EtatFinMini[10][2];
int lettercompteur = 0;
int j, i, k;
int n = 1, m = 1, compteur = 1;
int NbrOccurences = 4, NbrOccurences1, NbrOccurences2;
int compteur1, compteur2 = 0, compteur3;
int NbrEtatI, NbEtatFin;
int y, k1 = 1, nbalpha, nb_cara, a;
int Choix, EtatArrivee, nbligne, nbLettre;
void Saisir()
{
    printf("Veuillez saisir le nom de fichier : ");
    scanf("%s", &NomFiche);
    FILE *file = fopen(NomFiche, "r");
    if (file != NULL)
    {
        while (!feof(file))
        {
            fscanf(file, "%c", &TabContenueFichier[lettercompteur]);
            lettercompteur++;
        }
        fclose(file);
    }
    else
        printf("Fichier introuvable\n");
    // Demander a l'utilisateur de saisir les etats initiaux et finaux
    printf("Veuillez saisir le nombre des etats initiaux : ");
    scanf("%d", &NbrEtatI);
    fflush(stdin);
    for (i = 0; i < NbrEtatI; i++)
    {
        printf("Veuillez saisir l'etat initial %d : ", i);
        scanf("%c%c", &EtatIni[i][0], &EtatIni[i][1]);
        fflush(stdin);
    }
    printf("Veuillez saisir le nombre des etats finals : ");
    scanf("%d", &NbEtatFin);
    fflush(stdin);
    for (i = 0; i < NbEtatFin; i++)
    {
        printf("Veuillez saisir l'etat final %d : ", i);
        scanf("%c%c", &EtatFin[i][0], &EtatFin[i][1]);
        fflush(stdin);
    }

    // Si on saisi un Ã©tat entre "0" et "9" le deuxiemme digite sera "-"
    for (i = 0; i < NbrEtatI || i < NbEtatFin; i++)
    {
        if (EtatIni[i][1] == '\n')
            EtatIni[i][1] = '-';
        if (EtatFin[i][1] == '\n')
            EtatFin[i][1] = '-';
    }
    printf("\n");
    // affichage des etats initiaux
    printf("Les etats initiaux sont : ");
    for (i = 0; i < NbrEtatI; i++)
    {
        printf("%c%c", EtatIni[i][0], EtatIni[i][1]);
        printf(" ");
    }
    printf("\n");
    // affichage des etats finaux
    printf("les etats finaux sont : ");
    for (i = 0; i < NbEtatFin; i++)
    {

        printf("%c%c", EtatFin[i][0], EtatFin[i][1]);
        printf(" ");
    }
    printf("\n");

    // prendre les donnÃ©es precis Ã  partir du fichier.
    // stocker les Ã©tats de depart dans la premier colonne
    TabAutomate[0][0][0] = '*';
    for (i = 1; i < lettercompteur - 1; i++) // on a commencé par 1 et s'arreté à 'lettercompteur - 1' pour ne pas lire 'digraph{' et '}'
    {
        compteur = 1;
        k = 0;
        if (TabContenueFichier[i] == '\n')
        {
            while (compteur < 10)
            {
                if (TabContenueFichier[i + compteur] == '-' || TabContenueFichier[i + compteur] == '}') // une fois arrivée à l '-' on va stoper la boucle
                    break;
                TabAutomate[n][0][k] = TabContenueFichier[i + compteur]; // n est initialisé par '1'
                compteur++;
                k++;
            }
            n++;
        }
    }
    // stocker les Ã©tats d'arrivÃ©s dans la premier ligne
    for (i = 1; i < lettercompteur - 1; i++)
    {
        compteur = 1;
        k = 0;
        if (TabContenueFichier[i] == '>')
        {
            while (compteur < 10)
            {
                if (TabContenueFichier[i + compteur] == '[')
                    break;
                TabAutomate[0][m][k] = TabContenueFichier[i + compteur];
                compteur++;
                k++;
            }
            m++;
        }
    }
    m = 1;
    n = 1;
    // stocker les labels pour les Ã©tats departs et arrivÃ©s correspandentes
    for (i = 1; i < lettercompteur - 1; i++)
    {
        compteur = 1;
        k = 0;
        if (TabContenueFichier[i] == '"')
        {
            while (compteur < 10)
            {
                if (TabContenueFichier[i + compteur] == '"')
                    break;
                TabAutomate[m][n][k] = TabContenueFichier[i + compteur];
                compteur++;
                k++;
            }
            m++;
            n++;
            i += compteur + 1;
        }
    }
    // si on a plus de label que 4 on incremente k
    k = 0;
    for (i = 1; i < n; i++)
    {
        if (TabAutomate[i][0][0] == TabAutomate[i + 1][0][0] && TabAutomate[i][0][1] == TabAutomate[i + 1][0][1])
        {
            if (TabAutomate[0][i][0] == TabAutomate[0][i + 1][0] && TabAutomate[0][i][1] == TabAutomate[0][i + 1][1])
            {
                k++;
                if (k > NbrOccurences)
                    NbrOccurences = k;
            }
        }
    }
    // affectation de "-"  pour les colonnes vides de chaque cellule
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            for (k = 0; k < NbrOccurences; k++)
            {
                if (TabAutomate[i][j][k] == NULL)
                    TabAutomate[i][j][k] = '-';
            }
        }
    }
    // suppression des repétitions des ocurences des nombres
    k = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            // cherchons les Ã©tats de departs dupliquÃ©es
            if (TabAutomate[i][0][k] == TabAutomate[j][0][k] && TabAutomate[i][0][k + 1] == TabAutomate[j][0][k + 1] && i != j)
            {
                for (compteur = 1; compteur < j; compteur++)
                {
                    // cherchons les Ã©tats d'arrivÃ©es dupliquÃ©es
                    if (TabAutomate[0][compteur][k] == TabAutomate[0][j][k] && TabAutomate[0][compteur][k + 1] == TabAutomate[0][j][k + 1])
                    {
                        if (TabAutomate[i][compteur][k] != '-') // if la case n'est pas vide
                        {
                            for (compteur1 = 0; compteur1 < NbrOccurences; compteur1++) // NbrOccurences =4 dans notre example cad le nombre d'element dans chaque case
                            {
                                // prendre la label du deuxiÃ¨me transition dupliquÃ© dans la cellule de la premiÃ¨re transition qu'on va garder
                                if (TabAutomate[i][compteur][compteur1] == '-')
                                {
                                    TabAutomate[i][compteur][compteur1] = TabAutomate[j][j][k];
                                    TabAutomate[j][j][k] = '-';
                                    TabAutomate[0][j][k] = '-'; // les etats d'arrivés dupliqués doivent etre remplacer par '-'
                                    // on a remplacer la deuxiÃ¨me transition par des '-'
                                }
                            }
                        }
                        else // si la premiere case est vide et la deuxieme n'est pas vide on met la label dans la premier case et la remplacer par '-' dans la deuxieme
                        {
                            TabAutomate[i][compteur][k] = TabAutomate[j][j][k];
                            TabAutomate[j][j][k] = '-';
                            TabAutomate[0][j][k] = '-'; // les etats d'arrivés dupliqués doivent etre remplacer par '-'
                        }
                    }
                }
                TabAutomate[i][j][k] = TabAutomate[j][j][k];
                TabAutomate[j][j][k] = '-';
                TabAutomate[j][0][k] = '-'; // les etats de departs dupliqués doivent etre remplacer par '-'
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            if (TabAutomate[0][i][k] == TabAutomate[0][j][k] && TabAutomate[0][i][k + 1] == TabAutomate[0][j][k + 1] && i != j)
            {
                for (compteur = 0; compteur < NbrOccurences; compteur++)
                {
                    if (TabAutomate[j][i][compteur] == '-')
                    {
                        TabAutomate[j][i][compteur] = TabAutomate[j][j][k];
                        TabAutomate[j][j][k] = '-';
                        TabAutomate[0][j][k] = '-'; // les etats d'arrivés dupliqués doivent etre remplacer par '-'
                    }
                }
            }
        }
    }
    // extraction de repÃ©tition sur les lignes et les colones
    NbrOccurences1 = 0;
    NbrOccurences2 = 0;
    for (i = 0; i < n; i++)
    {
        if (TabAutomate[0][i][0] == '-') // on compte combien de cellule de la premiere ligne est remplie par "-" cad les Ã©tats d'arrivÃ©s vides
        {
            NbrOccurences1++;
        }
        if (TabAutomate[i][0][0] == '-') // on compte combien de cellule de la premiere colonne est remplie par "-" cad les Ã©tats de departs vides
        {
            NbrOccurences2++;
        }
    }
    // permuter les lignes vides et les passer a la fin de TabContenueFichierleau.
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            if (TabAutomate[0][i][0] == '-') // si on trouve un Ã©tat d'arrivÃ© vide
            {
                if (TabAutomate[0][i + j][0] != '-') // si on trouve un Ã©tat d'arrivÃ© non vide aprÃ¨s l'Ã©tat vide precedent
                {
                    for (compteur1 = 0; compteur1 < NbrOccurences; compteur1++) // compteur1 parcoure element par element de chaque cellule afin de permutter les cases vides et les cases non vides
                    {
                        for (compteur = 0; compteur < n; compteur++) // compteur parcoure ligne par ligne afin de placer les colonnes vides Ã  la fin du TabContenueFichierleau
                        {
                            TabAutomate[compteur][i][compteur1] = TabAutomate[compteur][j + i][compteur1]; // TabAutomate[compteur][j + i][compteur1] est non vide et TabAutomate[compteur][i][compteur1] est vide et on va les permuter
                            TabAutomate[compteur][j + i][compteur1] = '-';
                        }
                    }
                }
            }
            if (TabAutomate[i][0][0] == '-') // si on trouve un Ã©tat de depart  vide
            {
                if (TabAutomate[j + i][0][0] != '-') // si on trouve un Ã©tat de depar non vide aprÃ¨s l'Ã©tat vide precedent
                {
                    for (compteur1 = 0; compteur1 < NbrOccurences; compteur1++) // compteur1 parcoure element par element de chaque cellule afin de permutter les cases vides avec les cases non vides
                    {
                        for (compteur = 0; compteur < n; compteur++) // compteur parcoure colonne par colonne afin de placer les lignes vides Ã  la fin du TabContenueFichierleau
                        {
                            TabAutomate[i][compteur][compteur1] = TabAutomate[j + i][compteur][compteur1];
                            TabAutomate[j + i][compteur][compteur1] = '-';
                        }
                    }
                }
            }
        }
    }
    // trier les etats de departs et arrivés par ordre croissant
    char temp;
    for (i = 0; i < n - NbrOccurences2; i++) // i parcoure ligne par ligne sauf les lignes dupliquÃ©es
    {
        for (j = 1; j < m - NbrOccurences1; j++) // j parcoure colonne par colonne sauf les colonnes dupliquÃ©es
        {
            if (TabAutomate[0][j + 1][0] != NULL)
            {
                if (TabAutomate[0][j][0] >= TabAutomate[0][j + 1][0]) // si on trouve un etat superieur au niveau des colonnes Ã  un etat suivant on va les permuter
                {
                    if (TabAutomate[0][j][1] > TabAutomate[0][j + 1][1]) // traiter le cas de deux digites
                    {
                        for (compteur = 0; compteur < n - NbrOccurences2; compteur++)
                        {
                            for (compteur1 = 0; compteur1 < NbrOccurences; compteur1++)
                            {
                                temp = TabAutomate[compteur][j][compteur1];
                                TabAutomate[compteur][j][compteur1] = TabAutomate[compteur][j + 1][compteur1];
                                TabAutomate[compteur][j + 1][compteur1] = temp;
                            }
                        }
                    }
                    if (TabAutomate[0][j][1] == '-' && TabAutomate[0][j + 1][1] == '-') // drna haddi gha bach ila kano bjojhom fihom digit wa7d o wa7da kbira 3la lokhra nrtbhom tartib tasa3odi
                    {
                        for (compteur = 0; compteur < n - NbrOccurences2; compteur++)
                        {
                            for (compteur1 = 0; compteur1 < NbrOccurences; compteur1++)
                            {
                                temp = TabAutomate[compteur][j][compteur1];
                                TabAutomate[compteur][j][compteur1] = TabAutomate[compteur][j + 1][compteur1];
                                TabAutomate[compteur][j + 1][compteur1] = temp;
                            }
                        }
                    }
                }
            }
            if (TabAutomate[j + 1][0][0] != NULL) // si on trouve un etat superieur au niveau des lignes Ã  un etat suivant on va les permuter
            {
                if (TabAutomate[j][0][0] >= TabAutomate[j + 1][0][0])
                {
                    if (TabAutomate[j][0][1] > TabAutomate[j + 1][0][1])
                    {
                        for (compteur = 0; compteur < n - NbrOccurences2; compteur++)
                        {
                            for (compteur1 = 0; compteur1 < NbrOccurences; compteur1++)
                            {
                                temp = TabAutomate[j][compteur][compteur1];
                                TabAutomate[j][compteur][compteur1] = TabAutomate[j + 1][compteur][compteur1];
                                TabAutomate[j + 1][compteur][compteur1] = temp;
                            }
                        }
                    }
                    if (TabAutomate[j][0][0] == '-' && TabAutomate[j + 1][0][0] == '-')
                    {
                        for (compteur = 0; compteur < n - NbrOccurences2; compteur++)
                        {
                            for (compteur1 = 0; compteur1 < NbrOccurences; compteur1++)
                            {
                                temp = TabAutomate[j][compteur][compteur1];
                                TabAutomate[j][compteur][compteur1] = TabAutomate[j + 1][compteur][compteur1];
                                TabAutomate[j + 1][compteur][compteur1] = temp;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("\nTaper n'importe quelle bouton pour revenir au menu");
    getch();
}
void Affichage()
{
    // affichage de TabContenueFichierleau
    printf("\n");
    for (i = 0; i < n - NbrOccurences2; i++) // NbrOccurences2 : nombre de lignes dupliquées
    {
        for (j = 0; j < m - NbrOccurences1; j++) // NbrOccurences1 :nombre de colonne dupliquées
        {
            for (k = 0; k < NbrOccurences; k++) // NbrOccurences :nombre d'elements de chaque cellule
            {
                if (TabAutomate[i][j][k] == NULL)
                    TabAutomate[i][j][k] = '-';
                printf("%c", TabAutomate[i][j][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\nTaper n'importe quelle bouton pour revenir  au menu");

    FILE *file3 = fopen("FirstGraph.dot", "w+"); // implementer l'automate dans le fichier.dot
    fprintf(file3, "digraph G {\n");
    for (i = 1; i < n - NbrOccurences2; i++)
    {
        for (j = 1; j < m - NbrOccurences1; j++)
        {
            for (k = 0; k < NbrOccurences; k++)
            {
                if (TabAutomate[i][j][k] != '-')
                {
                    if (TabAutomate[i][0][1] != '-' && TabAutomate[0][j][1] != '-')
                        fprintf(file3, "%c%c->%c%c[label=\"%c\"];\n", TabAutomate[i][0][0], TabAutomate[i][0][1], TabAutomate[0][j][0], TabAutomate[0][j][1], TabAutomate[i][j][k]);

                    if (TabAutomate[i][0][1] == '-' && TabAutomate[0][j][1] == '-')
                        fprintf(file3, "%c->%c[label=\"%c\"];\n", TabAutomate[i][0][0], TabAutomate[0][j][0], TabAutomate[i][j][k]);

                    if (TabAutomate[i][0][1] != '-' && TabAutomate[0][j][1] == '-')
                        fprintf(file3, "%c%c->%c[label=\"%c\"];\n", TabAutomate[i][0][0], TabAutomate[i][0][1], TabAutomate[0][j][0], TabAutomate[i][j][k]);

                    if (TabAutomate[i][0][1] == '-' && TabAutomate[0][j][1] != '-')
                        fprintf(file3, "%c->%c%c[label=\"%c\"];\n", TabAutomate[i][0][0], TabAutomate[0][j][0], TabAutomate[0][j][1], TabAutomate[i][j][k]);
                }
            }
        }
    }
    fprintf(file3, "}\n");
    fclose(file3);
    getch();
}
void Determiniser()
{
    TabDeterministe[0][0][0] = '*';
    // remplir TabDeterministe  par "-" sauf la premier cellule
    for (i = 1; i < n + 20; i++)
    {
        for (j = 1; j < m; j++)
        {
            for (k = 0; k < 10; k++)
            {
                TabDeterministe[i][j][k] = '-';
            }
        }
    }
    // inserer les alphabets dans la premire ligne du TabContenueFichierleau TabDeterministe
    k1 = 1;
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            for (k = 0; k < 10; k++)
            {
                if (TabAutomate[i][j][k] != '-' && TabAutomate[i][j][k] != NULL)
                {
                    y = 1;
                    for (compteur = 1; compteur < k1; compteur++)
                    {
                        if (TabDeterministe[0][compteur][0] != TabAutomate[i][j][k])
                            y++;
                    }
                    if (y == k1)
                    {
                        TabDeterministe[0][k1][0] = TabAutomate[i][j][k];
                        k1++;
                    }
                }
            }
        }
    }
    // inserer les etats initiaux dans la premiere colonne et la deuxieme ligne du TabDeterministe cad remplir la premier cellule du deuxieme ligne
    compteur = 0;
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (TabAutomate[j][0][0] == EtatIni[i - 1][0] && TabAutomate[j][0][1] == EtatIni[i - 1][1])
            {
                TabDeterministe[1][0][compteur] = TabAutomate[j][0][0];
                TabDeterministe[1][0][compteur + 1] = TabAutomate[j][0][1];
                compteur += 2; // laisser espace entre les etats initiaux
            }
        }
    }
    // calculer le nombre d'alphabet
    nbalpha = 0;
    for (i = 1; i < m; i++)
    {
        if (TabDeterministe[0][i][0] != NULL)
            nbalpha++;
    }
    // TabContenueFichierleau de determinisation
    // compteur traverse les lignes du TabAutomate, compteur1 traverse les colonnes du TabAutomate, compteur2 traverse la troisieme dimention du TabDeterministe,compteur3 traverse les lignes du TabDeterministe et compteur4 traverse les colonnes du TabDeterministe
    int compteur4;
    compteur3 = 2;
    for (i = 1; i < n + 20; i++)
    {
        y = 1;
        for (compteur4 = nbalpha - 1; compteur4 >= 0; compteur4--)
        {
            compteur2 = 0;
            if (TabDeterministe[i][compteur4 + 1][0] != '-' && TabDeterministe[i][compteur4 + 1][0] != NULL)
                compteur3++;
            for (k = 0; k < 10; k += 2)
            {
                for (compteur = 1; compteur < n; compteur++)
                {
                    if (TabDeterministe[i][0][k] == TabAutomate[compteur][0][0] && TabDeterministe[i][0][k + 1] == TabAutomate[compteur][0][1]) // Si l'etat initial stocker dans TabDeterministe est egal Ã  un etat de depart du TabAutomate alors on fixe la ligne correspandente
                    {
                        for (compteur1 = 1; compteur1 < m; compteur1++)
                        {
                            for (k1 = 0; k1 < 10; k1++)
                            {
                                for (j = 0; j < compteur2; j += 2)
                                {
                                    y = 0;
                                    if (TabDeterministe[i][compteur4 + 1][j] != TabAutomate[0][compteur1][2 * k1]) // 2 * k1 : car dans la determinisation il se peut qu'on ait un ensemble d'etats qui necessite une grande espace
                                        y = 1;
                                    if (TabDeterministe[i][compteur4 + 1][j] == TabAutomate[0][compteur1][2 * k1] && TabDeterministe[i][compteur4 + 1][j + 1] != TabAutomate[0][compteur1][2 * k1 + 1])
                                        y = 1;
                                    if (TabDeterministe[i][compteur4 + 1][j] == TabAutomate[0][compteur1][2 * k1] && TabDeterministe[i][compteur4 + 1][j + 1] == TabAutomate[0][compteur1][2 * k1 + 1])
                                        break;
                                }
                                if (TabDeterministe[0][compteur4 + 1][0] == TabAutomate[compteur][compteur1][k1]) // on compare les labels de TabDeterministe avec celles du TabAutomate si elles sont les mÃªmes il stocke l'Ã©tat d'arrivÃ© de chaque transition  dans TabDeterministe
                                {
                                    if (y == 1)
                                    {
                                        TabDeterministe[i][compteur4 + 1][compteur2] = TabAutomate[0][compteur1][0];
                                        TabDeterministe[i][compteur4 + 1][compteur2 + 1] = TabAutomate[0][compteur1][1];
                                        TabDeterministe[compteur3][0][compteur2] = TabAutomate[0][compteur1][0];
                                        TabDeterministe[compteur3][0][compteur2 + 1] = TabAutomate[0][compteur1][1];
                                        compteur2 += 2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (TabDeterministe[i][compteur4 + 1][0] != '-' && TabDeterministe[i][compteur4 + 1][0] != NULL)
                compteur3++;
        }
    }
    // suppression de repetition
    for (i = 1; i < n + 10; i++)
    {
        y = 0;
        for (j = 1; j < n + 10; j++)
        {
            if (TabDeterministe[i][0][0] == TabDeterministe[i + j][0][0] && TabDeterministe[i][0][1] == TabDeterministe[i + j][0][1])
            {
                for (k = 2; k < 10; k += 2)
                {
                    if (TabDeterministe[i][0][k] == TabDeterministe[i + j][0][k] && TabDeterministe[i][0][k + 1] == TabDeterministe[i + j][0][k + 1]) // si une ligne est dupliquÃ© il va incrementer y
                        y++;
                    if (TabDeterministe[i][0][k] != TabDeterministe[i + j][0][k]) // si une ligne n'est pas dupliquÃ© il va affecter Ã  y= 0
                    {
                        y = 0;
                        break;
                    }
                }
                if (y != 0)
                {
                    for (compteur1 = 0; compteur1 <= nbalpha; compteur1++)
                    {
                        for (compteur2 = 0; compteur2 < 10; compteur2++) // remplacer les lignes dupliquÃ©es par "-"
                        {
                            TabDeterministe[i + j][compteur1][compteur2] = '-';
                        }
                    }
                }
            }
        }
    }
    int NbrOccurences3 = 0;
    for (i = 1; i < n + 10; i++) // calculer les lignes non vides
    {
        if (TabDeterministe[i][0][0] != '-')
            NbrOccurences3++;
    }
    nbligne = NbrOccurences3;
    // supression des lignes vides
    for (i = 1; i <= NbrOccurences3; i++) // placer les lignes vides en bas du TabDeterministe
    {
        for (j = 1; j <= NbrOccurences3; j++)
        {
            if (TabDeterministe[i][0][0] == '-' && TabDeterministe[i + j][0][0] != '-')
            {
                for (k = 0; k <= 10; k++)
                {
                    for (compteur = 0; compteur < 10; compteur++)
                    {
                        TabDeterministe[i][k][compteur] = TabDeterministe[i + j][k][compteur];
                        TabDeterministe[i + j][k][compteur] = '-';
                    }
                }
            }
        }
    }
    for (i = 1; i < n + 20; i++) // kan3mro les cases dyal les lignes vides b "-"
    {
        for (j = 0; j < m; j++)
        {
            for (k = 0; k < 10; k++)
            {
                if (TabDeterministe[i][j][k] == NULL)
                    TabDeterministe[i][j][k] = '-';
            }
        }
    }
    // stocker les etats finaux lors de la determinisation dans un TabContenueFichierleau nommé EtatFinDetermine[][]
    compteur1 = 0;
    for (i = 1; i <= NbrOccurences3; i++)
    {
        compteur2 = 0;
        for (compteur = 0; compteur < 10; compteur++)
        {
            if (EtatFin[compteur2][0] != '-') // chercher un etat final dans le TabContenueFichierleau des etats finaux EtatFin
            {
                for (j = 0; j < 10; j += 2)
                {
                    if (TabDeterministe[i][0][j] != '-')
                    {
                        if (TabDeterministe[i][0][j] == EtatFin[compteur][0] && TabDeterministe[i][0][j + 1] == EtatFin[compteur][1]) // chercher dans ligne par ligne dans la premiere colonne si on trouve un etat qui existe dans etafin
                        {
                            itoa(i, tochar, 10);                           // itoa ( int value, char * str, int base );
                            EtatFinDeterministe[compteur1][0] = tochar[0]; // changer le nom de l'etat ou il existe  l'etat final
                            EtatFinDeterministe[compteur1][1] = '-';
                            compteur1++;
                        }
                    }
                }
                compteur2 += 2;
            }
            else if (EtatFin[compteur][0] == NULL)
                break;
        }
    }
    // renomer les etats initiaux lors de la determinisation

    for (i = 1; i < 10; i++)
    {
        EtatIni[0][0] = '1';
        EtatIni[0][1] = '-';
        EtatIni[i][0] = NULL;
        EtatIni[i][1] = NULL;
    }
    // Renomer les etats
    int a, b;
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (compteur = 1; compteur <= NbrOccurences3; compteur++)
        {
            for (j = 1; j <= nbalpha; j++)
            {
                y = 0;
                for (k = 0; k < 10; k++)
                {
                    if (TabDeterministe[i][0][k] == TabDeterministe[compteur][j][k] && TabDeterministe[i][0][0] != '-') // si l etat rÃ©cupere (dakchi li west TabContenueFichierleau) est identique  Ã  l etat courant (colonne lowla dial TabContenueFichierleau y3ni les lignes)
                    {
                        y++;
                        a = compteur;
                        b = j;
                    }
                    if (TabDeterministe[i][0][k] != TabDeterministe[compteur][j][k])
                    {
                        y = 0;
                        break;
                    }
                    if (y == 10) // on s' assure que tout Ã©lement de la case sont identique Ã  ceux de la case courante (y3ni l'etat li khdamin 3liha f lcolonne lowla (les etats de depart)) pour renommer tout les cases li kaychbho lhadik d depart tani
                    {
                        compteur3 = 2;
                        itoa(i, tochar, 10);
                        TabDeterministe[a][b][0] = tochar[0];
                        TabDeterministe[a][b][1] = '-';
                        while (compteur3 < 10)
                        {
                            TabDeterministe[a][b][compteur3] = '-';
                            compteur3++;
                        }
                    }
                }
            }
        }
        compteur3 = 1; // renommer les etats de depart y3ni premiÃ¨re colonne
        itoa(i, tochar, 10);
        TabDeterministe[i][0][0] = tochar[0];
        while (compteur3 < 10)
        {
            TabDeterministe[i][0][compteur3] = '-'; // remplir les 9 colonnes restantes de la case par des '-' car au plus on aura 2 digits ce qui donnes 11 colonnes au total (dakchi li 3ndna)
            compteur3++;
        }
    }

    printf("\n");
    printf("les etats initiaux sont : ");
    for (i = 0; i < 10; i++)
    {
        printf("%c%c", EtatIni[i][0], EtatIni[i][1]);
        printf(" ");
    }
    printf("\n");
    printf("les etats finaux sont : ");
    for (i = 0; i < 10; i++)
    {
        printf("%c%c", EtatFinDeterministe[i][0], EtatFinDeterministe[i][1]);
        printf(" ");
    }
    printf("\n");

    // affichage du TabContenueFichierleau determinisation
    printf("\n");
    for (i = 0; i <= NbrOccurences3; i++)
    {
        for (j = 0; j <= nbalpha; j++)
        {
            for (k = 0; k <= 10; k++) // les 11 colonnes dialna dans chaque case
            {
                printf("%c", TabDeterministe[i][j][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
    FILE *file2 = fopen("graphdeterministe.dot", "w+");

    fprintf(file2, "digraph G {\n");
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (j = 1; j <= nbalpha; j++)
        {
            if (TabDeterministe[i][j][0] != '-')
            {
                fprintf(file2, "%c->%c[label=\"%c\"];\n", TabDeterministe[i][0][0], TabDeterministe[i][j][0], TabDeterministe[0][j][0]);
            }
        }
    }
    fprintf(file2, "}\n");
    fclose(file2);
    printf("\nTaper n'importe quelle bouton pour revenir  au menu");
    getch();
}
void Tester1(char mot2[50])
{
    memcpy(mot1, mot2, sizeof mot2); // stocker le contenu du  mot 2 dans mot 1
    etatcourant = '1';
    compteur = 0;
    for (a = 0; a < sizeof(mot1); a++)
    {
        for (j = 1; j <= 3; j++)
        {

            if (mot1[a] == TabDeterministe[0][j][0])
            {
                colonnecherchee = j;
                break;
            }
        }

        for (i = 1; i <= nbligne; i++)
        {
            if (TabDeterministe[i][0][0] == etatcourant)
            {
                if (TabDeterministe[i][colonnecherchee][0] != '-')
                {
                    etatcourant = TabDeterministe[i][colonnecherchee][0];
                    //  printf("L'etat courant %d est %c",a,etatcourant);
                    //  printf("lettre %d acceptee\n",a);
                    break;
                }
                else
                {
                    //  printf("\tlettre %d non accepTabContenueFichierle\n",a);
                    break;
                }
            }
        }
    }
    compteur = 0;
    for (i = 0; i < 10; i++)
    {
        if (etatcourant == EtatFinDeterministe[i][0])
        {
            break;
        }
        compteur++;
    }

    if (compteur != 10)
    {
        printf("%s\n", mot1);
    }
}
void Tester()
{
    printf("entrez le nombre de lettre de votre mot : ");
    scanf("%d", &nbLettre);
    printf("entrez  votre mot : ");
    scanf("%s", mot1);
    etatcourant = '1';
    compteur = 0;
    for (a = 0; a < nbLettre; a++)
    {

        for (j = 1; j <= 3; j++)
        {

            if (mot1[a] == TabDeterministe[0][j][0])
            {
                colonnecherchee = j;
                break;
            }
        }

        for (i = 1; i <= nbligne; i++)
        {
            if (TabDeterministe[i][0][0] == etatcourant)
            {
                if (TabDeterministe[i][colonnecherchee][0] != '-')
                {
                    etatcourant = TabDeterministe[i][colonnecherchee][0];
                    //  printf("L'etat courant %d est %c",a,etatcourant);
                    //  printf("lettre %d acceptee\n",a);
                    break;
                }
                else
                {
                    //  printf("\tlettre %d non accepTabContenueFichierle\n",a);
                    break;
                }
            }
        }
    }
    compteur = 0;
    for (i = 0; i < 10; i++)
    {
        if (etatcourant == EtatFinDeterministe[i][0])
        {

            printf("Mot acceptee\n");
            break;
        }
        compteur++;
    }

    if (compteur == 10)
    {
        printf("Mot non accepte");
    }
    getch();
}
void Minimiser()
{
    /*premier inversemet des arcs*/
    for (i = n - NbrOccurences2; i >= 0; i--) // i travesrse Ã  l'enverse l'intervalle suivant : [0-b] avec b le nombre des lignes non dupliquÃ©s de TabAutomate
    {
        for (k = 0; k <= NbrOccurences; k++) // stocker la premiere colonne du TabAutomate (les etats de depart)dans la premiere ligne du TabMinimisation(considerÃ© comme nouveaux etats d'arrivee)
        {
            TabMinimisation[0][n - NbrOccurences2 - i][k] = TabAutomate[i][0][k];
        }
    }
    for (i = m - NbrOccurences1; i >= 0; i--) // stocker la premiere ligne du TabAutomate (les etats d'arrivee)dans la premiere colonne du TabMinimisation(considerÃ© comme nouveaux etats de depart)
    {
        for (k = 0; k <= NbrOccurences; k++)
        {
            TabMinimisation[m - NbrOccurences1 - i][0][k] = TabAutomate[0][i][k];
        }
    }
    TabMinimisation[0][0][0] = '*';
    for (i = 1; i <= m - NbrOccurences1; i++)
    {
        for (compteur = 1; compteur <= m - NbrOccurences1; compteur++)
        {
            if (TabAutomate[compteur][0][0] == TabMinimisation[0][i][0] && TabAutomate[compteur][0][1] == TabMinimisation[0][i][1])
            {
                for (j = 1; j <= n - NbrOccurences2; j++)
                {
                    if (TabAutomate[compteur][j][0] != '-')
                    {
                        for (k = 1; k <= n - NbrOccurences2; k++)
                        {
                            if (TabAutomate[0][j][0] == TabMinimisation[k][0][0] && TabAutomate[0][j][1] == TabMinimisation[k][0][1])
                            {
                                for (compteur1 = 0; compteur1 < 10; compteur1++)
                                {
                                    TabMinimisation[k][i][compteur1] = TabAutomate[compteur][j][compteur1];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // permutation des etats initiaux et finaux
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 2; j++)
        {
            EtatIniMini[i][j] = EtatFin[i][j];
            EtatFinMini[i][j] = EtatIni[i][j];
        }
    }
    for (i = 0; i < m - NbrOccurences1; i++)
    {
        for (j = 0; j < n - NbrOccurences2; j++)
        {
            for (k = 0; k < 10; k++)
            {
                if (TabMinimisation[i][j][k] == NULL)
                    TabMinimisation[i][j][k] = '-';
            }
            printf(" ");
        }
    }
    /*La premiere determinisation*/
    TabDeterministe[0][0][0] = '*';
    // remplir TabDeterministe  par "-" sauf la premier cellule
    for (i = 1; i < n + 20; i++)
    {
        for (j = 1; j < m; j++)
        {
            for (k = 0; k < 10; k++)
            {
                TabDeterministe[i][j][k] = '-';
            }
        }
    }
    // inserer les alphabets dans le Tableau
    k1 = 1;
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            for (k = 0; k < 10; k++)
            {
                if (TabMinimisation[i][j][k] != '-' && TabMinimisation[i][j][k] != NULL)
                {
                    y = 1;
                    for (compteur = 1; compteur < k1; compteur++)
                    {
                        if (TabDeterministe[0][compteur][0] != TabMinimisation[i][j][k])
                            y++;
                    }
                    if (y == k1)
                    {
                        TabDeterministe[0][k1][0] = TabMinimisation[i][j][k];
                        k1++;
                    }
                }
            }
        }
    }
    // inserer des etats initiaux dans le TabContenueFichierleau
    compteur = 0;
    for (i = 1; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (TabMinimisation[0][j][0] == EtatIniMini[i - 1][0] && TabMinimisation[0][j][1] == EtatIniMini[i - 1][1])
            {
                TabDeterministe[1][0][compteur] = TabMinimisation[0][j][0];
                TabDeterministe[1][0][compteur + 1] = TabMinimisation[0][j][1];
                compteur += 2;
            }
        }
    }
    // calculer le nombre d'alphabet
    nbalpha = 0;
    for (i = 1; i < m; i++)
    {
        if (TabDeterministe[0][i][0] != NULL)
            nbalpha++;
    }
    // Tableau de determinisation
    int compteur4;
    compteur3 = 2;
    for (i = 1; i < n + 20; i++)
    {
        y = 1;
        for (compteur4 = 0; compteur4 < nbalpha; compteur4++)
        {
            compteur2 = 0;
            if (TabDeterministe[i][compteur4 + 1][0] != '-' && TabDeterministe[i][compteur4 + 1][0] != NULL)
                compteur3++;
            for (k = 0; k < 10; k += 2)
            {
                for (compteur = 1; compteur < n; compteur++)
                {
                    if (TabDeterministe[i][0][k] == TabMinimisation[compteur][0][0] && TabDeterministe[i][0][k + 1] == TabMinimisation[compteur][0][1])
                    {
                        for (compteur1 = 1; compteur1 < m; compteur1++)
                        {
                            for (k1 = 0; k1 < 10; k1++)
                            {
                                for (j = 0; j < compteur2; j += 2)
                                {
                                    y = 0;
                                    if (TabDeterministe[i][compteur4 + 1][j] != TabMinimisation[0][compteur1][2 * k1])
                                        y = 1;
                                    if (TabDeterministe[i][compteur4 + 1][j] == TabMinimisation[0][compteur1][2 * k1] && TabDeterministe[i][compteur4 + 1][j + 1] != TabMinimisation[0][compteur1][2 * k1 + 1])
                                        y = 1;
                                    if (TabDeterministe[i][compteur4 + 1][j] == TabMinimisation[0][compteur1][2 * k1] && TabDeterministe[i][compteur4 + 1][j + 1] == TabMinimisation[0][compteur1][2 * k1 + 1])
                                        break;
                                }
                                if (TabDeterministe[0][compteur4 + 1][0] == TabMinimisation[compteur][compteur1][k1])
                                {
                                    if (y == 1)
                                    {
                                        TabDeterministe[i][compteur4 + 1][compteur2] = TabMinimisation[0][compteur1][0];
                                        TabDeterministe[i][compteur4 + 1][compteur2 + 1] = TabMinimisation[0][compteur1][1];
                                        TabDeterministe[compteur3][0][compteur2] = TabMinimisation[0][compteur1][0];
                                        TabDeterministe[compteur3][0][compteur2 + 1] = TabMinimisation[0][compteur1][1];
                                        compteur2 += 2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (TabDeterministe[i][compteur4 + 1][0] != '-' && TabDeterministe[i][compteur4 + 1][0] != NULL)
                compteur3++;
        }
    }
    for (i = 1; i < n + 20; i++)
    {
        for (j = 0; j < m; j++)
        {
            for (k = 0; k <= 12; k++)
            {
                if (TabDeterministe[i][j][k] == NULL)
                    TabDeterministe[i][j][k] = '-';
            }
        }
    }
    // trier les etats de departs et arrivés par ordre croissant
    char temp;
    for (i = 1; i <= 20; i++)
    {
        for (j = 0; j <= nbalpha; j++)
        {
            for (compteur = 0; compteur <= 10; compteur += 2)
            {
                if (TabDeterministe[i][j][compteur + 2] != '-' && TabDeterministe[i][j][compteur + 2] != NULL)
                {
                    for (k = 0; k <= 12; k += 2)
                    {
                        if (TabDeterministe[i][j][k + 2] != '-' && TabDeterministe[i][j][k + 2] != NULL)
                        {
                            if (TabDeterministe[i][j][k] > TabDeterministe[i][j][k + 2])
                            {
                                if (TabDeterministe[i][j][k + 1] > TabDeterministe[i][j][k + 3])
                                {
                                    temp = TabDeterministe[i][j][k + 2];
                                    TabDeterministe[i][j][k + 2] = TabDeterministe[i][j][k];
                                    TabDeterministe[i][j][k] = temp;
                                }
                                if (TabDeterministe[i][j][k + 1] == '-' && TabDeterministe[i][j][k + 3] == '-')
                                {
                                    temp = TabDeterministe[i][j][k + 2];
                                    TabDeterministe[i][j][k + 2] = TabDeterministe[i][j][k];
                                    TabDeterministe[i][j][k] = temp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // suppression de repetition
    for (i = 1; i < n + 10; i++)
    {
        y = 0;
        for (j = 1; j < n + 10; j++)
        {
            if (TabDeterministe[i][0][0] == TabDeterministe[i + j][0][0] && TabDeterministe[i][0][1] == TabDeterministe[i + j][0][1])
            {
                for (k = 2; k <= 12; k += 2)
                {
                    if (TabDeterministe[i][0][k] == TabDeterministe[i + j][0][k] && TabDeterministe[i][0][k + 1] == TabDeterministe[i + j][0][k + 1])
                        y++;
                    if (TabDeterministe[i][0][k] != TabDeterministe[i + j][0][k])
                    {
                        y = 0;
                        break;
                    }
                }
                if (y != 0)
                {
                    for (compteur1 = 0; compteur1 <= nbalpha; compteur1++)
                    {
                        for (compteur2 = 0; compteur2 <= 12; compteur2++)
                        {
                            TabDeterministe[i + j][compteur1][compteur2] = '-';
                        }
                    }
                }
            }
        }
    }
    int NbrOccurences3 = 0;
    for (i = 1; i < n + 10; i++)
    {
        if (TabDeterministe[i][0][0] != '-')
            NbrOccurences3++;
    }
    // supression des lignes vides
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (j = 1; j <= NbrOccurences3; j++)
        {
            if (TabDeterministe[i][0][0] == '-' && TabDeterministe[i + j][0][0] != '-')
            {
                for (k = 0; k <= 12; k++)
                {
                    for (compteur = 0; compteur <= 12; compteur++)
                    {
                        TabDeterministe[i][k][compteur] = TabDeterministe[i + j][k][compteur];
                        TabDeterministe[i + j][k][compteur] = '-';
                    }
                }
            }
        }
    }
    // stocker les etats finaux lors de la determinisation dans un Tableau nommé EtatFinMini[][]
    compteur1 = 0;
    for (i = 1; i <= NbrOccurences3; i++)
    {
        compteur2 = 0;
        for (compteur = 0; compteur < 10; compteur++)
        {
            if (EtatIni[compteur2][0] != '-')
            {
                for (j = 0; j < 10; j += 2)
                {
                    if (TabDeterministe[i][0][j] != '-')
                    {
                        if (TabDeterministe[i][0][j] == EtatIni[compteur][0] && TabDeterministe[i][0][j + 1] == EtatIni[compteur][1])
                        {
                            itoa(i, tochar, 10);
                            EtatFinMini[compteur1][0] = tochar[0];
                            EtatFinMini[compteur1][1] = '-';
                            compteur1++;
                        }
                    }
                }
                compteur2 += 2;
            }
            else if (EtatIni[compteur][0] == NULL)
                break;
        }
    }
    //  renomer les etats initiaux lors de la determinisation
    for (i = 1; i < 10; i++)
    {
        EtatIniMini[0][0] = '1';
        EtatIniMini[0][1] = '-';
        EtatIniMini[i][0] = NULL;
        EtatIniMini[i][1] = NULL;
    }
    // renomer les etats
    int a, b;
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (compteur = 1; compteur <= NbrOccurences3; compteur++)
        {
            for (j = 1; j <= nbalpha; j++)
            {
                y = 0;
                for (k = 0; k <= 12; k++)
                {
                    if (TabDeterministe[i][0][k] == TabDeterministe[compteur][j][k] && TabDeterministe[i][0][0] != '-')
                    {
                        y++;
                        a = compteur;
                        b = j;
                    }
                    if (TabDeterministe[i][0][k] != TabDeterministe[compteur][j][k])
                    {
                        y = 0;
                        break;
                    }
                    if (y == 10)
                    {
                        compteur3 = 2;
                        itoa(i, tochar, 10);
                        TabDeterministe[a][b][0] = tochar[0];
                        TabDeterministe[a][b][1] = '0';
                        while (compteur3 < 20)
                        {
                            TabDeterministe[a][b][compteur3] = '-';
                            compteur3++;
                        }
                    }
                }
            }
        }
        compteur3 = 1;
        itoa(i, tochar, 10);
        TabDeterministe[i][0][0] = tochar[0];
        while (compteur3 < 20)
        {
            TabDeterministe[i][0][compteur3] = '-';
            compteur3++;
        }
    }
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (j = 1; j <= nbalpha; j++)
        {
            for (k = 0; k <= 10; k++)
            {
                if (TabDeterministe[i][j][k] == '0')
                    TabDeterministe[i][j][k] = '-';
            }
        }
    }
    /*Deuxieme phase de traitement : extraction de deuxieme Tableau*/

    for (i = 0; i <= NbrOccurences3; i++)
    {
        for (k = 0; k <= 10; k++)
        {
            TabMinimisation_1[i][0][k] = TabDeterministe[i][0][k];
            TabMinimisation_1[0][i][k] = TabDeterministe[i][0][k];
        }
    }
    for (i = 1; i <= NbrOccurences3; i++)
    {
        compteur2 = 0;
        if (TabMinimisation_1[i][0][0] == TabDeterministe[i][0][0] && TabMinimisation_1[i][0][1] == TabDeterministe[i][0][1])
        {
            for (j = 1; j <= nbalpha; j++)
            {
                for (compteur = 1; compteur <= NbrOccurences3; compteur++)
                {
                    if (TabDeterministe[i][j][0] == TabMinimisation_1[0][compteur][0] && TabDeterministe[i][j][1] == TabMinimisation_1[0][compteur][1])
                    {
                        TabMinimisation_1[i][compteur][compteur2] = TabDeterministe[0][j][0];
                        if (TabDeterministe[i][j][0] == TabDeterministe[i][j + 1][0] && TabDeterministe[i][j][1] == TabDeterministe[i][j + 1][1])
                            compteur2++;
                    }
                }
            }
        }
    }
    for (i = 0; i <= NbrOccurences3; i++)
    {
        for (j = 0; j <= NbrOccurences3; j++)
        {
            for (k = 0; k <= 10; k++)
            {
                if (TabMinimisation_1[i][j][k] == NULL)
                    TabMinimisation_1[i][j][k] = '-';
            }
            printf(" ");
        }
    }

    /*Inversement du deuxieme TabContenueFichierleau*/
    // Changement de direction des arcs
    for (i = NbrOccurences3; i >= 0; i--)
    {
        for (k = 0; k <= NbrOccurences; k++)
        {
            TabMinimisation_2[0][NbrOccurences3 - i + 1][k] = TabMinimisation_1[i][0][k];
        }
    }
    for (i = NbrOccurences3; i >= 0; i--)
    {
        for (k = 0; k <= NbrOccurences; k++)
        {
            TabMinimisation_2[NbrOccurences3 - i + 1][0][k] = TabMinimisation_1[0][i][k];
        }
    }
    TabMinimisation_2[0][0][0] = '*';
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (compteur = 1; compteur <= NbrOccurences3; compteur++)
        {
            if (TabMinimisation_2[compteur][0][0] == TabMinimisation_1[0][i][0] && TabMinimisation_2[compteur][0][1] == TabMinimisation_1[0][i][1])
            {
                for (j = 1; j <= n - NbrOccurences2; j++)
                {
                    if (TabMinimisation_1[compteur][j][0] != '-')
                    {
                        for (k = 1; k <= NbrOccurences3; k++)
                        {
                            if (TabMinimisation_2[0][j][0] == TabMinimisation_1[k][0][0] && TabMinimisation_2[0][j][1] == TabMinimisation_1[k][0][1])
                            {
                                for (compteur1 = 0; compteur1 < 10; compteur1++)
                                {
                                    TabMinimisation_2[k][i][compteur1] = TabMinimisation_1[compteur][j][compteur1];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Changement des etats initiaux et finaux
    char EtatIniMini_1[10][2], EtatFinMini_1[10][2];
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 2; j++)
        {
            EtatIniMini_1[i][j] = EtatFinMini[i][j];
            EtatFinMini_1[i][j] = EtatIniMini[i][j];
        }
    }
    for (i = 0; i <= NbrOccurences3; i++)
    {
        for (j = 0; j <= NbrOccurences3; j++)
        {
            for (k = 0; k <= 10; k++)
            {
                if (TabMinimisation_2[i][j][k] == NULL)
                    TabMinimisation_2[i][j][k] = '-';
            }
            printf(" ");
        }
    }

    /*Determinisation du deuxieme Tableau*/

    TabDeterministe[0][0][0] = '*';
    // remplir TabDeterministe  par "-" sauf la premier cellule
    for (i = 1; i < n + 20; i++)
    {
        for (j = 1; j < m; j++)
        {
            for (k = 0; k < 10; k++)
            {
                TabDeterministe[i][j][k] = '-';
            }
        }
    }
    // inserer les alphabet dans le TabContenueFichierleau
    k1 = 1;
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            for (k = 0; k < 10; k++)
            {
                if (TabMinimisation_2[i][j][k] != '-' && TabMinimisation_2[i][j][k] != NULL)
                {
                    y = 1;
                    for (compteur = 1; compteur < k1; compteur++)
                    {
                        if (TabDeterministe[0][compteur][0] != TabMinimisation_2[i][j][k])
                            y++;
                    }
                    if (y == k1)
                    {
                        TabDeterministe[0][k1][0] = TabMinimisation_2[i][j][k];
                        k1++;
                    }
                }
            }
        }
    }
    // inserer les etats initiaux dans la premiere colonne et la deuxieme ligne du TabMinimisation cad remplir la premier cellule du deuxieme ligne
    compteur = 0;
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (TabMinimisation_2[j][0][0] == EtatIniMini_1[i - 1][0] && TabMinimisation_2[j][0][1] == EtatIniMini_1[i - 1][1])
            {
                TabDeterministe[1][0][compteur] = TabMinimisation_2[j][0][0];
                TabDeterministe[1][0][compteur + 1] = TabMinimisation_2[j][0][1];
                compteur += 2;
            }
        }
    }
    // calculer le nombre d'alphabet
    nbalpha = 0;
    for (i = 1; i < m; i++)
    {
        if (TabDeterministe[0][i][0] != NULL)
            nbalpha++;
    }
    // Tableau de determinisation
    compteur3 = 2;
    for (i = 1; i < n + 20; i++)
    {
        y = 1;
        for (compteur4 = 0; compteur4 < nbalpha; compteur4++)
        {
            compteur2 = 0;
            if (TabDeterministe[i][compteur4 + 1][0] != '-' && TabDeterministe[i][compteur4 + 1][0] != NULL)
                compteur3++;
            for (k = 0; k < 10; k += 2)
            {
                for (compteur = 1; compteur < n; compteur++)
                {
                    if (TabDeterministe[i][0][k] == TabMinimisation_2[compteur][0][0] && TabDeterministe[i][0][k + 1] == TabMinimisation_2[compteur][0][1])
                    {
                        for (compteur1 = 1; compteur1 < m; compteur1++)
                        {
                            for (k1 = 0; k1 < 10; k1++)
                            {
                                for (j = 0; j < compteur2; j += 2)
                                {
                                    y = 0;
                                    if (TabDeterministe[i][compteur4 + 1][j] != TabMinimisation_2[0][compteur1][2 * k1])
                                        y = 1;
                                    if (TabDeterministe[i][compteur4 + 1][j] == TabMinimisation_2[0][compteur1][2 * k1] && TabDeterministe[i][compteur4 + 1][j + 1] != TabMinimisation_2[0][compteur1][2 * k1 + 1])
                                        y = 1;
                                    if (TabDeterministe[i][compteur4 + 1][j] == TabMinimisation_2[0][compteur1][2 * k1] && TabDeterministe[i][compteur4 + 1][j + 1] == TabMinimisation_2[0][compteur1][2 * k1 + 1])
                                        break;
                                }
                                if (TabDeterministe[0][compteur4 + 1][0] == TabMinimisation_2[compteur][compteur1][k1])
                                {
                                    if (y == 1)
                                    {
                                        TabDeterministe[i][compteur4 + 1][compteur2] = TabMinimisation_2[0][compteur1][0];
                                        TabDeterministe[i][compteur4 + 1][compteur2 + 1] = TabMinimisation_2[0][compteur1][1];
                                        TabDeterministe[compteur3][0][compteur2] = TabMinimisation_2[0][compteur1][0];
                                        TabDeterministe[compteur3][0][compteur2 + 1] = TabMinimisation_2[0][compteur1][1];
                                        compteur2 += 2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (TabDeterministe[i][compteur4 + 1][0] != '-' && TabDeterministe[i][compteur4 + 1][0] != NULL)
                compteur3++;
        }
    }
    /*INITIALISATION DES CASES VIDES AVEC DES'-' */
    for (i = 1; i < n + 20; i++)
    {
        for (j = 0; j < m; j++)
        {
            for (k = 0; k <= 12; k++)
            {
                if (TabDeterministe[i][j][k] == NULL)
                    TabDeterministe[i][j][k] = '-';
            }
        }
    }
    // tri des valeurs dans le TabContenueFichierleau deterministe
    temp;
    for (i = 1; i <= 20; i++)
    {
        for (j = 0; j <= nbalpha; j++)
        {
            for (compteur = 0; compteur <= 10; compteur += 2)
            {
                if (TabDeterministe[i][j][compteur + 2] != '-' && TabDeterministe[i][j][compteur + 2] != NULL)
                {
                    for (k = 0; k <= 10; k += 2)
                    {
                        if (TabDeterministe[i][j][k + 2] != '-' && TabDeterministe[i][j][k + 2] != NULL)
                        {
                            if (TabDeterministe[i][j][k] > TabDeterministe[i][j][k + 2])
                            {
                                if (TabDeterministe[i][j][k + 1] > TabDeterministe[i][j][k + 3])
                                {
                                    temp = TabDeterministe[i][j][k + 2];
                                    TabDeterministe[i][j][k + 2] = TabDeterministe[i][j][k];
                                    TabDeterministe[i][j][k] = temp;
                                }
                                if (TabDeterministe[i][j][k + 1] == '-' && TabDeterministe[i][j][k + 3] == '-')
                                {
                                    temp = TabDeterministe[i][j][k + 2];
                                    TabDeterministe[i][j][k + 2] = TabDeterministe[i][j][k];
                                    TabDeterministe[i][j][k] = temp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // suppression de repetition
    for (i = 1; i < n + 10; i++)
    {
        y = 0;
        for (j = 1; j < n + 10; j++)
        {
            if (TabDeterministe[i][0][0] == TabDeterministe[i + j][0][0] && TabDeterministe[i][0][1] == TabDeterministe[i + j][0][1])
            {
                for (k = 2; k <= 10; k += 2)
                {
                    if (TabDeterministe[i][0][k] == TabDeterministe[i + j][0][k] && TabDeterministe[i][0][k + 1] == TabDeterministe[i + j][0][k + 1])
                        y++;
                    if (TabDeterministe[i][0][k] != TabDeterministe[i + j][0][k])
                    {
                        y = 0;
                        break;
                    }
                }
                if (y != 0)
                {
                    for (compteur1 = 0; compteur1 <= nbalpha; compteur1++)
                    {
                        for (compteur2 = 0; compteur2 < 10; compteur2++)
                        {
                            TabDeterministe[i + j][compteur1][compteur2] = '-';
                        }
                    }
                }
            }
        }
    }
    NbrOccurences3 = 0;
    for (i = 1; i < n + 10; i++)
    {
        if (TabDeterministe[i][0][0] != '-')
            NbrOccurences3++;
    }
    // supression des lignes vides
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (j = 1; j <= NbrOccurences3; j++)
        {
            if (TabDeterministe[i][0][0] == '-' && TabDeterministe[i + j][0][0] != '-')
            {
                for (k = 0; k <= 10; k++)
                {
                    for (compteur = 0; compteur < 10; compteur++)
                    {
                        TabDeterministe[i][k][compteur] = TabDeterministe[i + j][k][compteur];
                        TabDeterministe[i + j][k][compteur] = '-';
                    }
                }
            }
        }
    }
    // stocker les etats finaux lors de la determinisation dans un TabContenueFichierleau nommé EtatFinMini_1[][]
    compteur1 = 0;
    for (i = 1; i <= NbrOccurences3; i++)
    {
        compteur2 = 0;
        for (compteur = 0; compteur < 10; compteur++)
        {
            if (EtatIni[compteur2][0] != '-')
            {
                for (j = 0; j < 10; j += 2)
                {
                    if (TabDeterministe[i][0][j] != '-')
                    {
                        if (TabDeterministe[i][0][j] == EtatIni[compteur][0] && TabDeterministe[i][0][j + 1] == EtatIni[compteur][1])
                        {
                            itoa(i, tochar, 10);
                            EtatFinMini_1[compteur1][0] = tochar[0];
                            EtatFinMini_1[compteur1][1] = '-';
                            compteur1++;
                        }
                    }
                }
                compteur2 += 2;
            }
            else if (EtatIni[compteur][0] == NULL)
                break;
        }
    }
    //  renomer les etats initiaux lors de la determinisation
    for (i = 1; i < 10; i++)
    {
        EtatIniMini_1[0][0] = '1';
        EtatIniMini_1[0][1] = '-';
        EtatIniMini_1[i][0] = NULL;
        EtatIniMini_1[i][1] = NULL;
    }
    // renomer les etats
    a, b;
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (compteur = 1; compteur <= NbrOccurences3; compteur++)
        {
            for (j = 1; j <= nbalpha; j++)
            {
                y = 0;
                for (k = 0; k < 10; k++)
                {
                    if (TabDeterministe[i][0][k] == TabDeterministe[compteur][j][k] && TabDeterministe[i][0][0] != '-')
                    {
                        y++;
                        a = compteur;
                        b = j;
                    }
                    if (TabDeterministe[i][0][k] != TabDeterministe[compteur][j][k])
                    {
                        y = 0;
                        break;
                    }
                    if (y == 10)
                    {
                        compteur3 = 2;
                        itoa(i, tochar, 10);
                        TabDeterministe[a][b][0] = tochar[0];
                        TabDeterministe[a][b][1] = '0';
                        while (compteur3 < 20)
                        {
                            TabDeterministe[a][b][compteur3] = '-';
                            compteur3++;
                        }
                    }
                }
            }
        }
        compteur3 = 1;
        itoa(i, tochar, 10);
        TabDeterministe[i][0][0] = tochar[0];
        while (compteur3 < 20)
        {
            TabDeterministe[i][0][compteur3] = '-';
            compteur3++;
        }
    }
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (j = 1; j <= nbalpha; j++)
        {
            for (k = 0; k <= 10; k++)
            {
                if (TabDeterministe[i][j][k] == '0')
                    TabDeterministe[i][j][k] = '-';
            }
        }
    }
    printf("\n");
    printf("les etats initiaux sont : ");
    for (i = 0; i < 10; i++)
    {
        printf("%c%c", EtatIniMini_1[i][0], EtatIniMini_1[i][1]);
        printf(" ");
    }
    printf("\n");
    printf("les etats finaux sont : ");
    for (i = 0; i < 10; i++)
    {
        printf("%c%c", EtatFinMini_1[i][0], EtatFinMini_1[i][1]);
        printf(" ");
    }
    printf("\n");
    // affichage de Tableau de determinisation
    printf("\n");
    for (i = 0; i <= NbrOccurences3; i++)
    {
        for (j = 0; j <= nbalpha; j++)
        {
            for (k = 0; k <= 10; k++)
            {
                printf("%c", TabDeterministe[i][j][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    // ECRITURE DANS LE FICHIER ET AFFICHAGE DE GRAPHE MINIMISER
    FILE *file4 = fopen("GraphMini.dot", "w+");

    fprintf(file4, "digraph G {\n");
    for (i = 1; i <= NbrOccurences3; i++)
    {
        for (j = 1; j <= nbalpha; j++)
        {
            if (TabDeterministe[i][j][0] != '-')
            {
                fprintf(file4, "%c->%c[label=\"%c\"];\n", TabDeterministe[i][0][0], TabDeterministe[i][j][0], TabDeterministe[0][j][0]);
            }
        }
    }
    fprintf(file4, "}\n");
    fclose(file4);
    printf("\nTaper n'importe quelle bouton pour revenir  au menu");
    getch();
}
void menu()
{
   system("cls"); // clean the screen of output
    printf("Choose option :\n");
    printf("\t\t|1- Implementer votre graphe \t\t\t\t|\n");
    printf("\t\t|2- Affichage du automate passe en parametre\t\t|\n");
    printf("\t\t|3- autommate deterministe\t\t\t\t|\n");
    printf("\t\t|4- Tester si un mot est engendre par cet automate\t|\n");
    printf("\t\t|5- Afficher les mots engendres par l'automate\t\t|\n");
    printf("\t\t|6- Minimisation\t\t\t\t\t|\n");
    printf("\t\t|7- Quitter\t\t\t\t\t\t|\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("Entrer Votre Choix : ");
}
int main()
{
    do
    {
        menu();
        scanf("%d", &Choix);
        if (Choix == 1)
        {
            Saisir();
        }
        if (Choix == 2)
        {
            Affichage();
        }
        if (Choix == 3)
        {
            Determiniser();
        }
        if (Choix == 4)
        {
            Tester();
        }
        if (Choix == 5)
        {
            FILE *fp;
            printf("Veuillez entrer le nom du fichier contenant les mots a tester :");
            scanf("%s", NomFiche);

            fp = fopen(NomFiche, "r");
            if (fp == NULL)
            {
                printf("There has been an error\n");
                getch();
                exit(1);
            }
            while (!feof(fp))
            {
                fgets(mot1, 150, fp);
                strtok(mot1, "\n"); // Removing new lins generated by fgets/
                // puts(mot1);
                // printf("\n");
                Tester1(mot1);
            }
            // printf("\nChercher le fichier file.txt et voir les mots engendre par votre automate.");
            getch();
            fclose(fp);
        }
        if (Choix == 6)
        {
            Minimiser();
        }
        if (Choix == 7)
        {
            printf("\tAppuyer Sur N'importe Quel Button Pour Quitter\n");
        }

    } while (Choix != 7);
}
