#define MWINCLUDECOLORS
//#include <nano-X.h>
#include <stdio.h>
#include <stdlib.h>
#include "Afich.h"
#include "capteur.h"
#include "button.h"
/*
#define SOLEIL  "/home/img/soleil.gif"
#define LUNE    "/home/img/lune.bmp" 
#define NUAGE   "/home/img/nuage.bmp"
#define PLUIE   "/home/img/pluie.bmp"
#define NEIGE   "/home/img/neige.bmp"
*/

int main(int ac,char **av)
{
  

	t_ptr_capteur c; 	/*objet de la struct capteur */
	//GR_WINDOW_ID wind; 	/* identifiant de la fenêtre */
	//GR_GC_ID gc;	  	/* identifiant du contexte graphique */  

	/*Configuration de l'ecran*/
  //wind = GrNewWindow(1, 5, 5, 150, 600, 5, BLACK, WHITE); /*(parent, x, y, largeur, hauteur, taille de bordure, couleur du fond, couleur du bord) */
  //GrMapWindow(wind); /*affichage de la fenêtre */

	//gc = GrNewGC(); /*Création d'un nouveau contexte graphique */
  //GrSetGCForeground(gc, WHITE);
  //GrSetGCUseBackground(gc, GR_FALSE);
  int code, fd1, fd2;


  system("insmod adc_s3c44.o");// Chargement du driver pour CAN
  system("insmod i2c_s3c44.o");// Chargement du driver du Bus I2C

  do{
       menu();
       code = 0;
       while(code == 0)
        {   
            if(Push_Button() == 1)
            {
              printf("Temperature en Celsius\n") ;
              lire_donnees(c);
              affichage(/*wind, gc,*/ c, 1);
              sleep(2);
              while(Push_Button() != 4){}
              code = 1;
              break;
            } 
            if(Push_Button() == 2)
            {
              printf("Temperature en Fahrenheit\n") ;
              lire_donnees(c);
              affichage(/*wind, gc,*/ c, 2);
              sleep(2);
              while(Push_Button() != 4){}
              code = 1;
              break;
            }
            if(Push_Button() == 3)
            {
              printf("              GOODBYE SEE YOU SOON\n") ;
              sleep(4);
              code = 0;
              break;
            }        
        }
  }while(code == 1);
    //GrDrawImageFromFile(wind, gc, 30, 50, 50, 50, SOLEIL , 0 );

    /*Fermeture du dispositif graphique*/
    //GrClose();
    return 0;
}
