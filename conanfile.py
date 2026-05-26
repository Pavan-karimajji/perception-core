from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain


class PerceptionCoreConan(ConanFile):
    name = "adas-perception-core-deps"
    version = "0.1.0"
    package_type = "application"

    settings = "os", "arch", "compiler", "build_type"
    requires = ("protobuf/3.21.12",)
    tool_requires = ("protobuf/3.21.12",)

    default_options = {
        "protobuf/*:shared": False,
        "protobuf/*:with_zlib": False,
    }

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

        deps = CMakeDeps(self)
        deps.build_context_activated = ["protobuf"]
        deps.build_context_suffix = {"protobuf": "_BUILD"}
        deps.generate()
