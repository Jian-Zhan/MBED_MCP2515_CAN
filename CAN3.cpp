#include "CAN3.h"

#include "mbed.h"
#include "mcp2515.h"
#include "mcp2515_can.h"
#include "mcp2515_defs.h"


CAN3::CAN3(SPI& _spi, PinName ncs, PinName itr)
        : spi(_spi), _mcp(spi, ncs), _itr(itr)
{
}

int CAN3::read(CANMessage &msg) {
    uint8_t stat;
    int res = 0;

    stat = _mcp.readStatus();

    if ( stat & MCP_STAT_RX0IF ) {
        // Msg in Buffer 0
        _mcp.read_canMsg( MCP_RXBUF_0, &msg);
        _mcp.modifyRegister(MCP_CANINTF, MCP_RX0IF, 0);
        res = 1;
    } else if ( stat & MCP_STAT_RX1IF ) {
        // Msg in Buffer 1
        _mcp.read_canMsg( MCP_RXBUF_1, &msg);
        _mcp.modifyRegister(MCP_CANINTF, MCP_RX1IF, 0);
        res = 1;
    } else {
        res = 0;
    }

    return res;
}

uint8_t CAN3::checkReceive(void) {
    uint8_t res;

    res = _mcp.readStatus(); // RXnIF in Bit 1 and 0
    if ( res & MCP_STAT_RXIF_MASK ) {
        return CAN_MSGAVAIL;
    } else {
        return CAN_NOMSG;
    }
}

int CAN3::write(CANMessage &msg) {
    uint8_t  txbuf_n;
    _mcp.getNextFreeTXBuf(&txbuf_n);
    if (txbuf_n == MCP_ALLTXBUSY) {
        return 0;
    }

    _mcp.write_canMsg(txbuf_n, &msg);
    _mcp.start_transmit(txbuf_n);
    return 1;
}

void CAN3::rise(void (*fptr)(void)) {
    _itr.rise(fptr);
}

void CAN3::fall(void (*fptr2)(void)) {
    _itr.fall(fptr2);
}

void CAN3::reset() {
}

int CAN3::frequency(int hz) {

    uint8_t res;

    res = _mcp.init(hz);
    wait(.001);

    _mcp.setRegister(MCP_CANINTE, 0x3);//0x3); //MCP_RX_INT);
    _mcp.setRegister(MCP_CANINTF, 0x3);// 0xff);

    // printf("Setting Normal-Mode - \n\r ");
    if ( _mcp.setCANCTRL_Mode(MODE_NORMAL) == MCP2515_OK) { //MODE_NORMAL MODE_LOOPBACK
        //     printf("OK\n\r");
    } else {
        error("failed\n\r");
    }

    _mcp.dumpExtendedStatus();
    wait(.001);

    if (res != MCP2515_OK) {
        return 0;

    }
    return 1;
}
