#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>


// Déclaration des variables globales 
int tab[] = {32, 434,2, 45,64,322,567,4,342,21,1334,12,98,0};
void *orderTable(void *vargp);
void tri_rapide(int first, int last) ;

// Nous utiliserons cette enregistrement en tant qu'argument pour nos threads ,"f" sera l'index du "First element " et "l" le "Last element "
struct argsTab
{
    int f;
    int l;
};

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

  
void tri_rapide(int first, int last) 
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
    pthread_t thread1;
        struct argsTab arg1;
    arg1.f=first;
    arg1.l=j;
    pthread_create(&thread1,NULL,orderTable,&arg1);

    pthread_t thread2;
        struct argsTab arg2;
    arg2.f=j+1;
    arg2.l=last;
    
    pthread_create(&thread2,NULL,orderTable,&arg2);
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    
} 


    void *orderTable(void *vargp)
    {
        struct argsTab* temp=(struct argsTab*) vargp;
        tri_rapide(temp->f,temp->l);
    }

  
// The function to be executed by all threads 

  
int main() 
{ 
    int n = 14;
    afficher_tab(tab, 0,n);
    
    
    tri_rapide(0, n-1); 
    printf("\n\nTableau trié :\n"); 
    afficher_tab(tab, 0, n); 
    return 0; 
}