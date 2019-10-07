//#include <SimpleDHT.h>

//pour le capteur de temperature et d'humidite
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_SENSOR_TYPE DHT11
//#define DHT_SENSOR_TYPE DHT22
//#define DHT_SENSOR_TYPE DHT21_


int rouge=2;
int verte=3;
int jaune=4;
int bleu=5;

// capteur temperature
static const int DHT_SENSOR_PIN = 6;

//DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
DHT_Unified dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);


// déclare 2 variables de stockage
int randDelai;
int randEtat;

//delai entre lecture temperature
//uint32_t delayMS;

void setup() {
  // pour programmation par port serie ordinateur
  // Open Serial port with:
  // baud rate: 9600
  // Data size: 8 bits
  // Parity: None
  // Stop Bits: 1 bit
  //Serial.begin(9600, SERIAL_7N1);
  Serial.begin(9600);
  
  // put your setup code here, to run once:
   pinMode(rouge, OUTPUT);
   pinMode(verte, OUTPUT);
   pinMode(bleu, OUTPUT);
   pinMode(jaune, OUTPUT);


  // Initialize device.
  dht.begin();
 
  

   
}

// fonction de tirage aléatoire pour la valeur donnée au délai
int attente() {
        randDelai = random(20, 150);
        return (randDelai);
}

// fonction de tirage aléatoire pour la valeur de l'état d'une sortie
int etat() {
        randEtat = random(0, 2);
        return (randEtat);
}


void loop() {
  
 //Serial.print("d"); //debogage
 
 
  

  if (Serial.available() > 0) {
    int  data=Serial.read();

    
  switch (data){
    case 'i':
      // Print temperature sensor details.
      Serial.println(F("DHT11 Unified Sensor Example"));
      sensor_t sensor;
      dht.temperature().getSensor(&sensor);
      Serial.println(F("------------------------------------"));
      Serial.println(F("Temperature Sensor"));
      Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
      Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
      Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
      Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
      Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
      Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
      Serial.println(F("------------------------------------"));
      // Print humidity sensor details.
      dht.humidity().getSensor(&sensor);
      Serial.println(F("Humidity Sensor"));
      Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
      Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
      Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
      Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
      Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
      Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
      Serial.println(F("------------------------------------"));
     
      break;
    case 'o':
        digitalWrite(rouge, HIGH);
        digitalWrite(verte, HIGH);
        digitalWrite(jaune, HIGH);
        digitalWrite(bleu, HIGH);
        Serial.println("On allume toutes les diodes"); 
      break;
    case 't':
          //GESTION CAPTEUR TEMPERATURE ET HUMIDITE
           
          // Get temperature event and print its value.
          sensors_event_t event;
          dht.temperature().getEvent(&event);
          if (isnan(event.temperature)) {
            Serial.println(F("Error reading temperature!"));
          }
          else {
            Serial.print(F("Temperature: "));
            Serial.print(event.temperature);
            Serial.println(F("°C"));
          }
          
       break;
    case 'h':
        
       
          
        // Get humidity event and print its value.
          dht.humidity().getEvent(&event);
          if (isnan(event.relative_humidity)) {
            Serial.println(F("Error reading humidity!"));
          }
          else {
            Serial.print(F("Humidity: "));
            Serial.print(event.relative_humidity);
            Serial.println(F("%"));
          }  
        break;
    case 'r':  
        if (digitalRead (rouge)==HIGH)
        {
            digitalWrite(rouge, LOW);
        }
        else
        {
            digitalWrite(rouge, HIGH);
        }
        break;
    case'z':
        digitalWrite(rouge, LOW);
        break;
    case 'v':
        if (digitalRead (verte)==HIGH)
        {
            digitalWrite(verte, LOW);
        }
        else
        {
            digitalWrite(verte, HIGH);
        }   
        break;
    case 'j':    
         if (digitalRead (jaune)==HIGH)
        {
            digitalWrite(jaune, LOW); 
        }
        else
        {
            digitalWrite(jaune, HIGH);
        }
        break;
    case 'b':
         if (digitalRead (bleu)==HIGH)
        {
            digitalWrite(bleu, LOW);
        }
        else
        {
            digitalWrite(bleu, HIGH);
        }
        break;
    case 'f':
        digitalWrite(bleu, LOW);
        digitalWrite(jaune, LOW);
        digitalWrite(verte, LOW);
        digitalWrite(rouge, LOW);
        break;
  }
  
  }
  
  
  
}
