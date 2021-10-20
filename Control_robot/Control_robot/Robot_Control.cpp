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
	int joint1, joint2, joint3, joint4, joint5, joint6;

	simxFloat joint_position1,joint_position2,joint_position3,joint_position4,joint_position5,joint_position6;

	if (argc>=2)
	{
		portNb=atoi(argv[1]);
		joint1 = atoi(argv[2]);
		joint2 = atoi(argv[3]);
		joint3 = atoi(argv[4]);
		joint4 = atoi(argv[5]);
		joint5 = atoi(argv[6]);
		joint6 = atoi(argv[7]);
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
		printf("a=axe1+,q=axe1-,z=axe2+,s=axe2-,e=axe3+,d=axe3-,r=axe4+,f=axe4-,t=axe5+,g=axe5-,y=axe5+,h=axe5-\n");
		while (simxGetConnectionId(clientID)!=-1)
		{
			//lecture de la position de l'articulation 2
			simxGetJointPosition(clientID,joint1,&joint_position1,simx_opmode_oneshot_wait);
			simxGetJointPosition(clientID, joint2, &joint_position2, simx_opmode_oneshot_wait);
			simxGetJointPosition(clientID, joint3, &joint_position3, simx_opmode_oneshot_wait);
			simxGetJointPosition(clientID, joint4, &joint_position4, simx_opmode_oneshot_wait); 
			simxGetJointPosition(clientID, joint5, &joint_position5, simx_opmode_oneshot_wait);
			simxGetJointPosition(clientID, joint6, &joint_position6, simx_opmode_oneshot_wait);

			printf("position actuelle : %f\n", joint_position1);
			printf("position actuelle : %f\n", joint_position2);
			printf("position actuelle : %f\n", joint_position3);
			printf("position actuelle : %f\n", joint_position4);
			printf("position actuelle : %f\n", joint_position5);
			printf("position actuelle : %f\n", joint_position6);
			//lire une touche du clavier
			char codechar;
			codechar=getch();
			//effectuer l'action demandée
			switch (codechar) 
			{
			case 'a': joint_position1=joint_position1+0.2;
				break;
			case 'q':joint_position1=joint_position1-0.2;
				break;
			case 'z': joint_position2 = joint_position2 + 0.2;
				break;
			case 's':joint_position2 = joint_position2 - 0.2;
				break;
			case 'e': joint_position3 = joint_position3 + 0.2;
				break;
			case 'd':joint_position3 = joint_position3 - 0.2;
				break;
			case 'r': joint_position4 = joint_position4 + 0.2;
				break;
			case 'f':joint_position4 = joint_position4 - 0.2;
				break;
			case 't': joint_position5 = joint_position5 + 0.2;
				break;
			case 'g':joint_position5 = joint_position5 - 0.2;
				break;
			case 'y': joint_position6 = joint_position6 + 0.2;
				break;
			case 'h':joint_position6 = joint_position6 - 0.2;
				break;

			}
			simxSetJointTargetPosition(clientID, joint1, joint_position1,simx_opmode_oneshot_wait ) ;
			simxSetJointTargetPosition(clientID, joint2, joint_position2, simx_opmode_oneshot_wait);
			simxSetJointTargetPosition(clientID, joint3, joint_position3, simx_opmode_oneshot_wait);
			simxSetJointTargetPosition(clientID, joint4, joint_position4, simx_opmode_oneshot_wait);
			simxSetJointTargetPosition(clientID, joint5, joint_position5, simx_opmode_oneshot_wait);
			simxSetJointTargetPosition(clientID, joint6, joint_position6, simx_opmode_oneshot_wait);
			extApi_sleepMs(100); //attente de 0.1 secondes
		
		}
		simxFinish(clientID);
	}
	return(0);
}

