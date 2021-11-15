import os
import yaml
import logging

logger = logging.getLogger("")

config_file = "config.yml"

extra_config = {
    "wifi": {
        "ssid": "",
        "pass": ""
        },
    "OTA": {
        "use": False,
        "hostname": "fogger",
        "pass": ""
        }
}
tmp_suffix = ".tmp"


def get_config():
    """
    get config from yaml file
    :return: dict with config variables
    """
    if os.path.exists(config_file):
        with open(config_file, "r") as file:
            file_contents = "\n".join(file.readlines())
        config: dict = yaml.load(file_contents, Loader=yaml.Loader)
        for key, section in extra_config.items():
            if key in config:
                section.update(config[key])
        return extra_config
    else:
        logger.error("Config file does not exist. See README.md")
        exit(2)
