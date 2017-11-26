
#ifndef _MCP2515_H_
#define _MCP2515_H_

#include <mbed.h>
#include "mcp2515_defs.h"
#include "can_support.h"

#define MCPDEBUG (1)
#if MCPDEBUG
#define _mcp2515_printf(...) printf(__VA_ARGS__)
#else
#define _mcp2515_printf(...)
#endif

#define MCP_CS_PORT PORTB
#define MCP_CS_DDR  DDRB
#define MCP_CS_BIT  PB0

#define MCP_N_TXBUFFERS (3)

#define MCP_RXBUF_0 (MCP_RXB0SIDH)
#define MCP_RXBUF_1 (MCP_RXB1SIDH)

#define MCP_TXBUF_0 (MCP_TXB0SIDH)
#define MCP_TXBUF_1 (MCP_TXB1SIDH)
#define MCP_TXBUF_2 (MCP_TXB2SIDH)

#define MCP2515_OK         (0)
#define MCP2515_FAIL       (1)
#define MCP_ALLTXBUSY      (2)

typedef unsigned char u8;

#include "mbed.h"
#include "SPI.h"
class mcp2515  {
   SPI& spi;
    DigitalOut _ncs;
    //Serial&  console =0;
    bool    debug;
public:
    //  mcp2515(PinName mosi, PinName miso, PinName clk, PinName ncs);
    mcp2515(SPI& _spi, PinName ncs);
    // void setInterface(SPI& spi);
    // float read (void);
    // void setThigh (float);
    // void setTlow (float);
    // float getThigh (void);
    // float getTlow (void);
    void _reset();
    void    setRegister(  uint8_t address,   uint8_t value);
    
    uint8_t readRegister(  uint8_t address);
    void    modifyRegister(  uint8_t address,   uint8_t mask,   uint8_t data);
    uint8_t setCANCTRL_Mode(uint8_t newmode);
    uint8_t init(  int canSpeed);
    void    initCANBuffers(void);
    void    setRegisterS(  uint8_t address,   uint8_t values[],   uint8_t n);
    void    write_can_id(   uint8_t mcp_addr,   uint8_t ext,   uint32_t can_id );
    //

    void    readRegisterS(  uint8_t address, uint8_t values[],   uint8_t n);
    uint8_t readXXStatus_helper(  uint8_t cmd);
    uint8_t readStatus(void);
    uint8_t RXStatus(void);

    void read_can_id(   uint8_t mcp_addr, uint8_t* ext, uint32_t* can_id );
    void read_can_idN(   uint8_t mcp_addr, CANFormat* ext, unsigned int* can_id );
    void read_canMsg(   uint8_t buffer_sidh_addr, CANMessage* msg);
    void write_canMsg(   uint8_t buffer_sidh_addr,  CANMessage* msg);

    uint8_t getNextFreeTXBuf(uint8_t *txbuf_n);

    void start_transmit(  uint8_t buffer_sidh_addr);

    void dumpExtendedStatus(void);

    void setDebugConsole(Serial c);
    
    int configRate(int bit_rate);
 
    // Private functions
private :
    void _select (void);
    void _deselect (void);
    int status();
    void _pollbusy() ;

    uint8_t _spi_readwrite(uint8_t data);
    uint8_t _spi_read(void);
};

#endif // _MCP2515_H_
