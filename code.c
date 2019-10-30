#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAILLEINPUT 11
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
    suivant->precedent = precedent;
    return suivant;
}

void afficherpile(pile* niveau) /* Affiche les valeurs des différents niveau de la pile, en partant du BAS vers le HAUT */
{
    if ( level != NULL ) /* Plus de niveau inférieur, on a fini de parcourir la pile */
    {
        afficherpile(niveau->suivant);
        printf("%d", niveau->valeur); /* du bas vers le haut, à passer au dessus de l'instruction pile_show(level->under); pour inverser */
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
    return strtol(instruction, &ptr, CONVERTION_BASE);
}
pile* operation ( pile* commande, char instruction[TAILLEINPUT] )
{
    if ( !strcmp("ROL", instruction) )
    {
        int n = commande->value;
        commande = commande_pop(commande);
        n = pile_rol(commande, commande->under, n-1);
        commande = level_add(commande, pilesuivant(n, commande));
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
        commande = div(commande);
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
    pile commande = NULL;
    for (int i = 0; i < N; i++) {
        char instruction[TAILLEINPUT];
        scanf("%s", instruction);
        if ( intoupas(instruction) )
            commande = pilesuivant(transformint(instruction), commande);
        else
            commande = operation(commande, instruction);
        
        
    }

    // Write an action using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    printf("answer\n");

    return 0;
}