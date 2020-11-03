#include <TridentTD_LineNotify.h>
#define SSID        " Your SSID "
#define PASSWORD    " Your Password"
#define LINE_TOKEN  " Your Token "
bool CHECK = true;
int digitalValue;

void setup() {
  pinMode(17, INPUT_PULLUP);
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  Serial.printf("\nWiFi connected\nIP : ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(400);
  }
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}

void loop() {
  delay(1);
  digitalValue = digitalRead(17);
  Serial.print(" digitalValue : ");
  Serial.println(digitalValue);
  CHECK_Connection();
  delay(1000);
  if ( CHECK == true && digitalValue == 0 ) {
    CHECK = false;
    LINE.notify(" H2S Alarm Contect : Khun Nattawut 093-319-0902 , Khun Kittisak 086-407-4897 , Khun Jaruwan 083-569-9619 ");
    Serial.println("Alarm");
  }
  if ( CHECK == false && digitalValue == 1 ) {
    LINE.notify(" H2S Normal");
    Serial.println("Normal");
    CHECK = true;
  }
}

void CHECK_Connection() {
  Serial.print("WiFi.status() : ");
  Serial.println(WiFi.status());
  Serial.print("WiFi.localIP() : ");
  Serial.println(WiFi.localIP());
  Serial.print("WL_CONNECTED : ");
  Serial.println(WL_CONNECTED);
  if ( WiFi.status() == 6 ) {
    ESP.restart();
  }
}
