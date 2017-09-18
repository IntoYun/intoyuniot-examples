/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  03-30-16
************************************************************************
功能描述：
IntoYun 产品开发模板文件。平台根据该格式自动生成代码

*/

/*
*  产品名称：
*  产品描述：
*  说    明： 该代码为平台自动根据产品内容生成的代码模板框架，
*             您可以在此框架下开发。此框架包括数据点的定义和读写。
*  模板版本： v1.4
*/

PRODUCT_ID(WP6KsBxqRPM9x1ab)                     //产品标识
PRODUCT_SECRET(e964ba2d7ebdfbf368ba3168aafd55cb) //产品密钥
PRODUCT_SOFTWARE_VERSION(1.2.0)                  //产品软件版本号
PRODUCT_HARDWARE_VERSION(1.0.0)                  //产品硬件版本号

//定义数据点
//格式：DPID_数据类型_数据点英文名. 如果英文名相同的，则在后面添加_1 _2 _3形式。
//说明：布尔型: BOOL. 数值型: NUMBER. 枚举型: ENUM. 字符串型: STRING. 透传型: BINARY
#define DPID_BOOL_SWITCH                      1  //布尔型     开关(可上送可下发)
#define DPID_NUMBER_TEMPATURE                 2  //数值型     温度(只上送)
#define DPID_NUMBER_HUMIDITY                  2  //数值型     湿度(只上送)
#define DPID_ENUM_COLOR                       3  //枚举型     颜色模式(可上送可下发)
#define DPID_STRING_DISPLAY                   4  //字符串型   显示字符串(可上送可下发)
#define DPID_BINARY_LOCATION                  5  //透传型     位置(可上送可下发)


//格式：数据类型+数据点英文名. 如果英文名相同的，则在后面添加_1 _2 _3形式。
//布尔型为bool
//枚举型为int
//整型为int
//浮点型为double
//字符型为String
//透传型为uint8_t*型
//透传型长度为uint16_t型

//定义变量
bool    dpBoolSwitch;          //开关
double  dpDoubleTemperature;   //温度
int     dpIntHumidity;         //湿度
int     dpEnumColor;           //颜色模式
String  dpStringDisplay;       //显示字符串
uint8_t *dpBianryLocation;     //位置
uint16_t dpBianryLocationLen;  //位置长度

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    if((event == event_cloud_data) && (param == ep_cloud_data_datapoint)) {
        //用户控制处理
        //开关
        if(RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_BOOL_SWITCH, dpBoolSwitch)) {
            //用户代码
        }

        // 颜色模式
        if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_ENUM_COLOR, dpEnumColor)) {
            //用户代码
        }

        // 显示字符串
        if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_STRING_DISPLAY, dpStringDisplay)) {
            //用户代码
        }

        // 位置信息
        if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_BINARY_LOCATION, dpBianryLocation, dpBianryLocationLen)) {
            //用户代码
        }
    }
}

void userHandle(void)
{
    //连接网络
    if(Cloud.connect() < 0) {
        if(Cloud.connect(JOIN_OTAA, 400) == 0) {
            LoRaWan.setMacClassType(CLASS_C);    //入网成功后设置为C类
        }
    }

    //更新数据点数据（数据点具备：上送属性）
    IntoRobot.writeDatapoint(DPID_BOOL_SWITCH, dpBoolSwitch);
    IntoRobot.writeDatapoint(DPID_NUMBER_TEMPATURE, dpDoubleTemperature);
    IntoRobot.writeDatapoint(DPID_NUMBER_HUMIDITY, dpIntHumidity);
    IntoRobot.writeDatapoint(DPID_ENUM_COLOR, dpEnumColor);
    IntoRobot.writeDatapoint(DPID_STRING_DISPLAY, "hello! intoyun!");
    IntoRobot.writeDatapoint(DPID_BINARY_LOCATION, "\x12\x34\x56\x78", 4);
    //发送数据点数据，建议不频繁上送数据
    Cloud.sendDatapointAll(false, 0);
    delay(60000);
}

void setup()
{
    //根据网关参数具体设置
    LoRaWan.setDataRate(DR_3);
    LoRaWan.setChannelDRRange(2, DR_3, DR_3);
    LoRaWan.setRX2Params(DR_3, 434665000);
    LoRaWan.setChannelStatus(0, false);       //关闭通道0
    LoRaWan.setChannelStatus(1, false);       //关闭通道1

    //定义事件回调函数
    System.on(event_cloud_data, system_event_callback);
    //定义产品数据点
    IntoRobot.defineDatapointBool(DPID_BOOL_SWITCH, DP_PERMISSION_UP_DOWN, false);                            //开关
    IntoRobot.defineDatapointNumber(DPID_NUMBER_TEMPATURE, DP_PERMISSION_UP_ONLY, 0, 100, 1, 0);              //温度
    IntoRobot.defineDatapointNumber(DPID_NUMBER_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0);               //湿度
    IntoRobot.defineDatapointEnum(DPID_ENUM_COLOR, DP_PERMISSION_UP_DOWN, 1);                                 //颜色模式
    IntoRobot.defineDatapointString(DPID_STRING_DISPLAY, DP_PERMISSION_UP_DOWN, 255, "hello! intoyun!");      //显示字符串
    IntoRobot.defineDatapointBinary(DPID_BINARY_LOCATION, DP_PERMISSION_UP_DOWN, 255, "\x12\x34\x56\x78", 4); //位置信息
}

void loop()
{
    userHandle();
}

