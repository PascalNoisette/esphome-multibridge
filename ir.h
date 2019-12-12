#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <RCSwitch.h>
#include "esphome.h"

extern IRsend irsend;
IRsend irsend = IRsend(D5);

extern RCSwitch mySwitch;
RCSwitch mySwitch = RCSwitch();

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
        register_service(
            &IRsendWrapper::send_samsung, 
            "send_samsung",
            {"data", "nbits", "repeat"}
        );
        register_service(
            &IRsendWrapper::rf_send, 
            "rf_send",
            {"data", "protocol", "pulse_length"}
        );
  }
  void send_nec(std::string data, int nbits, int repeat) {
    long int code = strtoul(data.c_str(), NULL, 16);
    ESP_LOGD("custom", "Launch function irsend.sendNEC(%#010lx, %d, %d)", code, nbits, repeat);
    irsend.sendNEC(code, nbits, repeat);
  }

  void send_samsung(std::string data, int nbits, int repeat) {
    long int code = strtoul(data.c_str(), NULL, 16);
    ESP_LOGD("custom", "Launch function irsend.sendSAMSUNG(%#010lx, %d, %d)", code , nbits, repeat);
    irsend.sendSAMSUNG(code, nbits, repeat);
  }

  void rf_send(std::string data, int protocol, int pulse_length) {
    ESP_LOGD("custom", "Launch function rf_send(%s, %d, %d)", data.c_str(), protocol, pulse_length);
    mySwitch.enableTransmit(D7);
    mySwitch.setProtocol(protocol);
    mySwitch.setPulseLength(pulse_length);
    mySwitch.send(data.c_str());
    mySwitch.disableTransmit();
  }
};
