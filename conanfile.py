from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain
from pathlib import Path
import re
import yaml


class PerceptionCoreConan(ConanFile):
    name = "adas-perception-core"
    package_type = "application"

    settings = "os", "arch", "compiler", "build_type"

    # A real Conan option (not an env var) so it participates in
    # package_id automatically, same fix as modules/df and modules/vdy -
    # plan.md item 14 Bug #16: ADAS_PROJECT used to be read via plain
    # os.environ.get() inside requirements(), invisible to Conan's package
    # identity. Applied here for consistency even though this component
    # has no build()/package() yet (conan create currently produces an
    # empty package regardless of project, same pre-item-14 state
    # df/vdy used to be in) - nothing to collide over yet, but no reason
    # for this component to carry the same latent bug once it does.
    # "ANY" (not an enumerated list) so a new project needs no
    # conanfile.py change - conf/build.yml's own variants: dict stays the
    # single source of truth (an unknown project still fails naturally in
    # _build_conf() below with a KeyError).
    options = {
        "project": ["ANY"],
    }

    default_options = {
        "project": "base",
        "protobuf/*:shared": False,
        "protobuf/*:with_zlib": False,
    }

    def _build_conf(self):
        conf_path = Path(self.recipe_folder) / "conf" / "build.yml"
        conf = yaml.safe_load(conf_path.read_text(encoding="utf-8"))
        return conf["variants"][str(self.options.project)]

    def requirements(self):
        for ref in self._build_conf().get("requires", []):
            self.requires(ref)

    def build_requirements(self):
        for ref in self._build_conf().get("tool_requires", []):
            self.tool_requires(ref)

    def set_version(self):
        cmakelists = Path(self.recipe_folder) / "CMakeLists.txt"
        content = cmakelists.read_text(encoding="utf-8")
        match = re.search(r"project\(\s*adas-perception-core\s+VERSION\s+([0-9]+\.[0-9]+\.[0-9]+)", content, re.IGNORECASE)
        if not match:
            raise RuntimeError("Could not extract VERSION from CMakeLists.txt")
        self.version = match.group(1)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

        deps = CMakeDeps(self)
        deps.build_context_activated = ["protobuf"]
        deps.build_context_suffix = {"protobuf": "_BUILD"}
        deps.generate()
