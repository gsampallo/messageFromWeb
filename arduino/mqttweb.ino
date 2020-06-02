#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

LiquidCrystal_I2C lcd(0x27,20,4);

const char* ssid = "WiFi";
const char* password = "Password";
const char* mqtt_server = "SERVER";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String lineas[] = { " "," "," "," "};

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  lcd.clear();
  lcd.setCursor(0,0);

  for(int l=3;l>=1;l--) {
    lineas[l] = lineas[(l-1)];
  }


  lineas[0] = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    //lcd.setCursor(0,0);
    //lcd.print((char)payload[i]);
    lineas[0] = lineas[0] + String((char)payload[i]);
  }
  
  Serial.println();

  for(int l=0; l<4; l++) {
    lcd.setCursor(0,l);
    lcd.print(lineas[l]);
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...

      // ... and resubscribe
      client.subscribe("MENSAJES");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();

  lcd.init();
  lcd.backlight();
  lcd.print("esperando");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}