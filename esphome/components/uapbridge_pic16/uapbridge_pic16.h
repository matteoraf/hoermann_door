#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

#define SYNC_BYTE 0x55

namespace esphome {
namespace uapbridge_pic16 {

class UAPBridge_pic16 : public uart::UARTDevice, public Component {
  public:
    // Enumeration for actions
    enum hoermann_action_t {
      hoermann_action_stop = 0,
      hoermann_action_open,
      hoermann_action_close,
      hoermann_action_venting,
      hoermann_action_toggle_light,
      hoermann_action_none
    };

    // Enumeration for states
    enum hoermann_state_t {
      hoermann_state_stopped = 0,
      hoermann_state_open,
      hoermann_state_closed,
      hoermann_state_venting,
      hoermann_state_opening,
      hoermann_state_closing,
      hoermann_state_error,
      hoermann_state_unkown
    };

    void setup() override;
    void loop() override;
    void add_on_state_callback(std::function<void()> &&callback);

    void action_open();
    void action_close();
    void action_stop();
    void action_venting();
    void action_toggle_light();

    hoermann_state_t get_state();
    std::string get_state_string();
    void set_venting(bool state);
    bool get_venting_enabled();
    void set_light(bool state);
    bool get_light_enabled();
    bool get_relay_enabled() const { return this->relay_enabled; }
    void set_relay_enabled(bool value) { this->relay_enabled = value; }
    bool get_error_state() const { return this->error_state; }
    void set_error_state(bool value) { this->error_state = value; }
    bool get_prewarn_state() const { return this->prewarn_state; }
    void set_prewarn_state(bool value) { this->prewarn_state = value; }
    bool get_pic16_com() const { return this->pic16_com; }
    void set_pic16_com(bool value) { this->pic16_com = value; }
    bool get_valid_broadcast() const { return this->valid_broadcast; }
    void set_valid_broadcast(bool value) { this->valid_broadcast = value; }
    bool has_data_changed();
    void clear_data_changed_flag();

  protected:
    CallbackManager<void()> state_callback_;
    hoermann_state_t actual_state = hoermann_state_unkown;
    hoermann_state_t last_door_state = hoermann_state_unkown;
    hoermann_action_t actual_action = hoermann_action_none;
    std::string actual_state_string = "unknown";

    bool venting_enabled = false;
    bool light_enabled = false;
    bool relay_enabled = false;
    bool error_state = false;
    bool prewarn_state = false;
    bool pic16_com = false;
    bool valid_broadcast = false;
    bool data_has_changed = false;

    uint8_t last_rx_buffer[16] = {0};
    uint8_t rx_buffer[16];
    uint8_t output_buffer[16];
    uint32_t last_parse_time = millis();

    // Internal methods
    bool read_rs232();
    void parse_input();
    void send_command();
    uint8_t calc_checksum(uint8_t *p_data, uint8_t length);
    void handle_state_change(hoermann_state_t new_state);
    void update_boolean_state(bool &current_state, bool new_state);
};

}  // namespace uapbridge_pic16
}  // namespace esphome
