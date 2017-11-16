/******************************

  作者  IntoRobot Team
  版本  V1.0.0
  日期  03-30-15

  功能描述：
  宠物喂食器：设想通过红外检测到是否有宠物，检测到后打开喂食开关。

  所需器件
  1.E18-D80NK 红外光电开关 漫反射式避障传感器模块
  2.继电器模块
  3.宠物喂食装置

  接线说明
  E18-D80NK                    核心板
  1.红色线                     +5V
  2.黑色线                     GND
  3.黄色线                     D1
  继电器模块
  1.DC+：                      +5V
  2.DC-：                      GND
  3.IN：                       D0
  4.NO：                       舵机的正极
  5.COM：                      +5V
  6.NC：                       悬空
  7.触发选择端：选择跳线与high短接, 即高电平触发。
 ***********************************/
/*该头文件引用由IntoRobot自动添加.*/
#include <WidgetPetfeeding.h>

#define INFRARED_SENSOR_INPUT    D1  //定义红外光电传感器引脚
#define MOTORPIN                 D0  //定义马达控制引脚

WidgetPetfeeding pet = WidgetPetfeeding();

void photoAndSendMail()
{
  Process p; //拍照
  p.begin("fswebcam");
  p.addParameter("-d /dev/video0 --no-banner -S 21  -r 640x480 --jpeg 95  /tmp/intorobot.jpg"); 
  p.run();

  Process p2; //将图片发送至邮箱
  p2.begin("cam_mail");
  p2.addParameter("xxxx@xxx.com");  // 修改为您的邮箱
  p2.run();
}

void petFeedCb(void)
{
    if(pet.getFeedSwitch())
    {
        pet.control(MOTORPIN,1); //打开马达
    }
    else
    {
        pet.control(MOTORPIN,0); //关闭马达
    }
    
    if(pet.getPhotoSwitch()) //拍照
    {
        photoAndSendMail();
    }
}

void setup()
{
    pinMode(INFRARED_SENSOR_INPUT, INPUT_PULLUP);
    pet.begin(petFeedCb);
}

void loop()
{
    if(!digitalRead(INFRARED_SENSOR_INPUT))
    {
        pet.displayPetStatus(1); // 发送宠物出现状态
    }
    else
    {
        pet.displayPetStatus(0); // 发送宠物未出现状态
    }

    delay(3000);
}
