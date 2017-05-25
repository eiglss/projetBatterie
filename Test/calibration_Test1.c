#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct _Point{
   int x;
   int y;
}Point;

//cacule la distance entre deux points
double distance(Point p1, Point p2){
   int dx = p1.x-p2.x;
   int dy = p1.y-p2.y;
   return sqrt(dx*dx + dy*dy);
}


void calibration (){
    int Nb_Pnt;
    Point p[Nb_Pnt];
    int min[2];  //pour sauvgarder les deux points le plus proche
    int i, j;


    printf("Donnez le Nb de point\n");
    scanf("%d",&Nb_Pnt);

    for(i=0; i<Nb_Pnt; i++)
    {
        int _x,_y;
        printf("Donnez la valeur de X\n");
        scanf("%d",&_x);
        p[i].x = _x;

        printf("Donnez la valeur de Y\n");
        scanf("%d",&_y);
        p[i].y = _y;

        printf("x : %2d y : %2d\n", p[i].x, p[i].y);
    }

//valeur init
    min[0] = 0;
    min[1] = 1;

//calcule la distance pour tous les pairs
    for(i=0; i<Nb_Pnt-1; i++){
        for(j=i+1; j<Nb_Pnt; j++){
            if(distance(p[i],p[j])<distance(p[min[0]],p[min[1]])){
                min[0] = i, min[1] = j;
            }
        }
    }

   printf("[le plus proche] : point(%d, %d)et Point(%d, %d)\n",
   p[min[0]].x,p[min[0]].y, p[min[1]].x,p[min[1]].y);
   printf(" - distance : %f\n", distance(p[min[0]],p[min[1]]));

}


void main()
{

    calibration();

    return ;
}
