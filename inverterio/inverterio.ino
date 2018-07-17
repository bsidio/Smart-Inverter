#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
char auth[] = "";
char ssid[] = "";
char pass[] = "@$";
int backLight = 9;    
float sample1=0; 
float sample2=0; 
float voltage=0.0;
float val; 
float actualval; 
float amps=0.0;
float totamps=0.0; 
float avgamps=0.0;
float amphr=0.0;
float watt=0.0;
float energy=0.0;

#define ESP8266_BAUD 9600
SoftwareSerial EspSerial(11, 12); 
ESP8266 wifi(&EspSerial);


void setup() {
   Serial.begin(9600);
  
                        // clear the screen
 EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

  Serial.begin(9600);
  Serial.print("Initializing network");
 
 
}

void loop() {


  Blynk.run();


long milisec = millis(); // calculate time in milisec
long time=milisec/1000; // convert time to sec

  for(int i=0;i<150;i++)
  {
    sample1+=analogRead(A0);  
    sample2+=analogRead(A3); //read the current from sensor
    delay(2);
  }
   sample1=sample1/150; 
   sample2=sample2/150;
   
   voltage=5.5879*2.695*sample1/1000; //
   val =(5.0*sample2)/1024.0; 
   actualval =val-2.517; 
   amps =actualval*10; 
   totamps=totamps+amps; 
   avgamps=totamps/time; // average amps
   amphr=(avgamps*time)/3600;  // amphour
   watt =voltage*amps;    
   energy=(watt*time)/3600;  
     Blynk.virtualWrite(V5, voltage);
     Blynk.virtualWrite(V1, amps);
     Blynk.virtualWrite(V1, watt);
     Blynk.virtualWrite(V2, energy);

  

  
delay(5000);


 
 

}
