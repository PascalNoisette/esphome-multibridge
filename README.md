# Multibridge

Define generic services to be called with parameters from home assistant.

- remove the clutter from defining one switch per remote code inside esphome
- common interface for all services (if possible) with consistant parameters : esphome.sensor_send_manufacturer(code, nbit, repeat);

Its purpuse is to be reused in home assistant https://github.com/PascalNoisette/homeassistant-config/blob/master/lovelace/remote/tiny_iremote.yaml 
