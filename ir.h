#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "esphome.h"

extern IRsend irsend;
IRsend irsend = IRsend(D5);

class IRsendWrapper : public Component, public CustomAPIDevice, public Sensor {
 public:
  void setup() override {
        
        irsend.begin();

        /* https://esphome.io/custom/custom_component.html?highlight=custom_component#native-api-custom-component */
        register_service(
            &IRsendWrapper::send_nec, 
            "send_nec",
            {"data", "nbits", "repeat"}
        );
  }
  void send_nec(int data, int nbits, int repeat) {
    ESP_LOGD("custom", "Launch function irsend.sendNEC(%#010x, %d, %d)", data, nbits, repeat);
    irsend.sendNEC(data, nbits, repeat);
  }
};
