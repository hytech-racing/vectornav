#include "VectorNavComms.hpp"

// Initializes the sensor by setting up the async callback handler
void comms::VectorNavDriver::init() 
{
    BinaryOutputRegister bor(
        ASYNCMODE_PORT1,
        200,
        COMMONGROUP_TIMESTARTUP | COMMONGROUP_YAWPITCHROLL,
        TIMEGROUP_NONE,
        IMUGROUP_NONE,
        GPSGROUP_NONE,
        ATTITUDEGROUP_NONE,
        INSGROUP_NONE, 
        GPSGROUP_NONE
    );
    vs.writeBinaryOutput1(bor);
    vs.registerAsyncPacketReceivedHandler(NULL, _ascii_or_binary_messaged_received);
}

// Changes the data output frequency for the sensor
void comms::VectorNavDriver::reconfigure_data_output_frequency(uint32_t newHz) 
{
    vs.writeAsyncDataOutputFrequency(newHz);
}

// Reconfigures heading mode by reading current registration configuration, changing what we want, and rewriting.
void comms::VectorNavDriver::reconfigure_heading_mode(vn::protocol::uart::HeadingMode hMode) {
    VpeBasicControlRegister vpeReg = vs.readVpeBasicControl();
    vpeReg.headingMode = hMode; 
    vs.writeVpeBasicControl(vpeReg);
}

void comms::VectorNavDriver::disconnect() 
{
    vs.unregisterAsyncPacketReceivedHandler();
    vs.disconnect();
}


// Callback handler for recieving new packets
void comms::VectorNavDriver::_ascii_or_binary_messaged_received(void* userData, Packet& p, size_t index)
{
    if (p.type() == vn::protocol::uart::Packet::TYPE_ASCII && p.determineAsciiAsyncType() == vn::protocol::uart::AsciiAsync::VNYPR) {
        vn::math::vec3f ypr;
        p.parseVNYPR(&ypr);
    }
    if (p.type() == vn::protocol::uart::Packet::TYPE_BINARY) {
        if (!p.isCompatible(
            COMMONGROUP_TIMESTARTUP | COMMONGROUP_YAWPITCHROLL, 
            TIMEGROUP_NONE,
            IMUGROUP_NONE,
            GPSGROUP_NONE, 
            ATTITUDEGROUP_NONE,
            INSGROUP_NONE,
            GPSGROUP_NONE)) {
                return;
            }
    }
    uint64_t timeStartup = p.extractUint64();
    // TODO extract binary data according to the order provided by the User manuals
}