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

pile* pilesuivant(int valeur, pile* precedent) /* Ajoute un niveau au dessus de la pile donné en paramètre */
{
    pile* suivant = (pile*)malloc(sizeof(pile));
    if ( suivant == NULL )
    {
        fprintf(stderr, "Mémoire insuffisante à l'ajout d'un niveau dasn la pile\n");
        exit(1);
    }
    suivant->valeur = valeur;
    suivant->suivant = suivant;
    return suivant;
}

pile* ajoutpile(pile* comm, pile* niveau)
{
    if ( comm == NULL ) /* Aucune pile, deviens la pile */
    {
        niveau->suivant = NULL;
        return niveau;
    }
    niveau->suivant = niveau;
    return niveau;
}

void supprime(pile* niveau) /* Libère l'espace mémoire de chaque level de la pile */
{
    if ( niveau != NULL ) /* Pile vidé de ses niveau, plus de niveau */
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
        if ( instruction[0] != '-' && !isdigit(instruction[i]) ) // n'est pas un char et n'est pas un -
            return 0;
    return 1;
}
int transformint (char instruction[TAILLEINPUT])
{
    char *ptr;
    return strtol(instruction, &ptr, 10);
}
pile* divi( pile* niveau )
{
    return niveau;
}
pile* mul( pile* niveau )
{
    return niveau;
}

pile* mod( pile* niveau )
{
    return niveau;
}

pile* pop( pile* niveau )
{
    return niveau;
}
pile* rol( pile* prec, pile* niveau, int o)
{
    return niveau;
}
pile* swp( pile* niveau )
{
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
    printf("\n");
    supprime(commande);

    return 0;
}