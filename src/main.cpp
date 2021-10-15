#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH

const char *ssid = "INPT-TEST";
const char *password = "iinnpptt";

const int led = 2;
const int capteurLuminosite = 34;
int number = 9999;

int delayLed = 1000;
bool etatLed = 0;
bool etatLedVoulu = 0;
int previousMillis = 0;

int digit1 = 25; //Display most left display
int digit2 = 33; //Display second left
int digit3 = 32; //Display second right display
int digit4 = 35; //Display most right display

int segA = 23; 
int segB = 22; 
int segC = 1; 
int segD = 3; 
int segE = 4; 
int segF = 16; 
int segG = 15; 

AsyncWebServer server(80);

void setup()
{
  //----------------------------------------------------Serial
  Serial.begin(115200);
  Serial.println("\n");

  //----------------------------------------------------GPIO
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(capteurLuminosite, INPUT);

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  //----------------------------------------------------SPIFFS
  if(!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  //----------------------------------------------------WIFI
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion...");

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  //----------------------------------------------------SERVER
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/w3.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

  server.on("/jquery-3.6.0.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/jquery-3.6.0.min.js", "text/javascript");
  });

  server.on("/lireLuminosite", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int val = analogRead(capteurLuminosite);
    String luminosite = String(val);
    request->send(200, "text/plain", luminosite);
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    etatLedVoulu = 1;
    request->send(204);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    etatLedVoulu = 0;
    digitalWrite(led, LOW);
    etatLed = 0;
    request->send(204);
  });

  server.on("/displaying", HTTP_POST, [](AsyncWebServerRequest *request) {
    if(request->hasParam("delayLed", true))
    {
      String message;
      message = request->getParam("delayLed", true)->value();
      delayLed = message.toInt();
      Serial.println("delayLed : " + message);
    }
    if(request->hasParam("numberDisplay", true))
    {
      String message;
      message = request->getParam("numberDisplay", true)->value();
      number = message.toInt();
      Serial.println("numberDisplay : " + message);
    }
    request->send(204);
  });

  server.begin();
  Serial.println("Serveur actif!");
}

void lightNumber(int numberToDisplay) {

  switch (numberToDisplay){

    case 0:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      break;
    case 1:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 2:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;

    case 3:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;

    case 4:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 5:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 6:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 7:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 8:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 9:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 10:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

  }
}

void displaying(int number){

  int num = number;
  boolean noThird = false;
  boolean noSecond = false;

  for(int digit = 1 ; digit < 5 ; digit++) { //for loop to place the number in the right digit

    
    switch(digit) {
    case 1:

      if(num > 999){                               
        digitalWrite(digit1, DIGIT_ON);
        lightNumber(num / 1000);            // for example 2511 / 1000 = 2
        num %= 1000;                        // new value of num = 511         num = num % 100

      }
     
      break;

    case 2:

      if(noThird == true){
        digitalWrite(digit2, DIGIT_ON);
        lightNumber(0);
      }
   
      if(num > 99 && num < 1000){
          digitalWrite(digit2, DIGIT_ON);
          lightNumber(num / 100);
          num %= 100;

          if (num < 10){
            noSecond = true;
          }else{
            noSecond = false;
          } 
      }
    
      break;

    case 3:

      if(noSecond == true){
        digitalWrite(digit3, DIGIT_ON);
        lightNumber(0);
        break;
      }
   
      if(num > 9 && num < 100){
        digitalWrite(digit3, DIGIT_ON);
        lightNumber(num / 10); 
        num %= 10; 
      }
    
      break;

    case 4:
    
      if(num < 10){
        digitalWrite(digit4, DIGIT_ON);
        lightNumber(num); 
      }

      break;
  
    }
  }

}



void loop() {
  if(etatLedVoulu)
  {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= delayLed)
    {
      previousMillis = currentMillis;

      etatLed = !etatLed;
      digitalWrite(led, etatLed);
    }
  }

  displaying(number);

}
