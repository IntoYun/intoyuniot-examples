/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
智能垃圾桶：通过红外检测到有人体靠近需要丢垃圾，则通过舵机控制垃圾桶盖自动打开，
丢完垃圾后垃圾桶盖自动关闭。

所需器件:
1.舵机
2.E18-D80NK红外光电开关

接线说明:
SG90 9G舵机                  核心板
1.红线                       +5V
2.暗灰线                     GND
3.橙黄线                     A0

E18-D80NK
1.红色线                     +5V
2.黑色线                     GND
3.黄色线                     D0
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

//智能垃圾桶应用topic定义
#define WASTEBIN_DATA_STATUS     "channel/wastebin_0/data/status"     //垃圾桶翻盖状态
#define WASTEBIN_CMD_SWITCH      "channel/wastebin_0/cmd/switch"      //垃圾桶开关控制
#define WASTEBIN_DATA_COUNTNUM   "channel/wastebin_0/data/countnum"  //丢垃圾次数

//打开和关闭垃圾桶盖时，舵机需要旋转的角度
#define OPEN_ANGLE	            70
#define	CLOSE_ANGLE	            180
#define CLOSE_TIME              3000            //关闭垃圾桶盖的延时
#define INFRARED_SENSOR_INPUT   D0              //红外控制引脚
#define SERVO_CONTROL_PIN       A0              //定义舵机控制引脚


Servo myservo;
volatile int cmdFlag = 0;
volatile uint32_t countNum = 0;

void setup()
{
	//初始化
	myservo.attach(SERVO_CONTROL_PIN);
	//接收舵机控制
	pinMode(INFRARED_SENSOR_INPUT, INPUT_PULLUP);
	IntoRobot.publish(WASTEBIN_DATA_COUNTNUM, countNum);
	IntoRobot.subscribe(WASTEBIN_CMD_SWITCH , NULL, wastebinSwitchCb);
}

void wastebinSwitchCb(uint8_t *payload, uint32_t len)
{
	if(payload[0] == '1')
	{
	    countNum++;
		cmdFlag = 1;
		myservo.write(OPEN_ANGLE);
		IntoRobot.publish(WASTEBIN_DATA_STATUS, 1);
		IntoRobot.publish(WASTEBIN_DATA_COUNTNUM, countNum);
	}
	else
	{
		cmdFlag = 0;
		myservo.write(CLOSE_ANGLE);
		IntoRobot.publish(WASTEBIN_DATA_STATUS, 0);
	}
}

void loop()
{
    IntoRobot.publish(WASTEBIN_DATA_COUNTNUM, countNum);
	if(cmdFlag == 0 && digitalRead(INFRARED_SENSOR_INPUT) == 0)
	{
	    
		countNum++;
		IntoRobot.publish(WASTEBIN_DATA_COUNTNUM, countNum);
		int32_t timerId = 0;
		myservo.write(OPEN_ANGLE);
		IntoRobot.publish(WASTEBIN_DATA_STATUS, 1);
		timerId = timerGetId();
		
		while(1)
		{
			if(timerIsEnd(timerId, CLOSE_TIME))
			{
				if(digitalRead(INFRARED_SENSOR_INPUT) == 1)
				{
					myservo.write(CLOSE_ANGLE);
					IntoRobot.publish(WASTEBIN_DATA_STATUS, 0);
					delay(1000);
					break;
				}
				else
				{
					timerId = timerGetId();
				}
			}
		}
	}
	delay(500);
}
