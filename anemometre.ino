// projet 123D.circuits.io : https://circuits.io/circuits/2455571
// projet github : https://github.com/man-ito-ba/anemometre

/* Déclarations du matériel */

// Anémomètre
int Anemometre = A0;				// Anemomètre (potentiomètre) connecté à l'entrée analogique A0
int AnemometreCAN;					// Variable globale

// Shift Registers
const int dataPin  = 2;
const int latchPin = 3;
const int clockPin = 4;
const int Virgule  = 5;

/* Tableaux et variables globales*/

int Chiffre[] = 					// Instruction destinée au Shift Register pour afficher les chiffres correspondants
	{	63,		// 0
		6,		// 1
		91,		// 2
		79,		// 3
		102,	// 4
		109,	// 5
		125,	// 6
		7,		// 7
		127,	// 8
		111};	// 9

/* Plan d'un afficheur
	--A--
	|	|
	F	B
	|	|
	--G--
	|	|
	E 	C
	|	|
	--D--
	*/

// Variables destinées au calcul de la moyenne
const int NbLectures = 5;						// à modifier pour augmenter temps de calcul de moyenne ; Définit le nombre d'échantillons à conserver pour calculer la moyenne ; plus le chiffre est elevé, plus le tableau sera "lissé", mais plus le programme sera lent. Utiliser une constante plutôt qu'une variable normale permet d'utiliser cette valeur pour déterminer la taille du tableau. J'ai réduit à 5 pour accélérer le programme.
int Tableau[NbLectures];						// Tableau recevant les signaux analogiques
int IndexTableau = 0;							// l'index de position du tableau
int Total;
int Moyenne;

// ****************************************************************************
// *                                   SETUP                                  *
// ****************************************************************************

void setup() {
	for(int i=2; i<6; i++){
		pinMode(i, OUTPUT);			// Initialisation des shift registers et de la led virgule
		digitalWrite(i, LOW);		// mise à 0V
	}

	pinMode(Anemometre, INPUT);		// Initialisation du pin de l'anémomètre en entrée

	// Mise à 0 des variables
	AnemometreCAN, Moyenne, Total = 0;
	//initialisation du Port série
	Serial.begin(9600);
	Serial.println("***************");
	Serial.println("Start");
}

// ****************************************************************************
// *                             Boucle principale                            *
// ****************************************************************************

void loop()
{
	digitalWrite(Virgule, HIGH);					// la virgule est allumée ainsi car je ne sais pas le faire autrement. C'est pas beau mais ça fonctionne :D 
	Moyenne_Glissante();							// Le calcul de la moyenne renvoie "Moyenne"
	AnemometreCAN = map(Moyenne, 0, 1023, 0, 200);	// On mappe "Moyenne" dans cette variable ""
	Serial.println(Moyenne);
	Affichage(AnemometreCAN);
	delay(10);
}

// ****************************************************************************
// *                                  Moyenne                                 *
// ****************************************************************************

int Moyenne_Glissante(){	 /*Tableau glissant (running average)*/
	/*----------*/									// Début du calcul
	Total = Total - Tableau[IndexTableau];			// soustraire à la position précédente
	Tableau[IndexTableau] = analogRead(Anemometre);	// lecture du capteur
	Total = Total + Tableau[IndexTableau];			// ajouter la lecture au tableau
	IndexTableau = IndexTableau + 1;				// avancer à la position suivante dans le tableau (= "glisser")
	if (IndexTableau >= NbLectures) 
	{
		IndexTableau = 0;							// Si on est à la fin du tableau... recommencer au début
	}
	Moyenne = Total / NbLectures;					// Calcul de la moyenne à partir des valeurs accumulées lors du glissement
	delay(100); 									// délai entre les lectures
	return(Moyenne);								// la fonction renvoie la valeur de Moyenne à la fonction Loop
}

// ****************************************************************************
// *                       Affichage sur 3 sept-segments                      *
// ****************************************************************************

void Affichage(int AnemometreCAN) {						/*Fonction d'affichage des chiffres*/
	if(AnemometreCAN<100){
	    digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, MSBFIRST, Chiffre[ AnemometreCAN / 100]);			// 0 aux centaines
		shiftOut(dataPin, clockPin, MSBFIRST, Chiffre[ AnemometreCAN / 10]);			// Affichage des dizaines (le calcul est différent car on n'a pas de risque de devoir afficher de "10", ce qui n'est pas possible sur un seul digit)
		shiftOut(dataPin, clockPin, MSBFIRST, Chiffre[ AnemometreCAN % 10]);			// Affichage des unités
		digitalWrite(latchPin, HIGH);
	}
	else{
		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, MSBFIRST, Chiffre[ AnemometreCAN / 100]);			// Affichage des centaines
		shiftOut(dataPin, clockPin, MSBFIRST, Chiffre[ AnemometreCAN / 10 % 10]);		// Affichage des dizaines (le calcul est obligatoirement différent pour avoir un "10")
		shiftOut(dataPin, clockPin, MSBFIRST, Chiffre[ AnemometreCAN % 10]);			// Affichage des unités
		digitalWrite(latchPin, HIGH);
		delay(500);
	}
}