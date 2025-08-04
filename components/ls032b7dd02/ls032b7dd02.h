#pragma once

#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"
#include "esphome/components/spi/spi.h"

namespace esphome
{
  namespace ls032b7dd02
  {

    class LS032B7DD02;

    using ls032b7dd02_writer_t = std::function<void(LS032B7DD02 &)>;

    class LS032B7DD02 : public display::DisplayBuffer,
                        public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                              spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_4MHZ>
    {
    public:
      void set_height(uint16_t height) { this->height_ = height; }
      void set_width(uint16_t width) { this->width_ = width; }

      void setup() override;
      void dump_config() override;
      float get_setup_priority() const override;
      void update() override;
      void fill(Color color) override;
      void write_display_data();
      display::DisplayType get_display_type() override { return display::DisplayType::DISPLAY_TYPE_BINARY; }
     
    private:
      void lcd_clear(void);
      void lcd_toggle_vcom(void);
      static uint16_t reverse_line_number(uint16_t value);

      uint8_t vcom = 0x00;

    protected:
      int get_height_internal() override { return this->height_; }
      int get_width_internal() override { return this->width_; }
      size_t get_buffer_length_();
      void draw_absolute_pixel_internal(int x, int y, Color color) override;

      int16_t width_ = 336, height_ = 536;

    };

  } // namespace ls032b7dd02
} // namespace esphome


