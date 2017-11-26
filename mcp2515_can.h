#ifndef MCP2515_CAN_H_
#define MCP2515_CAN_H_

#define CANUSELOOP 0

#define CANSENDTIMEOUT (200) /* milliseconds */

// initial value of gCANAutoProcess
#define CANAUTOPROCESS (1)
#define CANAUTOON  (1)
#define CANAUTOOFF (0)

#define CAN_STDID (0)
#define CAN_EXTID (1)

#define CANDEFAULTIDENT    (0x55CC)
#define CANDEFAULTIDENTEXT (CAN_EXTID)

#define CAN_OK         (0)
#define CAN_FAILINIT   (1)
#define CAN_FAILTX     (2)
#define CAN_MSGAVAIL   (3)
#define CAN_NOMSG      (4)
#define CAN_CTRLERROR  (5)
#define CAN_FAIL       (0xff)

#define CAN_MAX_CHAR_IN_MESSAGE (8)


#endif
