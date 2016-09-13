#include "system_state.h"

// SystemState public methods
// ------------------------------------------------------------------------------------------------

SystemState::SystemState() { }

void SystemState::initialize()
{ 
    //Serial.begin(115200);  // DEBUGGING
    setup_analog_input();
    setup_timer();        
}


void SystemState::update_on_loop()
{
    send_and_recv();        

    // Do other things ... 
    // -----------------------------
    
    // -----------------------------
}


// SystemState protected methods
// ------------------------------------------------------------------------------------------------
void SystemState::send_and_recv()
{
    if (new_msg_flag_)
    {
        new_msg_flag_ = false;
        if (!send_msg_to_host())
        {
            on_send_msg_error();
        }
        else
        {
            if (!recv_msg_from_host())
            {
                on_recv_msg_error();
            }
        }
    } 
}

bool SystemState::send_msg_to_host()
{ 
    bool rtn_val = true;
    DevToHostMsg dev_to_host_msg = create_dev_to_host_msg();
    int num_bytes = RawHID.send(&dev_to_host_msg,constants::DevToHostTimeout);
    if (num_bytes != sizeof(DevToHostMsg))
    {
        rtn_val = false;
    }
    return rtn_val;
}


void SystemState::on_send_msg_error()  
{
    // Take action on send message error - empty for example
}


void SystemState::on_recv_msg_error()  
{
    // Take action on receive message error - empty for example
}


bool SystemState::recv_msg_from_host()
{
    bool rtn_val = true;
    HostToDevMsg host_to_dev_msg;
    int num_bytes = RawHID.recv(&host_to_dev_msg,constants::HostToDevTimeout);
    if (num_bytes != sizeof(HostToDevMsg))
    {
        rtn_val = false;
    }
    else
    {
        host_to_dev_msg_last_ = host_to_dev_msg;
        command_switchyard();
    }
    return rtn_val;
}


DevToHostMsg SystemState::create_dev_to_host_msg()
{
    DevToHostMsg dev_to_host_msg;

    // Get current time in us
    uint32_t micros_curr = micros();
    uint32_t micros_dt = micros_curr - micros_last_;
    micros_last_ = micros_curr;
    time_us_ += uint64_t(micros_dt);
    dev_to_host_msg.time_us = time_us_;

    // Set stepper position and velocity - just pretend for example
    for (int i=0; i<constants::NumStepper; i++)
    {
        dev_to_host_msg.stepper_position[i] = 0;
        dev_to_host_msg.stepper_velocity[i] = 0;
    }

    // Set pwm position - just pretend for example
    for (int i=0; i<constants::NumPwm; i++)
    {
        dev_to_host_msg.pwm_position[i] = 0;
    }

    // Read Analog inputs 
    for (int i=0; i<constants::NumAnalogInput; i++)
    {
        dev_to_host_msg.analog_input[i] = analogRead(constants::AnalogInputPinArray[i]);
    }

    // Set status information
    dev_to_host_msg.status = 0;

    // Echo back message count - can be used for lag checking 
    dev_to_host_msg.count = host_to_dev_msg_last_.count;

    // Echo back last command and set command response data
    dev_to_host_msg.command = host_to_dev_msg_last_.command;
    dev_to_host_msg.command_data = 0;

    return dev_to_host_msg;
}


void SystemState::command_switchyard()
{
    // Do something with message (host_to_dev_msg_last_) 
    //
    // For example take action based on command id, etc.
}


void SystemState::setup_analog_input()
{
    analogReadResolution(constants::AnalogReadNumBits);
    analogReadAveraging(constants::AnalogReadNumAvg);
    analogReference(constants::AnalogRefType);
}


void SystemState::setup_timer()
{
    timer_.priority(constants::TimerPriority);
    timer_.begin(timer_callback,constants::TimerPeriod_us);
}


// SystemState Instance
// ------------------------------------------------------------------------------------------------
SystemState system_state = SystemState();

