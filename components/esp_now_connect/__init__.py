import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import esp8266
from esphome.const import CONF_ID

CODEOWNERS = ["@atshome"]

esp_now_ns = cg.esphome_ns.namespace("esp_now_connect")
ESPNowComponent = esp_now_ns.class_("ESPNowComponent", cg.Component)

CONF_COMMANDS = "commands"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(ESPNowComponent),
        cv.Optional(CONF_COMMANDS, default={}): cv.All(
            cv.ensure_list(cv.Schema({cv.string: cv.lambda_}))
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    for command in config[CONF_COMMANDS]:
        cmd_str = list(command.keys())[0]
        cmd_lambda = command[cmd_str]

        lambda_func = await cg.process_lambda(cmd_lambda, [], return_type=cg.void)
        cg.add(var.on(cmd_str, lambda_func))
