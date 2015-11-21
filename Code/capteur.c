#include "capteur.h"

int config_temperature(int fd, unsigned char mask)
{
	int ret;
    unsigned char octets[2];

    ret = ioctl(fd, I2C_SLAVE, I2C_ADDRESS_TEMP);   // Configuration de l'adresse
    if(ret < 0){
        perror("Erreur lors de la configuration de l'adresse I2C");
        return EXIT_FAILURE;
    }

    octets[0] = 0x01;                               // Configuration Register 0x01 : Configuration register
    octets[1] = mask;                               // Masque de configuration, Converter Resolution

    ret = write(fd, octets, 2);                     // Ecriture sur le bus I2C
    if (ret < 0)
    {
        perror("Erreur lors de l'ecriture sur le bus I2C");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/*Recupération et interprétation de la température */
int temperature(int fd, double * T, double * Tf)
{
    int ret;
    unsigned char octets[2];
    short data;

    ret = ioctl(fd, I2C_SLAVE, I2C_ADDRESS_TEMP);   // Configuration de l'adresse
    if(ret == -1)
    {
        perror("Erreur lors de la configuration de l'adresse I2C");
        return EXIT_FAILURE;
    }

    octets[0] = 0x00;                          //Registre de température 0x00 : Temperature register (p. 5)

    ret = write(fd, octets, 1);                // Ecriture sur le BUs I2C
    if (ret == -1)
    {
        perror("Erreur lors de la configuration du registre");
        return EXIT_FAILURE;
    }

    ret = read(fd, octets, 2);                      // Lecture Temperature Register
    if (ret == -1)
    {
        perror("Erreur lors de la lecture du registre de temperature");
        return EXIT_FAILURE;
    }

    /* étape 1
    	data = [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
		octets[0] = [T11][T10][T9][T8][T7][T6][T5][T4]
		octets[1] = [T3][T2][T1][T0][0][0][0][0]
	   étape 2
	   	data = [0][0][0][0][T11][T10][T9][T8][T7][T6][T5][T4][0][0][0][0]
	   étape 3
	   (octets[1] >> 4) = [0][0][0][0][T3][T2][T1][T0]
	   	data | (octets[1] >> 4) = [0][0][0][0][T11][T10][T9][T8][T7][T6][T5][T4][T3][T2][T1][T0]
     */
    data = (octets[0] << 4) ;
    data = data | (octets[1] >> 4);
    /* 128 = 1000 0000 0000
    2048 = 128
    data = T
    T = data * 128 /2048 */
    *T = data * 128/2048;                           // temperature * resolution
    *Tf = *T*1.8 + 32;                              // conversion en fahrenheit 

    return EXIT_SUCCESS;
}

int humidity(int fd, double TC,  double TF, double * HC, double * HF)/*Recupération et interprétation du taux d'humidité */
{
	int ret;
    short data;
    double Vout, Vs;

    ret = ioctl(fd, ADC_CHANNEL, ADC_HUMIDITY); // Configuration du canal
    if(ret == -1)
    {
        perror("Erreur lors de la configuration du canal");
        return EXIT_FAILURE;
    }

    read(fd, &data, 2);                             // Lecture de la valeur du capteur

    // Calcul humidite physique
    Vout = (2.5 / 1024) * data * 2; // Convertir le binaire en valeur décimale de tension
    Vs = 5;							// tension de seuil

    // Vout = Vs(0.0062 * H + 0.16)
    // Vout = Vs*0.0062*H + Vs*0.16
    // Vout - Vs*0.16 = Vs*0.0062*H 
    // H = Vout - Vs * 0.16 / Vs*0.0062
    *HC = (Vout - Vs * 0.16) / (Vs * 0.0062);
    *HF = (Vout - Vs * 0.16) / (Vs * 0.0062);
    // H = H / 1.0546-0.00216 * T (En degres)      
    *HC = *HC / (1.0546 - 0.00216 * TC);  
    // H = H / 1.093-0.0012 * T (En fahrenheit) 
    *HF = *HF / (1.093 - 0.0012 * TF);         

    return EXIT_SUCCESS;
}

/*Recupération et interprétation de la pression athmosphérique */
int pression(int fd, double * P)
{
	int ret;
    short data;
    double Vout, Vs;

    ret = ioctl(fd, ADC_CHANNEL, ADC_PRESSURE); // Configuration du canal
    if(ret == -1)
    {
        perror("Erreur lors de la configuration du canal");
        return EXIT_FAILURE;
    }

    read(fd, &data, 2);                             // Lecture de la valeur du capteur

    Vout = (2.5 / 1024) * data * 2;	// Convertir le binaire en valeur décimale de tension
    Vs = 5.1;       //tension de seuil
    // Vout = Vs(P * 0.01059 - 0.1518)
    // Vout = Vs*P*0.01059 - Vs*0.1518
    // Vout + Vs*0.1518 = Vs*P*0.1059
    // P = Vout + Vs * 0.1518 / Vs * 0.1059
    *P = (Vout + Vs * 0.1518) / (Vs * 0.01059);
    *P = *P * 10;    // kpA * 10 = hpA

    return EXIT_SUCCESS;

}

int lire_donnees(t_ptr_capteur p)
{
	int fd, res;

/****************************************Température**********************************************/

    fd = open(I2C_DEVICE, O_RDWR); //ouverture du bus I2C, O_RDWR : Lecture/Ecriture
    if (fd == -1) 
    {
        perror("Erreur de l'ouverture du périphérique");
        return EXIT_FAILURE;
    }


    res = config_temperature(fd, CONFIG_TEMP_R0 | CONFIG_TEMP_R1); //Resolution 0.0625
    if (res != EXIT_SUCCESS)
    {
        perror("Erreur lors de la configuration registre de la temperature");
        return EXIT_FAILURE;
    }
    
    res = temperature(fd, &p->TC, &p->TF);
    if (res != EXIT_SUCCESS)
    {
        perror("Erreur lors de la recuperation de la temperature");
        return EXIT_FAILURE;
    }

    close(fd);

/****************************************Humidité/Pression**********************************************/

    fd = open(ADC_DEVICE, O_RDONLY); // Ouverture du Bus ADC, O_RDONLY : Lecture seulement
    if ( fd == -1)
    {
        perror("Erreur lors de l'ouverture du périphérique");
        return EXIT_FAILURE;
    }

    res = pression(fd, &p->P);
    if (res != EXIT_SUCCESS)
    {
        perror("Erreur lors de la recuperation la préssion");
        return EXIT_FAILURE;
    }

    res = humidity(fd, p->TC, p->TF, &p->HC, &p->HF);
    if (res != EXIT_SUCCESS)
    {
        perror("Erreur lors de la recuperation de l'humidite");
        return EXIT_FAILURE;
    }

    close(fd);
    
    return EXIT_SUCCESS;
}


