#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define Nb_Pnt 5

typedef struct _Point{
   float x;
   float y;
   float r;
}Point;

float distance(Point p1, Point p2){
    float dx = p1.x-p2.x;
    float dy = p1.y-p2.y;
    return sqrt(dx*dx + dy*dy);
}

void main(){

    int i, j;
    Point p[Nb_Pnt];

//pour tester, donne des vqleurs    OK
    for(i = 0; i<Nb_Pnt; i++){
        float _x,_y;
        printf("Donnez la valeur de X\n");
        scanf("%f",&_x);
        p[i].x = _x;

        printf("Donnez la valeur de Y\n");
        scanf("%f",&_y);
        p[i].y = _y;

        printf("x : %2f y : %2f\n", p[i].x, p[i].y);
    }
    printf("Liste des points avant de trier\n");
    for(i=0;i<Nb_Pnt;i++)
        printf("x : %2f y : %2f\n", p[i].x, p[i].y);

//calcule le rqyon le plus petit    OK
    for(i = 0; i<Nb_Pnt; i++){
        for(j = 0; j<Nb_Pnt; j++){
            if(i != j){
                float r_min;
                if(distance(p[i], p[j+1]) > distance(p[i], p[j+2]))
                    r_min = distance(p[i], p[j+1]);
                else
                    r_min = distance(p[i], p[j]);
                p[i].r = r_min/2;
            }
        }
    }

//Trier par le rqyon    OK
    for (i = 0; i<Nb_Pnt - 1; i++){
  		for (j = 0; j<Nb_Pnt - 1 - i; j++){
   			Point tmp;
   			if ( p[j].r > p[j + 1].r){
    			tmp = p[j];
    			p[j] = p[j + 1];
    			p[j + 1] = tmp;
   			}
  		}
 	}
 	Point tmp;
 	tmp = p[0];
    p[0] = p[1];
    p[1] = tmp;

//pour tester de trier
    printf("\nListe des points apres de trier\n");
    for(i = 0; i<Nb_Pnt; i++)
        printf("x : %2f y : %2f r : %2f\n", p[i].x, p[i].y, p[i].r);



//ameliorer le rayon
    for(i = 0; i<Nb_Pnt-1; i++){
        if( distance(p[i], p[i+1]) > ((p[i].r)+(p[i+1].r)) )
            p[i+1].r = (distance(p[i], p[i+1])) - (p[i].r);
    }


//pour tester de trier
    printf("\n Liste des points apres d'ameliorer \n");
    for(i = 0; i<Nb_Pnt; i++)
        printf("x : %2f y : %2f r : %2f\n", p[i].x, p[i].y, p[i].r);

}




