#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <dht.h>
#define dht_apin A0                 // Analog Pin sensor is connected to DHT11
#define dht_apin1 A1                 // Analog Pin sensor is connected to DHT11

#define gas_sensor A2           // Analog Pin sensor is connected to MQ2
#define lm1  A3                    // Analog Pin sensor is connected to lm35
#define lm2  A4                    // Analog Pin sensor is connected to lm35
#define flame1  A5                    // Analog Pin sensor is connected to flame sensor 1
#define flame2  A6                    // Analog Pin sensor is connected to flame sensor 2
#define rain    A7                    // Analog Pin sensor is connected to rain sensor 

#define motion1  9                 // digital Pin sensor is connected to motion sensor1       
#define motion2  10               // digital Pin sensor is connected to motion sensor2
#define sound  50             // digital Pin sensor is connected to sound sensor
#define buzzer1  51             // digital Pin sensor is connected to buzzer

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial myserial (7,8) ;            // RX=7 AND TX=8

 

 
volatile double r0_air,ratio,vin,rs_air,r_init,rs;
volatile int digital_val=0;
volatile int adc_count,x,y;
volatile float T; 

dht DHT;

void setup(){

  myserial.begin(9600); 
  Serial.begin (9600) ;
  lcd.begin(16, 2);
  pinMode(motion1, INPUT);      
  pinMode(motion2, INPUT);
  pinMode(sound, INPUT);      

  pinMode(buzzer1,OUTPUT);
  delay(2000);//Delay to let system boot
  for(int i=0;i<5;i++)
{
    digital_val=digital_val+analogRead(gas_sensor);
    delay(100);
}
digital_val=digital_val/5;
vin=(digital_val*5)/256;
rs_air=(5-vin)/vin;
r0_air=rs_air/9.8;
  
}
 

 
void loop()
{

  delay(1000);
  lcd.clear();
    DHT11_1();
    flame_sensor_buzzer1();
    
    flame_sensor_buzzer2();     
    delay(500);

  lcd.clear();    
    DHT11_2(); 
    
    flame_sensor_buzzer1();
    
    flame_sensor_buzzer2();
    delay(1000);
   lcd.clear();   
    MQ2_result(r0_air);
    
    flame_sensor_buzzer1();
    
    flame_sensor_buzzer2();
   sound_sensor();       
    delay(500);
    lcd.clear();   
   temperature_sensor_1();   
   temperature_sensor_2();
   
    flame_sensor_buzzer1();
    
    flame_sensor_buzzer2();
   delay(3000);   

   motin_sensor1();
   motin_sensor2();
   
    flame_sensor_buzzer1();
    
    flame_sensor_buzzer2();
delay(1000);
    lcd.clear();   

   flame_sensor1();
   flame_sensor2();
   delay(1000); 
    lcd.clear();   
   rain_sensor();
   delay(2000); 

}// end loop() 





void DHT11_1(void)
{
    lcd.setCursor(0, 0);
    DHT.read11(dht_apin);
    lcd.print("humidity1=");
    Serial.print("humidity1=");
   myserial.print("humidity1=");
    lcd.print(DHT.humidity);
    Serial.print(DHT.humidity);
  myserial.print(DHT.humidity);
    lcd.print("% ");
    Serial.print("% ");
    myserial.print("% ");
      lcd.setCursor(0, 1);
    lcd.print("temperatur1=");
    Serial.print("temperatur1=");
    myserial.print("temperatur1=");
    lcd.print(DHT.temperature); 
    Serial.print(DHT.temperature); 
    myserial.print(DHT.temperature); 
    lcd.print("C  ");
    Serial.println("C  ");
    myserial.println("C  ");
 
  delay(3000);//Wait 3 seconds before accessing sensor again.
 }


void DHT11_2(void)
{
    lcd.setCursor(0, 0);
    DHT.read11(dht_apin1);
    lcd.print("humidity2=");
    Serial.print("humidity2=");
   myserial.print("humidity2=");
    lcd.print(DHT.humidity);
    Serial.print(DHT.humidity);
  myserial.print(DHT.humidity);
    lcd.print("% ");
    Serial.print("% ");
    myserial.print("% ");
      lcd.setCursor(0, 1);
    lcd.print("temperatur2=");
    Serial.print("temperatur2=");
    myserial.print("temperatur2=");
    lcd.print(DHT.temperature); 
    Serial.print(DHT.temperature); 
    myserial.print(DHT.temperature); 
    lcd.print("C  ");
    Serial.println("C  ");
    myserial.println("C  ");
 
  delay(3000);//Wait 3 seconds before accessing sensor again.
 

 }

 void temperature_sensor_1(void)
{
     lcd.setCursor(0,0);
  adc_count=analogRead(lm1);
  T =(adc_count*0.48828125);
  lcd.print("TEMPERATUR3="); 
  Serial.print("TEMPERATUR3="); 
  myserial.print("TEMPERATUR3="); 
  lcd.print(T); 
  Serial.print(T);
  myserial.print(T);
  lcd.print("*c"); 
  Serial.println(" *C");
   myserial.println(" *C");
}



 void temperature_sensor_2(void)
{
     lcd.setCursor(0,1);
  adc_count=analogRead(lm2);
  T =(adc_count*0.48828125);
  lcd.print("TEMPERATUR4="); 
  Serial.print("TEMPERATUR4="); 
  myserial.print("TEMPERATUR4="); 
  lcd.print(T); 
  Serial.print(T);
  myserial.print(T);
  lcd.print("*c"); 
  Serial.println(" *C");
   myserial.println(" *C");
}

void MQ2_result(double x)
{
digital_val=analogRead(gas_sensor);
vin=(digital_val*5)/256;
rs=(5-vin)/vin;
ratio=rs/x;
if(ratio<=5)
{
   lcd.setCursor(0,0);
   Serial.println("gas is leakage ");
   myserial.println("gas is leakage ");
   lcd.print("gas is leakage ");

}
else
{
    lcd.setCursor(0,0);
   Serial.println("gas is normal ");
   myserial.println("gas is normal ");
   lcd.print("gas is normal ");

}
delay(3000);
}

void motin_sensor1(void)
{
  lcd.setCursor(0,0);
  if (digitalRead(motion1) == HIGH) 
  {           
      lcd.print("Motion1 detected!  ");
      Serial.println("Motion1 detected!");
      myserial.println("Motion1 detected!");
  } 
  else 
  {

      lcd.print("Motion1 ended!  ");
      Serial.println("Motion1 ended!");
      myserial.println("Motion1 ended!");
  }
 
 
}


void motin_sensor2(void)
{
  lcd.setCursor(0,1);
  if (digitalRead(motion2) == HIGH) 
  {           
      lcd.print("Motion2 detected!  ");
      Serial.println("Motion2 detected!");
      myserial.println("Motion2 detected!");
  } 
  else 
  {

      lcd.print("Motion2 ended!  ");
      Serial.println("Motion2 ended!");
      myserial.println("Motion2 ended!");
  }
 
}

void sound_sensor(void)
{
    lcd.setCursor(0,1);
  if (digitalRead(sound) == HIGH) 
  {           
      lcd.print("sound detected!");
      Serial.println("sound detected!");
      myserial.println("sound detected!");
  } 
  else 
  {

      lcd.print("sound ended!  ");
      Serial.println("sound ended!");
      myserial.println("sound ended!");
  }
 
  delay(1000);
}


void flame_sensor1(void)
{
    lcd.setCursor(0,0);
    
  y=analogRead(flame1);
  if (y<500) 
  {          
      lcd.print("fire detected!");
      Serial.println("fire detected!");
      myserial.println("fire detected!");
      digitalWrite(buzzer1,HIGH);
      delay(100);
  } 
  else 
  {

      lcd.print("no fire ");
      Serial.println("no fire");
      myserial.println("no fire ");
      digitalWrite(buzzer1,LOW);

  }
 
}


void flame_sensor2(void)
{
    lcd.setCursor(0,1);
  x=analogRead(flame2);
  if (x<500) 
  {           
      lcd.print("fire detected!");
      Serial.println("fire detected!");
      myserial.println("fire detected!");
      digitalWrite(buzzer1,HIGH);
   delay(100);
  } 
  else 
  {

      lcd.print("no fire ");
      Serial.println("no fire");
      myserial.println("no fire ");
      digitalWrite(buzzer1,LOW);

  }
 
}


void rain_sensor(void)
{
 lcd.setCursor(0,0);
 if(analogRead(rain)<300)
 {
 lcd.print("Heavy Rain");
 Serial.println("Heavy Rain");
 myserial.println("Heavy Rain");

 }
 else if(analogRead(rain)<500)
 {
 lcd.print("Moderate Rain");
 Serial.println("Moderate Rain");
 myserial.println("Moderate Rain");

 }
 else
 {
 lcd.print("No Rain");
 Serial.println("No Rain");
 myserial.println("No Rain");

 }

 delay(250);  
}





void flame_sensor_buzzer1(void)
{
  y=analogRead(flame1);
  if (y<500) 
  {          
      digitalWrite(buzzer1,HIGH);
  } 
  else 
  {
      digitalWrite(buzzer1,LOW);
  }
 
}


void flame_sensor_buzzer2(void)
{
    x=analogRead(flame2);
  if (x<500) 
  {           
      
      digitalWrite(buzzer1,HIGH);
   delay(100);
  } 
  else 
  {

   
      digitalWrite(buzzer1,LOW);

  }
 
}

