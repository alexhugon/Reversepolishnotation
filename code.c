#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAILLEINPUT 11
int err =0;
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
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

void afficherpile(pile* niveau, int etage) /* Affiche les valeurs des différents niveau de la pile */
{
    if ( niveau != NULL && etage < 20) 
    {
        afficherpile(niveau->suivant, etage + 1);
        printf("%d", niveau->valeur);
        if ( etage != 0){printf(" ");}
    }
}
int intoupas (char instruction[TAILLEINPUT])
{
    int i;
    for ( i = 0; i < TAILLEINPUT && instruction[i] != '\0'; i++ )
        if ( instruction[0] != '-' && !isdigit(instruction[i]) ) 
            return 0;
    return 1;
}
int transformint (char instruction[TAILLEINPUT])
{
    char *ptr;
    return strtol(instruction, &ptr, 10);
}
pile* pop( pile* niveau )
{
    pile* precedent = NULL;
    if ( niveau != NULL ) 
    {
        precedent = niveau->suivant;
        free(niveau);
    }
    return precedent;
}
pile* divi( pile* niveau )
{
    if ( niveau == NULL ) 
        return NULL;
    if ( niveau->suivant == NULL ) 
    {
        err = 1;
        niveau = pop(niveau);
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    if ( droit == 0 )
    {
        err = 1;
        niveau = pop(niveau);
        niveau = pop(niveau);
        return niveau;
    }
    pile* suivant = niveau->suivant->suivant;
    free(niveau->suivant);
    free(niveau);
    return ajoutpile(suivant, pilesuivant(gauche/droit, suivant));
}
pile* mul( pile* niveau )
{
    if ( niveau == NULL ) 
        return NULL;
    if ( niveau->suivant == NULL ) 
    {
        err = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau->suivant);
    free(niveau);
    return ajoutpile(suivant, pilesuivant(gauche*droit, suivant));
}

pile* mod( pile* niveau )
{
    if ( niveau == NULL ) 
        return NULL;
    if ( niveau->suivant == NULL ) 
    {
        err = 1;
        free(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau->suivant);
    free(niveau);
    return ajoutpile(suivant, pilesuivant(gauche%droit, suivant));
}


pile* rol( pile* prec, pile* niveau, int o)
{
    if ( prec == NULL || niveau == NULL ) 
    {
        err = 1;
        return 0;
    }
    if ( o == 1 )
    {
        pile* suivant = niveau->suivant;
        int valeur = niveau->valeur;
        free(niveau); 
        prec->suivant = suivant;
        return valeur;
    }
    else
         return rol ( niveau, niveau->suivant, o-1 );
}
pile* swp( pile* niveau )
{
    if ( niveau == NULL )
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
    if ( niveau == NULL ) 
        return NULL;
    if ( niveau->suivant == NULL )
    {
        err = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau->suivant);
    free(niveau);
    return ajoutpile(suivant, pilesuivant(gauche-droit, suivant));
}

pile* add( pile* niveau ) /* addition */
{
    if ( niveau == NULL )
        return NULL;
    if ( niveau->suivant == NULL )
    {
        err = 1;
        niveau = pop(niveau);
        return niveau;
    }
    int gauche = niveau->suivant->valeur, droit = niveau->valeur;
    pile* suivant = niveau->suivant->suivant;
    free(niveau->suivant);
    free(niveau);
    return ajoutpile(suivant, pilesuivant(gauche+droit, suivant));
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
    else if ( !strcmp("SWP", instruction) )
        commande = swp(commande);
    else if ( !strcmp("DUP", instruction) )
        commande = dup(commande);
    else if ( !strcmp("POP", instruction) )
        commande = pop(commande);
    else if ( !strcmp("MOD", instruction) )
        commande = mod(commande);
    else if ( !strcmp("DIV", instruction) )
        commande = divi(commande);
    else if ( !strcmp("MUL", instruction) )
        commande = mul(commande);
    else if ( !strcmp("SUB", instruction) )
        commande = sub(commande);
    else if ( !strcmp("ADD", instruction) )
        commande = add(commande);
    else
        err = 1;
    return commande;
}

int main()
{
    
    int N;
    scanf("%d", &N);
    pile* commande = NULL;
    for (int i = 0; i < N; i++) {
        char instruction[TAILLEINPUT];
        scanf("%s", instruction);
        if ( intoupas(instruction) )
            commande = ajoutpile(commande, pilesuivant(transformint(instruction), commande));
        else
            commande = operation(commande, instruction);
        
        
    }
    afficherpile(commande,0);
    if ( err == 1)
    {
         printf(" ERROR");
    }
    printf("\n");
    supprime(commande);

    return 0;
}