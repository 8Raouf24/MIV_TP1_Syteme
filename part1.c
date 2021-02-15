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
    
    if(first>=last) return;
    
    int pivot_value = tab[(last + first) / 2];
    
    int i=first;
    int j=last;
    

    while(i<j){
     
        while((tab[i] < pivot_value)&&(i<j)) i++;
        while((tab[j] > pivot_value)&&(i<j)) j--;
          
        if(i == j) break;

        swap(&tab[i], &tab[j]);
    }
    
    // Appel de la fonction pour trier les parties droite et gauche
    tri_rapide(tab, first, j-1);
    tri_rapide(tab, j+1, last);
    
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
    
    
    int n = 14;
    int tab[] = {32, 434,2, 45,64,322,567,4,342,21,1334,12,98,0};
    afficher_tab(tab, 0,n);
    
    
    tri_rapide(tab, 0, n-1); 
    printf("\n\nTableau trié :\n"); 
    afficher_tab(tab, 0, n); 
    return 0; 
} 