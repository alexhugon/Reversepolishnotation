#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAILLEINPUT 11
int erreur =0;


typedef struct pile
{
        int valeur;
        struct pile* suivant;
}pile;
 

pile* pilesuivant(int valeur, pile* precedent) /* niveau de pile en plus */
{
    pile* suivant = (pile*)malloc(sizeof(pile));
    if ( suivant == NULL )
    {
        fprintf(stderr, "Mémoire insuffisante \n");
        exit(1);
    }
    suivant->valeur = valeur;
    suivant->suivant = precedent;
    return suivant;
}

pile* ajoutpile(pile* comm, pile* niveau)
{
    if ( comm == NULL ) /* si rien pour le moment, débute une pile*/
    {
        niveau->suivant = NULL;
        return niveau;
    }
    niveau->suivant = comm;
    return niveau;
}

void supprime(pile* niveau) 
{
    if ( niveau != NULL ) 
    {
        supprime(niveau->suivant);
        free(niveau);
    }
}

void afficherpile(pile* niveau, int etage) /* On affiche la pile */
{
    if ( niveau != NULL) 
    {
        afficherpile(niveau->suivant, etage + 1);
        printf("%d", niveau->valeur);
        if ( etage != 0){printf(" ");}
    }
}
int intoupas (char instruction[TAILLEINPUT])  /* POURQUOI TU INT ! */
{
    int i;
    for ( i = 0; i < TAILLEINPUT && instruction[i] != '\0'; i++ )
        if ( instruction[0] != '-' && !isdigit(instruction[i]) ) 
            return 0;
    return 1;
}
int transformint (char instruction[TAILLEINPUT]) /* transforme en int..... */
{
    char *ptr;
    return strtol(instruction, &ptr, 10);
}
pile* pop( pile* niveau )  /* Snap fingers */
{
    pile* precedent = NULL;
    if ( niveau != NULL ) 
    {
        precedent = niveau->suivant;
        free(niveau);
    }
    return precedent;
}
pile* divi( pile* niveau )  /* division */
{
    if ( niveau == NULL)
        return NULL;
    if ( niveau->suivant == NULL ) 
    {
        erreur = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    if ( droit == 0 )
    {
        erreur = 1;
        niveau = pop(niveau);
        niveau = pop(niveau);
        return niveau;
    }
    pile* suivant = niveau->suivant->suivant;
    free(niveau);
    free(niveau->suivant);
    return ajoutpile(suivant, pilesuivant(gauche/droit, suivant));
}
pile* mul( pile* niveau ) /* Multiplication */
{
    if ( niveau == NULL)
        return NULL;
    if ( niveau->suivant == NULL ) 
    {
        erreur = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau);
    free(niveau->suivant);
    return ajoutpile(suivant, pilesuivant(gauche*droit, suivant));
}

pile* mod( pile* niveau ) /* MODULO */
{
    if ( niveau == NULL)
        return NULL;
    if ( niveau->suivant == NULL ) 
    {
        erreur = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau);
    free(niveau->suivant);
    return ajoutpile(suivant, pilesuivant(gauche%droit, suivant));
}


pile* rol( pile* prec, pile* niveau, int o)  /* DO A BARRELROLL*/
{
    if ( prec == NULL || niveau == NULL ) 
    {
        erreur = 1;
        return 0;
    }
    if ( o == 1 )
    {
        pile* swap = niveau->suivant;
        int num = niveau->valeur;
        free(niveau); 
        prec->suivant = swap;
        return num;
    }
    else
         return rol ( niveau, niveau->suivant, o-1 );
}
pile* swp( pile* niveau ) /* SWAP */
{
    if ( niveau == NULL)
        return NULL;
    if ( niveau->suivant != NULL )
    {
        int swap = niveau->valeur;
        niveau->valeur = niveau->suivant->valeur;
        niveau->suivant->valeur = swap;
    }
    return niveau;
}

pile* sub( pile* niveau ) /* soustraction */
{
    if ( niveau == NULL)
        return NULL;
    if ( niveau->suivant == NULL )
    {
        erreur = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau);
    free(niveau->suivant);
    return ajoutpile(suivant, pilesuivant(gauche-droit, suivant));
}

pile* add( pile* niveau ) /* addition */
{
    if ( niveau == NULL)
        return NULL;
    if ( niveau->suivant == NULL )
    {
        erreur = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau);
    free(niveau->suivant);
    return ajoutpile(suivant, pilesuivant(gauche+droit, suivant));
}
pile* dup(pile* niveau)
{
   if ( niveau == NULL )
        return NULL;
    return ajoutpile(niveau, pilesuivant(niveau->valeur, niveau));
}


pile* operation ( pile* commande, char instruction[TAILLEINPUT] )
{
    if ( !strcmp("ROL", instruction) )
    {
        int n = commande->valeur;
        commande = pop(commande);
        n = rol(commande, commande->suivant, n-1);
        commande = ajoutpile(commande, pilesuivant(n, commande));
    }
    else if ( !strcmp("SWP", instruction))
        commande = swp(commande);
    else if ( !strcmp("DUP", instruction))
        commande = dup(commande);
    else if ( !strcmp("DUP", instruction))
        commande = dup(commande);
    else if ( !strcmp("POP", instruction))
        commande = pop(commande);
    else if ( !strcmp("MOD", instruction))
        commande = mod(commande);
    else if ( !strcmp("DIV", instruction))
        commande = divi(commande);
    else if ( !strcmp("MUL", instruction))
        commande = mul(commande);
    else if ( !strcmp("SUB", instruction))
        commande = sub(commande);
    else if ( !strcmp("ADD", instruction))
        commande = add(commande);
    else
        erreur = 1;
    return commande;
}

int main()
{
    pile* commande = NULL;
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N && erreur != 1; i++) 
    {
        char instruction[TAILLEINPUT];
        scanf("%s", instruction);
        
        if (intoupas(instruction))
        {
            commande = ajoutpile(commande, pilesuivant(transformint(instruction), commande));
        }
        else
        {
            commande = operation(commande, instruction);
        }
        
    }
    afficherpile(commande,0);
    if ( erreur == 1)
    {
        if (commande != NULL )
        {
            printf(" ");
        }
        printf("ERROR");
    }
    
    printf("\n");
    supprime(commande);

    return 0;
}