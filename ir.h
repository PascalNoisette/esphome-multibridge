#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "esphome.h"

extern IRsend irsend;
IRsend irsend = IRsend(D5);

class IRsendWrapper : public Component {
 public:
  void setup() override {
        
        irsend.begin();
  }
  void loop() override {
    // This will be called by App.loop()
  }
};
