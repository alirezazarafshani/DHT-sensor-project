// make an array to save Seven Segment pin configuration of numbers

int num_array[10][7] = {  { 1,1,1,1,1,1,0 },    // 0
                          { 0,1,1,0,0,0,0 },    // 1
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,0,0,1 },    // 3
                          { 0,1,1,0,0,1,1 },    // 4
                          { 1,0,1,1,0,1,1 },    // 5
                          { 1,0,1,1,1,1,1 },    // 6
                          { 1,1,1,0,0,0,0 },    // 7
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,1,1,0,0,1,1 }};   // 9
void Num_Write(int);                                       


//note:connect all same segment in one spot and then connect them to the board



#include "DHT.h"

//*********************define your DHT sensor************************
  #define DHTPIN 13                                                   
  #define DHTTYPE DHT11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)                             
//*******************************************************************

DHT dht(DHTPIN, DHTTYPE);



void setup() 
{ 
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
 
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  //seven segment leds
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //clock pins that connecet to two of negetive pins on seven segments
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  //thse two are for buton's
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  
 
}
//a is variable that print on seven segment
int a=0;
//c and e are for buton
int c=1,e=1;
int but1,but2;
void loop() 
{

//two button chang the show case from temp to humidity and another one change it to show temp in cantigerad or farenhite
  //define button one
  but1=digitalRead(11);
  if(but1==HIGH){
    if(c==0){c=1;}
    else{c=0;}
    delay(500);}
//define button two
    but2=digitalRead(12);
    if(but2==HIGH && c==0){
      if(e==0){e=1;}else{e=0;}
      delay(500);}

//define what it mast to print
  if(c==0 && e==0){a= dht.readTemperature();if(a>30){digitalWrite(0,HIGH);}delay(0);digitalWrite(0,LOW);}
  if(c==0 && e==1){a=  dht.readTemperature(true);}
  if(c==1){a=dht.readHumidity();if(a>80){digitalWrite(1,HIGH);delay(0);digitalWrite(1,LOW);}}
  


  
 //process to print digits on seven segment(its for two digit seven segment)
 //it takes almost two or three seconds in uno and DHT11 to print the new variables

 //it shows the first digit
  digitalWrite(10,HIGH);
  digitalWrite(9,LOW);  
   Num_Write(a/10);
   delayMicroseconds(2000);
  //shows the second digit
  digitalWrite(10,LOW);
  digitalWrite(9,HIGH);  
   Num_Write(a%10);
    delayMicroseconds(2000);
     digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);  
    

 
  
   
  
 
}

// for print digit's on seven segment  
void Num_Write(int number) 
{
  int pin= 2;
  for (int j=0; j < 7; j++) {
   digitalWrite(pin, num_array[number][j]);
   pin++;
  }
}



