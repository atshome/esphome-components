#include "esp_now_connect.h"

namespace esphome {
namespace esp_now_connect {

static ESPNowComponent *global_esp_now = nullptr;

void ESPNowComponent::setup() {  
  global_esp_now = this;
  WiFi.mode(WIFI_AP_STA);
  if (esp_now_init() == 0) {
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    uint8_t broadcast[] = {255, 255, 255, 255, 255, 255};
    if (esp_now_is_peer_exist(broadcast)) {
      esp_now_del_peer(broadcast);
    }
    esp_now_add_peer(broadcast, ESP_NOW_ROLE_COMBO, 1, nullptr, 0);
    esp_now_register_recv_cb([](uint8_t *mac, uint8_t *payload, uint8_t size) {
      std::string msg(reinterpret_cast<char *>(payload), size);
      if (global_esp_now && global_esp_now->command_handlers_.count(msg)) {
        global_esp_now->command_handlers_[msg]();
      }
    });
  }
}

void ESPNowComponent::send(const std::string &msg) {  
  uint8_t broadcast[] = {255, 255, 255, 255, 255, 255};
  esp_now_send(broadcast, (uint8_t *)msg.c_str(), msg.length());
}

void ESPNowComponent::on(const std::string &command, std::function<void()> callback) {
  command_handlers_[command] = callback;
}

}  // namespace esp_now_connect
}  // namespace esphome
