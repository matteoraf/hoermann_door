#include "uapbridge_pic16_binarySensor.h"

namespace esphome {
namespace uapbridge_pic16 {

static const char *const TAG = "uapbridge_pic16.binary_sensor";

void UAPBridge_pic16RelaySensor::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
    this->publish_state(this->parent_->get_relay_enabled());
}

void UAPBridge_pic16RelaySensor::on_event_triggered() {
    if (this->parent_->get_relay_enabled() != this->state) {
        this->publish_state(this->parent_->get_relay_enabled());
    }
}

void UAPBridge_pic16RelaySensor::dump_config() {
    ESP_LOGCONFIG(TAG, "UAPBridge_pic16RelaySensor");
}

void UAPBridge_pic16IsConnected::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
    this->publish_state(this->parent_->get_data_valid());
}

void UAPBridge_pic16IsConnected::on_event_triggered() {
    if (this->parent_->get_data_valid() != this->state) {
        this->publish_state(this->parent_->get_data_valid());
    }
}

void UAPBridge_pic16IsConnected::dump_config() {
    ESP_LOGCONFIG(TAG, "UAPBridge_pic16IsConnected");
}

void UAPBridge_pic16ErrorSensor::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
    this->publish_state(this->parent_->get_error_state());
}

void UAPBridge_pic16ErrorSensor::on_event_triggered() {
    if (this->parent_->get_error_state() != this->state) {
        this->publish_state(this->parent_->get_error_state());
    }
}

void UAPBridge_pic16ErrorSensor::dump_config() {
    ESP_LOGCONFIG(TAG, "UAPBridge_pic16ErrorSensor");
}

void UAPBridge_pic16PrewarnSensor::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
    this->publish_state(this->parent_->get_prewarn_state());
}

void UAPBridge_pic16PrewarnSensor::on_event_triggered() {
    if (this->parent_->get_prewarn_state() != this->state) {
        this->publish_state(this->parent_->get_prewarn_state());
    }
}

void UAPBridge_pic16PrewarnSensor::dump_config() {
    ESP_LOGCONFIG(TAG, "UAPBridge_pic16PrewarnSensor");
}

}  // namespace uapbridge_pic16
}  // namespace esphome
