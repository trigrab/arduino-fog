from config import get_config, tmp_suffix, logger


def before_upload(source, target, env):
    """
    add auth flag to upload_flags
    :param source:
    :param target:
    :param env: Scons Construction Environment
    :return: None
    """
    config = get_config()
    if env["UPLOAD_PROTOCOL"] == "espota":
        if config["OTA"]["pass"]:
            env["UPLOAD_FLAGS"] = ["--auth=%s" % config["OTA"]["pass"]]


def before_buildprog(source, target, env):
    config = get_config()
    build_flags = ""
    for section_name, section in config.items():
        for key, item in section.items():
            macro_name = f"{section_name.upper()}_{key.upper()}"
            macro_value = f"\\\"{section[key]}\\\""
            env.Append(CPPDEFINES=[
              (macro_name, macro_value)
            ])
