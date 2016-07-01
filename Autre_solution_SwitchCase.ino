int a=12,b=11,c=10,d=9,e=8,f=7,g=6;
int Dizaines=0, Compteur=0, Unitees=0, Tempo=0;


void setup(){
  for(int i=4; i<13; i++){
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
  }
}

void loop(){
	do{
		Dizaines = Compteur / 10;
		Unitees = Compteur % 10;
			for (Tempo = 0; Tempo < 10 ; Tempo++){ 
				delay(50);
				digitalWrite(4,0);	//alterner l'affichage
				digitalWrite(5,1);
				switch(Dizaines){
					case 0:
						Zero();
						break;
					case 1:
						Un();
						break;
					case 2:
						Deux();
						break;
					case 3:
						Trois();
						break;
					case 4:
						Quatre();
						break;
					case 5:
						Cinque();
						break;
					case 6:
						Six();
						break;
					case 7:
						Sept();
						break;
					case 8:
						Huit();
						break;
					case 9:
						Neuf();
						break;
				}
				delay(50);       
				digitalWrite(5,0);	//alterner l'affichage
				digitalWrite(4,1);
				
				switch(Unitees){
					case 0:
						Zero();
						break;
					case 1:
						Un();
						break;
					case 2:
						Deux();
						break;
					case 3:
						Trois();
						break;
					case 4:
						Quatre();
						break;
					case 5:
						Cinque();
						break;
					case 6:
						Six();
						break;
					case 7:
						Sept();
						break;
					case 8:
						Huit();
						break;
					case 9:
						Neuf();
						break;
				}
			}
		Compteur++;
		if(Compteur == 100){
			Compteur = 0;
		}
	}
	while(101);
}


void Zero(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,1);
  digitalWrite(g,0);
}

void Un(){
  digitalWrite(a,0);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,0);
  digitalWrite(e,0);
  digitalWrite(f,0);
  digitalWrite(g,0);
}

void Deux(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,0);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,0);
  digitalWrite(g,1);
}

void Trois(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,0);
  digitalWrite(f,0);
  digitalWrite(g,1);
}

void Quatre(){
  digitalWrite(a,0);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,0);
  digitalWrite(e,0);
  digitalWrite(f,1);
  digitalWrite(g,1);
}

void Cinque(){
  digitalWrite(a,1);
  digitalWrite(b,0);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,0);
  digitalWrite(f,1);
  digitalWrite(g,1);
}

void Six(){
  digitalWrite(a,0);
  digitalWrite(b,0);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,1);
  digitalWrite(g,1);
}

void Sept(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,0);
  digitalWrite(e,0);
  digitalWrite(f,0);
  digitalWrite(g,0);
}

void Huit(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,1);
  digitalWrite(g,1);
}

void Neuf(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,0);
  digitalWrite(f,1);
  digitalWrite(g,1);
}