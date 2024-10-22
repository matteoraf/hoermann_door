import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

# Create UAPBridge_pic16 namespace
uapbridge_pic16_ns = cg.esphome_ns.namespace("uapbridge_pic16")
UAPBridge_pic16 = uapbridge_pic16_ns.class_("UAPBridge_pic16", cg.Component, uart.UARTDevice)

CONF_UAPBRIDGE_PIC16_ID = "uapbridge_pic16_id"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(UAPBridge_pic16),
    }
).extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "uapbridge_pic16_uart",
    require_tx=True,
    require_rx=True,
    baud_rate=19200
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
