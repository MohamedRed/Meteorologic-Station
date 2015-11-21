CC = arm-elf-gcc 
CCOPTS = -elf2flt

all : capteur afich button main prog
	
afich : Afich.c Afich.h
	$(CC) $(CCOPTS) -c Afich.c

capteur : capteur.c capteur.h
	$(CC) $(CCOPTS) -c capteur.c

button : button.c button.h
	$(CC) $(CCOPTS) -c button.c

main : main.c capteur.c Afich.c button.c
	$(CC) $(CCOPTS) -c main.c

prog : main.o Afich.o capteur.o
	$(CC) $(CCOPTS) -o main Afich.o capteur.o button.o main.o -lnano-X

clean :
	rm *.o all

#./nano-X -p &
#./nxview tux.gif
#insmod i2c_s3c44.o









