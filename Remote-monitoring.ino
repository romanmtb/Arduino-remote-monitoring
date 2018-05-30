//Роман Алексейченко//
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT22  
#define         MG_PIN                       (0)     
#define         BOOL_PIN                     (2)
#define         DC_GAIN                      (8.5)   
 

#define         READ_SAMPLE_INTERVAL         (50)    
#define         READ_SAMPLE_TIMES            (5)      
                                                     

#define         ZERO_POINT_VOLTAGE           (0.220) 
#define         REACTION_VOLTGAE             (0.020)
 

DHT dht(DHTPIN, DHTTYPE);
float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};   
                                                     
 
void setup()
{
    Serial.begin(9600);                              
    pinMode(BOOL_PIN, INPUT);                        
    digitalWrite(BOOL_PIN, HIGH);                    
    dht.begin();
 
   Serial.print("Pokazaniya vlazhnosti i temperatyru\n");                
}
 
void loop()
{
    int percentage;
    float volts;
    float h = dht.readHumidity(); 
    float t = dht.readTemperature();
    if (isnan(t) || isnan(h)) { 
    Serial.println("Failed to read from DHT"); 
  } 
  else { 
    Serial.print("Humidity: "); 
    Serial.print(h); 
    Serial.print(" %\t"); 
    Serial.print("Temperature: "); 
    Serial.print(t); 
    Serial.println(" *C"); 
  } 
    
    volts = MGRead(MG_PIN);
    Serial.print( "Soderzhanie " );
    
 
    percentage = MGGetPercentage(volts,CO2Curve);
    Serial.print("CO2:");
    if (percentage == -1) {
        Serial.print( "<400" );
    } else {
        Serial.print(percentage);
    }
 
    Serial.print( "ppm" );  
    Serial.print("\n");
 
    if (digitalRead(BOOL_PIN) ){
        Serial.print( "=============================================" );
    } else {
        Serial.print( "=============================================" );
    }
 
    Serial.print("\n");
 
    delay(200);
}
 

float MGRead(int mg_pin)
{
    int i;
    float v=0;
 
    for (i=0;i<READ_SAMPLE_TIMES;i++) {
        v += analogRead(mg_pin);
        delay(READ_SAMPLE_INTERVAL);
    }
    v = (v/READ_SAMPLE_TIMES) *5/1024 ;
    return v;  
}
 

int  MGGetPercentage(float volts, float *pcurve)
{
   if ((volts/DC_GAIN )>=ZERO_POINT_VOLTAGE) {
      return -1;
   } else { 
      return pow(10, ((volts/DC_GAIN)-pcurve[1])/pcurve[2]+pcurve[0]);
   }
}
//Роман Алексейченко//
