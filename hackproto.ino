extern "C" {
  #include "crypto/base64.h"
}
/*ПРИ КОМПИЛЯЦИИ ПРОЕКТА ИСПОЛЬЗОВАТЬ СВОБ БИБЛИОТЕКУ,ТАМ ФУНКЦИИ ПЕРЕПИСАНЫ ПОД GSM!!!!"
*/
#include <WiFiClientSecure.h>
#include <WiFiMulti.h>
#include "mbedtls/base64.h"
WiFiMulti WiFiMulti;
#define SerialMon Serial
// Set serial for AT commands (to the module)
#define SerialAT  Serial1

// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM800          // Modem is SIM800
#define TINY_GSM_RX_BUFFER      1024   // Set RX buffer to 1Kb

#include <TinyGsmClient.h>
 #define SIM800L_IP5306_VERSION_20190610
BluetoothSerial ESP_BT;
const char *host = "ub.pkozlov.ru";
const char *uri = "/api";
int g = 0;
String data = "";

void fun_to_server(String date, bool door);

void fun_to_server(String date, bool door) {
  Serial.print("Connecting to ");
  Serial.println(host);
  WiFiClientSecure client;
  const char* root_ca = \
                        "-----BEGIN CERTIFICATE-----\n" \
                        "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n" \
                        "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
                        "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n" \
                        "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n" \
                        "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n" \
                        "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n" \
                        "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n" \
                        "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n" \
                        "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n" \
                        "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n" \
                        "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n" \
                        "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n" \
                        "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n" \
                        "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n" \
                        "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n" \
                        "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n" \
                        "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n" \
                        "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n" \
                        "-----END CERTIFICATE-----\n";
  client.setCACert(root_ca);
  if (!client.connect(host, 443)) {
    Serial.println("Connection failed.");
    Serial.println("Waiting 5 seconds before retrying...");
    delay(5000);
    //return;
  } 
  //String body = "{\"operationName\":null,\"variables\":{},\"query\":\"mutation{ RPassUpdate( data: { id:\\\"" + String("5f6891ed55717d6bb94554af") + "\\\", dateFactOut: \\\"" + String(1600875060) + "000" + "\\\",  penetrated: true})}\"}";
  String body = "{\"operationName\":null,\"variables\":{},\"query\":\"{ RPing}\"}";
  const char bodyl = body.length();
  String postRequest = String("POST /api/")  + " HTTP/1.1\r\nHost: " + host + "\r\n" + "Content-Type: application/json\r\nmalinka: 5eda2f12bf6c092871c961d7\r\nAuthorization:  Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJyaWQiOiI1ZWRhMmYxMmJmNmMwOTI4NzFjOTYxZDciLCJiY2lkIjoiNWU1N2NkMjE1NWI3NTUwNTdhZjA4MDI2IiwicGwiOiJyYnAiLCJpYXQiOjE2MDE1NDM3MzZ9.ohNZ5IML5vGvTejuCY7HJl69N6449oBp1LpT7Id03Kw\r\n" + "Content-Length: " + body.length() + "\r\n" + "\r\n" + body;
  Serial.println(postRequest);
  client.print(postRequest);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  client.stop();
  Serial.println();
  Serial.println("***DONE***");
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  ESP_BT.begin("ESP32_LED_Control");
      Serial.println("Bluetooth Device is Ready to Pair");
     pinMode (LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
   SerialMon.begin(115200);

    delay(10);

    // Start power management
    if (setupPMU() == false) {
        Serial.println("Setting power error");
    }

    setupSDCard();

    // Some start operations
    setupModem();

    // Set GSM module baud rate and UART pins
    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
    delay(1000);
    SerialMon.println("Initializing modem...");
    modem.restart();
    delay(1000);
     String modemInfo = modem.getModemInfo();
    SerialMon.print("Modem: ");
    SerialMon.println(modemInfo);

    // Unlock your SIM card with a PIN if needed
    if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
        modem.simUnlock(simPIN);
    }

    SerialMon.print("Waiting for network...");
    if (!modem.waitForNetwork(240000L)) {
        SerialMon.println(" fail");
        delay(10000);
        return;
    }
    SerialMon.println(" OK");

    // When the network connection is successful, turn on the indicator
    digitalWrite(LED_GPIO, LED_ON);

    if (modem.isNetworkConnected()) {
        SerialMon.println("Network connected");
    }

    SerialMon.print(F("Connecting to APN: "));
    SerialMon.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
        SerialMon.println(" fail");
        delay(10000);
        return;
    }
  //unsigned char * testqr = "NWY2ODkxZWQ1NTcxN2Q2YmI5NDU1NGFmMTYwMDg0OTgyNjAyMA==";
  //unsigned char output[64];
  //size_t outlen;
  //mbedtls_base64_decode(output, 64, &outlen, testqr, testqr.length());
//  Serial.println(output);
  Serial.println("");
  Serial.println("IP address: ");
  delay(1000);
}
void loop()
{
  /*if (Serial.available()) {
    int anw = Serial.read();
    if (data.length() == 52) {
      fun_to_server(data, true);
    }
    else {
      char b = anw;
      data += b;
      Serial.print(b);
    }
  }*/
  fun_to_server(data,true);
  delay(120000);
  /* if (g == 54) {

     delay(1000);

     g = 0;
    }
    else{
     g = g + 1;
     Serial.println(g);
    } */

}
