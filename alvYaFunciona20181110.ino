#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

WiFiClientSecure client;

const char ssid[] = "TP-LINK_1E99";  // "IZZI-D25C";
const char password[] = "04330738"; //"A811FC2CD25C";
const char server[] = "staging-api.cimas.io";//sensors/logs";
const int port = 443;
const char fingerprint[] = "FB B9 68 E8 98 CC 7D FE F1 EC 03 AA 58 B4 DD C4 16 75 F6 A3";
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection...");
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  printWifiStatus();

}


void loop(){
  String data;
  while(true){
    data = "aquí pones tus datos";
    post(data);
  }
}



void post(String dataString)
{

  String post = "POST /sensors/logs HTTP/1.1";

  Serial.print("Conection server: ");
  Serial.println(client.connect(server,port));

  if (client.connect(server, port)) {
    Serial.println("POST message:");
    String PostData = "{" + dataString + "}"; // aquí enviarias los datos
    client.println(post);
    client.println("Host: staging-api.cimas.io");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(PostData.length());
    client.println();
    client.println(PostData);
  } else {
    Serial.println("connection failed");
  }

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

//  if (!client.connected()) {
//    Serial.println("disconnecting from server.");
//  }

  delay(5000);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
