#include <DHT20.h>
#include <WiFi.h>
#include <HttpClient.h>
#include <Arduino.h>

#define SDA GPIO_NUM_21 // initialize sda pin
#define SCL GPIO_NUM_22 // initialize scl pin
// This example downloads the URL "http://arduino.cc/"

DHT20 dht; // initialize dht20 sensor

char ssid[] = "nakano 2.4G";    // your network SSID (name) 
char pass[] = "19850916"; // your network password (use for WPA, or use as key for WEP)

// Name of the server we want to connect to
//const char kHostname[] = "worldtimeapi.org";
const char kHostname[] = "54.177.107.177"; // 

// Path to download (this is the bit after the hostname in the URL
// that you want to download
//const char kPath[] = "/api/timezone/Europe/London.txt";
char kPath[] = "/?t=00.00&h=00.00";

uint16_t port = 5000;

// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

void getData(){
  dht.read();// start reading
  float temp = dht.getTemperature(); // get temp val as float
  float humidity = dht.getHumidity(); // get humidity val as float
  String t = String(temp); // convert then to string
  String h = String(humidity);

  for(int i{0}; i<5; i++){ // replace 00.00 with actual value.
    kPath[4+i] = t[i]; // for temp
    kPath[12+i] = h[i]; // for humidity
  }
}

void setup() {
  Serial.begin(9600);

  //Initialize sensor
  dht.begin(SDA,SCL);

  // We start by connecting to a WiFi network
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {

  int err =0;
  
  WiFiClient c;
  HttpClient http(c);

  getData();
  
  err = http.get(kHostname, port, kPath);
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = http.responseStatusCode();
    if (err >= 0)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      // Usually you'd check that the response code is 200 or a
      // similar "success" code (200-299) before carrying on,
      // but we'll print out whatever response we get

      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        int bodyLen = http.contentLength();
        Serial.print("Content length is: ");
        Serial.println(bodyLen);
        Serial.println();
        Serial.println("Body returned follows:");
      
        // Now we've got to the body, so we can print it out
        unsigned long timeoutStart = millis();
        char c;

        // Whilst we haven't timed out & haven't reached the end of the body
        while ( (http.connected() || http.available()) && ((millis() - timeoutStart) < kNetworkTimeout) )
        {
          if (http.available())
          {
            c = http.read();
            // Print out this character
            Serial.print(c);

            bodyLen--;
            // We read something, reset the timeout counter
            timeoutStart = millis();
          }
          else
          {
            // We haven't got any data, so let's pause to allow some to arrive
            delay(kNetworkDelay);
          }
        }
      }
      else
      {
        Serial.print("Failed to skip response headers: ");
        Serial.println(err);
      }
    }
    else
    {    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();

  delay(1000);
}