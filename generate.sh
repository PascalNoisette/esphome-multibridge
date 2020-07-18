#!/bin/bash

cat > ir.h <<EOF
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <RCSwitch.h>
#include "esphome.h"

extern IRsend irsend;
IRsend irsend = IRsend(D5);

extern RCSwitch mySwitch;
RCSwitch mySwitch = RCSwitch();


std::string snakeCase(std::string &&camelCase) {
  std::string str(1, tolower(camelCase[0]));

  // First place underscores between contiguous lower and upper case letters.
  for (auto it = camelCase.begin() + 1; it != camelCase.end(); ++it) {
    if (isupper(*it) && *(it-1) != '_' && islower(*(it-1))) {
      str += "_";
    }
    str += *it;
  }

  // Then convert it to lower case.
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);

  return str;
}

class IRsendWrapper : public Component, public CustomAPIDevice, public Sensor {
 public:
  void rf_send(std::string data, int protocol, int pulse_length) {
    ESP_LOGD("custom", "Launch function rf_send(%s, %d, %d)", data.c_str(), protocol, pulse_length);
    mySwitch.setProtocol(protocol);
    mySwitch.setPulseLength(pulse_length);
    mySwitch.send(data.c_str());
  }
  void setup() override {
        
        irsend.begin();
        mySwitch.enableTransmit(D7);


        /* https://esphome.io/custom/custom_component.html?highlight=custom_component#native-api-custom-component */
        register_service(
            &IRsendWrapper::rf_send, 
            "rf_send",
            {"data", "protocol", "pulse_length"}
        );
EOF


cat ./nmcu_multibridge/.piolibdeps/nmcu_multibridge/IRremoteESP8266/src/IRsend.h | tr -d '\n' | sed 's/;/;\n/g' |  grep 'void.*' -o | sed -E "s/[[:space:]]+/ /g" | sed "s/ = [a-zA-Z0-9_]\+//g" | sed "s/const //g" | sed "s/unsigned //g" | sed "s/nbytes/nbits/" | grep 'uint64_t data, uint16_t nbits, uint16_t repeat' | grep 'send[^(]\+' -o > supported_function_1.txt
cat ./nmcu_multibridge/.piolibdeps/nmcu_multibridge/IRremoteESP8266/src/IRsend.h | tr -d '\n' | sed 's/;/;\n/g' |  grep 'void.*' -o | sed -E "s/[[:space:]]+/ /g" | sed "s/ = [a-zA-Z0-9_]\+//g" | sed "s/const //g" | sed "s/unsigned //g" | grep 'char data\[\], uint16_t nbytes, uint16_t repeat'| grep 'send[^(]\+' -o > supported_function_2.txt
cat supported_function_1.txt | xargs -L1 -I% echo '        register_service(&IRsendWrapper::%, snakeCase("%"), {"data", "nbits", "repeat"});' >> ir.h
cat supported_function_2.txt | xargs -L1 -I% echo '        register_service(&IRsendWrapper::%, snakeCase("%"), {"data", "nbits", "repeat"});' >> ir.h

echo '    };' >> ir.h 

echo

cat supported_function_1.txt | xargs -L1 -Iµ echo '    void µ(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.µ(%#010lx, %d, %d)", code , nbits, repeat);irsend.µ(code, nbits, repeat);}' >> ir.h
cat supported_function_2.txt | xargs -L1 -Iµ echo '    void µ(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.µ(%s, %d, %d)", code ,  nbits, repeat);irsend.µ(code, nbits, repeat);}' >> ir.h



echo '};' >> ir.h 