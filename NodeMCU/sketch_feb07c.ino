#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// Update these with values suitable for your network.
const char* ssid = "";
const char* password = "";
const char* mqtt_server = "XXX.XXX.X.XXX"; //my local ip

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {
    delay(100);
    // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Command from MQTT broker is : [");
  Serial.print(topic);
  Serial.print("]");
  int p = (char)payload[0]-'0';
  char* t1="hello1";
  char* t2="hello2";

  for (int i=0; i<length; i++){
    Serial.print((char)payload[i]);
    
  }
  Serial.println();
} //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password

    if (client.connect(clientId.c_str())){
      Serial.println("connected");
      client.subscribe("MQTT Examples2");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()

void setup() {
  Serial.begin(9600);
  Serial.println("Mi sto avviando");
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //client.publish("MQTT Examples", "Hello from ESP8266");
  //client.subscribe("MQTT Examples");

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
