testWireCheck:
	arduino-cli compile ./Tests/WireCheck/WireCheck.ino --fqbn esp32:esp32:nodemcu-32s --port $(PORT) --upload --verbose