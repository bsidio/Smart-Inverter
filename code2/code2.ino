

/**
Energy monitoring data upload to xively
**/


#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 6, 5, 4, 3, 2);
int backLight = 9;    // pin 9 will control the backlight
float sample1=0; // for voltage
float sample2=0; // for current
float voltage=0.0;
float val; // current callibration
float actualval; // read the actual current from ACS 712
float amps=0.0;
float totamps=0.0; 
float avgamps=0.0;
float amphr=0.0;
float watt=0.0;
float energy=0.0;



void setup() {
   Serial.begin(9600);
  pinMode(backLight, OUTPUT);          //set pin 13 as output
  analogWrite(backLight, 150);        //controls the backlight intensity 0-254
  
  lcd.begin(16,2);                    // columns, rows. size of display
  lcd.clear();                        // clear the screen
 

  Serial.begin(9600);
  Serial.println("Initializing network");
 
 
}

void loop() {

  lcd.setCursor(16,1); // set the cursor outside the display count
  lcd.print(" ");      // print empty character


// send the supplied values to Cosm, printing some debug information as we go

long milisec = millis(); // calculate time in milisec
long time=milisec/1000; // convert time to sec

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                      /// taking 150 samples from sensors with a inerval of 2sec and then average the samples data collected
  for(int i=0;i<150;i++)
  {
    sample1+=analogRead(A0);  //read the voltage from the sensor
    sample2+=analogRead(A3); //read the current from sensor
    delay(2);
  }
   sample1=sample1/150; 
   sample2=sample2/150;
   
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  /////voltage calculation//////////////////////
   voltage=5.5879*2.695*sample1/1000; //  callibration // 3.25v from voltage div is eqv 696 in A2 reading  // multiply 2 to get actual voltage
  /// current calculation //////////////////////
   val =(5.0*sample2)/1024.0; 
   actualval =val-2.517; // offset voltage is 2.5v 
   amps =actualval*10; // 100mv/A from data sheet 
   totamps=totamps+amps; // total amps 
   avgamps=totamps/time; // average amps
   amphr=(avgamps*time)/3600;  // amphour
   watt =voltage*amps;    // power=voltage*current
   energy=(watt*time)/3600;   //energy in watt hour
   // energy=(watt*time)/(1000*3600);   // energy in kWh
   
////////////////////////////////////DISPLAY IN SERIAL MONITOR//////////////////////////////////////////////////////////

/* Serial.print("VOLTAGE : ");
Serial.print(voltage);
Serial.println("Volt");
Serial.print("CURRENT :");
Serial.print(amps);
Serial.println("Amps");
Serial.print("POWER :");
Serial.print(watt);
Serial.println("Watt");
Serial.print("ENERGY CONSUMED :");
Serial.print(energy);
Serial.println("Watt-Hour");
Serial.println(""); // print the next sets of parameter after a blank line
delay(2000); 
*/
///////////////////////////////////DISPLAY IN LCD//////////////////////////////////////////////////////////////////
  
 lcd.setCursor(1,0); // set the cursor at 1st col and 1st row
 // lcd.print("POWER :");
  lcd.print(watt);
  lcd.print("W    ");
  lcd.print(voltage);
  lcd.print("V");
  
  lcd.setCursor(1,1); // set the cursor at 1st col and 2nd row
  //lcd.print("ENERGY :");
  lcd.print(energy);
  lcd.print("WH   ");
  lcd.print(amps);
  lcd.print("A");
  
  //////////////////////////////////////////XIVELY UPLOAD///////////////////////////////////////////////////////

 
 

 

}
