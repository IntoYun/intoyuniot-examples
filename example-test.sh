#! /bin/bash
# Author: chenkaiyao <chenkaiyao@molmc.com>

if false;then
intoyuniot run -d ./Basics/AnalogReadSerial
intoyuniot run -d ./Basics/Blank
intoyuniot run -d ./Basics/Blink
intoyuniot run -d ./Basics/DigitalReadSerial
intoyuniot run -d ./Basics/Fade
intoyuniot run -d ./Basics/ReadAnalogVoltage
fi

if false;then
intoyuniot run -d ./Digital/BlinkWithoutDelay/
intoyuniot run -d ./Digital/Button/
intoyuniot run -d ./Digital/Debounce/
intoyuniot run -d ./Digital/DigitalInputPullup/
intoyuniot run -d ./Digital/StateChangeDetection/
intoyuniot run -d ./Digital/toneKeyboard/
intoyuniot run -d ./Digital/toneMelody/
intoyuniot run -d ./Digital/toneMultiple/
intoyuniot run -d ./Digital/tonePitchFollower/
fi

if false;then
intoyuniot run -d ./Analog/AnalogInOutSerial/
intoyuniot run -d ./Analog/AnalogInput/
intoyuniot run -d ./Analog/AnalogWrite/
intoyuniot run -d ./Analog/Calibration/
intoyuniot run -d ./Analog/Fading/
intoyuniot run -d ./Analog/Smoothing/
fi

if false;then
intoyuniot run -d ./SPI/BarometricPressureSensor/
intoyuniot run -d ./SPI/DigitalPotControl/
fi

if false;then
intoyuniot run -d ./Servo/knob/
intoyuniot run -d ./Servo/sweep/
fi

if false;then
intoyuniot run -d ./EEPROM/eeprom_read/
intoyuniot run -d ./EEPROM/eeprom_write/
fi

if false;then
intoyuniot run -d ./I2C/DigitalPotentiometer/
intoyuniot run -d ./I2C/MasterRead/
intoyuniot run -d ./I2C/MasterWrite/
intoyuniot run -d ./I2C/SlaveReceiver/
intoyuniot run -d ./I2C/SlaveSend/
intoyuniot run -d ./I2C/SRFxx_Read/
fi

if false;then
intoyuniot run -d ./Accel/ADXL3xx/
intoyuniot run -d ./Accel/Knock/
intoyuniot run -d ./Accel/Memsic2125/
fi

if false;then
intoyuniot run -d ./Serial/ASCIITable/
intoyuniot run -d ./Serial/Dimmer/
intoyuniot run -d ./Serial/Graph/
intoyuniot run -d ./Serial/Midi/
intoyuniot run -d ./Serial/MultiSerialMega/
intoyuniot run -d ./Serial/PhysicalPixel/
intoyuniot run -d ./Serial/ReadASCIIString/
intoyuniot run -d ./Serial/SerialCallResponse/
intoyuniot run -d ./Serial/SerialEvent/
intoyuniot run -d ./Serial/VirtualColorMixer/
fi

if false;then
intoyuniot run -d ./Network/TcpClient/
intoyuniot run -d ./Network/TcpServer/
fi

if false;then
intoyuniot run -d ./Syntax/Arrays/
intoyuniot run -d ./Syntax/ForLoopIteration/
intoyuniot run -d ./Syntax/IfStatementConditional/
intoyuniot run -d ./Syntax/WhileStatementConditional/
intoyuniot run -d ./Syntax/switchCase/
intoyuniot run -d ./Syntax/switchCase2/
fi

if false;then
intoyuniot run -d ./WiFi/ConnectNoEncryption/
intoyuniot run -d ./WiFi/ConnectWithWEP/
intoyuniot run -d ./WiFi/ConnectWithWPA/
intoyuniot run -d ./WiFi/ScanNetworks/
fi

if false;then
intoyuniot run -d ./IntoYun/humiture/
intoyuniot run -d ./IntoYun/lightControlLamp/
intoyuniot run -d ./IntoYun/smartLight/
intoyuniot run -d ./IntoYun/LoRaWan_classA_block/
intoyuniot run -d ./IntoYun/LoRaWan_classA_event/
intoyuniot run -d ./IntoYun/LoRaWan_classC_block/
intoyuniot run -d ./IntoYun/LoRaWan_classC_event/
intoyuniot run -d ./IntoYun/p2p_rx_block/
intoyuniot run -d ./IntoYun/p2p_rx_event/
intoyuniot run -d ./IntoYun/p2p_tx_block/
intoyuniot run -d ./IntoYun/p2p_tx_event/
intoyuniot run -d ./IntoYun/tempControlFan/
intoyuniot run -d ./IntoYun/template/
fi

if false;then
intoyuniot run -d ./String/CharacterAnalysis/
intoyuniot run -d ./String/StringAdditionOperator/
intoyuniot run -d ./String/StringAppendOperator/
intoyuniot run -d ./String/StringCaseChanges/
intoyuniot run -d ./String/StringCharacters/
intoyuniot run -d ./String/StringComparisonOperators/
intoyuniot run -d ./String/StringConstructors/
intoyuniot run -d ./String/StringIndexOf/
intoyuniot run -d ./String/StringLength/
intoyuniot run -d ./String/StringLengthTrim/
intoyuniot run -d ./String/StringReplace/
intoyuniot run -d ./String/StringStartsWithEndsWith/
intoyuniot run -d ./String/StringSubstring/
intoyuniot run -d ./String/StringToInt/
intoyuniot run -d ./String/StringToIntRGB/
fi

exit 0
