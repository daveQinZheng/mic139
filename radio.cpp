#include "pxt.h"

using namespace pxt;

#define MAX_FIELD_NAME_LENGTH 12
#define MAX_FIELD_DOUBLE_NAME_LENGTH 8
#define MAX_PAYLOAD_LENGTH 20
#define PACKET_PREFIX_LENGTH 9
#define VALUE_PACKET_NAME_LEN_OFFSET 13
#define DOUBLE_VALUE_PACKET_NAME_LEN_OFFSET 17


// Packet Spec:
// | 0              | 1 ... 4       | 5 ... 8           | 9 ... 28
// ----------------------------------------------------------------
// | packet type    | system time   | serial number     | payload
//
// Serial number defaults to 0 unless enabled by user

// payload: number (9 ... 12)
#define PACKET_TYPE_NUMBER 0

// payload: number (9 ... 12), name length (13), name (14 ... 26)
#define PACKET_TYPE_VALUE 1

// payload: string length (9), string (10 ... 28)
#define PACKET_TYPE_STRING 2

// payload: buffer length (9), buffer (10 ... 28)
#define PACKET_TYPE_BUFFER 3

// payload: number (9 ... 16)
#define PACKET_TYPE_DOUBLE 4

// payload: number (9 ... 16), name length (17), name (18 ... 26)
#define PACKET_TYPE_DOUBLE_VALUE 5

//% color=#E3008C weight=96 icon="\uf012"
namespace radioxx {

    // -------------------------------------------------------------------------
    // radioxx
    // -------------------------------------------------------------------------
    bool radioxxEnabled = false;
    bool transmitSerialNumber = false;

    PacketBuffer packet;

    uint8_t type;
    uint32_t time;
    uint32_t serial;
    int ivalue;
    double dvalue;
    String msg; // may be NULL before first packet
    Buffer bufMsg; // may be NULL before first packet

    int radioxxEnable() {
        int r = uBit.radio.enable();
        if (r != MICROBIT_OK) {
            uBit.panic(43);
            return r;
        }
        if (!radioxxEnabled) {
            uBit.radio.setGroup(pxt::programHash());
            uBit.radio.setTransmitPower(6); // start with high power by default
            radioxxEnabled = true;
        }
        return r;
    }

   
    /**
     * Change the output power level of the transmitter to the given value.
    * @param power a value in the range 0..7, where 0 is the lowest power and 7 is the highest. eg: 7
    */
    //% help=radioxx/set-transmit-power
    //% weight=9 blockGap=8
    //% blockId=radioxx_set_transmit_power block="radioxx set transmit power %power"
    //% power.min=0 power.max=7
    //% advanced=true
    void setTransmitPower(int power) {
        if (radioxxEnable() != MICROBIT_OK) return;
        uBit.radio.setTransmitPower(power);
    }

}
