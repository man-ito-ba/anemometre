/*Anemometre 1.6
  url du fichier 123D.circuits.io :
  https://123d.circuits.io/circuits/2367833
  */
/*Matériel*/
int Anemometre = A0;       //capteur
int ValeurAnemometre;   //variable de lecture du capteur

//Déclaration des deux afficheurs : dizaines & unitées
int Dizaines[7] = {
  11 ,  // a
  10 ,  // b
   7 ,  // c
   8 ,  // d
   9 ,  // e
  13 ,  // f
  12  };  // g
int Unitees [7] = {
   4 ,  // a
   3 ,  // b
   2 ,  // c
   0 ,  // d
   1 ,  // e
   6 ,  // f
   5 }; // g
/* Plan d'un afficheur
   --A--
   |  |
   F   B
   |  |
   --G--
   |  |
   E  C
   |  |
   --D--
   */

/*Variables destinées au calcul de la moyenne*/
const int NbLectures = 10;  //Définit le nombre d'échantillons à conserver pour calculer la moyenne ; plus le chiffre est elevé, plus le tableau sera "lissé", mais plus le programme sera lent. Utiliser une constante plutôt qu'une variable normale permet d'utiliser cette valeur pour déterminer la taille du tableau.
int Tableau[NbLectures];  // Tableau recevant les signaux analogiques
int IndexTableau = 0;   // l'index de position du tableau
int Moyenne, ValeurMoyenne, Total;

// Tableau utilisé pour l'affichage des chiffres
int Digits[10] = {
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

void setup() {
  //initialisation du Port série
    Serial.begin(9600);
    Serial.println("Start");
  pinMode(Anemometre, INPUT); // Initialisation du pin de bouton en entree
  for(int i=0; i<=13; i++){   // Initialisation des 13 pins utilisées pour les dizaines et les unitées, et mise à 0V (pour éviter les soucis)
     pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }

  //Initialisation des variables à 0 pour éviter les comportements erratiques
  ValeurAnemometre=0;
  Moyenne=0;
  ValeurMoyenne=0;
  Total=0;
}

void loop() {
  ValeurAnemometre=analogRead(A0);    // lecture du capteur
  CalculMoyenne(ValeurAnemometre);    // Calcul de la moyenne
  AffichageDigits(1, Digits[Moyenne * 2 / 1023]);       // C'est en changeant ce 2 qu'on permet à l'afficheur des dizaines d'indiquer le maximum à afficher (au lieu de passer par une fonction "map")
  AffichageDigits(2, Digits[(Moyenne * 20 / 1023) % 10]); //C'Pareil mais avec les unités
  delayMicroseconds(10);
}

int CalculMoyenne(int ValeurAnemometre){    /*Tableau glissant (running average)*/
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
  delay(100);  // délai entre les lectures
  return(Moyenne);
}

void AffichageDigits(int Segment, int Digit) {
  int* Segment_Actuel = ((Segment == 1) ? Dizaines : Unitees); // choix du Segment (à l'aide d'un pointeur, identifié ici par "*")
  for (int i = 0; i < 7; ++i) {
    digitalWrite(Segment_Actuel[i], Digit & 1); // writes the least significant bit
    Digit >>= 1;
  }
}

void Extinction() {//une fonction pour éteindre l'ensemble des segments (on va jusqu'à 20 dans la boucle "for" car les pins analog ont été converties en sorties ; donc on a de 15 à 19 en plus pour contrôler les digits.)
  for(int i=0; i<20; i++){
    digitalWrite(i, 1);//éteint tout le reste
  }
}