#include "controller.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <csignal>
#include <iostream>
#include <iomanip>

using namespace constants;

// SIGINT handler - for quit via CTL-C
// ------------------------------------------------------------------------------------
bool quit_flag = false;
void sig_int_handler(int param)
{
    quit_flag = true;
}

// Controller Methods
// --------------------------------------------------------------------------------------

Controller::Controller(int vid, int pid) 
{
    std::signal(SIGINT,sig_int_handler);
    hid_dev_ = RawHIDDevice(vid,pid);
}


bool Controller::open()
{
    return hid_dev_.open();
}


void Controller::close()
{
    hid_dev_.close();
}


void Controller::run()
{
    std::cout << "clearing receive buffer" << std::endl;

    // Clear buffer to sync messages 
    hid_dev_.clearRecvBuffer();

    bool is_first = false;
    uint8_t msg_count = 0;
    double t_sec_last = 0.0;

    std::cout << std::setprecision(DisplayPrecision);
    std::cout << std::fixed;

    // Run message loop until CTL-C
    while (!quit_flag)
    {
        // Receive data from device
        DevToHostMsg dev_to_host_msg;
        if (!hid_dev_.recvData(&dev_to_host_msg))
        {
            std::cout << "error: recvData" << std::endl;
            continue;
        }

        // Send data to device
        HostToDevMsg host_to_dev_msg;
        host_to_dev_msg.count = msg_count;
        if (!hid_dev_.sendData(&host_to_dev_msg))
        {
            std::cout << "error: sendData" << std::endl;
        }

        // Get elapsed time between messages
        double t_sec = dev_to_host_msg.time_us*1.0e-6;
        double dt_sec = t_sec - t_sec_last;
        t_sec_last = t_sec;

        // Get lag between messages (minus -1 because device is echoing back last count)
        uint8_t lag = host_to_dev_msg.count - dev_to_host_msg.count - 1;

        // Display data
        std::cout << "dt:     " << dt_sec << std::endl;
        std::cout << "lag:    " << int(lag) << std::endl;; 
        for (int i=0; i<NumAnalogInput; i++)
        {
            std::cout << "ain[" << i << "]: " << dev_to_host_msg.analog_input[i] << std::endl;
        }
        std::cout << std::endl;

        msg_count++;
    }  // while (!quit_flag)

    std::cout << "done" << std::endl;
}




