/*
    进入系统休眠状态，您可以通过该例程测试休眠功耗
*/

void init_before_setup(void)
{
    System.enableFeature(SYSTEM_FEATURE_CONFIG_SAVE_ENABLED); //不保存配置模式
}

STARTUP( init_before_setup() );

static void SystemWakeUpHandler(void)
{
    if(Serial.isEnabled()) {
        Serial.end();
    }
    Serial.begin(115200);
    Serial.println("mcuWakeup");
}

// setup函数, 上电后或者复位后只运行一次
void setup()
{
    //用户接管三色灯控制权
    RGB.control(true);
}

// loop函数, 循环执行
void loop()
{
    RGB.color(255, 255, 255);
    delay(30000);                         // 等待30s

    RGB.off();
    System.sleep(SystemWakeUpHandler,30); // 休眠30s
}

