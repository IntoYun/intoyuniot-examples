/*该头文件引用由IntoRobot自动添加.*/
#include <IntoBike_Bluetooth_Control.h>
/*该头文件引用由IntoRobot自动添加.*/
#include <Sonar_Sensor_Processing.h>
/*该头文件引用由IntoRobot自动添加.*/
#include <IntoBike_Balance_Control.h>
/*该头文件引用由IntoRobot自动添加.*/
#include <IntoBike_StepMotor_Control.h>
/*该头文件引用由IntoRobot自动添加.*/
#include <IntoBike_OledDisplay.h>
/*该头文件引用由IntoRobot自动添加.*/
#include <IntoBike_AccelGyro_Sensor_Processing.h>
/*该头文件引用由IntoRobot自动添加.*/
#include <IntoBike_IntoRobotCloud_Interface.h>
/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  Dec. 21 2016
************************************************************************
描述：
IntoBike是由IntoRobot团队推出的双轮自平衡小车，具有一定的难度，是广大青少年学习机器人的利器。
IntoBike能够与IntoRobotCloud相连，实现任意距离的远程控制。
其工作原理是，利用IntoRobot－Neutron上的加速度计和陀螺仪获得小车的倾角和速度值，
经由IntoRobot团队开发的自动控制算法（开源），计算得到连接两轮的两个步进电机的运转速度，
最后经由IntoRobot－Neutron的PWM输出口，输出与速度值成正比的PWM波，控制步进电机运转，
实现两轮小车的自平衡运动控制。
IntoRobot-Bcar的程序主要包括：
1. 电池电压检测
2. OLED屏幕的显示
3. 步进电机的控制
4. 传感器的获取与滤波
5. 自平衡算法
6. 避碰算法
*/
#define TIMER_PERIOD   0.002
#define BALANCE_CONTROL_PERIOD (TIMER_PERIOD * 5.0)
#define SENSOR_PERIOD          (TIMER_PERIOD * 5.0)
#define FILTER_KALMAN         0
#define FILTER_COMPLEMENTARY  1
//motor pin definitions
#define FR_L   D4    //Left  motor: Direction
#define STEP_L D0    //Left  motor: PWM pulse, One pulse means one step for the Step Motor
#define FR_R   D7    //Right motor: Direction
#define STEP_R D3    //Right motor: PWM pulse, One pulse means one step for the Step Motor
#define STOP   A4    //Enable motor, Active HIGH 
IntoBikeOledDisplay       _oled_display;
SonarSensorProcessing     _sonar_sensor;
AccelGyroSensorProcessing _accelgyro_sensor;
BalanceControl            _balance_controller;
StepMotorControl          _stepmotor_control[2];
IntoBikeStateMachine      _state_machine;
StateMachineInfo          _statemachine_info;
EventInputData _event_data;
int _esp_time;
int8_t _balance_control_ct = 0;
int8_t _sensor_ct = 0;
WheelsSpeed  _velocity;
Timer _process_timer(2, processTimerISR);
void processTimerISR(void)
{
    long int start_time;
    PoseData pose_data;
    start_time = micros();
    //Sensor
    _sensor_ct++;
    if(_sensor_ct * TIMER_PERIOD == SENSOR_PERIOD)
    {
        _accelgyro_sensor.processData();
        _sensor_ct = 0;
    }
    //Balance_control
    _balance_control_ct++;
    if(_balance_control_ct * TIMER_PERIOD == BALANCE_CONTROL_PERIOD)
    {
        pose_data = _accelgyro_sensor.getFilteredData();
        _statemachine_info = _state_machine.getInfo();
        _velocity.left_  = _stepmotor_control[0].getEncoder();
        _velocity.right_ = -_stepmotor_control[1].getEncoder();		//left and right motors should be oposite
        //events detection
        _event_data.pitch_       = pose_data.pitch_;
        _event_data.pitch_rate_  = pose_data.pitch_rate_;
        _event_data.accel_z_     = _accelgyro_sensor.getAccel(2);
        _event_data.encoder_left_  = _velocity.left_;
        _event_data.encoder_right_ = _velocity.right_;
        _state_machine.detectEvent(_event_data);
        if(_statemachine_info.state_ == FALL_DOWN || _statemachine_info.state_ == PICKED_UP)
        {
            _stepmotor_control[0].disableMotors();
            _stepmotor_control[1].disableMotors();
            _balance_controller.restart();
        }
        else
        {
            if(_statemachine_info.state_ == BLOCKED)
            {
                _balance_controller.setObstacleBlockedStatus(true);
            }
            _stepmotor_control[0].enableMotors();
            _stepmotor_control[1].enableMotors();
            _velocity  = _balance_controller.doControl(pose_data.pitch_, pose_data.pitch_rate_, _velocity);
            _stepmotor_control[0].setMotorSpeed(_velocity.left_);
            _stepmotor_control[1].setMotorSpeed(-_velocity.right_);			//left and right motors should be oposite
        }
        _balance_control_ct = 0;
    }
    _esp_time = micros() - start_time;
}

void setup()
{
    Serial.begin(9600);
    SerialUSB.begin(9600);
    _oled_display.begin();
    _sonar_sensor.begin();
    _accelgyro_sensor.begin((float)SENSOR_PERIOD, FILTER_COMPLEMENTARY);
    _balance_controller.begin((float)BALANCE_CONTROL_PERIOD);
    _stepmotor_control[0].begin(FR_L, STEP_L, STOP);
    _stepmotor_control[1].begin(FR_R, STEP_R, STOP);
    IntoBikeCloudInterface::getInstance()->begin(_stepmotor_control, &_balance_controller);	//FIXME: Note don't instanize IntoRobotCloudInterface again
    _process_timer.start();
}

void loop()
{
    PoseData     pose_data    = _accelgyro_sensor.getFilteredData();
    DisplayData  display_data;
    DisplayDebugInfo display_debug_info;
    display_data.velocity_l_        = _velocity.left_;
    display_data.velocity_r_        = _velocity.right_;
    display_data.pitch_             = pose_data.pitch_;
    display_data.pitch_rate_        = pose_data.pitch_rate_;
    display_data.obstacle_distance_ = _sonar_sensor.getDistance();
    display_debug_info = _balance_controller.getDebugInfo(_accelgyro_sensor.getFilterType());
    _event_data.obstacle_distance_ = _sonar_sensor.getDistance();	//set value here becsof sonar uses a timer
    _oled_display.setData(display_data);	//display data  info
    _oled_display.setData(display_debug_info);	//display debug info
    _oled_display.setData(_statemachine_info);
    _oled_display.displayData();
    char cmd;
    if(bluetoothDataReady(true) == true)
    {
        if(processBluetoothData(&cmd, true))
        {
            _balance_controller.remoteControl(cmd);
            _oled_display.switchDisplay(cmd);
        }
    }
    delay(20);
}
