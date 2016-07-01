/*Code Capteur & Deux Afficheurs*/

int Anemometre = A0;
	
int Digits[10] = {		// Tableau d'affichage des chiffres
	B00111111 , // 0
	B00000110 , // 1
	B01011011 , // 2
	B01001111 , // 3
	B01100110 , // 4
	B01101101 , // 5
	B01111101 , // 6
	B00000111 , // 7
	B01111111 , // 8
	B01101111 };

int Dizaines[7] = {
	11 ,	// a
	10 ,	// b
	 7 ,	// c
	 8 , 	// d
	 9 ,	// e
	13 ,	// f
	12	};	// g

int Unitees[7] = {
	 4 ,	// a
	 3 , 	// b
	 2 , 	// c
	 0 , 	// d
	 1 ,	// e
	 6 ,	// f
	 5 };	// g

/*Variables destinées au calcul de la moyenne*/
const int NbLectures = 10;	//Définit le nombre d'échantillons à conserver pour calculer la moyenne ; plus le chiffre est elevé, plus le tableau sera "lissé", mais plus le programme sera lent. Utiliser une constante plutôt qu'une variable normale permet d'utiliser cette valeur pour déterminer la taille du tableau.
int Tableau[NbLectures];	// Tableau recevant les signaux analogiques
int IndexTableau = 0;	 // l'index de position du tableau
int Moyenne, Total;

void setup() {
	for (int i = 0; i <= 13; ++i)
		pinMode(i, OUTPUT);
	}

void loop() {
	long ValeurAnemometre = analogRead(Anemometre);
	CalculMoyenne(ValeurAnemometre);
	//Calcul de la moyenne à partir de ValeurAnemometre puis retour dans la loop avec la valeur Moyenne
	AffichageDigits(1, Digits[Moyenne * 2 / 1023]);				// C'est en changeant ce 2 qu'on permet à l'afficheur des dizaines d'indiquer le maximum à afficher (au lieu de passer par une fonction "map")
	AffichageDigits(2, Digits[(Moyenne * 20 / 1023) % 10]);	//C'est pareil mais avec les unités
	delay(500);
}

long CalculMoyenne(long ReleveAnemometre){
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
	delay(100);	// délai entre les lectures
	return(Moyenne);
}

void AffichageDigits(int Segment, int Digit) {
	if(Digit==0){
	    return;
	}
	int* Segment_Actuel = ((Segment == 1) ? Dizaines : Unitees); // choix du Segment (à l'aide d'un pointeur, identifié ici par "*")
	/*Est-ce que je peux pas tout établir en if ?
		if segment actuel = 1
			dizaines
		if segment actuel = 2
			unitées
		if segment actuel = 3
			virgules
		?
		*/
	for (int i = 0; i < 7; ++i) {
		digitalWrite(Segment_Actuel[i], Digit & 1); // writes the least significant bit
		Digit >>= 1;
	}
}