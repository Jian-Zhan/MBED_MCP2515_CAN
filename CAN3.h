
#ifndef _CAN3_H_
#define _CAN3_H_

#include "mbed.h"
#include "mcp2515.h"
#include "mcp2515_defs.h"
#include "mcp2515_can.h"
#include "SPI.h"

class CAN3
{
public:
    CAN3(SPI& _spi, PinName ncs, PinName itr);

    int read(CANMessage &msg);
    int write(CANMessage &msg);
    int frequency(int hz);

    void reset();
    unsigned char rderror();
    unsigned char tderror();

    // Not implemented:
    // void 	monitor (bool silent)
    // int 	mode (Mode mode)
    // int 	filter (unsigned int id, unsigned int mask, CANFormat format=CANAny, int handle=0)
    // void 	attach (Callback< void()> func, IrqType type=RxIrq)

    void rise(void (*fptr)(void));
    void fall(void (*fptr2)(void));

private :
    SPI& spi;
    mcp2515 _mcp;
    InterruptIn _itr;

    uint8_t checkReceive(void);
};

#endif // _MCP2515_H_
