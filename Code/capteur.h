
#ifndef __CAPTEUR_H__
#define __CAPTEUR_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> // pour open(), close(), read(), close(), ioctl()

#define ADC_PRESSURE    	4
#define ADC_HUMIDITY    	5
#define I2C_ADDRESS_TEMP    0x92  
#define ADC_CHANNEL 		0x500
#define I2C_SLAVE   		0x0703

/****Bit de configuration du registre de temperature****/
#define CONFIG_TEMP_OS      0x80
#define CONFIG_TEMP_R0      0x40
#define CONFIG_TEMP_R1      0x20
#define CONFIG_TEMP_F0      0x10
#define CONFIG_TEMP_F1      0x08
#define CONFIG_TEMP_POL     0x04
#define CONFIG_TEMP_TM      0x02
#define CONFIG_TEMP_SD      0x01

/***Emplacement des periphériques*****/
#define ADC_DEVICE "/dev/adc"       
#define I2C_DEVICE "/dev/i2c0"      



//Structure avec les valeurs des capteurs
typedef struct capteur
{
    double TC;    //Temperature (en C)
    double TF;	  //Temperature (en F)
    double P;     //Pression (en hPA)
    double HC;    //Humidite (en %) pour degres
    double HF;	  //Humidite (en %) pour fahrenheit
} t_capteur, * t_ptr_capteur;

extern int config_temperature(int fd, unsigned char mask);

/*Recupération et interprétation de la température */
extern int temperature(int fd, double * T, double * Tf);

/*Recupération et interprétation du taux d'humidité */
extern int  humidity(int fd, double TC, double TF, double * HC, double * HF);

/*Recupération et interprétation de la pression athmosphérique */
extern int pression(int fd, double * P);

extern int lire_donnees(t_ptr_capteur p);

#endif