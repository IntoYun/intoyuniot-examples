/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 舵机控制：控制舵机的运动

 所需器件:
 1.舵机（舵机电流过大需单独供电）


 接线说明:
 SG90 9G舵机                  核心板
 1.红线                       +5V
 2.暗灰线                     GND
 3.橙黄线                     A0

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

//舵机控制应用topic定义
#define SERVO_CMD_ANGLE     "channel/servo_0/cmd/angle"    //控制角度
#define SERVO_DATA_STATUS   "channel/servo_0/data/status"  //控制状态

#define SERVO_CONTROL_PIN    A0 //定义舵机控制引脚

Servo myservo;

void servoAngleControlCb(uint8_t *payload, uint32_t len)
{
    int pos = atoi((char *)payload);
    if((pos>=0) && (pos<=180))
    {
        myservo.write(pos);
        IntoRobot.publish(SERVO_DATA_STATUS,"1");
    }
}

void setup()
{
    //初始化
    myservo.attach(SERVO_CONTROL_PIN);
    //接收舵机控制
    IntoRobot.subscribe(SERVO_CMD_ANGLE, NULL, servoAngleControlCb);
}

void loop()
{
}

