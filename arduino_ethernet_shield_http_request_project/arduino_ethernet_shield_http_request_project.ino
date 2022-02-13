#include <SPI.h>
#include <Ethernet.h>

//replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

int    http_port   = 80;
String http_method = "GET"; // or POST method
char   host_name[] = "***********"; // request website
String path_name   = "/*******"; // request website page path

void setup() {
  Serial.begin(9600);
  //initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }
  // connect to web server on port 80:
  if(client.connect(host_name, http_port)) {
    //if connected:
    Serial.println("Connected to server");
    //make a HTTP request:
    //send HTTP header
    client.println(http_method + " " + path_name + " HTTP/1.1");
    client.println("Host: " + String(host_name));
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        //read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
    //the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
}
void loop() {

}
