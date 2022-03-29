# Package

version       = "0.1.0"
author        = "Jeremy DeJournett"
description   = "REST API frontend for an Arduino based remote"
license       = "MIT"
srcDir        = "src"
bin           = @["arduino_remote"]


# Dependencies

requires "nim >= 1.4.8"
requires "serial#a25637daec680b1c91f70b3d456b3f4b0251735c"
