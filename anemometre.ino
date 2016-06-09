// Define the number of samples to keep track of.  The higher the number,
// the more the Tableau will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the Tableau array.
const int NbLectures = 10;

int Tableau[NbLectures];      // the Tableau from the analog input
int IndexTableau = 0;              // the index of the current reading
int Total = 0;                  // the running Total
int Moyenne = 0;                // the Moyenne

int Anemometre = A0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the Tableau to 0:
  for (int thisReading = 0; thisReading < NbLectures; thisReading++) {
    Tableau[thisReading] = 0;
  }
}

void loop() {
  // subtract the last reading:
  Total = Total - Tableau[IndexTableau];
  // read from the sensor:
  Tableau[IndexTableau] = analogRead(Anemometre);
  // add the reading to the Total:
  Total = Total + Tableau[IndexTableau];
  // advance to the next position in the array:
  IndexTableau = IndexTableau + 1;

  // if we're at the end of the array...
  if (IndexTableau >= NbLectures) {
    // ...wrap around to the beginning:
    IndexTableau = 0;
  }

  // calculate the Moyenne:
  Moyenne = Total / NbLectures;
  // send it to the computer as ASCII digits
  Serial.print("Capteur : ");
  Serial.println(analogRead(Anemometre));
  Serial.print("Moyenne : ");
  Serial.println(Moyenne);
  delay(100);        // delay in between reads for stability
}

