#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define Nb_Pnt 5

#define min(a, b) ((a) < (b))? (a) : (b)

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

// initialisation rayon a 0
void init_rayon(Point* tab){
int i = 0;
    tab[0].r = distance(tab[0],tab[1])/2;
for(i = 1; i <Nb_Pnt; i++){
    tab[i].r = 0;
}
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



void Calcul_rayon_tamb (Point* tab_tam)
{
       int i=0,j=0;
       float calc = 0,calc2 = 0;
       init_rayon(tab_tam);
////////////// Premier calcul de rayon /////////////////////////
       for(i=0; i<Nb_Pnt; i++)
        {
            for(j=1; j<Nb_Pnt; j++)
            {
            if(i!= j)
            {
                if(tab_tam[i].r == 0)
                {
                    tab_tam[i].r = distance(tab_tam[0],tab_tam[i])/2;
                }
                else if(tab_tam[i].r > (calc = distance(tab_tam[i],tab_tam[j])/2))
                {
                    tab_tam[i].r = calc;
                }
            }
            }
        }
 ////////////////////////////////////////////////////////////////
 ///////// Vérification  et Amelioration des rayons /////////////
      tri_tab(tab_tam);
      for(i=1;i<Nb_Pnt;i++)
      {
          if((calc =distance(tab_tam[i-1],tab_tam[i]))!=(tab_tam[i-1].r + tab_tam[i].r))
          {
            if (i+1 != Nb_Pnt)
            {
                if ((calc2 =distance(tab_tam[i],tab_tam[i+1]))!=(tab_tam[i].r + tab_tam[i+1].r))
                  {
                      tab_tam[i].r = min((calc-tab_tam[i-1].r),(calc2-tab_tam[i+1].r));
                  }
            }
            else
            {
                tab_tam[i].r = calc-tab_tam[i-1].r;
            }
          }

      }
}

///////////// PROGRAMME DE TEST DES FONCTIONS ////////////////
//int main()
//{
//
//    int i, j;
//    Point tab[Nb_Pnt];
//
//    ///////////// VALEURS POUR TESTER ///////////////
//    for(i = 0; i<Nb_Pnt; i++)
//        {
//            float _x;
//            printf("Donnez la valeur de X\n");
//            scanf("%f",&_x);
//            tab[i].x = _x;
//        }
//    printf("Liste des points avant de trier\n");
//    for(i=0;i<Nb_Pnt;i++)
//        printf("x : %2f\n", tab[i].x);
//    /////////////////////////////////////////////////
//
//    //////////////// TRI DU TABLEAU /////////////////
////    tri_tab(tab);
////    printf("\nListe des points apres triage\n");
////    for(i = 0; i<Nb_Pnt; i++)
////        printf("x : %2f \n", tab[i].x);
//    /////////////////////////////////////////////////
//
//    //////////////// CALCUL RAYONS //////////////////
//    Calcul_rayon_tamb(tab);
//    printf("\nListe des points apres calcul rayon\n");
//    for(i = 0; i<Nb_Pnt; i++)
//        printf("x : %2f r : %2f\n", tab[i].x,tab[i].r);
//
//}


