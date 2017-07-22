#! /bin/bash
# Author: chenkaiyao <chenkaiyao@molmc.com>

if false;then
intoyuniot run -d ./01.Basics/AnalogReadSerial
intoyuniot run -d ./01.Basics/Blank
intoyuniot run -d ./01.Basics/Blink
intoyuniot run -d ./01.Basics/DigitalReadSerial
intoyuniot run -d ./01.Basics/Fade
intoyuniot run -d ./01.Basics/ReadAnalogVoltage
fi

if false;then
intoyuniot run -d ./02.Digital/BlinkWithoutDelay/
intoyuniot run -d ./02.Digital/Button/
intoyuniot run -d ./02.Digital/Debounce/
intoyuniot run -d ./02.Digital/DigitalInputPullup/
intoyuniot run -d ./02.Digital/StateChangeDetection/
intoyuniot run -d ./02.Digital/toneKeyboard/
intoyuniot run -d ./02.Digital/toneMelody/
intoyuniot run -d ./02.Digital/toneMultiple/
intoyuniot run -d ./02.Digital/tonePitchFollower/
fi

if false;then
intoyuniot run -d ./03.Analog/AnalogInOutSerial/
intoyuniot run -d ./03.Analog/AnalogInput/
intoyuniot run -d ./03.Analog/AnalogWrite/
intoyuniot run -d ./03.Analog/Calibration/
intoyuniot run -d ./03.Analog/Fading/
intoyuniot run -d ./03.Analog/Smoothing/
fi

if false;then
intoyuniot run -d ./04.SPI/BarometricPressureSensor/
intoyuniot run -d ./04.SPI/DigitalPotControl/
fi

if false;then
intoyuniot run -d ./05.Servo/knob/
intoyuniot run -d ./05.Servo/sweep/
fi

if false;then
intoyuniot run -d ./06.EEPROM/eeprom_read/
intoyuniot run -d ./06.EEPROM/eeprom_write/
fi

if false;then
intoyuniot run -d ./07.I2C/DigitalPotentiometer/
intoyuniot run -d ./07.I2C/MasterRead/
intoyuniot run -d ./07.I2C/MasterWrite/
intoyuniot run -d ./07.I2C/SlaveReceiver/
intoyuniot run -d ./07.I2C/SlaveSend/
intoyuniot run -d ./07.I2C/SRFxx_Read/
fi

if false;then
intoyuniot run -d ./08.Accel/ADXL3xx/
intoyuniot run -d ./08.Accel/Knock/
intoyuniot run -d ./08.Accel/Memsic2125/
fi

if false;then
intoyuniot run -d ./09.Serial/ASCIITable/
intoyuniot run -d ./09.Serial/Dimmer/
intoyuniot run -d ./09.Serial/Graph/
intoyuniot run -d ./09.Serial/Midi/
intoyuniot run -d ./09.Serial/MultiSerialMega/
intoyuniot run -d ./09.Serial/PhysicalPixel/
intoyuniot run -d ./09.Serial/ReadASCIIString/
intoyuniot run -d ./09.Serial/SerialCallResponse/
intoyuniot run -d ./09.Serial/SerialEvent/
intoyuniot run -d ./09.Serial/VirtualColorMixer/
fi

if false;then
intoyuniot run -d ./10.Network/TcpClient/
intoyuniot run -d ./10.Network/TcpServer/
fi

if false;then
intoyuniot run -d ./11.Syntax/Arrays/
intoyuniot run -d ./11.Syntax/ForLoopIteration/
intoyuniot run -d ./11.Syntax/IfStatementConditional/
intoyuniot run -d ./11.Syntax/WhileStatementConditional/
intoyuniot run -d ./11.Syntax/switchCase/
intoyuniot run -d ./11.Syntax/switchCase2/
fi

if false;then
intoyuniot run -d ./12.WiFi/ConnectNoEncryption/
intoyuniot run -d ./12.WiFi/ConnectWithWEP/
intoyuniot run -d ./12.WiFi/ConnectWithWPA/
intoyuniot run -d ./12.WiFi/ScanNetworks/
fi

if false;then
intoyuniot run -d ./13.IntoYun/humiture/
intoyuniot run -d ./13.IntoYun/lightControlLamp/
intoyuniot run -d ./13.IntoYun/smartLight/
intoyuniot run -d ./13.IntoYun/sx1278_RX/
intoyuniot run -d ./13.IntoYun/sx1278_TX/
intoyuniot run -d ./13.IntoYun/tempControlFan/
intoyuniot run -d ./13.IntoYun/template/
fi

if false;then
intoyuniot run -d ./14.String/CharacterAnalysis/
intoyuniot run -d ./14.String/StringAdditionOperator/
intoyuniot run -d ./14.String/StringAppendOperator/
intoyuniot run -d ./14.String/StringCaseChanges/
intoyuniot run -d ./14.String/StringCharacters/
intoyuniot run -d ./14.String/StringComparisonOperators/
intoyuniot run -d ./14.String/StringConstructors/
intoyuniot run -d ./14.String/StringIndexOf/
intoyuniot run -d ./14.String/StringLength/
intoyuniot run -d ./14.String/StringLengthTrim/
intoyuniot run -d ./14.String/StringReplace/
intoyuniot run -d ./14.String/StringStartsWithEndsWith/
intoyuniot run -d ./14.String/StringSubstring/
intoyuniot run -d ./14.String/StringToInt/
intoyuniot run -d ./14.String/StringToIntRGB/
fi




exit 0
