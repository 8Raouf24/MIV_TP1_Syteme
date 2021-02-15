#include <stdio.h> 
#include <stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/* Echanger deux variables */
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}


/* Afficher les éléments d'un tableau */
void afficher_tab(int tab[], int start, int end) 
{ 
    int i; 
    for (i=start; i < end; i++) 
        printf("%d ", tab[i]); 
    printf("\n"); 
    
    return;
} 


/* Fonction qui effectue le tri */
void tri_rapide(int * tab, int first, int last) 
{ 
    
    if(first>=last) 
    {if (first == last){
    printf("Le processus %d à traiter le tableau suivant:",getpid());
    printf("TAB[%d] = %d\n", last, tab[last]);}
    return;}
    
    int pivot_value = tab[(last + first) / 2];
    
    int i=first;
    int j=last;
    

    while(i<j){
     
        while((tab[i] < pivot_value)&&(i<j)) i++;
        while((tab[j] > pivot_value)&&(i<j)) j--;
          
        if(i == j) break;

        swap(&tab[i], &tab[j]);
    }
    printf("Le processus %d à traiter le tableau suivant:",getpid());
    printf("TAB[%d] = %d\n", j, pivot_value);
    // Appel de la fonction pour trier les parties droite et gauche
    
    int fils1 = fork();
    if(fils1==0){
        tri_rapide(tab, first, j-1);
        exit(0);
    }
    
    int fils2 = fork();
    if(fils2==0){
        tri_rapide(tab, j+1, last);
        exit(0);
    }
    wait(0);
    wait(0);
    return;
    
    
} 

 
 
int main() 
{
    /*
    int n;
    printf("\nEntrer la longueur du tableau : ");
    scanf("%d", &n);
    printf("\n");
    int tab[n];
    for(int i=0; i<n; i++){
        printf("Tab[%d] = ", i);
        scanf("%d", &tab[i]);
    }*/
    
    //  0 1 2 3  4  5  6  7  8  9   10  11  12  13
    //  0 2 4 12 21 32 45 64 98 322 342 434 567 1334
    int n = 14;
    int tab[] = {32, 434,2, 45,64,322,567,4,342,21,1334,12,98,0};
    afficher_tab(tab, 0,n);
    
    
    tri_rapide(tab, 0, n-1); 
    printf("\n\nTableau trié :\n"); 
    afficher_tab(tab, 0, n); 
    return 0; 
} 