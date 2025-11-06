
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// --- CONFIGURAÇÕES DHT22 ---
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// --- CONFIGURAÇÕES MQTT ---
const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";
const char* BROKER_MQTT = "44.223.0.185";
const int BROKER_PORT = 1883;

const char* TOPICO_SUBSCRIBE = "TEF/device2007/cmd";
const char* TOPICO_PUBLISH = "TEF/device2007/attrs/v";
const char* ID_MQTT = "fiware_2007";

// --- PINOS ---
const int LED_PIN = 2;
const int LDR_PIN = 34;  // sensor de luminosidade (potenciômetro no Wokwi)

// --- OBJETOS ---
WiFiClient espClient;
PubSubClient MQTT(espClient);

// --- VARIÁVEIS ---
char EstadoSaida = '0';

// --- FUNÇÕES ---
void initSerial() {
  Serial.begin(115200);
}

void initWiFi() {
  Serial.println("Conectando-se à rede Wi-Fi...");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\n Wi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  Serial.print(" Mensagem recebida: ");
  Serial.println(msg);

  if (msg.equalsIgnoreCase("ON")) {
    digitalWrite(LED_PIN, HIGH);
    EstadoSaida = '1';
  } else if (msg.equalsIgnoreCase("OFF")) {
    digitalWrite(LED_PIN, LOW);
    EstadoSaida = '0';
  }
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Conectando ao Broker MQTT...");
    if (MQTT.connect(ID_MQTT)) {
      Serial.println(" Conectado!");
      MQTT.subscribe(TOPICO_SUBSCRIBE);
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(MQTT.state());
      Serial.println(" Tentando novamente em 2s");
      delay(2000);
    }
  }
}

void sendSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int sensorValue = analogRead(LDR_PIN);
  int luminosity = map(sensorValue, 0, 4095, 0, 100);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(" Falha ao ler o DHT22. Mantendo dados anteriores...");
    return;
  }

  //String payload = String("{\"temp\":") + temperature +
  //                 ",\"umid\":" + humidity +
  //                 ",\"lum\":" + luminosity + "}";
  Serial.print(" Publicando: ");
  //Serial.println(payload);
  String payload = String(luminosity)
  Serial.println(luminosity);
  MQTT.publish(TOPICO_PUBLISH, payload.c_str());
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  initSerial();
  initWiFi();
  initMQTT();
  dht.begin();

  Serial.println("Sistema iniciado com sucesso!");
}

void loop() {
  if (!MQTT.connected()) reconnectMQTT();
  MQTT.loop();
  sendSensorData();
  delay(4000);  // intervalo entre leituras
}
