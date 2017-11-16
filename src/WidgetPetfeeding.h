#ifndef WIDGET_PETFEEDING_H_
#define WIDGET_PETFEEDING_H_

#include "application.h"

class WidgetPetfeeding: public WidgetBaseClass
{
    public:
        WidgetPetfeeding(uint8_t ucItem = 0);
        ~WidgetPetfeeding();

        void begin(void (*UserCallBack)(void) = NULL);
        char getFeedSwitch(void);
        char getPhotoSwitch(void);
        void displayFeedStatus(uint8_t ucVal);
        void control(uint8_t ucPin, uint8_t ucVal);
        void displayPetStatus(uint8_t ucVal);

    private:
        char pCmdSwitchTopic[64];
        char pDataStatusTopic[64];
        char pDataPetStatusTopic[64];
        char _feedSwitchKey = 0;
        char _photoSwitchKey = 0;
        uint8_t _Item=0;
        void (*_EventCb)(void);
        void widgetBaseCallBack(uint8_t *payload, uint32_t len);
};

#endif
