#! /bin/bash
# Author: chenkaiyao <chenkaiyao@molmc.com>

set -v

# test Analog
intoyuniot run -d ./Analog/AnalogInOutSerial/ 2>&1 1>/dev/null
intoyuniot run -d ./Analog/AnalogInput/ 2>&1 1>/dev/null
intoyuniot run -d ./Analog/AnalogWriteDAC/ 2>&1 1>/dev/null
intoyuniot run -d ./Analog/AnalogWritePWM/ 2>&1 1>/dev/null
intoyuniot run -d ./Analog/Calibration/ 2>&1 1>/dev/null
intoyuniot run -d ./Analog/Fading/ 2>&1 1>/dev/null
intoyuniot run -d ./Analog/Smoothing/ 2>&1 1>/dev/null

# test Basics
intoyuniot run -d ./Basics/AnalogReadSerial 2>&1 1>/dev/null
intoyuniot run -d ./Basics/Blank 2>&1 1>/dev/null
intoyuniot run -d ./Basics/Blink 2>&1 >/dev/null
intoyuniot run -d ./Basics/DigitalReadSerial 2>&1 1>/dev/null
intoyuniot run -d ./Basics/Fade 2>&1 1>/dev/null
intoyuniot run -d ./Basics/ReadAnalogVoltage 2>&1 1>/dev/null

# test Digital
intoyuniot run -d ./Digital/BlinkWithoutDelay/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/Button/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/Debounce/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/DigitalInputPullup/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/Pulse/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/StateChangeDetection/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/toneKeyboard/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/toneMelody/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/toneMultiple/ 2>&1 1>/dev/null
intoyuniot run -d ./Digital/tonePitchFollower/ 2>&1 1>/dev/null

# test EEPROM
intoyuniot run -d ./EEPROM/eeprom_clear/ 2>&1 1>/dev/null
intoyuniot run -d ./EEPROM/eeprom_crc/ 2>&1 1>/dev/null
intoyuniot run -d ./EEPROM/eeprom_get/ 2>&1 1>/dev/null
intoyuniot run -d ./EEPROM/eeprom_iteration/ 2>&1 1>/dev/null
intoyuniot run -d ./EEPROM/eeprom_put/ 2>&1 1>/dev/null
intoyuniot run -d ./EEPROM/eeprom_read/ 2>&1 1>/dev/null
intoyuniot run -d ./EEPROM/eeprom_update/ 2>&1 1>/dev/null
intoyuniot run -d ./EEPROM/eeprom_write/ 2>&1 1>/dev/null

# test HTTP
intoyuniot run -d ./HTTP/Authorization/ 2>&1 1>/dev/null
intoyuniot run -d ./HTTP/BasicHttpClient/ 2>&1 1>/dev/null
intoyuniot run -d ./HTTP/BasicHttpPost/ 2>&1 1>/dev/null
intoyuniot run -d ./HTTP/ReuseConnection/ 2>&1 1>/dev/null
intoyuniot run -d ./HTTP/StreamHttpClient/ 2>&1 1>/dev/null

# test IntoRobot
intoyuniot run -d ./IntoRobot/airMonitor/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/alcoholDetector/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/barometer/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/bodyThermometer/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/cardiotachometer/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/cloudLight/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/diastimeter/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/figLight/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/fireAlarm/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/fishTank/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/flowerPot/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/formaldehyde2/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/formaldehydeDetector/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/GP2Y1051/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/humanInfraredSensor/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/humidity/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/humiture/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/incubator/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/incubator_lcd12864/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/lightControlLamp/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/lightIntensityMeter/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/neopixel/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/neutronBarometer/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/neutronLight/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/neutronSensors/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/neutronTemperature/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/nutLight/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/nutLightCtrlLamp/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/nutTemperatureCtrlFan/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/overflowWatermeter/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/passengerCounter/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/petFeed/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/PM2.5/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/rainDetector/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/robotArm/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/selfBalancedCar/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/servoControl/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/smartFan/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/smartLight/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/smartNest/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/smartWastebin/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/smokeAlarm/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/smokeDetector/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/soilMoistureDetector/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/switchControl/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/temperature/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/temperatureContrlFan/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/touchDetetor/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/UVIntensityMeter/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/vibrationAlarm/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/voiceContrlLamp/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/watering/ 2>&1 1>/dev/null
intoyuniot run -d ./IntoRobot/waterThermometer/ 2>&1 1>/dev/null

# test LoRa
intoyuniot run -d ./LoRa/p2p_rx_block/ 2>&1 1>/dev/null
intoyuniot run -d ./LoRa/p2p_rx_event/ 2>&1 1>/dev/null
intoyuniot run -d ./LoRa/p2p_tx_block/ 2>&1 1>/dev/null
intoyuniot run -d ./LoRa/p2p_tx_event/ 2>&1 1>/dev/null

# test LoRaWan
intoyuniot run -d ./LoRaWan/LoRaWan_classA_block/ 2>&1 1>/dev/null
intoyuniot run -d ./LoRaWan/LoRaWan_classA_event/ 2>&1 1>/dev/null
intoyuniot run -d ./LoRaWan/LoRaWan_classC_block/ 2>&1 1>/dev/null
intoyuniot run -d ./LoRaWan/LoRaWan_classC_event/ 2>&1 1>/dev/null

# test MQTT
intoyuniot run -d ./MQTT/mqtt_auth/ 2>&1 1>/dev/null
intoyuniot run -d ./MQTT/mqtt_basic/ 2>&1 1>/dev/null
intoyuniot run -d ./MQTT/mqtt_publish_in_callback/ 2>&1 1>/dev/null
intoyuniot run -d ./MQTT/mqtt_reconnect_nonblocking/ 2>&1 1>/dev/null

# test Projects
intoyuniot run -d ./Projects/envMonitor_LoRaWan/ 2>&1 1>/dev/null
intoyuniot run -d ./Projects/garden_LoRaWan/ 2>&1 1>/dev/null
intoyuniot run -d ./Projects/humiture/ 2>&1 1>/dev/null
intoyuniot run -d ./Projects/lightControlLamp/ 2>&1 1>/dev/null
intoyuniot run -d ./Projects/smartLight/ 2>&1 1>/dev/null
intoyuniot run -d ./Projects/tempControlFan/ 2>&1 1>/dev/null

# test Serial
intoyuniot run -d ./Serial/ASCIITable/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/Dimmer/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/Graph/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/Midi/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/MultiSerialMega/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/PhysicalPixel/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/ReadASCIIString/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/SerialCallResponse/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/SerialEvent/ 2>&1 1>/dev/null
intoyuniot run -d ./Serial/VirtualColorMixer/ 2>&1 1>/dev/null

# test Servo
intoyuniot run -d ./Servo/knob/ 2>&1 1>/dev/null
intoyuniot run -d ./Servo/sweep/ 2>&1 1>/dev/null

# test SPI
intoyuniot run -d ./SPI/BarometricPressureSensor/ 2>&1 1>/dev/null
intoyuniot run -d ./SPI/DigitalPotControl/ 2>&1 1>/dev/null

# test String
intoyuniot run -d ./String/CharacterAnalysis/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringAdditionOperator/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringAppendOperator/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringCaseChanges/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringCharacters/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringComparisonOperators/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringConstructors/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringIndexOf/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringLength/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringLengthTrim/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringReplace/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringStartsWithEndsWith/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringSubstring/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringToInt/ 2>&1 1>/dev/null
intoyuniot run -d ./String/StringToIntRGB/ 2>&1 1>/dev/null

# test Syntax
intoyuniot run -d ./Syntax/Arrays/ 2>&1 1>/dev/null
intoyuniot run -d ./Syntax/ForLoopIteration/ 2>&1 1>/dev/null
intoyuniot run -d ./Syntax/IfStatementConditional/ 2>&1 1>/dev/null
intoyuniot run -d ./Syntax/switchCase/ 2>&1 1>/dev/null
intoyuniot run -d ./Syntax/switchCase2/ 2>&1 1>/dev/null
intoyuniot run -d ./Syntax/WhileStatementConditional/ 2>&1 1>/dev/null

# test TCP
intoyuniot run -d ./TCP/TcpClient/ 2>&1 1>/dev/null
intoyuniot run -d ./TCP/TcpServer/ 2>&1 1>/dev/null

# test WiFi
intoyuniot run -d ./WiFi/ConnectNoEncryption/ 2>&1 1>/dev/null
intoyuniot run -d ./WiFi/ConnectWithWEP/ 2>&1 1>/dev/null
intoyuniot run -d ./WiFi/ConnectWithWPA/ 2>&1 1>/dev/null
intoyuniot run -d ./WiFi/ScanNetworks/ 2>&1 1>/dev/null

# test Wire
intoyuniot run -d ./Wire/digital_potentiometer/ 2>&1 1>/dev/null
intoyuniot run -d ./Wire/master_reader/ 2>&1 1>/dev/null
intoyuniot run -d ./Wire/master_writer/ 2>&1 1>/dev/null
intoyuniot run -d ./Wire/SFRRanger_reader/ 2>&1 1>/dev/null
intoyuniot run -d ./Wire/slave_receiver/ 2>&1 1>/dev/null
intoyuniot run -d ./Wire/slave_sender/ 2>&1 1>/dev/null

exit 0

