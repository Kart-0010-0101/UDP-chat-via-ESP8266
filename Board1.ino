#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID     "WIFI NAME"
#define WIFI_PASSWORD "WIFI PASS"

#define NODE_ID 'A'              
#define PEER_IP "BOARD 2 IP"   
#define PORT 5000

WiFiUDP udp;

uint16_t msgID = 1;
char rxBuf[256];
String input = "";

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(PORT);
  Serial.println("Ready.");
}

void loop() {
  // ---------- RECEIVE ----------
  int size = udp.parsePacket();
  if (size) {
    int len = udp.read(rxBuf, 255);
    rxBuf[len] = 0;

    String pkt = rxBuf;

    int p1 = pkt.indexOf('|');
    int p2 = pkt.indexOf('|', p1 + 1);

    uint16_t id = pkt.substring(0, p1).toInt();
    String type = pkt.substring(p1 + 1, p2);
    String data = pkt.substring(p2 + 1);

    if (type == "MSG") {
      Serial.println("[RECEIVED] " + data);

      udp.beginPacket(PEER_IP, PORT);
      udp.printf("%d|ACK|OK", id);
      udp.endPacket();
    }

    if (type == "ACK") {
      Serial.println("[DELIVERED]");
    }
  }

  // ---------- SEND ----------
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      udp.beginPacket(PEER_IP, PORT);
      udp.printf("%d|MSG|%c:%s", msgID++, NODE_ID, input.c_str());
      udp.endPacket();

      Serial.println("[SENT] " + input);
      input = "";
    } else if (c != '\r') {
      input += c;
    }
  }
}
