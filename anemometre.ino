// https://circuits.io/circuits/2385926
// Déclarations
	const int segmentPins[] = {4,7,8,6,5,3,2,9};
	const int Afficheur = 3;							// Afficheurs / transistors
	const int Afficheur_transistor[Afficheur] = {11,12,13}; // contrôle des transistors qui permettent de passer d'un afficheur à un autre

/* Matériel */
/*----------*/

// Boutons
	int BoutonPlus = A0;
	int BoutonMoins = A1;
		bool previousUp = LOW;
		bool currentUp = LOW;
		bool previousDown = LOW;
		bool currentDown = LOW;
		int Decompte = 0;

// Anémomètre
	int Anemometre = A2;
		int ValeurAnemometre;
		int AnemometreCAN;

// Led de virgule
	int Virgule = 10;

/* Variables globales */
/*--------------------*/

// Variables destinées au calcul de la moyenne
	const int NbLectures = 10;			//Définit le nombre d'échantillons à conserver pour calculer la moyenne ; plus le chiffre est elevé, plus le tableau sera "lissé", mais plus le programme sera lent. Utiliser une constante plutôt qu'une variable normale permet d'utiliser cette valeur pour déterminer la taille du tableau.
	int Tableau[NbLectures];			// Tableau recevant les signaux analogiques
	int IndexTableau = 0;				// l'index de position du tableau
	int Moyenne, Total;

// Tableau pour l'affichage des leds dans chaque afficheur 7 segments
// bits représentant les segments A à G (et la virgule) for les chiffres 0 - 9
	const int Chiffres[10] =
	// ABCDEFGdp
	 {  B11111100 , // 0
		B01100000 , // 1
		B11011010 , // 2
		B11110010 , // 3
		B01100110 , // 4
		B10110110 , // 5
		B00111110 , // 6
		B11100000 , // 7
		B11111110 , // 8
		B11100110 };  // 9
/* Plan d'un afficheur
	--A--
	|	|
	F  B
	|	|
	--G--
	|	|
	E C
	|	|
	--D--
	*/


void setup() {
	// Initialisation des broches digitales en sorties et mise à 0V
	for(int i = 0; i < 8; i++){
		pinMode(segmentPins[i], OUTPUT);
		digitalWrite(i, LOW);
	}

	// Initialisation des broches digitales des transistors en sorties et mise à 0V
	for(int i = 0; i < Afficheur; i++){
		pinMode(Afficheur_transistor[i], OUTPUT);
		digitalWrite(i, LOW);
	}
	
	pinMode(Virgule, OUTPUT);
	digitalWrite(Virgule, LOW);

	pinMode(BoutonMoins, INPUT); //button pin for Decompte down
	pinMode(BoutonPlus, INPUT); //button pin for Decompte up
	pinMode(Anemometre, INPUT);

	// Mise à 0 des variables
	ValeurAnemometre, AnemometreCAN, Moyenne, Total = 0;
}

void loop() {
   digitalWrite(Virgule, HIGH);
	CalculMoyenne(AnemometreCAN);
	AffichageDuChiffre(AnemometreCAN);
}

int CalculMoyenne(int ValeurAnemometre){	 /*Tableau glissant (running average)*/
  // soustraire à la position précédente
	Total = Total - Tableau[IndexTableau];
	// lecture du capteur
	Tableau[IndexTableau] = analogRead(Anemometre);
	// ajouter la lecture au tableau
	Total = Total + Tableau[IndexTableau];
	// avancer à la position suivante dans le tableau (= "glisser")
	IndexTableau = IndexTableau + 1;

	// Si on est à la fin du tableau...
	if (IndexTableau >= NbLectures) {
	// ...recommencer au début
		IndexTableau = 0;
	}

	// Calcul de la moyenne à partir des valeurs accumulées lors du glissement
	Moyenne = Total / NbLectures;
	AnemometreCAN = map(Moyenne, 0, 1023, 0, 200);
	delay(100); // délai entre les lectures
	return(AnemometreCAN);
}

void AffichageDuChiffre(int Nombre){
	if(Nombre == 0)
		SegmentsUtilises(0, Afficheur - 1); // affiche 0 le plus à droite D0 D1 D2 D3("0")
	else{
		// Affiche la valeur correspondante à chaque digit
		// l'afficheur le plus à gauche est 0
		for(int digit = Afficheur - 1; digit >= 0; digit--){
			if(Nombre > 0){
				SegmentsUtilises(Nombre % 10, digit);
				Nombre = Nombre/10;
			}
		}
	}
}

// Affiche le nombre indiqué sur l'afficheur à 7 segments sur l'afficheur indiqué
void SegmentsUtilises(int Nombre, int digit){
	digitalWrite(Afficheur_transistor[digit], HIGH);
	for(int Segment = 1; Segment < 8; Segment++){
		bool isBitSet = bitRead(Chiffres[Nombre], Segment);
		//isBitSet sera vrai si le bit donné est 1
		//isBitSet = !isBitSet; //enlever le commentaire de cette ligne pour un afficheur avec une anode commune
		digitalWrite(segmentPins[Segment], isBitSet);
	}
	delay(15);
	digitalWrite(Afficheur_transistor[digit], LOW);
}