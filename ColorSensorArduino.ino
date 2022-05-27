// R - 2, G - 3, B - 4
int LEDs[] = {2, 3, 4};

// variabila boolean care verifica daca s-a efectuat calibrarea
boolean calib = false;

// array pentru culoarea detectata
float colors[] = {0, 0, 0};

// array-uri folosite la calibrare, care vor retine intensitatile luminoase pentru alb si negru
float whiteArray[] = {0, 0, 0};
float blackArray[] = {0, 0, 0};

// variabila pentru a retine media valorilor citite de la LDR;+
int LDR;

// functie pentru setarea culorii led-ului RGB
void setColor(int red, int green, int blue) {
  
    analogWrite(2, red);
    analogWrite(3, green);
    analogWrite(4, blue);
  
}

void setup() {
 
   // setam iesirile
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
 
   // pornim comunicatia seriala
   Serial.begin(9600);
 
}

void loop() {  

   // calibrarea senzorului
   isCalibrated();

   // obtinerea valorilor R, G, B pentru detectia culorii obiectului
   getColor();

   // afisare valori R, G, B
   printColor();
    
}

// functie prin care senzorul nu porneste daca nu este calibrat
void isCalibrated(){
  
  if(calib == false) { 
    calibration();
  }
  
}

// functie pentru citirea valorii de la LDR de mai multe ori si efectuarea mediei pentru o mai buna acuratete
void readLDR(int n) {
  
   int value;
   int k = 0;
   for(int i = 0;i < n;i++) {
     value = analogRead(0);
     k = value + k;
     delay(10);
   }
   LDR = (k)/n;
}

void calibration() {

   //---------Calibrare culoare alba-----------
   // delay 5 secunde pentru a avea timp sa asezam o hartie alba in fata senzorului
   delay(5000);    
                         
   // culoare rosie
   setColor(0, 255, 255);
   delay(100);
   // citim valoare LDR
   readLDR(5);
   // setare intensitate obtinuta la reflectia colorii rosii in foaia alba         
   whiteArray[0] = LDR;
   // oprire LED
   setColor(255, 255, 255);
   delay(100);

   // culoare verde
   setColor(255, 0, 255);
   delay(100);
   // citim valoare LDR
   readLDR(5);     
   // setare intensitate obtinuta la reflectia colorii verzi in foaia alba  
   whiteArray[1] = LDR;
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);

   // culoare albastra
   setColor(255, 255, 0);
   delay(100);
   // citim valoare LDR
   readLDR(5);          
   // setare intensitate obtinuta la reflectia colorii albastre in foaia alba  
   whiteArray[2] = LDR;
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);
  
   //---------Calibrare culoare neagra-----------
   // delay 5 secunde pentru a avea timp sa asezam o hartie neagra in fata senzorului
   delay(5000);            

   // culoare rosie
   setColor(0, 255, 255);
   delay(100);
   // citim valoare LDR
   readLDR(5); 
   // setare intensitate obtinuta la reflectia colorii albastre in foaia neagra     
   blackArray[0] = LDR;
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);

   // culoare verde 
   setColor(255, 0, 255);
   delay(100);
   // citim valoare LDR
   readLDR(5);
   // setare intensitate obtinuta la reflectia colorii verzi in foaia neagra      
   blackArray[1] = LDR;
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);

   // culoare albastra
   setColor(255, 255, 0);
   delay(100);
   // citim valoare LDR
   readLDR(5);        
   // setare intensitate obtinuta la reflectia colorii albastre in foaia neagra
   blackArray[2] = LDR;
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);

   // calibrare efectuata
   calib = true;
   
   // delay 5 secunde la finalul calibrarii
   delay(5000);
  }


void getColor() {

   // culoare rosie
   setColor(0, 255, 255);  
   // delay pentru LDR deoarece functioneaza lent
   delay(100);          
   readLDR(5);
   // setare valoare citita de LDR
   colors[0] = LDR;    
   // diferenta dintre intensitatea maxima si cea minima ne da intervalul in care vom obtine valori
   float range = whiteArray[0] - blackArray[0];  
   // calcul pentru a obtine valoarea intensitatii rosii aproximativ in intervalul [0, 255]
   colors[0] = (colors[0] - blackArray[0])/(range) * 255; 
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);

   // culoare verde
   setColor(255, 0, 255);  
   // delay pentru LDR deoarece functioneaza lent
   delay(100);                   
   readLDR(5);
   // setare valoare citita de LDR
   colors[1] = LDR;
   // diferenta dintre intensitatea maxima si cea minima ne da intervalul in care vom obtine valori
   range = whiteArray[1] - blackArray[1];  
   // calcul pentru a obtine valoarea intensitatii verzi aproximativ in intervalul [0, 255]
   colors[1] = (colors[1] - blackArray[1])/(range) * 255; 
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);

   // culoare albastra
   setColor(255, 255, 0);  
   // delay pentru LDR deoarece functioneaza lent
   delay(100);                   
   readLDR(5);
   // setare valoare citita de LDR
   colors[2] = LDR;
   // diferenta dintre intensitatea maxima si cea minima ne da intervalul in care vom obtine valori
   range = whiteArray[2] - blackArray[2];  
   // calcul pentru a obtine valoarea intensitatii albastre aproximativ in intervalul [0, 255]
   colors[2] = (colors[2] - blackArray[2])/(range) * 255; 
   // oprim LED-ul
   setColor(255, 255, 255);
   delay(100);
  
}

// functie pentru afisarea pe comunicatia seriala a valorilor R, G, B pentru fiecare culoare detectata
void printColor() {
  
    Serial.print("R = ");
    Serial.println(int(colors[0]));
    
    Serial.print("G = ");
    Serial.println(int(colors[1]));
    
    Serial.print("B = ");
    Serial.println(int(colors[2]));

}
