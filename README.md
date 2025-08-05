# 🧩 Custom ESPHome Components

This repository contains a collection of custom components for [ESPHome](https://esphome.io/) that I use in my personal [Home Assistant](https://www.home-assistant.io/) setup.

Each component is designed to extend ESPHome’s functionality with additional sensors, displays, or other HW that aren't (yet) part of the official ESPHome distribution.

## 📦 Included Components

| Component             | Description                                               |
|-----------------------|-----------------------------------------------------------|
| [`LS032B7DD02`](./components/ls032b7dd02/README.md)         | Driver for Sharp Memory LCD LS032B7DD02 (336x536 SPI)     |
| *(more coming...)*    | New entries will appear here as I add them                |

## 📁 Directory Structure

Each component lives in its own folder inside the `components/` directory:

```
components/
├── ls032b7dd02/
│   └── ...              # LCD driver code and documentation
├── other_component/
│   └── ...
```

## 🚀 How to Use

You can use these components in your ESPHome projects by referencing this repository in your `external_components` block.

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/Sl-Alex/esphome-components
    components: [ls032b7dd02]
```

Then, follow each component's documentation for usage and configuration. Example YAMLs and instructions are provided in the individual component folders.

## 📜 License

This repository follows [ESPHome License](https://github.com/esphome/esphome/blob/dev/LICENSE):
> The ESPHome License is made up of two base licenses: MIT and the GNU GENERAL PUBLIC LICENSE. The C++/runtime codebase of the ESPHome project (file extensions .c, .cpp, .h, .hpp, .tcc, .ino) are published under the GPLv3 license. The python codebase and all other parts of this codebase are published under the MIT license.

## 🙌 Contributions

Suggestions, bug reports, and pull requests are welcome! Feel free to fork and adapt these components to your own needs.
