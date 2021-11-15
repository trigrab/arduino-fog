
Import("env")
Import("projenv")

# this is no valid python file as it is interpreted by platformio's SCon configuration system

import os
try:
    import yaml
except ImportError:
    env.Execute("$PYTHONEXE -m pip install -r extra_script/requirements.txt")
    import yaml
from pre_extra_script import before_buildprog, before_upload

# fix espota
from config import get_config

_config = get_config()

for item in os.listdir(env.get("PROJECTSRC_DIR")):
    full_path = os.path.join("${BUILD_DIR}", "src", item) + ".o"
    env.AddPreAction(full_path, before_buildprog)

env.AddPreAction("upload", before_upload)
