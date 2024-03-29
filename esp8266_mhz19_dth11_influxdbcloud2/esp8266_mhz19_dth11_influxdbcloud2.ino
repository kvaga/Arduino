/**
 * Secure Write Example code for InfluxDBClient library for Arduino
 * Enter WiFi and InfluxDB parameters below
 *
 * Demonstrates connection to any InfluxDB instance accesible via:
 *  - unsecured http://...
 *  - secure https://... (appropriate certificate is required)
 *  - InfluxDB 2 Cloud at https://cloud2.influxdata.com/ (certificate is preconfigured, 
 *  but it's recomended to download one more time certificate for the INFLUXDB_URL and save to the InfluxDbClient.h)
 * Measures signal level of the actually connected WiFi network
 * This example demonstrates time handling, secure connection and measurement writing into InfluxDB
 * Data can be immediately seen in a InfluxDB 2 Cloud UI - measurement wifi_status
 * Src: https://github.com/bonitoo-io/influxdb-client-arduino/blob/master/examples/SecureWrite/SecureWrite.ino
 **/
#if defined(ESP32)
#include <WiFiMulti.h>

WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

#include <credentials.h>
#include "InfluxDbClient.h"
#include "InfluxDbCloud.h"

/*
// WiFi AP SSID
#define WIFI_SSID "defined in credentials.h"
// WiFi password
#define WIFI_PASSWORD "defined in credentials.h"
// InfluxDB v2 server url, e.g. https://eu-central-1-1.aws.cloud2.influxdata.com (Use: InfluxDB UI -> Load Data -> Client Libraries)
#define INFLUXDB_URL "https://europe-west1-1.gcp.cloud2.influxdata.com"
// InfluxDB v2 server or cloud API authentication token (Use: InfluxDB UI -> Load Data -> Tokens -> <select token>)
#define INFLUXDB_TOKEN "defined in credentials.h"
// InfluxDB v2 organization id (Use: InfluxDB UI -> Settings -> Profile -> <name under tile> )
#define INFLUXDB_ORG "defined in credentials.h"
// InfluxDB v2 bucket name (Use: InfluxDB UI -> Load Data -> Buckets)
#define INFLUXDB_BUCKET "defined in credentials.h"
*/

// Set timezone string according to https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
// Examples:
//  Pacific Time: "PST8PDT"
//  Eastern: "EST5EDT"
//  Japanesse: "JST-9"
//  Central Europe: "CET-1CEST,M3.5.0,M10.5.0/3"
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point
//Point sensor("wifi_status");
Point sensor_dth11("dth11");
Point sensor_mhz19("mhz19");

#include <SimpleDHT.h>
#include <SoftwareSerial.h>;


int pinDHT11 = 14; // пин data сенсора dth14 к D5 esp8266
SimpleDHT11 dht11;
char lcd_temperature_text[256];
char lcd_humidity_text[256];

// Arduino ESP8266
#define D7 13
#define D6 12
#define MH_Z19_RX D6
#define MH_Z19_TX D7
SoftwareSerial mySerial(MH_Z19_RX,MH_Z19_TX); // D7(esp8266) - к RX(mhz19), D6(esp8266) - к TX(mhz19). Важно: mhz19 требует напряжение 5В! esp8266 может его выдать только на пине VU


void timeSync() {
  // Synchronize UTC time with NTP servers
  // Accurate time is necessary for certificate validaton and writing in batches
  configTime(0, 0, "pool.ntp.org", "time.nis.gov");
  // Set timezone
  setenv("TZ", TZ_INFO, 1);

  // Wait till time is synced
  Serial.print("Syncing time");
  int i = 0;
  while (time(nullptr) < 1000000000ul && i < 100) {
    Serial.print(".");
    delay(100);
    i++;
  }
  Serial.println();

  // Show time
  time_t tnow = time(nullptr);
  Serial.print("Synchronized time: ");
  Serial.println(String(ctime(&tnow)));
}

void setup() {
    mySerial.begin(9600);
  Serial.begin(115200);

  // Setup wifi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Add tags
  sensor_dth11.addTag("device", DEVICE);
  sensor_dth11.addTag("SSID", WiFi.SSID());
  sensor_dth11.addTag("ip", ipAddress2String(WiFi.localIP()));
  sensor_mhz19.addTag("device", DEVICE);
  sensor_mhz19.addTag("SSID", WiFi.SSID());
  sensor_mhz19.addTag("ip", ipAddress2String(WiFi.localIP()));


  // Sync time for certificate validation
  timeSync();

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}


int getTH(byte* temperature, byte* humidity) {
  byte data[40] = {0};
  if (dht11.read(pinDHT11, temperature, humidity, data)) {
    Serial.println("Read DHT11 failed");
    return -1;
  }
  //  Serial.print(*temperature); Serial.print(" *C, ");
  //  Serial.print(*humidity); Serial.println(" %");
  return 0;
}


String ipAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3])  ;
}

int send_humidity_temperature() {
  byte data[40] = {0};
  byte temperature = 0;
  byte humidity = 0;

  if (getTH(&temperature, &humidity) < 0) {
    Serial.println("Nothing to send to the InfluxDB because an error was occured on DTH11");
    return -1;
  }

  sensor_dth11.addField("temperature" , temperature);
  sensor_dth11.addField("humidity"    , humidity);
  //sensor_dth11.addTag("ip", ipAddress2String(WiFi.localIP()));
  //InfluxData row_temperature("dth11_temperature");
  //row_temperature.addTag("ip", ipAddress2String(WiFi.localIP()));
  //row_temperature.addValue("value", (int) temperature);
 // influx.write(row_temperature);

//  InfluxData row_humidity("dth11_humidity");
 // row_humidity.addTag("ip", ipAddress2String(WiFi.localIP()));
 // row_humidity.addValue("value", (int) humidity);
 // influx.write(row_humidity);

  //  delay(5000);
}

int send_co2() {

  int co2 = readCO2();

  if (co2 < 0) {
    Serial.println("Nothing to send to the InfluxDB because an error was occured on MHZ19");
    return -1;
  }

  sensor_mhz19.addField("co2" , co2);
//  sensor_mhz19.addTag("ip", ipAddress2String(WiFi.localIP()));
  
  //InfluxData row_co2("mhz19_co2");
  //row_co2.addTag("ip", ipAddress2String(WiFi.localIP()));
  //row_co2.addValue("value", co2);
//  influx.write(row_co2);
  return 0;
  //  delay(5000);
}
int mhz19_getPpm() {
  // Initialization before setup
  // SoftwareSerial mySerial(A0, A1); // A0 - к TX сенсора, A1 - к RX
  // In setup():
  // mySerial.begin(9600);

  byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  unsigned char response[9];
  mySerial.write(cmd, 9);
  memset(response, 0, 9);
  mySerial.readBytes(response, 9);
  int i;
  byte crc = 0;
  for (i = 1; i < 8; i++) crc += response[i];
  crc = 255 - crc;
  crc++;

  if ( !(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc) ) {
    Serial.println("CRC error: " + String(crc) + " / " + String(response[8]));
    return -1;
  } else {
    unsigned int responseHigh = (unsigned int) response[2];
    unsigned int responseLow = (unsigned int) response[3];
    unsigned int ppm = (256 * responseHigh) + responseLow;
    //    Serial.println(ppm);
    return ppm;
  }

}
int readCO2()
{

  byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  // command to ask for data
  byte response[9]; // for answer

  mySerial.write(cmd, 9); //request PPM CO2

  // The serial stream can get out of sync. The response starts with 0xff, try to resync.
  while (mySerial.available() > 0 && (unsigned char)mySerial.peek() != 0xFF) {
    mySerial.read();
  }

  memset(response, 0, 9);
  mySerial.readBytes(response, 9);

  if (response[1] != 0x86)
  {
    Serial.println("Invalid response from co2 sensor!");
    return -1;
  }

  byte crc = 0;
  for (int i = 1; i < 8; i++) {
    crc += response[i];
  }
  crc = 255 - crc + 1;

  if (response[8] == crc) {
    int responseHigh = (int) response[2];
    int responseLow = (int) response[3];
    int ppm = (256 * responseHigh) + responseLow;
    return ppm;
  } else {
    Serial.println("CRC error!");
    return -1;
  }

}

void loop() {
  // Store measured value into point
  sensor_mhz19.clearFields();
    sensor_dth11.clearFields();

  
  send_humidity_temperature();
  //UNO
  // Serial.println(mhz19_getPpm());
  // ESP (requies 5v current)
  //Serial.println(readCO2());
  send_co2();

// Print what are we exactly writing
  Serial.print("Writing mhz19: ");
  Serial.println(sensor_mhz19.toLineProtocol());
  Serial.print("Writing dth11: ");
  Serial.println(sensor_dth11.toLineProtocol());
  // If no Wifi signal, try to reconnect it
  if ((WiFi.RSSI() == 0) && (wifiMulti.run() != WL_CONNECTED))
    Serial.println("Wifi connection lost");
  // Write point
  if (!client.writePoint(sensor_dth11)) {
    Serial.print("InfluxDB write failed (dth11): ");
    Serial.println(client.getLastErrorMessage());
  }
  if (!client.writePoint(sensor_mhz19)) {
    Serial.print("InfluxDB write failed (mhz19): ");
    Serial.println(client.getLastErrorMessage());
  }
  
  //Wait 10s
  Serial.println("Wait 10s");
  delay(10000);
  
  /*
  // Store measured value into point
  sensor.clearFields();
  // Report RSSI of currently connected network
  sensor.addField("rssi", WiFi.RSSI());
  // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(sensor.toLineProtocol());
  // If no Wifi signal, try to reconnect it
  if ((WiFi.RSSI() == 0) && (wifiMulti.run() != WL_CONNECTED))
    Serial.println("Wifi connection lost");
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  //Wait 10s
  Serial.println("Wait 10s");
  delay(10000);
  */
}
