
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <InfluxDb.h>
#include <SimpleDHT.h>
#include <Wire.h>
#include <credentials.h>
#include <SoftwareSerial.h>;

int pinDHT11 = 14;
SimpleDHT11 dht11;
char lcd_temperature_text[256];
char lcd_humidity_text[256];

Influxdb influx(INFLUXDB_HOST);

// Arduino ESP8266
#define D7 13
#define D6 12
#define MH_Z19_RX D6
#define MH_Z19_TX D7
SoftwareSerial mySerial(MH_Z19_RX,MH_Z19_TX); // D7 - к RX сенсора, D6 - к RX

// Arduino UNO
//SoftwareSerial mySerial(A0, A1); // A0 - к TX сенсора, A1 - к RX

void setup()
{
  mySerial.begin(9600);
  Serial.begin(115200);
  Serial.println("Starting...");
  Serial.printf("Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    //    Serial.print(WiFi.status());
  }
  Serial.println(" connected");

  influx.setDb(INFLUXDB_DB);
  influx.setPort(INFLUXDB_PORT);
  // Uncomment if you want to use InfluxDB v2
  //  influx.setBucket(“myBucket");
  //  influx.setVersion(2);
  //  influx.setOrg(“myOrg");
  //  influx.setToken(“myToken");
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
  byte temperature=0;
  byte humidity=0;

  if(getTH(&temperature,&humidity)<0){
    Serial.println("Nothing to send to the InfluxDB because an error was occured on DTH11");
    return -1;
  }

  InfluxData row_temperature("dth11_temperature");
  row_temperature.addTag("ip", ipAddress2String(WiFi.localIP()));
  row_temperature.addValue("value", (int) temperature);
  influx.write(row_temperature);

  InfluxData row_humidity("dth11_humidity");
  row_humidity.addTag("ip", ipAddress2String(WiFi.localIP()));
  row_humidity.addValue("value", (int) humidity);
  influx.write(row_humidity);

//  delay(5000);
}

int send_co2() {
  
  int co2=readCO2();
  
  if(co2<0){
    Serial.println("Nothing to send to the InfluxDB because an error was occured on MHZ19");
    return -1;
  }

  InfluxData row_co2("mhz19_co2");
  row_co2.addTag("ip", ipAddress2String(WiFi.localIP()));
  row_co2.addValue("value", co2);
  influx.write(row_co2);
  return 0;
//  delay(5000);
}
int mhz19_getPpm(){
  // Initialization before setup
  // SoftwareSerial mySerial(A0, A1); // A0 - к TX сенсора, A1 - к RX
  // In setup():
  // mySerial.begin(9600);
  
  byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
  unsigned char response[9];
  mySerial.write(cmd, 9);
  memset(response, 0, 9);
  mySerial.readBytes(response, 9);
  int i;
  byte crc = 0;
  for (i = 1; i < 8; i++) crc+=response[i];
  crc = 255 - crc;
  crc++;

  if ( !(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc) ) {
    Serial.println("CRC error: " + String(crc) + " / "+ String(response[8]));
    return -1;
  } else {
    unsigned int responseHigh = (unsigned int) response[2];
    unsigned int responseLow = (unsigned int) response[3];
    unsigned int ppm = (256*responseHigh) + responseLow;
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
void loop()
{
//  send_humidity_temperature();
//UNO
// Serial.println(mhz19_getPpm());
 // ESP (requies 5v current)
//Serial.println(readCO2());
send_co2();
  delay(10000);
}
