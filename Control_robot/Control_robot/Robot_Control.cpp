#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
extern "C" {
    #include "extApi.h"
/*	#include "extApiCustom.h" if you wanna use custom remote API functions! */
}

int main(int argc,char* argv[])
{
	int portNb=0;
	int joint2;
	simxFloat joint_position2;

	if (argc>=2)
	{
		portNb=atoi(argv[1]);
		joint2=atoi(argv[2]);
	}
	else
	{
		printf("Indicate following arguments: 'portNumber  joint2Handle'!\n");
		extApi_sleepMs(5000);
		return 0;
	}

	int clientID=simxStart((simxChar*)"127.0.0.1",portNb,true,true,2000,5);
	if (clientID!=-1)
	{

		//afficher les commandes possibles
		printf("a=axe2+,b=axe2-\n");
		while (simxGetConnectionId(clientID)!=-1)
		{
			//lecture de la position de l'articulation 2
			simxGetJointPosition(clientID,joint2,&joint_position2,simx_opmode_oneshot_wait);
			printf("position actuelle : %f\n",joint_position2);
			//lire une touche du clavier
			char codechar;
			codechar=getch();
			//effectuer l'action demandée
			switch (codechar) 
			{
			case 'a': joint_position2=joint_position2+0.2;
				break;
			case 'b':joint_position2=joint_position2-0.2;
				break;

			}
			simxSetJointTargetPosition(clientID,joint2,joint_position2,simx_opmode_oneshot_wait ) ;
			extApi_sleepMs(1000); //attente de 1 secondes
		
		}
		simxFinish(clientID);
	}
	return(0);
}

