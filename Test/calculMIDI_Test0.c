#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define NB_OF_MPU 1
#define NB_TOMS 4
#define MAIN_D 0
#define MAIN_G 1
#define PIED_D 2
#define PIED_G 3
#define MAIN (0 | 1)
#define PIED (2 | 3)

static float zero_point=0;

typedef struct
{
	float z;
	float rayon;
	int num_MIDI;
}T_tom;

void main(){
	int i = 1;
	int j = 0;
	int k = 0;
	T_tom tab_toms[NB_TOMS];

	tab_toms[0].z = 10;
	tab_toms[0].rayon = 10;
	tab_toms[0].num_MIDI = 0;

	tab_toms[1].z = 20;
	tab_toms[1].rayon = 20;
	tab_toms[1].num_MIDI = 0;

	tab_toms[2].z = 30;
	tab_toms[2].rayon = 30;
	tab_toms[2].num_MIDI = 0;

	tab_toms[3].z = 40;
	tab_toms[3].rayon = 40;
	tab_toms[3].num_MIDI = 0;

	if((i == MAIN_D) || (i == MAIN_G))
	{
		for (j=0; j<NB_TOMS; j++)
		{
			for (k=0; k<NB_TOMS; k++)
			{
				if(j!=k)
				{
					if((tab_toms[j].z) > (tab_toms[k].z))
					{
						tab_toms[j].num_MIDI++;
					}
				}
			}
		}
		printf("avant donner vrai num de MIDI\n");
		for(i=0; i<NB_TOMS; i++)
		{
			printf("toms%d est MIDI numero %d \n", i, tab_toms[i].num_MIDI);
		}
		//Donne Numero de MIDI
		for (j=0;j<NB_TOMS;j++)
		{
			switch (tab_toms[j].num_MIDI)
			{
				case 0 :
					tab_toms[j].num_MIDI = 38;
					break;
				case 1 :
					tab_toms[j].num_MIDI = 50;
					break;
				case 2 :
					tab_toms[j].num_MIDI = 43;
					break;
				case 3 :
					tab_toms[j].num_MIDI = 41;
					break;
				default:
					printf("Erreur affectation num MIDI\n");
					break;
			}
		}
	}

	printf("apres donner vrai num de MIDI\n");
	for(i=0; i<NB_TOMS; i++)
	{
		printf("toms%d est MIDI numero %d \n", i, tab_toms[i].num_MIDI);
	}


}
