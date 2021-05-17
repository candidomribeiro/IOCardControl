#ifndef IOCARDCONTROL_H
#define IOCARDCONTROL_H

#include <QtCore/qglobal.h>

#if defined(IOCARDCONTROL_LIBRARY)
#  define IOCARDCONTROL_EXPORT Q_DECL_EXPORT
#else
#  define IOCARDCONTROL_EXPORT Q_DECL_IMPORT
#endif

#include <QCoreApplication>
#include <array>
#include <iostream>
//#include <cmath>
#include <bdaqctrl.h>

using namespace Automation::BDaq;

class IOCARDCONTROL_EXPORT IOCardControl
{
public:
   /// <summary>建设IO卡对象，IO卡的号 = 0</summary>
   IOCardControl();

   /// <summary>建设IO卡对象。</summary>
   /// <param name="int deviceNumber">int deviceNumber: IO卡的号。</param>
   IOCardControl(int deviceNumber);

   /// <summary>检查IO卡的存在。</summary>
   /// <return>return, true IO卡存在，false IO卡不存在。</return>
   bool CheckIOCard();

   /// <summary>退回IO卡的数量在电脑里。</summary>
   /// <return>return IO卡的数量。</return>
   int GetIOCount();

   /// <summary>将所有继电器转到高或低位置。</summary>
   /// <param name="bool high">bool high: true 将所有继电器转到`高`位置。false 将所有继电器转到`低`位置。</param>
   /// <return>return ErrorCode</return>
   unsigned int Init(bool high);

   /// <summary>将特定的继电器转到高或低位置。</summary>
   /// <param name="int id">int id 继电器的识别号。</param>
   /// <param name="bool high">bool high: true 继电器转到`高`位置。false 继电器转到`低`位置。</param>
   /// <return>return ErrorCode</return>
   unsigned int SetIO(int id, bool high);

   /// <summary>将所有继电器转到高或低位置 根据8 bit号 (0 - 255)十进制。</summary>
   /// <param name="unsigned char value">unsigned char value: (0 - 255), 每个bit 0表示低值，每个bit 1表示高值。</param>
   /// <return>return ErrorCode</return>
   unsigned int SetIO(unsigned char value);

   /// <summary>退回所有继电器的情况 根据8 bit号 (0 - 255), 每个bit 0表示低值，每个bit 1表示高值。</summary>
   /// <return>return unsigned char</return>
   unsigned char GetIO();

   /// <summary>退回特定继电器的情况。</summary>
   /// <param name="int id">int id 继电器的识别号。</param>
   /// <param name="bool & output">bool & output 继电器的情况，true 高位置，false 低位置。</param>
   /// <return>return, true 成功，false 失败。</return>
   bool GetIO(int id, bool & output);

   /// <summary>退回最后的结果号码。</summary>
   /// <return>return ErrorCode</return>
   ErrorCode GetLastErrorCode();

   ~IOCardControl();

private:
   ErrorCode ret = Success;
   static int32 const portStart = 0;
   static int32 const portCount = 1;
   unsigned char values[portCount];
   int deviceNumber = 0;
   InstantDoCtrl * ctrl;
   DeviceInformation devInfo;
};

#endif // IOCARDCONTROL_H
