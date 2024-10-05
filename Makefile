rcs:
	arduino-cli compile ./RCS/RCS.ino --fqbn esp32:esp32:nodemcu-32s --port $(PORT) --upload --verbose

testWireCheck:
	arduino-cli compile ./Tests/WireCheck/WireCheck.ino --fqbn esp32:esp32:nodemcu-32s --port $(PORT) --upload --verbose

testSbusTx:
	arduino-cli compile ./Tests/SBUSLib/SBUSLib.ino --fqbn esp32:esp32:nodemcu-32s --port $(PORT) --upload --verbose

testSX127X:
	arduino-cli compile ./Tests/Radio/Radio.ino --fqbn esp32:esp32:nodemcu-32s --port $(PORT) --upload --verbose
