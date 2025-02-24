# ESPHome components

[![License][license-shield]][license]
[![ESPHome release][esphome-release-shield]][esphome-release]

[license-shield]: https://img.shields.io/static/v1?label=License&message=GPL%203.0&color=orange&logo=license
[license]: https://opensource.org/license/gpl-3-0
[esphome-release-shield]: https://img.shields.io/static/v1?label=ESPHome&message=2023.12&color=green&logo=esphome
[esphome-release]: https://GitHub.com/esphome/esphome/releases/



A collection of my ESPHome components.

To use this repository you should confugure it inside your yaml-configuration:

```yaml
external_components:
  - source: github://atshome/esphome-components

esp_now_connect:
  id: espnow
  commands:
```

## Usage examples

ATTENTION: Make sure to use the latest arduino version as this uses the new esp-now broadcast feature. And it's recommended to use the same channel as your wifi router.

1. Node1 contains simple gpio switch

```yaml

esphome:
  name: node1
  friendly_name: Node1
esp8266:
  board: nodemcuv2
  framework:
    version: recommended

external_components:
  - source: github://atshome/esphome-components

esp_now_connect:
  id: espnow
  commands:
    - led toggle: |-
        id(led)->toggle();
switch:
  - platform: gpio
    id: led
    name: "Switch 1"
    pin: GPIO2
    inverted: true

```

2. Node2 contains a Button

```yaml

external_components:
  - source: github://atshome/esphome-components

esp_now_connect:
  id: espnow
  
binary_sensor:
  - platform: gpio
    pin:
      number: D2
      mode: input_pullup
    name: "Button"
    on_press:
      - lambda: |-
          id(espnow)->send("led toggle");

```

## What's next

* Waiting for Your Suggestions 😁😁


## Acknowledgments

THIS REPO is Ported from (https://github.com/iphong/esphome-espnow) all Thanks to (iphong) (https://github.com/iphong)

You are free to use and modify these code to better fit your project and you can star the project

Cheers!!
