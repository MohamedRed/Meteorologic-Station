#include <stdio.h>
#include "capteur.h"
#include "Afich.h"

void affichage(/*GR_WINDOW_ID wind, GR_GC_ID gc,*/ t_ptr_capteur c,  int number)/* affichage des données capturées */
{
	//char TempC[20], TempF[20], Press[20], Humid[20];

	
	printf(" ______________________________________________\n");
	printf("|                ");
	printf("Station Meteo");
	printf("                 |\n");
	printf("|                                              |\n");
	printf("|    ");
	if(number == 1){
		printf("T = %.2f 'C ", c->TC);
  	   	printf("                             |\n");
	}         
    else{
    	printf("T = %.2f 'F",c->TF);
		printf("                              |\n");
    }

	printf("|    ");
	printf("P = %.2f hpa",c->P );
	printf("                            |\n");

	printf("|    ");
	if(number == 1)         
       printf("H = %.2f %%", c->HC);
    else
    	printf("H = %.2f %%",c->HF);
	printf("                               |\n");
	printf("|                                              |\n");
	printf("|   ");
	printf(" Boutton 4 : Retour au menu");
	printf("                |\n");
	printf("|______________________________________________|\n");

	//sprintf(TempC , "T = %.2f 'C\n" ,c->TC); /*recuperation de la température pour la mettre dans Temp */
	//sprintf(TempF , "/ %.2f 'F\n" ,c->TF); /*recuperation de la température pour la mettre dans Temp */
	//sprintf(Press, "P = %.2f hpa\n",c->P ); /*recuperation de la pression athmosphérique pour la mettre dans Press */
	//sprintf(Humid, "H = %.2f %%\n" ,c->H ); /*recuperation du taux d'humidité pour le mettre dans Humid */ 

	/* GrText(id, gc, x, y , str[], counts, Flags) */
	//GrText(wind, gc, 30, 20, "Station Meteo", -1, GR_TFASCII); 
	//GrText(wind, gc, 5,  80,  TempC,  -1, GR_TFASCII);
	//GrText(wind, gc, 85,  80,  TempF,  -1, GR_TFASCII);
    //GrText(wind, gc, 5, 100, Press,  -1, GR_TFASCII);
    //GrText(wind, gc, 5, 120, Humid,  -1, GR_TFASCII);

}

void menu()
{
	printf(" ______________________________________________\n");
	printf("|                ");
	printf("Station Meteo");
	printf("                 |\n");
	printf("|                                              |\n");
	printf("|    ");
	printf("Boutton 1 : Temperature en Celsius");
	printf("        |\n");
	printf("|    ");
	printf("Boutton 2 : Temperature en Fahrenheit");
	printf("     |\n");
	printf("|    ");
	printf("Boutton 3 : Eteindre la station meteo");
	printf("     |\n");
	printf("|______________________________________________|\n");



}
