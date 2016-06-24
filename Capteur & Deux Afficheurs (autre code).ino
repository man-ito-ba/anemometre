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

void setup() {
	for (int i = 0; i <= 13; ++i)
		pinMode(i, OUTPUT);
	}

void loop() {
	long ValeurAnemometre = analogRead(Anemometre);
	AffichageDigits(1, Digits[ValeurAnemometre * 2 / 1023]);				// C'est en changeant ce 2 qu'on permet à l'afficheur des dizaines d'indiquer le maximum à afficher (au lieu de passer par une fonction "map")
	AffichageDigits(2, Digits[(ValeurAnemometre * 20 / 1023) % 10]);	//C'Pareil mais avec les unités
	delay(500);
}

void AffichageDigits(int Segment, int Digit) {
	int* Segment_Actuel = ((Segment == 1) ? Dizaines : Unitees); // choix du Segment (à l'aide d'un pointeur, identifié ici par "*")
	for (int i = 0; i < 7; ++i) {
		digitalWrite(Segment_Actuel[i], Digit & 1); // writes the least significant bit
		Digit >>= 1;
	}
}