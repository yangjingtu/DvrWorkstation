/* ****************************************************************** */
/*                            UartHost.h                              */
/* ****************************************************************** */

#ifndef _UARTHOST_H_
#define _UARTHOST_H_


#include <windows.h>
#include <conio.h>
#include "iostream.h"

#include "Api_def.h"

#define COMMENT_STRING  "//"
#define MAX_PACKET_SIZE 66

//
// Packet header types.
//
#define NO_DATA_PACKET           0x00
#define COMMAND_HEADER           0x01
#define DATA_HEADER              0x02
#define LAST_COMMAND_HEADER      0x03
#define LAST_DATA_HEADER         0x04
#define SYNC_HEADER              0x43
#define HOST_ACK_HEADER          0x54
#define I43_ACK_HEADER           0x54

#define PACKET_HEADER_SIZE       0x02



#endif // _UARTHOST_H_


