#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <position.h>


#define min(a, b) ((a) < (b))? (a) : (b)


//fonction permettant de calculer la distance entre deux points
float distance(T_tom p1, T_tom p2){
    float dz = abs(p1.z-p2.z);
    return dz;
}

// initialisation rayon a 0
void init_rayon(T_tom* tab){
int i = 0;
    tab[0].rayon = abs_angle_diff(tab[0],tab[1])/2;
for(i = 1; i <NB_TOMS; i++){
    tab[i].rayon = 0;
}
}

//fonction permettant de trier le tableau on fonction de x
void tri_tab(T_tom* tab_tam)
{
  int i,j;

  for (i = 0; i<NB_TOMS - 1; i++){
  		for (j = 0; j<NB_TOMS - 1 - i; j++){
   			T_tom tmp;
   			if ( tab_tam[j].x > tab_tam[j + 1].x){
    			tmp = tab_tam[j];
    			tab_tam[j] = tab_tam[j + 1];
    			tab_tam[j + 1] = tmp;
   			}
  		}
 	}
}

void Calcul_rayon_tamb (T_tom* tab_tam)
{
       int i=0,j=0;
       float calc = 0,calc2 = 0;
       init_rayon(tab_tam);
////////////// Premier calcul de rayon /////////////////////////
       for(i=0; i<NB_TOMS; i++)
        {
            for(j=1; j<NB_TOMS; j++)
            {
            if(i!= j)
            {
                if(tab_tam[i].rayon == 0)
                {
                    tab_tam[i].rayon = abs_angle_diff(tab_tam[0],tab_tam[i])/2;
                }
                else if(tab_tam[i].rayon > (calc = abs_angle_diff(tab_tam[i],tab_tam[j])/2))
                {
                    tab_tam[i].rayon = calc;
                }
            }
            }
        }
 ////////////////////////////////////////////////////////////////
 ///////// Vérification  et Amelioration des rayons /////////////
      tri_tab(tab_tam);
      for(i=1;i<NB_TOMS;i++)
      {
          if((calc =abs_angle_diff(tab_tam[i-1],tab_tam[i]))!=(tab_tam[i-1].rayon + tab_tam[i].rayon))
          {
            if (i+1 != NB_TOMS)
            {
                if ((calc2 =abs_angle_diff(tab_tam[i],tab_tam[i+1]))!=(tab_tam[i].rayon + tab_tam[i+1].rayon))
                  {
                      tab_tam[i].rayon = min((calc-tab_tam[i-1].rayon),(calc2-tab_tam[i+1].rayon));
                  }
            }
            else
            {
                tab_tam[i].rayon = calc-tab_tam[i-1].rayon;
            }
          }

      }
}

/////////////// PROGRAMME DE TEST DES FONCTIONS ////////////////
//int main()
//{
//
//    int i, j;
//    T_tom tab[NB_TOMS];
//
//    ///////////// VALEURS POUR TESTER ///////////////
//    for(i = 0; i<NB_TOMS; i++)
//        {
//            float _x;
//            printf("Donnez la valeur de X\n");
//            scanf("%f",&_x);
//            tab[i].x = _x;
//        }
//    printf("Liste des points avant de trier\n");
//    for(i=0;i<NB_TOMS;i++)
//        printf("x : %2f\n", tab[i].x);
//    /////////////////////////////////////////////////
//
//    //////////////// TRI DU TABLEAU /////////////////
////    tri_tab(tab);
////    printf("\nListe des points apres triage\n");
////    for(i = 0; i<NB_TOMS; i++)
////        printf("x : %2f \n", tab[i].x);
//    /////////////////////////////////////////////////
//
//    //////////////// CALCUL RAYONS //////////////////
//    Calcul_rayon_tamb(tab);
//    printf("\nListe des points apres calcul rayon\n");
//    for(i = 0; i<NB_TOMS; i++)
//        printf("x : %2f r : %2f\n", tab[i].x,tab[i].r);
//
//}


