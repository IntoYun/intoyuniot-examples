/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
浇灌器：具有土壤湿度检测功能的浇花控制器

所需器件:
1. YL38 土壤湿度传感器
2. 电磁阀

接线说明    核心板
电池阀		D0
YL38        A0
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#include <yl38.h>

//洒水器应用topic定义
#define SPRINKLER_DATA_SOILHUMIDITY    "channel/sprinkler_0/data/soilHumidity"  //土壤湿度
#define SPRINKLER_CMD_CONTROL          "channel/sprinkler_0/cmd/control"  	    //浇水开关    
#define SPRINKLER_DATA_STATUS          "channel/sprinkler_0/data/status"        //浇水状态

#define SPRINKLER_SWITCH_PIN    D0   //定义浇水开关引脚
#define YL38_PIN  A0
YL38 yl38 = YL38(YL38_PIN);

uint8_t   wateringDelay;  //浇水时间
uint8_t   wateringFlag;   //浇水标志
uint32_t  wateringTimer;  //浇水定时器

void wateringCb(uint8_t * payload, uint32_t len)
{
	int wateringStatus;
    aJsonClass aJson;
	aJsonObject *root = aJson.parse((char *)payload);
	if(root == NULL)
	{
	    aJson.deleteItem(root);
		return;
	}
	
	aJsonObject *_waterCmd = aJson.getObjectItem(root, "watering");
	if(_waterCmd == NULL)
	{
		aJson.deleteItem(root);
		return;    
	}
	
	aJsonObject *_waterStatus = aJson.getObjectItem(_waterCmd, "status");
	if(_waterStatus == NULL)
	{
	  	aJson.deleteItem(root);
		return;  
	}
	wateringStatus = _waterStatus->valueint;

	aJsonObject *_waterTime = aJson.getObjectItem(_waterCmd, "time");
	if(_waterTime == NULL)
	{
	  	aJson.deleteItem(root);
		return;  
	}
	wateringDelay = _waterTime->valueint;
	aJson.deleteItem(root);

	if(wateringStatus)
	{
		digitalWrite(SPRINKLER_SWITCH_PIN, HIGH);
		IntoRobot.publish(SPRINKLER_DATA_STATUS,"1"); //打开浇水
		
		if(wateringDelay != 0)
		{
			wateringFlag = 1;
			wateringTimer = timerGetId();
		}
		else
		{
			wateringFlag = 0;
		}
	}
	else 
	{
		digitalWrite(SPRINKLER_SWITCH_PIN, LOW); //关闭浇水
		IntoRobot.publish(SPRINKLER_DATA_STATUS,"0");
		wateringFlag = 0;
	}
}

void setup()
{
    //初始化
	yl38.begin(); 
	pinMode(SPRINKLER_SWITCH_PIN, OUTPUT);
	//接收浇水控制
	IntoRobot.subscribe(SPRINKLER_CMD_CONTROL, NULL, wateringCb); 
}

void loop()
{
	IntoRobot.publish(SPRINKLER_DATA_SOILHUMIDITY,yl38.CalculateHumidity());  //上送土壤湿度

	if(wateringFlag && timerIsEnd(wateringTimer,wateringDelay*60000))
	{
		digitalWrite(SPRINKLER_SWITCH_PIN, LOW); //浇水时间到，关闭浇水
		IntoRobot.publish(SPRINKLER_DATA_STATUS,"0");
		wateringFlag = 0;
	}

	delay(2000);
}
