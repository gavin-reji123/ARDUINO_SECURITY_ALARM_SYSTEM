#include <Servo.h>  
#include <SoftwareSerial.h>                                    
int i,echo=9,trig=8,buzz=13,servoPin=10; 
SoftwareSerial gsm(2,3);
                         
float t,d;                                               
Servo s1;
float dist()                   
{ 
    digitalWrite(trig,HIGH);
    delay(10);
    digitalWrite(trig, LOW);
    t=pulseIn(echo,HIGH);
    d=t*0.0343/2;                                      
    return d;
}
void alarm()              
{
      digitalWrite(buzz, HIGH);
      delay(3000);
      digitalWrite(buzz,LOW);
      delay(300);
      d=dist();
}
void setup()
{
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(buzz,OUTPUT);
  gsm.begin(9600);
  Serial.println("SIM800");
  delay(1000);
  s1.attach(servoPin);
  Serial.begin(9600); 
}
void loop()
{
   for (i=0;i<180;i++)
   {
      s1.write(i);
      delay(10);
      d=dist();           
      Serial.print(d);
      Serial.println("cm.");
      Serial.println(i);
      if (d<50)
       {
          alarm();      
          Serial.print( " OBject Detected at " );
          Serial.print(d);
          Serial.println("cm.");
          s1.write(0);
          break;                     
       }
    }  
                
               if(d<50)
                   {
                     Serial.println("Motion detected!");
                     Serial.println("calling....");
                     gsm.println("ATD +918921974641;");
                     delay(20000); 
                   }
               updateSerial();
           
  }
 void updateSerial()
     {
          delay(500);
          while(Serial.available())
           {
                gsm.write(Serial.read());
           }
 
          while(gsm.available())
           {
                Serial.write(gsm.read());
           }
           
     }
