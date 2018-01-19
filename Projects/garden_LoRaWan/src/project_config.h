/**
 ******************************************************************************
 Copyright (c) IntoRobot Team.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

#ifndef PROJECT_CONFIG_H_
#define PROJECT_CONFIG_H_

//产品ID
//产品ID是一个16个字节的字符串，为一个产品的标识符。设备通过上送产品ID可以把设备归属到该类产品中。
//产品ID属于绝密信息，请防止泄露。
#define PRODUCT_ID_DEF                            BysPnpkCgHPhM1ec

//产品密钥
//产品密钥是一个32个字节的字符串，通过产品密钥可以完成设备的自动注册。产品密钥在任何时候不传输。
//产品密钥属于绝密信息，请防止泄露。
#define PRODUCT_SECRET_DEF                        745f24b07bce12ad6eb5aa6463fd2556

//硬件版本号
//硬件版本号，为设备的硬件版本号。该版本号将上送至服务器。
#define HARDWARE_VERSION_DEF                      v1.0.0

//软件版本号
//软件版本号，为设备当前软件的版本号。该版本号将上送至服务器。
#define SOFTWARE_VERSION_DEF                      1.1.0

//是否带确认发送
//true:  带确认发送，数据一定到达平台。该种方式发送不成功，将重发。
//false: 不带确认发送，数据不一定到达平台。默认采取该种方式。
#define IS_SEND_CONFIRMED_DEF                     false

#endif
