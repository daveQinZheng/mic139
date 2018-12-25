
enum radioxxPacketProperty {
    //% blockIdentity=radioxx._packetProperty
    //% block="signal strength"
    SignalStrength = 2,
    //% blockIdentity=radioxx._packetProperty
    //% block="time"
    Time = 0,
    //% block="serial number"
    //% blockIdentity=radioxx._packetProperty
    SerialNumber = 1
}

/**
 * Communicate data using radioxx packets
 */
//% color=#E3008C weight=96 icon="\uf012"
namespace radioxx {
    export class Packet {
        /**
         * The number payload if a number was sent in this packet (via ``sendNumber()`` or ``sendValue()``)
         * or 0 if this packet did not contain a number.
         */
        public receivedNumber: number;
        /**
         * The string payload if a string was sent in this packet (via ``sendString()`` or ``sendValue()``)
         * or the empty string if this packet did not contain a string.
         */
        public receivedString: string;
        /**
         * The buffer payload if a buffer was sent in this packet
         * or the empty buffer
         */
        
        /**
         * The system time of the sender of the packet at the time the packet was sent.
         */
        public time: number;
        /**
         * The serial number of the sender of the packet or 0 if the sender did not sent their serial number.
         */
        public serial: number;
        /**
         * The received signal strength indicator (RSSI) of the packet.
         */
        public signal: number;
    }


    let lastPacket: Packet;
    /**
     * Returns properties of the last radioxx packet received.
     * @param type the type of property to retrieve from the last packet
     */
    //% help=radioxx/received-packet
    //% weight=11 blockGap=8
    //% blockId=radioxx_received_packet block="received packet %type=radioxx_packet_property" blockGap=16
    export function receivedPacket(type: number) {
        if (lastPacket) {
            switch(type) {
                case radioxxPacketProperty.Time: return lastPacket.time;
                case radioxxPacketProperty.SerialNumber: return lastPacket.serial;
                case radioxxPacketProperty.SignalStrength: return lastPacket.signal;
            }
        }
        return 0;
    }

    /**
     * Gets a packet property.
     * @param type the packet property type, eg: PacketProperty.time
     */
    //% blockId=radioxx_packet_property block="%note"
    //% shim=TD_ID blockHidden=1
    export function _packetProperty(type: radioxxPacketProperty): number {
        return type;
    }
}
