
#ifndef __AFICH_H__
#define __AFICH_H__

//#include <nano-X.h>
#include "capteur.h"

/* affichage des données capturées en temps réel*/
extern void affichage(/*GR_WINDOW_ID wind, GR_GC_ID gc,*/ t_ptr_capteur c,  int number);
extern void menu();

#endif