#pragma once

#include <iostream> 
#include "libvncxx/sensors.h"
#include "libvncxx/packet.h"

using namespace vn::math;
using namespace vn::sensors;
using namespace vn::protocol::uart;
using namespace vn::xplat;

namespace comms
{
    class VectorNavDriver 
    {
        public:
            VectorNavDriver(std::string& sensor_port, uint32_t sensor_baudrate)
            {
                vs.connect(sensor_port, sensor_baudrate);
            }
            // Initializes sensor to recieve async data measurements
            void init();
            // Methods for reconfiguring the sensor
            void reconfigure_data_output_frequency(uint32_t newHz);
            void reconfigure_heading_mode(vn::protocol::uart::HeadingMode heading_mode);     
            // Method for disconnecting the sensor
            void disconnect();

            // TODO add getters for all the data we want
        protected: 
            vn::sensors::VnSensor vs;
            vn::math::vec3f ypr;

            // Callback method for when data is received
            static void _ascii_or_binary_messaged_received(void* userData, vn::protocol::uart::Packet& p, size_t index);
            
    };
}

