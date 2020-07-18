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
        register_service(&IRsendWrapper::sendNEC, snakeCase("sendNEC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSony, snakeCase("sendSony"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSherwood, snakeCase("sendSherwood"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSAMSUNG, snakeCase("sendSAMSUNG"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSamsung36, snakeCase("sendSamsung36"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendLG, snakeCase("sendLG"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendLG2, snakeCase("sendLG2"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSharpRaw, snakeCase("sendSharpRaw"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendJVC, snakeCase("sendJVC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDenon, snakeCase("sendDenon"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSanyoLC7461, snakeCase("sendSanyoLC7461"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDISH, snakeCase("sendDISH"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendPanasonic64, snakeCase("sendPanasonic64"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendRC5, snakeCase("sendRC5"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendRC6, snakeCase("sendRC6"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendRCMM, snakeCase("sendRCMM"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendCOOLIX, snakeCase("sendCOOLIX"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendWhynter, snakeCase("sendWhynter"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMitsubishi, snakeCase("sendMitsubishi"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMitsubishi2, snakeCase("sendMitsubishi2"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendInax, snakeCase("sendInax"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendAiwaRCT501, snakeCase("sendAiwaRCT501"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendGree, snakeCase("sendGree"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendGoodweather, snakeCase("sendGoodweather"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendNikai, snakeCase("sendNikai"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMidea, snakeCase("sendMidea"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMagiQuest, snakeCase("sendMagiQuest"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendLasertag, snakeCase("sendLasertag"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendCarrierAC, snakeCase("sendCarrierAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendGICable, snakeCase("sendGICable"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendLutron, snakeCase("sendLutron"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendPioneer, snakeCase("sendPioneer"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendVestelAc, snakeCase("sendVestelAc"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendTeco, snakeCase("sendTeco"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendLegoPf, snakeCase("sendLegoPf"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSamsungAC, snakeCase("sendSamsungAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendSharpAc, snakeCase("sendSharpAc"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMitsubishi136, snakeCase("sendMitsubishi136"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMitsubishi112, snakeCase("sendMitsubishi112"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMitsubishiAC, snakeCase("sendMitsubishiAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMitsubishiHeavy88, snakeCase("sendMitsubishiHeavy88"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMitsubishiHeavy152, snakeCase("sendMitsubishiHeavy152"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendFujitsuAC, snakeCase("sendFujitsuAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendKelvinator, snakeCase("sendKelvinator"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDaikin, snakeCase("sendDaikin"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDaikin128, snakeCase("sendDaikin128"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDaikin152, snakeCase("sendDaikin152"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDaikin160, snakeCase("sendDaikin160"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDaikin176, snakeCase("sendDaikin176"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDaikin2, snakeCase("sendDaikin2"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendDaikin216, snakeCase("sendDaikin216"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendArgo, snakeCase("sendArgo"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendTrotec, snakeCase("sendTrotec"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendToshibaAC, snakeCase("sendToshibaAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendHaierAC, snakeCase("sendHaierAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendHaierACYRW02, snakeCase("sendHaierACYRW02"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendHitachiAC, snakeCase("sendHitachiAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendHitachiAC1, snakeCase("sendHitachiAC1"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendHitachiAC2, snakeCase("sendHitachiAC2"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendHitachiAc424, snakeCase("sendHitachiAc424"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendWhirlpoolAC, snakeCase("sendWhirlpoolAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendElectraAC, snakeCase("sendElectraAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendPanasonicAC, snakeCase("sendPanasonicAC"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendMWM, snakeCase("sendMWM"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendTcl112Ac, snakeCase("sendTcl112Ac"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendNeoclima, snakeCase("sendNeoclima"), {"data", "nbits", "repeat"});
        register_service(&IRsendWrapper::sendAmcor, snakeCase("sendAmcor"), {"data", "nbits", "repeat"});
    };
    void sendNEC(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendNEC(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendNEC(code, nbits, repeat);}
    void sendSony(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendSony(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendSony(code, nbits, repeat);}
    void sendSherwood(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendSherwood(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendSherwood(code, nbits, repeat);}
    void sendSAMSUNG(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendSAMSUNG(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendSAMSUNG(code, nbits, repeat);}
    void sendSamsung36(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendSamsung36(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendSamsung36(code, nbits, repeat);}
    void sendLG(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendLG(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendLG(code, nbits, repeat);}
    void sendLG2(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendLG2(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendLG2(code, nbits, repeat);}
    void sendSharpRaw(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendSharpRaw(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendSharpRaw(code, nbits, repeat);}
    void sendJVC(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendJVC(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendJVC(code, nbits, repeat);}
    void sendDenon(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendDenon(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendDenon(code, nbits, repeat);}
    void sendSanyoLC7461(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendSanyoLC7461(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendSanyoLC7461(code, nbits, repeat);}
    void sendDISH(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendDISH(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendDISH(code, nbits, repeat);}
    void sendPanasonic64(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendPanasonic64(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendPanasonic64(code, nbits, repeat);}
    void sendRC5(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendRC5(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendRC5(code, nbits, repeat);}
    void sendRC6(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendRC6(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendRC6(code, nbits, repeat);}
    void sendRCMM(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendRCMM(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendRCMM(code, nbits, repeat);}
    void sendCOOLIX(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendCOOLIX(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendCOOLIX(code, nbits, repeat);}
    void sendWhynter(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendWhynter(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendWhynter(code, nbits, repeat);}
    void sendMitsubishi(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendMitsubishi(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendMitsubishi(code, nbits, repeat);}
    void sendMitsubishi2(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendMitsubishi2(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendMitsubishi2(code, nbits, repeat);}
    void sendInax(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendInax(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendInax(code, nbits, repeat);}
    void sendAiwaRCT501(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendAiwaRCT501(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendAiwaRCT501(code, nbits, repeat);}
    void sendGree(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendGree(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendGree(code, nbits, repeat);}
    void sendGoodweather(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendGoodweather(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendGoodweather(code, nbits, repeat);}
    void sendNikai(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendNikai(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendNikai(code, nbits, repeat);}
    void sendMidea(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendMidea(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendMidea(code, nbits, repeat);}
    void sendMagiQuest(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendMagiQuest(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendMagiQuest(code, nbits, repeat);}
    void sendLasertag(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendLasertag(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendLasertag(code, nbits, repeat);}
    void sendCarrierAC(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendCarrierAC(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendCarrierAC(code, nbits, repeat);}
    void sendGICable(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendGICable(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendGICable(code, nbits, repeat);}
    void sendLutron(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendLutron(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendLutron(code, nbits, repeat);}
    void sendPioneer(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendPioneer(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendPioneer(code, nbits, repeat);}
    void sendVestelAc(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendVestelAc(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendVestelAc(code, nbits, repeat);}
    void sendTeco(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendTeco(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendTeco(code, nbits, repeat);}
    void sendLegoPf(std::string data, int nbits, int repeat) {long int code = strtoul(data.c_str(), NULL, 16);ESP_LOGD("custom", "Launch function irsend.sendLegoPf(%#010lx, %d, %d)", code , nbits, repeat);irsend.sendLegoPf(code, nbits, repeat);}
    void sendSamsungAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendSamsungAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendSamsungAC(code, nbits, repeat);}
    void sendSharpAc(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendSharpAc(%s, %d, %d)", code ,  nbits, repeat);irsend.sendSharpAc(code, nbits, repeat);}
    void sendMitsubishi136(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendMitsubishi136(%s, %d, %d)", code ,  nbits, repeat);irsend.sendMitsubishi136(code, nbits, repeat);}
    void sendMitsubishi112(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendMitsubishi112(%s, %d, %d)", code ,  nbits, repeat);irsend.sendMitsubishi112(code, nbits, repeat);}
    void sendMitsubishiAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendMitsubishiAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendMitsubishiAC(code, nbits, repeat);}
    void sendMitsubishiHeavy88(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendMitsubishiHeavy88(%s, %d, %d)", code ,  nbits, repeat);irsend.sendMitsubishiHeavy88(code, nbits, repeat);}
    void sendMitsubishiHeavy152(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendMitsubishiHeavy152(%s, %d, %d)", code ,  nbits, repeat);irsend.sendMitsubishiHeavy152(code, nbits, repeat);}
    void sendFujitsuAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendFujitsuAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendFujitsuAC(code, nbits, repeat);}
    void sendKelvinator(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendKelvinator(%s, %d, %d)", code ,  nbits, repeat);irsend.sendKelvinator(code, nbits, repeat);}
    void sendDaikin(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendDaikin(%s, %d, %d)", code ,  nbits, repeat);irsend.sendDaikin(code, nbits, repeat);}
    void sendDaikin128(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendDaikin128(%s, %d, %d)", code ,  nbits, repeat);irsend.sendDaikin128(code, nbits, repeat);}
    void sendDaikin152(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendDaikin152(%s, %d, %d)", code ,  nbits, repeat);irsend.sendDaikin152(code, nbits, repeat);}
    void sendDaikin160(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendDaikin160(%s, %d, %d)", code ,  nbits, repeat);irsend.sendDaikin160(code, nbits, repeat);}
    void sendDaikin176(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendDaikin176(%s, %d, %d)", code ,  nbits, repeat);irsend.sendDaikin176(code, nbits, repeat);}
    void sendDaikin2(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendDaikin2(%s, %d, %d)", code ,  nbits, repeat);irsend.sendDaikin2(code, nbits, repeat);}
    void sendDaikin216(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendDaikin216(%s, %d, %d)", code ,  nbits, repeat);irsend.sendDaikin216(code, nbits, repeat);}
    void sendArgo(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendArgo(%s, %d, %d)", code ,  nbits, repeat);irsend.sendArgo(code, nbits, repeat);}
    void sendTrotec(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendTrotec(%s, %d, %d)", code ,  nbits, repeat);irsend.sendTrotec(code, nbits, repeat);}
    void sendToshibaAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendToshibaAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendToshibaAC(code, nbits, repeat);}
    void sendHaierAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendHaierAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendHaierAC(code, nbits, repeat);}
    void sendHaierACYRW02(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendHaierACYRW02(%s, %d, %d)", code ,  nbits, repeat);irsend.sendHaierACYRW02(code, nbits, repeat);}
    void sendHitachiAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendHitachiAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendHitachiAC(code, nbits, repeat);}
    void sendHitachiAC1(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendHitachiAC1(%s, %d, %d)", code ,  nbits, repeat);irsend.sendHitachiAC1(code, nbits, repeat);}
    void sendHitachiAC2(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendHitachiAC2(%s, %d, %d)", code ,  nbits, repeat);irsend.sendHitachiAC2(code, nbits, repeat);}
    void sendHitachiAc424(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendHitachiAc424(%s, %d, %d)", code ,  nbits, repeat);irsend.sendHitachiAc424(code, nbits, repeat);}
    void sendWhirlpoolAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendWhirlpoolAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendWhirlpoolAC(code, nbits, repeat);}
    void sendElectraAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendElectraAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendElectraAC(code, nbits, repeat);}
    void sendPanasonicAC(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendPanasonicAC(%s, %d, %d)", code ,  nbits, repeat);irsend.sendPanasonicAC(code, nbits, repeat);}
    void sendMWM(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendMWM(%s, %d, %d)", code ,  nbits, repeat);irsend.sendMWM(code, nbits, repeat);}
    void sendTcl112Ac(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendTcl112Ac(%s, %d, %d)", code ,  nbits, repeat);irsend.sendTcl112Ac(code, nbits, repeat);}
    void sendNeoclima(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendNeoclima(%s, %d, %d)", code ,  nbits, repeat);irsend.sendNeoclima(code, nbits, repeat);}
    void sendAmcor(std::string data, int nbits, int repeat) {const unsigned char* code = reinterpret_cast<const unsigned char*> (data.c_str()); ESP_LOGD("custom", "Launch function irsend.sendAmcor(%s, %d, %d)", code ,  nbits, repeat);irsend.sendAmcor(code, nbits, repeat);}
};
