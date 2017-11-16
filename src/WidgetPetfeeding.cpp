#include "WidgetPetfeeding.h"


WidgetPetfeeding::WidgetPetfeeding(uint8_t ucItem)
{
    _Item=ucItem;
    memset(pCmdSwitchTopic,0,sizeof(pCmdSwitchTopic));
    memset(pDataStatusTopic,0,sizeof(pDataStatusTopic));
    memset(pDataPetStatusTopic,0,sizeof(pDataPetStatusTopic));
    sprintf(pCmdSwitchTopic,"channel/petfeeding_%d/cmd/control",_Item);
    sprintf(pDataStatusTopic,"channel/petfeeding_%d/data/feedStatus",_Item);
    sprintf(pDataPetStatusTopic,"channel/petfeeding_%d/data/patStatus",_Item);
}

WidgetPetfeeding::~WidgetPetfeeding()
{

}

void WidgetPetfeeding::begin(void (*UserCallBack)(void))
{
    _EventCb=UserCallBack;
    IntoRobot.subscribe(pCmdSwitchTopic, NULL, this);
}

char WidgetPetfeeding::getFeedSwitch(void)
{
    return _feedSwitchKey;
}

char WidgetPetfeeding::getPhotoSwitch(void)
{
    return _photoSwitchKey;
}

void WidgetPetfeeding::displayFeedStatus(uint8_t ucVal)
{
    IntoRobot.publish(pDataStatusTopic,ucVal);
}

void WidgetPetfeeding::control(uint8_t ucPin, uint8_t ucVal)
{
    pinMode(ucPin,OUTPUT);
    digitalWrite(ucPin, ucVal);
    displayFeedStatus(ucVal);
}

void WidgetPetfeeding::displayPetStatus(uint8_t ucVal)
{
    IntoRobot.publish(pDataPetStatusTopic,ucVal);
}

void WidgetPetfeeding::widgetBaseCallBack(uint8_t *payload, uint32_t len)
{
     if(!jsonGetValue(payload, "feed", _feedSwitchKey)) return;
     if(!jsonGetValue(payload, "photo", _photoSwitchKey)) return;
     _EventCb();
}
