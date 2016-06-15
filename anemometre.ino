float Anemometre;   //
float ValeurAnemometre;

/*Variables destinées au calcul de la moyenne*/
const int NbLectures = 5;    //Définit le nombre d'échantillons à conserver pour calculer la moyenne ; plus le chiffre est elevé, plus le tableau sera "lissé", mais plus le programme sera lent. Utiliser  une constante plutôt qu'une variable normale permet d'utiliser cette valeur pour déterminer la taille du tableau.

int Tableau[NbLectures];      // Tableau recevant les signaux analogiques
int IndexTableau = 0;         // l'index de position du tableau
float Moyenne;
float Total;

//déclaration des constantes de broche 
  //Digit 1
    int D1_A=8;
    int D1_B=9;
    int D1_C=10;
    int D1_D=11;
    int D1_E=12;
    int D1_G=13;
  //Digit 2
    int D2_A=7;
    int D2_B=6;
    int D2_C=5;
    int D2_D=4;
    int D2_E=3;
    int D2_F=2;
    int D2_G=1;
    int D2_DP=0;
  //Digit 3
    int D3_A=A1;
    int D3_C=A2;
    int D3_D=A3;
    int D3_F=A4;
    int D3_G=A5;

void setup() {
  //initialisation du Port série
  Serial.begin(9600);
  Serial.println("Start");
  //Initialisation du pin de bouton en entree
  pinMode(Anemometre, INPUT);
  //Initialisation des pins de digit en sorties
    pinMode(D1_A, OUTPUT);
    pinMode(D1_B, OUTPUT);
    pinMode(D1_C, OUTPUT);
    pinMode(D1_D, OUTPUT);
    pinMode(D1_E, OUTPUT);

    pinMode(D2_A, OUTPUT);
    pinMode(D2_B, OUTPUT);
    pinMode(D2_C, OUTPUT);
    pinMode(D2_D, OUTPUT);
    pinMode(D2_E, OUTPUT);
    pinMode(D2_F, OUTPUT);
    pinMode(D2_G, OUTPUT);
    pinMode(D2_DP, OUTPUT);

    pinMode(D3_A, OUTPUT);
    pinMode(D3_C, OUTPUT);
    pinMode(D3_D, OUTPUT);
    pinMode(D3_F, OUTPUT);
    pinMode(D3_G, OUTPUT);
  //Initialisation des variables à 0 pour éviter les comportements erratiques
  Anemometre=0;
  ValeurAnemometre=0;
  Moyenne=0;
  Total=0;
}

void loop() {
  CalculMoyenne();            //calcul de la moyenne
  Serial.println("Anemometre mapped :");
  Serial.println(ValeurAnemometre);
  Affichage(ValeurAnemometre);      //Affichage de la moyenne
  delay(500);
}

float CalculMoyenne(){
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
  ValeurAnemometre=map(Moyenne, 0, 1023, 0, 20);
  delay(100);   // délai entre les lectures
  return(ValeurAnemometre);
}

void Affichage(float Moyenne){

  if(Moyenne < 0.5){
    D123_0();
  }
  if(Moyenne >= 1 && Moyenne < 1.5){
    D1_0(), D2_1(), D3_0();
  }
  if(Moyenne >= 1.5 && Moyenne < 2){
    D1_0(), D2_1(), D3_5();
  }
  if(Moyenne >= 2 && Moyenne < 2.5){
    D1_0(), D2_2(), D3_0();
  }
  if(Moyenne >= 2.5 && Moyenne < 3){
    D1_0(), D2_2(), D3_5();
  }
  if(Moyenne >= 3 && Moyenne < 3.5){
    D1_0(), D2_3(), D3_0();
  }
  if(Moyenne >= 3.5 && Moyenne < 4){
    D1_0(), D2_3(), D3_5();
  }
  if(Moyenne >= 4 && Moyenne < 4.5){
    D1_0(), D2_4(), D3_0();
  }
  if(Moyenne >= 4.5 && Moyenne < 5){
    D1_0(), D2_4(), D3_5();
  }
  if(Moyenne >= 5 && Moyenne < 5.5){
    D1_0(), D2_5(), D3_0();
  }
  if(Moyenne >= 5.5 && Moyenne < 6){
    D1_0(), D2_5(), D3_5();
  }
  if(Moyenne >= 6 && Moyenne < 6.5){
    D1_0(), D2_6(), D3_0();
  }
  if(Moyenne >= 6.5 && Moyenne < 7){
    D1_0(), D2_6(), D3_5();
  }
  if(Moyenne >= 7 && Moyenne < 7.5){
    D1_0(), D2_7(), D3_0();
  }
  if(Moyenne >= 7.5 && Moyenne < 8){
    D1_0(), D2_7(), D3_5();
  }
  if(Moyenne >= 8 && Moyenne < 8.5){
    D1_0(), D2_8(), D3_0();
  }
  if(Moyenne >= 8.5 && Moyenne < 9){
    D1_0(), D2_8(), D3_5();
  }
  if(Moyenne >= 9 && Moyenne < 9.5){
    D1_0(), D2_9(), D3_0();
  }
  if(Moyenne >= 9.5 && Moyenne < 10){
    D1_0(), D2_9(), D3_5();
  }
  if(Moyenne >= 10 && Moyenne < 10.5){
    D1_1(), D2_0(), D3_0();
  }
  if(Moyenne >= 10.5 && Moyenne < 11){
    D1_1(), D2_0(), D3_5();
  }
  if(Moyenne >= 11 && Moyenne < 11.5){
    D1_1(), D2_1(), D3_0();
  }
  if(Moyenne >= 11.5 && Moyenne < 12){
    D1_1(), D2_1(), D3_5();
  }
  if(Moyenne >= 12 && Moyenne < 12.5){
    D1_1(), D2_2(), D3_0();
  }
  if(Moyenne >= 12.5 && Moyenne < 13){
    D1_1(), D2_2(), D3_5();
  }
  if(Moyenne >= 13 && Moyenne < 13.5){
    D1_1(), D2_3(), D3_0();
  }
  if(Moyenne >= 13.5 && Moyenne < 14){
    D1_1(), D2_3(), D3_5();
  }
  if(Moyenne >= 14 && Moyenne < 14.5){
    D1_1(), D2_4(), D3_0();
  }
  if(Moyenne >= 14.5 && Moyenne < 15){
    D1_1(), D2_4(), D3_5();
  }
  if(Moyenne >= 15 && Moyenne < 15.5){
    D1_1(), D2_5(), D3_0();
  }
  if(Moyenne >= 15.5 && Moyenne < 16){
    D1_1(), D2_5(), D3_5();
  }
  if(Moyenne >= 16 && Moyenne < 16.5){
    D1_1(), D2_6(), D3_0();
  }
  if(Moyenne >= 16.5 && Moyenne < 17){
    D1_1(), D2_6(), D3_5();
  }
  if(Moyenne >= 17 && Moyenne < 17.5){
    D1_1(), D2_7(), D3_0();
  }
  if(Moyenne >= 17.5 && Moyenne < 18){
    D1_1(), D2_7(), D3_5();
  }
  if(Moyenne >= 18 && Moyenne < 18.5){
    D1_1(), D2_8(), D3_0();
  }
  if(Moyenne >= 18.5 && Moyenne < 19){
    D1_1(), D2_8(), D3_5();
  }
  if(Moyenne >= 19 && Moyenne < 19.5){
    D1_1(), D2_9(), D3_0();
  }
  if(Moyenne >= 19.5 && Moyenne < 20){
    D1_1(), D2_9(), D3_5();
  }
  if(Moyenne >= 20 && Moyenne < 20.5){
    D1_2(), D2_0(), D3_0();
  }
  if(Moyenne >= 20.5){
    D1_2(), D2_0(), D3_5();
  }
}

// Chiffres du digit 1 ---------------------------------------

void D1_0(){
  digitalWrite(D1_G,0);
}

void D1_1(){
  digitalWrite(D1_A,1),
  digitalWrite(D1_B,0),
  digitalWrite(D1_C,0),
  digitalWrite(D1_D,1),
  digitalWrite(D1_E,1),
  digitalWrite(D1_G,1);
}

void D1_2(){
  digitalWrite(D1_A,0),
  digitalWrite(D1_B,0),
  digitalWrite(D1_C,1),
  digitalWrite(D1_D,0),
  digitalWrite(D1_E,0),
  digitalWrite(D1_G,0);
}

// Chiffres du digit 2 ---------------------------------------

void D2_0(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,1),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,0),
  digitalWrite(D2_DP,0);
}

void D2_1(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,0),
  digitalWrite(D2_C,0),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,1),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,0);
}

void D2_2(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,0),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,1),
  digitalWrite(D2_F,0),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,0);
}

void D2_3(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,0),
  digitalWrite(D2_F,0),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,1);
}
  
void D2_4(){
  digitalWrite(D2_A,0),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,0),
  digitalWrite(D2_E,0),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,1);
}

void D2_5(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,0),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,0),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,1);
}
  
void D2_6(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,0),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,1),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,1);
}

void D2_7(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,0),
  digitalWrite(D2_E,0),
  digitalWrite(D2_F,0),
  digitalWrite(D2_G,0),
  digitalWrite(D2_DP,1);
}

void D2_8(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,1),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,1);
}

void D2_9(){
  digitalWrite(D2_A,1),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,0),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,1);
}

// Chiffres du digit 3 ---------------------------------------

void D3_0(){
digitalWrite(D3_G,1);
}

void D3_5(){
  digitalWrite(D3_A,0),
  digitalWrite(D3_C,0),
  digitalWrite(D3_D,0),
  digitalWrite(D3_F,0),
  digitalWrite(D3_G,0);
}

void D123_0(){
  digitalWrite(D1_A,1),
  digitalWrite(D1_B,1),
  digitalWrite(D1_C,1),
  digitalWrite(D1_D,1),
  digitalWrite(D1_E,1),
  digitalWrite(D1_G,1),

  digitalWrite(D2_A,1),
  digitalWrite(D2_B,1),
  digitalWrite(D2_C,1),
  digitalWrite(D2_D,1),
  digitalWrite(D2_E,1),
  digitalWrite(D2_F,1),
  digitalWrite(D2_G,1),
  digitalWrite(D2_DP,1),

  digitalWrite(D3_A,1),
  digitalWrite(D3_C,1),
  digitalWrite(D3_D,1),
  digitalWrite(D3_F,1),
  digitalWrite(D3_G,1);
}