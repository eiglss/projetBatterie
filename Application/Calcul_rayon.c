#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define Nb_Pnt 5

//a remplacer par la structure TAM (?)
typedef struct _Point{
   float x;
   float r;
}Point;

//fonction permettant de calculer la distance entre deux points
float distance(Point p1, Point p2){
    float dx = abs(p1.x-p2.x);
    return dx;
}

//fonction permettant de trier le tableau on fonction de x
void tri_tab(Point* tab_tam)
{
  int i,j;

  for (i = 0; i<Nb_Pnt - 1; i++){
  		for (j = 0; j<Nb_Pnt - 1 - i; j++){
   			Point tmp;
   			if ( tab_tam[j].x > tab_tam[j + 1].x){
    			tmp = tab_tam[j];
    			tab_tam[j] = tab_tam[j + 1];
    			tab_tam[j + 1] = tmp;
   			}
  		}
 	}
}

//fonction qui calcule les rayons de chaque tambour
//voir si on retourne une valeur particulière
void Calcul_rayon(Point* tab_tam)
{
    int i;

        for(i=0; i<Nb_Pnt; i++)
        {
        //pour la première case du tableau, je teste qu'avec la deuxieme case
         if(i == 0)
         {
           tab_tam[i].r = distance(tab_tam[i], tab_tam[i+1])/2;
         }
         //pour la dernière case, je teste qu'avec l'avant derniere
         else if(i == Nb_Pnt-1)
         {
          tab_tam[i].r = distance(tab_tam[i-1],tab_tam[i])/2;
         }
         // pour les autres je teste avec celle qui les precede et celle qui les suive
         else if (distance(tab_tam[i-1],tab_tam[i])<distance(tab_tam[i],tab_tam[i+1]))
         {
          tab_tam[i].r = distance(tab_tam[i-1],tab_tam[i])/2;
         }
         else
         {
           tab_tam[i].r = distance(tab_tam[i],tab_tam[i+1])/2;
         }
         }
}


/////////// PROGRAMME DE TEST DES FONCTIONS ////////////////
int main()
{

    int i, j;
    Point tab[Nb_Pnt];

    ///////////// VALEURS POUR TESTER ///////////////
    for(i = 0; i<Nb_Pnt; i++)
        {
            float _x;
            printf("Donnez la valeur de X\n");
            scanf("%f",&_x);
            tab[i].x = _x;
        }
    printf("Liste des points avant de trier\n");
    for(i=0;i<Nb_Pnt;i++)
        printf("x : %2f\n", tab[i].x);
    /////////////////////////////////////////////////

    //////////////// TRI DU TABLEAU /////////////////
    tri_tab(tab);
    printf("\nListe des points apres triage\n");
    for(i = 0; i<Nb_Pnt; i++)
        printf("x : %2f \n", tab[i].x);
    /////////////////////////////////////////////////

    //////////////// CALCUL RAYONS //////////////////
    Calcul_rayon(tab);
    printf("\nListe des points apres calcul rayon\n");
    for(i = 0; i<Nb_Pnt; i++)
        printf("x : %2f r : %2f\n", tab[i].x,tab[i].r);

}


