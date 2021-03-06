#include "sets.h"             //Содержится в пакете

File fsUploadFile;
TickerScheduler ts(10);
DNSServer dnsServer;
ESP8266WebServer HTTP(80);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer HTTPWAN(8080);

Ticker motion;
Ticker furnace[8];

WiFiUDP udp;
WiFiClient wclient;
StringCommand sCmd;     // Обьект для работы с командами
PubSubClient client(wclient);

OneWire *oneWire;
DallasTemperature sensors;
DHT dht;

RCSwitch mySwitch = RCSwitch();
IRrecv *irReceiver;
decode_results results;
IRsend *irSender;

LivoloTx *gLivolo;

WS2812FX ws2812fx = WS2812FX();

Bounce * buttons = new Bounce[NUM_BUTTONS];


HLW8012 hlw8012;

void setup() {
  //Serial.begin(115200);
  TickerScheduler(1);
  start_init();
}

void loop() {
  ts.update();
  HTTP.handleClient();
  yield();
  HTTPWAN.handleClient();
  yield();
  handleSSDP();
  dnsServer.processNextRequest();
  handleScenary();
  handleMQTT();
  ws2812fx.service();
  handleRfReceiv();
  handleButtons();
}
