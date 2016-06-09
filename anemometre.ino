const int NbLectures = 10;    //Définit le nombre d'échantillons à conserver pour calculer la moyenne ; plus le chiffre est elevé, plus le tableau sera "lissé", mais plus le programme sera lent. Utiliser  une constante plutôt qu'une variable normale permet d'utiliser cette valeur pour déterminer la taille du tableau.

int Tableau[NbLectures];      // Tableau recevant les signaux analogiques
int IndexTableau = 0;         // l'index de position du tableau
int Total = 0;
int Moyenne = 0;

int Anemometre = A0;          // Anémomètre sur le pin analogique A0

void setup() {
  // initialisation de la communication avec le port série
  Serial.begin(9600);
  // initialisation de toutes les positions dans le tableau à 0
  for (int thisReading = 0; thisReading < NbLectures; thisReading++) {
    Tableau[thisReading] = 0;
  }
}

void loop() {
  // soustraire à la position précédente
  Total = Total - Tableau[IndexTableau];
  // lecture du capteur
  Tableau[IndexTableau] = analogRead(Anemometre);
  // ajouter la lecture au tableau
  Total = Total + Tableau[IndexTableau];
  // avancer à la position suivante dans le tableau
  IndexTableau = IndexTableau + 1;

  // Si on est à la fin du tableau...
  if (IndexTableau >= NbLectures) {
    // ...recommencer au début
    IndexTableau = 0;
  }

  // Calcul de la moyenne:
  Moyenne = Total / NbLectures;
  // l'envoyer au port série en chiffres ASCII
  Serial.print("Capteur : ");
  Serial.println(analogRead(Anemometre));
  Serial.print("Moyenne : ");
  Serial.println(Moyenne);
  delay(100);        // délai entre les lectures
}

