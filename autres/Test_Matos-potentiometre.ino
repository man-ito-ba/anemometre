// Test du potentiomètre
float Anemometre = A0;
float ValeurAnemometre;

void setup()
{
	//initialisation du Port série
		Serial.begin(9600);
		Serial.println("Start");
	pinMode(Anemometre, INPUT);
	ValeurAnemometre = 0;
}

void loop()
{
	ValeurAnemometre=analogRead(Anemometre);
	Serial.println("Valeur Anemometre : ");
	Serial.println(ValeurAnemometre);
	delay(100);
}