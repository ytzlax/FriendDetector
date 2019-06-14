#include "./esppl_functions.h"

void setup() {
  delay(500);
  Serial.begin(115200);
  esppl_init(cb);
}

String mac2String(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

String converter(uint8_t *str) {
  return String((char *)str);
}

void cb(esppl_frame_info *info) {


  Serial.print("sourceaddr:" );
  Serial.println( mac2String(info->sourceaddr));
  Serial.print("receiveraddr:" );
  Serial.println( mac2String(info->receiveraddr));
  Serial.print("destinationaddr:" );
  Serial.println( mac2String(info->destinationaddr));
  Serial.print("transmitteraddr:" );
  Serial.println( mac2String(info->transmitteraddr));
  Serial.print("rssi:" );
  Serial.println( (info->rssi));
  Serial.print("ssid:" );
  Serial.println( converter(info->ssid));
  Serial.print("bssid:" );
  Serial.println( converter(info->bssid));
  Serial.println();
  Serial.println();


}


void loop() { // I didn't write this part but it sure looks fancy.
  esppl_sniffing_start();
  while (true) {
    for (int i = ESPPL_CHANNEL_MIN; i <= ESPPL_CHANNEL_MAX; i++ ) {
      esppl_set_channel(i);
      while (esppl_process_frames()) {
      }
    }
  }
}
