#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define Nb_Pnt 3
#define Marge_Ang 30.
#define Rayon_Inf 360

typedef struct _Point{
   float x;
   float r;
}Point;

float distance(Point p0, Point p1){
    float dx = abs(p0.x-p1.x);
    printf("\n dx : %2f \n", dx);
    return dx;
}

void main(){
    int i, j;
    Point p[Nb_Pnt];

//pour tester, donne des vqleurs    OK
    for(i = 0; i<Nb_Pnt; i++){
        float _x;
        printf("Donnez la valeur de X entre 0 et 359\n");
        scanf("%f",&_x);
        p[i].x = _x;

        printf("x : %2f \n", p[i].x);
    }
    printf("Liste des points avant de trier\n");
    for(i=0;i<Nb_Pnt;i++)
        printf("x : %2f\n", p[i].x);

//calcule
    if(Nb_Pnt==1)
        p[0].r = Marge_Ang;
    else if(Nb_Pnt==2){
        p[0].r = (distance(p[0], p[1]))/2;
        p[1].r = (distance(p[0], p[1]))/2;
    }
    else if(Nb_Pnt==3){
        for(i = 0; i<Nb_Pnt; i++){
            float r_min = Rayon_Inf;
            for(j = 0; j<Nb_Pnt; j++){
                if(i != j){
                    if( (distance(p[i], p[j]))/2 < r_min)
                        r_min = distance(p[i], p[j]);
                    p[i].r = r_min/2.;
                }
            }
        }

        //pour tester avqnt trier
        printf("\nListe des points Rayon\n");
        for(i = 0; i<Nb_Pnt; i++)
            printf("x : %2f r : %2f\n", p[i].x, p[i].r);


        //Trier par le rqyon
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

        //pour tester avqnt trier
        printf("\nListe des points apres de trier\n");
        for(i = 0; i<Nb_Pnt; i++)
        printf("x : %2f r : %2f\n", p[i].x, p[i].r);

        //ameliorer le rayon
        for(i = 1; i<Nb_Pnt-1; i++){
            if( distance(p[i], p[i+1]) > ((p[i].r)+(p[i+1].r)) )
                p[i+1].r = (distance(p[i], p[i+1])) - (p[i].r);

        }

    }

    //pour tester de trier
    printf("\nListe des points apres de trier\n");
    for(i = 0; i<Nb_Pnt; i++)
        printf("x : %2f r : %2f\n", p[i].x, p[i].r);

}




