#include "esphome.h"



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
 private:
    remote_transmitter::RemoteTransmitterComponent *remote_transmitter_remotetransmittercomponent;
    /* Begin declare action */
    remote_base::LGAction<> *remote_base_LGAction;
    remote_base::SonyAction<> *remote_base_SonyAction;
    remote_base::SamsungAction<> *remote_base_SamsungAction;
    remote_base::DraytonAction<> *remote_base_DraytonAction;
    remote_base::RC5Action<> *remote_base_RC5Action;
    remote_base::ByronSXAction<> *remote_base_ByronSXAction;
    remote_base::DishAction<> *remote_base_DishAction;
    remote_base::RC6Action<> *remote_base_RC6Action;
    remote_base::PanasonicAction<> *remote_base_PanasonicAction;
    remote_base::Samsung36Action<> *remote_base_Samsung36Action;
    remote_base::CanalSatAction<> *remote_base_CanalSatAction;
    remote_base::CanalSatLDAction<> *remote_base_CanalSatLDAction;
    remote_base::NECAction<> *remote_base_NECAction;
    remote_base::CoolixAction<> *remote_base_CoolixAction;
    /* End declare action */

    
 public:
    IRsendWrapper(remote_transmitter::RemoteTransmitterComponent *r) {
        remote_transmitter_remotetransmittercomponent = r;
    }

    void setup() override {
      /* Begin setup action */
        remote_base_LGAction = new remote_base::LGAction<>();
        remote_base_LGAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendLG, snakeCase("sendLG"), {"data", "nbits", "repeat"});

        remote_base_SonyAction = new remote_base::SonyAction<>();
        remote_base_SonyAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendSony, snakeCase("sendSony"), {"data", "nbits", "repeat"});

        remote_base_SamsungAction = new remote_base::SamsungAction<>();
        remote_base_SamsungAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendSamsung, snakeCase("sendSamsung"), {"data", "nbits", "repeat"});

        remote_base_DraytonAction = new remote_base::DraytonAction<>();
        remote_base_DraytonAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendDrayton, snakeCase("sendDrayton"), {"data", "nbits", "repeat"});

        remote_base_RC5Action = new remote_base::RC5Action<>();
        remote_base_RC5Action->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendRC5, snakeCase("sendRC5"), {"data", "nbits", "repeat"});

        remote_base_ByronSXAction = new remote_base::ByronSXAction<>();
        remote_base_ByronSXAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendByronSX, snakeCase("sendByronSX"), {"data", "nbits", "repeat"});

        remote_base_DishAction = new remote_base::DishAction<>();
        remote_base_DishAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendDish, snakeCase("sendDish"), {"data", "nbits", "repeat"});

        remote_base_RC6Action = new remote_base::RC6Action<>();
        remote_base_RC6Action->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendRC6, snakeCase("sendRC6"), {"data", "nbits", "repeat"});

        remote_base_PanasonicAction = new remote_base::PanasonicAction<>();
        remote_base_PanasonicAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendPanasonic, snakeCase("sendPanasonic"), {"data", "nbits", "repeat"});

        remote_base_Samsung36Action = new remote_base::Samsung36Action<>();
        remote_base_Samsung36Action->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendSamsung36, snakeCase("sendSamsung36"), {"data", "nbits", "repeat"});

        remote_base_CanalSatAction = new remote_base::CanalSatAction<>();
        remote_base_CanalSatAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendCanalSat, snakeCase("sendCanalSat"), {"data", "nbits", "repeat"});

        remote_base_CanalSatLDAction = new remote_base::CanalSatLDAction<>();
        remote_base_CanalSatLDAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendCanalSatLD, snakeCase("sendCanalSatLD"), {"data", "nbits", "repeat"});

        remote_base_NECAction = new remote_base::NECAction<>();
        remote_base_NECAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendNEC, snakeCase("sendNEC"), {"data", "nbits", "repeat"});

        remote_base_CoolixAction = new remote_base::CoolixAction<>();
        remote_base_CoolixAction->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::sendCoolix, snakeCase("sendCoolix"), {"data", "nbits", "repeat"});

      /* End setup action */

        ESP_LOGD("custom", "Setup of IRsendWrapper is sucessfull");
    };
    /* Begin define service */
    void sendLG(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        long __INT32_TYPE__ code = strtoul(data.c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendLG(%#010lx, %d, %d)", code , nbits, repeat);
        remote_base_LGAction->set_data(code);
        remote_base_LGAction->set_nbits(nbits);
        remote_base_LGAction->set_send_times(repeat);
        remote_base_LGAction->set_send_wait(25000);
        remote_base_LGAction->play_complex();
    }

    void sendSony(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        long __INT32_TYPE__ code = strtoul(data.c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendSony(%#010lx, %d, %d)", code , nbits, repeat);
        remote_base_SonyAction->set_data(code);
        remote_base_SonyAction->set_nbits(nbits);
        remote_base_SonyAction->set_send_times(repeat);
        remote_base_SonyAction->set_send_wait(25000);
        remote_base_SonyAction->play_complex();
    }

    void sendSamsung(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        long __INT32_TYPE__ code = strtoul(data.c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendSamsung(%#010lx, %d, %d)", code , nbits, repeat);
        remote_base_SamsungAction->set_data(code);
        remote_base_SamsungAction->set_nbits(nbits);
        remote_base_SamsungAction->set_send_times(repeat);
        remote_base_SamsungAction->set_send_wait(25000);
        remote_base_SamsungAction->play_complex();
    }

    void sendNEC(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendNEC(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendNEC(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_NECAction->set_address(address);
        remote_base_NECAction->set_command(command);
        remote_base_NECAction->set_command_repeats(1);
        remote_base_NECAction->set_send_times(repeat);
        remote_base_NECAction->set_send_wait(25000);
        remote_base_NECAction->play_complex();
    }

    void sendDrayton(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendDrayton(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendDrayton(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_DraytonAction->set_address(address);
        remote_base_DraytonAction->set_command(command);
        remote_base_DraytonAction->set_send_times(repeat);
        remote_base_DraytonAction->set_send_wait(25000);
        remote_base_DraytonAction->play_complex();
    }

    void sendRC5(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendRC5(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendRC5(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_RC5Action->set_address(address);
        remote_base_RC5Action->set_command(command);
        remote_base_RC5Action->set_send_times(repeat);
        remote_base_RC5Action->set_send_wait(25000);
        remote_base_RC5Action->play_complex();
    }

    void sendByronSX(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendByronSX(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendByronSX(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_ByronSXAction->set_address(address);
        remote_base_ByronSXAction->set_command(command);
        remote_base_ByronSXAction->set_send_times(repeat);
        remote_base_ByronSXAction->set_send_wait(25000);
        remote_base_ByronSXAction->play_complex();
    }

    void sendDish(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendDish(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendDish(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_DishAction->set_address(address);
        remote_base_DishAction->set_command(command);
        remote_base_DishAction->set_send_times(repeat);
        remote_base_DishAction->set_send_wait(25000);
        remote_base_DishAction->play_complex();
    }

    void sendRC6(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendRC6(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendRC6(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_RC6Action->set_address(address);
        remote_base_RC6Action->set_command(command);
        remote_base_RC6Action->set_send_times(repeat);
        remote_base_RC6Action->set_send_wait(25000);
        remote_base_RC6Action->play_complex();
    }

    void sendPanasonic(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendPanasonic(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendPanasonic(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_PanasonicAction->set_address(address);
        remote_base_PanasonicAction->set_command(command);
        remote_base_PanasonicAction->set_send_times(repeat);
        remote_base_PanasonicAction->set_send_wait(25000);
        remote_base_PanasonicAction->play_complex();
    }

    void sendSamsung36(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendSamsung36(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendSamsung36(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_Samsung36Action->set_address(address);
        remote_base_Samsung36Action->set_command(command);
        remote_base_Samsung36Action->set_send_times(repeat);
        remote_base_Samsung36Action->set_send_wait(25000);
        remote_base_Samsung36Action->play_complex();
    }

    void sendCanalSat(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendCanalSat(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendCanalSat(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_CanalSatAction->set_address(address);
        remote_base_CanalSatAction->set_command(command);
        remote_base_CanalSatAction->set_send_times(repeat);
        remote_base_CanalSatAction->set_send_wait(25000);
        remote_base_CanalSatAction->play_complex();
    }

    void sendCanalSatLD(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.sendCanalSatLD(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendCanalSatLD(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_CanalSatLDAction->set_address(address);
        remote_base_CanalSatLDAction->set_command(command);
        remote_base_CanalSatLDAction->set_send_times(repeat);
        remote_base_CanalSatLDAction->set_send_wait(25000);
        remote_base_CanalSatLDAction->play_complex();
    }

    void sendCoolix(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        long __INT32_TYPE__ code = strtoul(data.c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.sendCoolix(%#010lx, %d, %d)", code , nbits, repeat);
        remote_base_CoolixAction->set_first(code);
        if (repeat>1) {
                remote_base_CoolixAction->set_second(code);
        }
        remote_base_CoolixAction->set_send_times(repeat);
        remote_base_CoolixAction->set_send_wait(25000);
        remote_base_CoolixAction->play_complex();
    }

    /* End define service */
};
