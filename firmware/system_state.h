#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H
#include "Arduino.h"
#include "constants.h"
#include "rawhid_msg_types.h"

class SystemState
{
    public:

        volatile bool new_msg_flag_ = false; 

        SystemState();

        void initialize();           
        void update_on_loop(); 
        inline void set_msg_flag_on_timer();

    protected:

        IntervalTimer timer_;                     
        volatile uint32_t timer_count_ = 0;

        HostToDevMsg host_to_dev_msg_last_; // Last message received

        // Time variables
        uint32_t micros_last_ = 0;          // Value from last call to micros
        uint64_t time_us_ = 0;              // Elapsed time in us

        // Messaging methods
        void send_and_recv();                      
        bool send_msg_to_host();   
        bool recv_msg_from_host(); 
        void on_send_msg_error();  
        void on_recv_msg_error();  
        DevToHostMsg create_dev_to_host_msg();  
        void command_switchyard();              

        // Setup methods
        void setup_timer();
        void setup_analog_input();
};

extern SystemState system_state; 


// Timer update functions
// --------------------------------------------------------------------------------------
inline void SystemState::set_msg_flag_on_timer()
{
    system_state.new_msg_flag_ = true;
}


inline void timer_callback()
{
    system_state.set_msg_flag_on_timer();
}




#endif 

