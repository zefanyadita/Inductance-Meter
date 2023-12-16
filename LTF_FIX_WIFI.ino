#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;
char auth[] = "lJab69NE8sdOiO72pKQHNcjZ5aqMBWtB";
char ssid[] = "Patwan Saputra";
char pass[] = "12345678";
                                
double pulse, frequency, inductance;
const int inputpin = 25;
const int outputpin = 22;

void myTimerEvent()
{
digitalWrite(22, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(22,LOW);
  delayMicroseconds(100); //make sure resination is measured
  pulse = pulseIn(25,HIGH,50000L);//returns 0 if timeout
  
  Serial.print("High for uS:");
  Serial.print( pulse );
  
  if(pulse>1){ //if a timeout did not occur and it took a reading:
  frequency   = 1.E8/(2*pulse);
  inductance  = (3*pow(10,11)*pow(frequency,(-2.066)));
  
  //Serial print
  Serial.print(" inductance mH:");
  Serial.println( inductance,5 );
  Blynk.virtualWrite(V1, inductance);
  delay(1000);
  }
  else { Serial.println("Test Gagal..."); }
  delay(1000); 
}

void setup(){

  Serial.begin(115200);
  pinMode(25, INPUT);
  pinMode(22, OUTPUT);
  Serial.println("Starting.....");
  delay(200);
  Blynk.begin(auth, ssid, pass);
timer.setInterval(1000L, myTimerEvent);           
}

void loop(){
  Blynk.run();
timer.run();
}
