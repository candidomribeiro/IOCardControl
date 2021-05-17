#include "iocardcontrol.h"

IOCardControl::IOCardControl()
{
    this->ctrl = AdxInstantDoCtrlCreate();
    DeviceInformation devInfo(deviceNumber);
    this->devInfo = devInfo;
    ret = ctrl->setSelectedDevice(devInfo);
    if (ret != Success)
    {
        std::cerr << "Open device failed. error code = " << ret << std::endl;       
    }
}

IOCardControl::IOCardControl(int deviceNumber)
{
    this->deviceNumber = deviceNumber;

    this->ctrl = AdxInstantDoCtrlCreate();
    DeviceInformation devInfo(deviceNumber);
    this->devInfo = devInfo;
    ret = ctrl->setSelectedDevice(devInfo);
    if (ret != Success)
    {
        std::cerr << "Open device failed. error code = " << ret << std::endl;       
    }
}

IOCardControl::~IOCardControl()
{
    ctrl->Cleanup();
    ctrl->Dispose();
}

bool IOCardControl::CheckIOCard()
{
    InstantDoCtrl * ctrl = AdxInstantDoCtrlCreate();
    ErrorCode ret = Success;

        DeviceInformation devInfo(deviceNumber);
        ret = ctrl->setSelectedDevice(devInfo);
        if (ret == Success)
        {
           return true;
        }

    return false;
}

int IOCardControl::GetIOCount()
{
    InstantDoCtrl * ctrl = AdxInstantDoCtrlCreate();
    ErrorCode ret = Success;
    int deviceCounter = 0;

    for(int deviceNumber = 0; deviceNumber < 16; deviceNumber++)
    {
        DeviceInformation devInfo(deviceNumber);
        ret = ctrl->setSelectedDevice(devInfo);
        if (ret == Success)
        {
           deviceCounter++;           
        }
    }
    return deviceCounter;
}

unsigned int IOCardControl::Init(bool high)
{
    if (high == true)
    {
        values[portStart] = 255;
    }
    else
    {
        values[portStart] = 0;
    }

    ret = ctrl->Write(portStart, portCount, values);

    return ret;
}

unsigned int IOCardControl::SetIO(int id, bool high)
{
    unsigned char old_values[portCount];
    unsigned char new_values[portCount];

    ret = ctrl->Read(portStart, portCount, old_values);
    new_values[portStart] = static_cast<unsigned char>(1 << id);  // locate the led position according to given id.
                           //static_cast<unsigned char>(pow(2.0,id));
    if(high == true)
    {
        new_values[portStart] |= old_values[portStart]; // perform a bitwise `or` between new_values and old_values.
        ret = ctrl->Write(portStart, portCount, new_values);
    }
    else
    {
        new_values[portStart] ^= old_values[portStart]; // perform a bitwise `xor` between new_values and old_values.
        ret = ctrl->Write(portStart, portCount, new_values);
    }

    return ret;
}

unsigned int IOCardControl::SetIO(unsigned char value)
{
    ret = ctrl->Write(portStart, portCount, &value);

    return ret;
}

bool IOCardControl::GetIO(int id, bool & output)
{
    unsigned char test_values[portCount];
    test_values[portStart] = static_cast<unsigned char>(1 << id);  // locate the led position according to given id.
                             //static_cast<unsigned char>(pow(2.0,id));
    ret = ctrl->Read(portStart,portCount,values);
    values[portStart] &= test_values[portStart]; // perform a bitwise `and` between new_values and old_values.

    output = static_cast<bool>(values[portStart]);

    if(ret == Success)
    {
        return true;
    }

    return false;
}

unsigned char IOCardControl::GetIO()
{
    ret = ctrl->Read(portStart,portCount,values);
    return *values;
}

ErrorCode IOCardControl::GetLastErrorCode()
{
    return this->ret;
}


