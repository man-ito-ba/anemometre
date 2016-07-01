// URL du document https://123d.circuits.io/circuits/2333666-the-unnamed-circuit/

/*Test des Digits : 
	le tout fonctionne bien. Le programme fait s'allumer les segments des digits effectivement utilisés. */

/* Plan du segment
		--A--
		|	|
		F   B
		|	|
		--G--
		|	|
		E	C
		|	|
		--D--
	*/

/* 	Definition des segments de Led composant les chiffres de 0 à 9
	En dessous, chaque tableau sert à programmer l'état des pins utilisés pour chaque Digit. Les Pins sont reliés aux entrées, de A à G (puis DP) dans chaque 7_Segments_Display, et sont contrôlés comme des Led
	note : 1 = éteint, 0 = allumé
	*/

//        Pin utilisés: 8  9 10 11 12 13 --   --
//                      A  B  C  D  E  F  G   DP
bool Digit1[ 3][6] = {{ 1, 0, 0, 1, 1,    1     },  // = 1
                      { 0, 0, 1, 0, 0,    0     }}; // = 2

//       Pin utilisés:  0  1  2  3  4  5  6   7
//					    A  B  C  D  E  F  G   DP
bool Digit2[10][8] = {{ 0, 0, 0, 0, 0, 0, 1,  0 },  // = 0
                      { 1, 0, 0, 1, 1, 1, 1,  0 },  // = 1 //ici par exemple, le DP est allumé. Je l'allume une fois sur deux pour le fun, mais dans l'app de Flo, il faudra que le DP soit contrôlé autrement.
                      { 0, 0, 1, 0, 0, 1, 0,  0 },  // = 2
                      { 0, 0, 0, 0, 1, 1, 0,  0 },  // = 3
                      { 1, 0, 0, 1, 1, 0, 0,  0 },  // = 4
                      { 0, 1, 0, 0, 1, 0, 0,  0 },  // = 5
                      { 0, 1, 0, 0, 0, 0, 0,  0 },  // = 6
                      { 0, 0, 0, 1, 1, 1, 1,  0 },  // = 7
                      { 0, 0, 0, 0, 0, 0, 0,  0 },  // = 8
                      { 0, 0, 0, 0, 1, 0, 0,  0 }}; // = 9

//       Pin utilisés: A1 -- A2 A3 -- A4 A5   --
//					    A  B  C  D  E  F  G   DP
bool Digit3[ 2][5] = {{ 1,    1, 1,    1, 1,    },  // = 0 (soit aucun affichage)
					  { 0,    0, 0,    0, 0,    }}; // = 5

/*Variables pratiques*/
int Temps=500; //pour pouvoir accélérer ou ralentir le programme sans devoir changer le temps à chaque endroit

void setup() {
	//Initialisation Digit 1
	for(int i=8; i<14; i++){//avec cette boucle, les pins sont mis en mode sortie, même le pin DP (branché sur le pin 9)
	    pinMode(i, OUTPUT);
	    digitalWrite(i, 1);
	}
	//Initialisation Digit 2
	for(int i=0; i<8; i++){
	    pinMode(i, OUTPUT);
	    digitalWrite(i, 1);
	}
	//initialisation Digit 3
	for(int i=15; i<20; i++){
	    pinMode(i, OUTPUT);
	    digitalWrite(i, 1);
	}
	Extinction();  //commencer avec le "point" allumé
}

/*
	//j'utilise cette loop qui sinon est mise en commentaire pour être mutée afin de tester que chaque segment est bien connecté
	void loop()
	{
		for(int i=8; i<14; i++){
		    digitalWrite(i, 0);
		    delay(500);
		    digitalWrite(i, 1);
		    delay(500);
		}
		for(int i=0; i<8; i++){
		    digitalWrite(i, 0);
		    delay(500);
		    digitalWrite(i, 1);
		    delay(500);
		}
	    digitalWrite(A1, 0);
	    delay(500);
	    digitalWrite(A1, 1);
	    delay(500);
	    digitalWrite(A2, 0);
	    delay(500);
	    digitalWrite(A2, 1);
	    delay(500);
	    digitalWrite(A3, 0);
	    delay(500);
	    digitalWrite(A3, 1);
	    delay(500);
	    digitalWrite(A4, 0);
	    delay(500);
	    digitalWrite(A4, 1);
	    delay(500);
	    digitalWrite(A5, 0);
	    delay(500);
	    digitalWrite(A5, 1);
	    delay(500);
	}*/

void loop() {
	//tout allumer
	for(int i=0; i<20; i++){
	    digitalWrite(i, 0);
	}
	delay(1*Temps);
	Extinction();
	//Count down digit 1
	for (int count = 2; count > 0; --count) { //boucle de décompte
		AffichageChiffre(count - 1); 
		delay(1*Temps);
	}
	Extinction();
	delay(2*Temps);
	//Count down digit 2
  	for(int count = 10; count > 0; count--){ //boucle de décompte
		delay(1*Temps);
		AffichageChiffre2(count - 1);
	}
	Extinction();
	delay(2*Temps);
	//Count down digit 3
	for(int count = 2; count > 0; count--){
	    delay(1*Temps);
	    AffichageChiffre3(count - 1);
	}
	//Extinction avant nouvelle loop
	delay(1*Temps);
	Extinction();
	delay(1*Temps);
}

void AffichageChiffre(int Chiffre){
	int Pin = 8;//j'indique qu'on commence au pin 8 ; cette indication se retrouve dans le digitalWrite de la boucle de temporisation "for" ci-dessous.
	for (int CodeChiffre = 0; CodeChiffre < 7; ++CodeChiffre) {
		digitalWrite(Pin, Digit1[Chiffre][CodeChiffre]);
		++Pin;
	}
}

void AffichageChiffre2(int Chiffre){
	int Pin = 0;//j'indique qu'on commence au pin 0 ; cette indication se retrouve dans le digitalWrite de la boucle de temporisation "for" ci-dessous.
	for(int CodeChiffre = 0; CodeChiffre < 8; CodeChiffre++){
	    digitalWrite(Pin, Digit2[Chiffre][CodeChiffre]);
	    ++Pin;
	}
}

void AffichageChiffre3(int Chiffre){
	int Pin = 15;
	for(int CodeChiffre = 0; CodeChiffre < 5; CodeChiffre++){
	    digitalWrite(Pin, Digit3[Chiffre][CodeChiffre]);
	    ++Pin;
	}
}

void Extinction() {//une fonction pour éteindre l'ensemble des segments (on va jusqu'à 20 dans la boucle "for" car les pins analog ont été converties en sorties ; donc on a de 15 à 19 en plus pour contrôler les digits.)
  for(int i=0; i<20; i++){
      digitalWrite(i, 1);//éteint tout le reste
  }
}