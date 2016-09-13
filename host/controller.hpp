#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include "rawhid_device.hpp"
#include "rawhid_msg_types.h"

class Controller
{
    public:

        static const int Default_USB_VID = 0x16C0;
        static const int Default_USB_PID = 0x0486;
        static const int DisplayPrecision = 6;

        Controller(int vid=Default_USB_VID, int pid=Default_USB_PID);

        bool open();
        void close();
        void run();

    protected:

        RawHIDDevice hid_dev_;
};

#endif
