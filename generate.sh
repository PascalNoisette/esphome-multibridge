#!/bin/bash

#LIST=`grep ": public RemoteTransmitterActionBase<Ts...> {" -R ./.esphome/build/tinyremote/src/esphome/components/remote_base/ | grep -o "[A-Za-z0-9]\+Action" | grep -v RemoteTransmitterAction`
SIMPLE=`grep 'TEMPLATABLE_VALUE.*data' -R ./.esphome/build/tinyremote/src/esphome/components/remote_base/  -l | xargs grep  'TEMPLATABLE_VALUE.*nbits' -l | xargs grep ": public RemoteTransmitterActionBase<Ts...> {" | grep -o "[A-Za-z0-9]\+Action" | grep -v RemoteTransmitterAction`
ADDRES=`grep 'TEMPLATABLE_VALUE.*address' -R ./.esphome/build/tinyremote/src/esphome/components/remote_base/  -l | xargs grep  'TEMPLATABLE_VALUE.*command)' -l | xargs grep ": public RemoteTransmitterActionBase<Ts...> {" | grep -o "[A-Za-z0-9]\+Action" | grep -v RemoteTransmitterAction| grep -v NECAction`
CADDRES=("NECAction")
FIRST=`grep 'TEMPLATABLE_VALUE.*first' -R ./.esphome/build/tinyremote/src/esphome/components/remote_base/  -l | xargs grep  'TEMPLATABLE_VALUE.*second)' -l | xargs grep ": public RemoteTransmitterActionBase<Ts...> {" | grep -o "[A-Za-z0-9]\+Action" | grep -v RemoteTransmitterAction`
LIST=`echo ${SIMPLE[@]} ${ADDRES[@]} ${CADDRES[@]}  ${FIRST[@]}`

printf "%s\n" ${LIST[@]}  | xargs -I% echo '    remote_base::%<> *remote_base_%;' > action
ed -s service.h <<EOF
/Begin declare action/+,/End declare action/-d
/Begin declare action/ r action
w
q
EOF
rm action


printf "%s\n" ${LIST[@]} | sed 's/Action//' | xargs -I% echo '        remote_base_%Action = new remote_base::%Action<>();
        remote_base_%Action->set_transmitter(remote_transmitter_remotetransmittercomponent);
        register_service(&IRsendWrapper::send%, snakeCase("send%"), {"data", "nbits", "repeat"});
' > action
ed -s service.h <<EOF
/Begin setup action/+,/End setup action/-d
/Begin setup action/ r action
w
q
EOF
rm action


printf "%s\n" ${SIMPLE[@]} | sed 's/Action//' | xargs -I£ echo '    void send£(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        long __INT32_TYPE__ code = strtoul(data.c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.send£(%#010lx, %d, %d)", code , nbits, repeat);
        remote_base_£Action->set_data(code);
        remote_base_£Action->set_nbits(nbits);
        remote_base_£Action->set_send_times(repeat);
        remote_base_£Action->set_send_wait(25000);
        remote_base_£Action->play_complex();
    }
' > action
printf "%s\n" ${CADDRES[@]} | sed 's/Action//' | xargs -I£ echo '    void send£(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.send£(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.send£(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_£Action->set_address(address);
        remote_base_£Action->set_command(command);
        remote_base_£Action->set_command_repeats(1);
        remote_base_£Action->set_send_times(repeat);
        remote_base_£Action->set_send_wait(25000);
        remote_base_£Action->play_complex();
    }
' >> action

printf "%s\n" ${ADDRES[@]} | sed 's/Action//' | xargs -I£ echo '    void send£(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        if (data.size()<8) {
            ESP_LOGD("custom", "Invalid code function irsend.send£(%s, %d, %d) is too short, expect 32 bits such as 0x538DDB4A", data , nbits, repeat);
        }
        __INT16_TYPE__ command = strtoul(data.substr(data.size() - 4).c_str(), NULL, 16);
        __INT16_TYPE__ address = strtoul(data.substr(data.size() - 8).substr(0, 4).c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.send£(%#010lx, %#010lx, %d, %d)", address, command , nbits, repeat);
        remote_base_£Action->set_address(address);
        remote_base_£Action->set_command(command);
        remote_base_£Action->set_send_times(repeat);
        remote_base_£Action->set_send_wait(25000);
        remote_base_£Action->play_complex();
    }
' >> action

printf "%s\n" ${FIRST[@]} | sed 's/Action//' | xargs -I£ echo '    void send£(std::string data, __INT32_TYPE__ nbits, __INT32_TYPE__ repeat) {
        long __INT32_TYPE__ code = strtoul(data.c_str(), NULL, 16);
        ESP_LOGD("custom", "Launch function irsend.send£(%#010lx, %d, %d)", code , nbits, repeat);
        remote_base_£Action->set_first(code);
        if (repeat>1) {
                remote_base_£Action->set_second(code);
        }
        remote_base_£Action->set_send_times(repeat);
        remote_base_£Action->set_send_wait(25000);
        remote_base_£Action->play_complex();
    }
' >> action

ed -s service.h <<EOF
/Begin define service/+,/End define service/-d
/Begin define service/ r action
w
q
EOF
rm action


## TODO https://raw.githubusercontent.com/esphome/esphome-docs/current/components/remote_transmitter.rst