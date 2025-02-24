#pragma once

#include "esphome.h"
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <map>
#include <string>
#include <functional>

namespace esphome {
namespace esp_now_connect {

class ESPNowComponent : public Component {
 public:
  void setup() override;  
  void send(const std::string &msg);
  void on(const std::string &command, std::function<void()> callback);

 private:
  std::map<std::string, std::function<void()>> command_handlers_;
};

}  // namespace esp_now_connect
}  // namespace esphome
