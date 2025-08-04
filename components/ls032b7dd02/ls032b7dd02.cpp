#include "ls032b7dd02.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/components/display/display_buffer.h"

namespace esphome
{
  namespace ls032b7dd02
  {

    static const char *const TAG = "ls032b7dd02";

    void LS032B7DD02::setup()
    {
      ESP_LOGCONFIG(TAG, "Setting up LS032B7DD02...");

      /* Initialize display buffer */
      this->init_internal_(this->get_buffer_length_());

      this->dump_config();

      /* Initialize pins */
      this->spi_setup();
      this->cs_->setup();
      this->cs_->digital_write(false);
      lcd_clear();
      this->set_interval(1000, [this]() { this->lcd_toggle_vcom(); });
    }

    /** Clear display memory */
    void LS032B7DD02::lcd_clear(void) {
      this->cs_->digital_write(true);
      this->write_array((uint8_t *)"\x20\x00", 2);
      this->cs_->digital_write(false);
    }

    /** Toggle VCOM bit */
    void LS032B7DD02::lcd_toggle_vcom(void) {
	  vcom ^= 0x40;
	  this->cs_->digital_write(true);
	  this->write_byte(vcom);
	  this->write_byte('\0');
	  this->cs_->digital_write(false);
    }
    
    /** Reverse bit order for line number */
    uint16_t LS032B7DD02::reverse_line_number(uint16_t value) {
      uint16_t ret = 0;
      for(int i = 0; i < 10; i++) {
        ret <<= 1;
        ret |= value & 0x0001;
        value >>= 1;
      }
      return ret;
    }

    /** Flush display buffer */
    void HOT LS032B7DD02::write_display_data()
    {
      uint8_t *ptr = this->buffer_;
      uint32_t line = 1;

      this->cs_->digital_write(true);

      /* Write line */
      uint16_t cmd = 0x8000;

      do {
        uint16_t tmp = reverse_line_number(line);
        tmp |= cmd;
        /* Send line number */
        uint8_t tmp_byte = tmp >> 8;
        this->write_array(&tmp_byte, 1);
        tmp_byte = tmp & 0xFF;
        this->write_array(&tmp_byte, 1);
        /* Send line data */
        this->write_array(ptr, this->width_ >> 3);
        ptr += this->width_ >> 3;
      } while (line++ < this->height_);

      /* Last 16-bit trailer */
      this->write_array((uint8_t *)"\x00\x00", 2);

      this->cs_->digital_write(false);
    }

    void LS032B7DD02::fill(Color color) {
      memset(this->buffer_, color.is_on() ? 0x00 : 0xFF, this->get_buffer_length_());
    }

    void LS032B7DD02::dump_config()
    {
      LOG_DISPLAY("", "LS032B7DD02", this);
      ESP_LOGCONFIG(TAG, "  Height: %d", this->height_);
      ESP_LOGCONFIG(TAG, "  Width: %d", this->width_);
      LOG_PIN("  CS Pin: ", this->cs_);
      LOG_UPDATE_INTERVAL(this);
    }

    float LS032B7DD02::get_setup_priority() const { return setup_priority::PROCESSOR; }

    void LS032B7DD02::update()
    {
      this->do_update_();
      this->write_display_data();
    }

    void HOT LS032B7DD02::draw_absolute_pixel_internal(int x, int y, Color color)
    {
      /* Calculate byte offset */
      uint32_t offset = ((y * this->width_) + x) >> 3;
      // Calculate bit offset
      uint8_t bpos = x & 0x07;
  
      /* Update pixel in the buffer */
      if (color.is_on()) {
        this->buffer_[offset] &=~(0x80 >> bpos);
      } else {
        this->buffer_[offset] |= (0x80 >> bpos);
      }
    }

    size_t LS032B7DD02::get_buffer_length_() {
      return size_t(this->get_width_internal()) * size_t(this->get_height_internal()) / 8u;
    }

  } // namespace ls032b7dd02
} // namespace esphome
