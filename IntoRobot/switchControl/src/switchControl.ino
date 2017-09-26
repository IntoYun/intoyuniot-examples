/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
开关：开关控制

所需器件:
开关
D0
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#define    SWITCH_CMD_SWITCH    "channel/switch_0/cmd/switch"  //开关命令
#define    SWITCH_PIN           D0 //定义开关控制引脚

void switchCb(uint8_t *payload, uint32_t len)
{
	if(payload[0] == '1')
	{
		digitalWrite(SWITCH_PIN, HIGH);		// 打开开关
	} 
	else 
	{
		digitalWrite(SWITCH_PIN, LOW);		// 关闭开关
	}
}

void setup()
{
    //初始化
	pinMode(SWITCH_PIN,OUTPUT);
	//接收开关控制命令
	IntoRobot.subscribe(SWITCH_CMD_SWITCH, NULL, switchCb);
}

void loop()
{
}