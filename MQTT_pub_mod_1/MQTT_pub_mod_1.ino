#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <ArduinoModbus.h>
#include "arduino_secrets.h"

float temperature;
float humidity;

char ssid[] = SSID;        // your network SSID (name)
char pass[] = PASSWD;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;              //creates a Wi-Fi client
MqttClient mqttClient(wifiClient);  //connects the Wi-Fi client to the MQTT client

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "Your_topic";
const char topic2[]  = "Your_topic_2";

//set interval for sending messages (milliseconds)
const long interval = 2000;
unsigned long previousMillis = 0;

int count = 0;

int status = WL_IDLE_STATUS;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass); // connects to Wi-Fi with credentials.

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the status:
  printWifiStatus();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  //connects to broker (and port)
  while (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.print(mqttClient.connectError());
    Serial.println(" try again in 5 seconds");
    delay(5000);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    /*Before we can send any data to an IoT platform using MQTT, we must first read it from the Modbus sensor.*/
    // send a input registers read request to (slave) id 1, for 2 registers
    if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 0x0001, 2)) {
      Serial.print("failed to read registers! ");
      Serial.println(ModbusRTUClient.lastError());
    } else {
    // If the request succeeds, the sensor sends the readings, that are
    // stored in the holding registers. The read() method can be used to
    // get the raw temperature and the humidity values.
    short rawtemperature = ModbusRTUClient.read();
    short rawhumidity = ModbusRTUClient.read();

    // To get the temperature in Celsius and the humidity reading as
    // a percentage, divide the raw value by 10.0.
    temperature = rawtemperature / 10.0;
    humidity = rawhumidity / 10.0;
    }
    // save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1 and A2
    float Rvalue = temperature;
    float Rvalue2 = humidity;

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(Rvalue);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2);
    Serial.println(Rvalue2);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(Rvalue);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print(Rvalue2);
    mqttClient.endMessage();

    Serial.println();
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
