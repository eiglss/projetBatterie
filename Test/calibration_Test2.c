#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define Nb_Pnt 10

typedef struct _Point{
   int x;
   int y;
   float r;
}Point;

double distance(Point p1, Point p2){
    int dx = p1.x-p2.x;
    int dy = p1.y-p2.y;
    return sqrt(dx*dx + dy*dy);
}

void main(){

    int i, j;
    Point p[Nb_Pnt];

    for(i=0;i<Nb_Pnt;i++){
        int _x,_y;
        printf("Donnez la valeur de X\n");
        scanf("%d",&_x);
        p[i].x = _x;

        printf("Donnez la valeur de Y\n");
        scanf("%d",&_y);
        p[i].y = _y;

        printf("x : %2d y : %2d\n", p[i].x, p[i].y);
    }
    for(i=0;i<Nb_Pnt;i++)
    printf("x : %2d y : %2d\n", p[i].x, p[i].y);

//Todo il faut completer cette fonction
    for(i=0;i<Nb_Pnt-1;i++){
        for(j=i+1;j<Nb_Pnt;j++){

            if(distance(p[i], p[j]) > distance(p[i], p[j+1])){
                Point tmp;
                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }

    for(i=0;i<Nb_Pnt;i++)
        printf("x : %2d y : %2d\n", p[i].x, p[i].y);
}
