from esphome.components import binary_sensor
import esphome.config_validation as cv
import esphome.codegen as cg
from .. import uapbridge_pic16_ns, CONF_UAPBRIDGE_PIC16_ID, UAPBridge_pic16
from esphome.const import (
    DEVICE_CLASS_CONNECTIVITY,
    DEVICE_CLASS_PROBLEM,
    DEVICE_CLASS_SAFETY,
)

DEPENDENCIES = ["uapbridge_pic16"]

UAPBridge_pic16IsConnected = uapbridge_pic16_ns.class_("UAPBridge_pic16IsConnected", binary_sensor.BinarySensor, cg.Component)
UAPBridge_pic16RelaySensor = uapbridge_pic16_ns.class_("UAPBridge_pic16RelaySensor", binary_sensor.BinarySensor, cg.Component)
UAPBridge_pic16ErrorSensor = uapbridge_pic16_ns.class_("UAPBridge_pic16ErrorSensor", binary_sensor.BinarySensor, cg.Component)
UAPBridge_pic16PrewarnSensor = uapbridge_pic16_ns.class_("UAPBridge_pic16PrewarnSensor", binary_sensor.BinarySensor, cg.Component)

CONF_IS_CONNECTED = "is_connected"
CONF_RELAY_STATE = "relay_state"
CONF_ERROR_STATE = "error_state"
CONF_PREWARN_STATE = "prewarn_state"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_UAPBRIDGE_PIC16_ID): cv.use_id(UAPBridge_pic16),
        cv.Optional(CONF_IS_CONNECTED): binary_sensor.binary_sensor_schema(
            UAPBridge_pic16IsConnected
        ).extend({
            cv.Optional("device_class", default=DEVICE_CLASS_CONNECTIVITY): cv.string,
        }),
        cv.Optional(CONF_RELAY_STATE): binary_sensor.binary_sensor_schema(
            UAPBridge_pic16RelaySensor
        ),
        cv.Optional(CONF_ERROR_STATE): binary_sensor.binary_sensor_schema(
            UAPBridge_pic16ErrorSensor
        ).extend({
            cv.Optional("device_class", default=DEVICE_CLASS_PROBLEM): cv.string,
        }),
        cv.Optional(CONF_PREWARN_STATE): binary_sensor.binary_sensor_schema(
            UAPBridge_pic16PrewarnSensor
        ).extend({
            cv.Optional("device_class", default=DEVICE_CLASS_SAFETY): cv.string,
        }),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_UAPBRIDGE_PIC16_ID])
    
    if conf := config.get(CONF_IS_CONNECTED):
        con_sens = await binary_sensor.new_binary_sensor(conf)
        await cg.register_component(con_sens, conf)
        cg.add(con_sens.set_uapbridge_pic16_parent(parent))
    
    if conf := config.get(CONF_RELAY_STATE):
        relay_sens = await binary_sensor.new_binary_sensor(conf)
        await cg.register_component(relay_sens, conf)
        cg.add(relay_sens.set_uapbridge_pic16_parent(parent))
    
    if conf := config.get(CONF_ERROR_STATE):
        error_sens = await binary_sensor.new_binary_sensor(conf)
        await cg.register_component(error_sens, conf)
        cg.add(error_sens.set_uapbridge_pic16_parent(parent))
    
    if conf := config.get(CONF_PREWARN_STATE):
        prewarn_sens = await binary_sensor.new_binary_sensor(conf)
        await cg.register_component(prewarn_sens, conf)
        cg.add(prewarn_sens.set_uapbridge_pic16_parent(parent))
