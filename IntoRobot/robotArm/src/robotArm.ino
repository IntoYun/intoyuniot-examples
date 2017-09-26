/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
机械臂：控制机械臂运动

所需器件:
1. AL5A Robotic Arm 机械臂

接线说明
机械臂      核心板
RX          串口(Serial组)的TX
TX		    串口(Serial组)的RX

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
请注意核心板串口引脚区别，避免接线错误。
*/

//机械臂应用topic定义
#define ROBOTARM_CMD_CONTROL    "channel/robotArm_0/cmd/control" //控制命令
#define ROBOTARM_DATA_STATUS    "channel/robotArm_0/data/status" //控制状态

//底座舵机控制
void baseControl(int base)
{
	int pos;
	String cmd = "";
	static int base_old = 0x00;

	if(base != base_old)
	{
		//base 500 ~ 2500  (2500-500)/180 ~ 12
		pos = 1500 + 12 * base;
		cmd = cmd + "#" + "0" + " P" + String(pos) + " T" + 500;
		Serial.println(cmd);
	}
	base_old = base;
}

//肩部舵机控制
void shoulderControl(int shoulder)
{
	int pos;
	String cmd = "";
	static int shoulder_old = 0x00;

	if(shoulder != shoulder_old)
	{
		//shoulder 1500 ~ 2300  (2300-1500)/180 ~ 5
		pos = 1900 + 5 * shoulder;
		cmd = cmd + " #" + "1" + " P" + String(pos) + " T" + 500;
		Serial.println(cmd);
	}
	shoulder_old = shoulder;
}

//肘部舵机控制
void elbowControl(int elbow)
{
	int pos;
	String cmd = "";
	static int elbow_old = 0x00;

	if(elbow != elbow_old)
	{
		//elbow 600 ~ 2000  (2000-600)/180 ~ 8
		pos = 1300 + 5 * elbow;
		cmd = cmd + " #" + "2" + " P" + String(pos) + " T" + 500;
		Serial.println(cmd);
	}
	elbow_old = elbow;
}

//腕部舵机控制
void wristControl(int wrist)
{
	int pos;
	String cmd = "";
	static int wrist_old = 0x00;

	if(wrist != wrist_old)
	{
		//wrist 700 ~ 2500  (2500-700)/180 ~ 10
		pos = 1600 + 10 * wrist;
		cmd = cmd + " #" + "3" + " P" + String(pos) + " T" + 500;
		Serial.println(cmd);
	}
	wrist_old = wrist;
}

//夹具舵机控制
void gripperControl(int gripper)
{
	int pos;
	String cmd = "";
	static int gripper_old = 0x00;

	if(gripper != gripper_old)
	{
		//gripper 1000 ~ 2500  (2500-1000)/180 ~ 9
		pos = 1750 + 9 * gripper;
		cmd = cmd + " #" + "4" + " P" + String(pos) + " T" + 500;
		Serial.println(cmd);
	}
	gripper_old = gripper;
}

//机械臂控制回调{"b":-45, "s": -45, "e": -45, "w":-45, "g":-45}
void robotArmControlCb(uint8_t * payload, uint32_t len)
{
	String  baseValue;
	String  shoulderValue;
	String  elbowValue;
	String  wristValue;
	String  gripperValue;

	if(jsonGetValue(payload,"b",baseValue)) 
	{
	    baseControl(baseValue.toInt());
	}
	
	if(jsonGetValue(payload,"s",shoulderValue)) 
	{
	   	shoulderControl(shoulderValue.toInt());
	}

	if(jsonGetValue(payload,"e",elbowValue)) 
    {
	    elbowControl(elbowValue.toInt());
	}

	if(jsonGetValue(payload,"wr",wristValue)) 
	{
	    wristControl(wristValue.toInt());
	}

	if(jsonGetValue(payload,"g",gripperValue)) 
	{
	    gripperControl(gripperValue.toInt());
	}
	
	IntoRobot.publish(ROBOTARM_DATA_STATUS,"1");	
}

void setup()
{
    //初始化
	Serial.begin(115200);
	while (!Serial);
	delay(500);
	//接收机械臂控制命令
	IntoRobot.subscribe(ROBOTARM_CMD_CONTROL, NULL, robotArmControlCb);
}

void loop()
{
}