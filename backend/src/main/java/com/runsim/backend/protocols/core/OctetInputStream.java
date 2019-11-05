package com.runsim.backend.protocols.core;

import com.runsim.backend.protocols.bits.Bit;
import com.runsim.backend.protocols.octets.Octet;
import com.runsim.backend.protocols.octets.Octet2;
import com.runsim.backend.protocols.octets.OctetString;

public class OctetInputStream {
    private final byte[] data;
    private final int length;
    private final boolean isBigEndian;
    private int index;

    public OctetInputStream(byte[] data, boolean isBigEndian) {
        this.data = data;
        this.length = data.length;
        this.index = 0;
        this.isBigEndian = true;
    }

    public OctetInputStream(byte[] data) {
        this(data, true);
    }

    /************ Peek Bit ************/

    public int peekBitI(int offset) {
        return peekOctetI(offset / 8) >> (offset % 8) & 1;
    }

    public int peekBitI() {
        return peekBitI(0);
    }

    public boolean peekBitB(int offset) {
        return peekBitI(offset) != 0;
    }

    public boolean peekBitB() {
        return peekBitB(0);
    }

    public Bit peekBit(int offset) {
        return new Bit(peekBitI(offset));
    }

    public Bit peekBit() {
        return peekBit(0);
    }

    /************ Peek Octet ************/

    public int peekOctetI(int offset) {
        return data[index + offset] & 0xFF;
    }

    public int peekOctetI() {
        return peekOctetI(0);
    }

    public Octet peekOctet(int offset) {
        return new Octet(peekOctetI(offset));
    }

    public Octet peekOctet() {
        return peekOctet(0);
    }

    /************ Peek Octet 2 ************/

    public int peekOctet2I(int offset) {
        int big = peekOctetI(isBigEndian ? offset : offset + 1);
        int little = peekOctetI(isBigEndian ? offset + 1 : offset);
        return (big << 8) | little;
    }

    public int peekOctet2I() {
        return peekOctet2I(0);
    }

    public Octet2 peekOctet2(int offset) {
        return new Octet2(peekOctet2I(offset));
    }

    public Octet2 peekOctet2() {
        return peekOctet2(0);
    }

    /************ Peek Octet Array ************/

    public int[] peekOctetArrayI(int offset, int length) {
        int[] res = new int[length];
        for (int i = 0; i < length; i++)
            res[i] = peekOctetI(offset + i);
        return res;
    }

    public Octet[] peekOctetArray(int offset, int length) {
        Octet[] res = new Octet[length];
        for (int i = 0; i < length; i++)
            res[i] = peekOctet(offset + i);
        return res;
    }

    public OctetString peekOctetString(int offset, int length) {
        return new OctetString(peekOctetArray(offset, length));
    }

    public OctetString peekOctetString(int length) {
        return new OctetString(peekOctetArray(0, length));
    }

    /************ Read Octet Array ************/
    public int[] readOctetArrayI(int offset, int length) {
        int[] res = new int[length];
        for (int i = 0; i < length; i++)
            res[i] = readOctetI(offset + i);
        return res;
    }

    public Octet[] readOctetArray(int offset, int length) {
        Octet[] res = new Octet[length];
        for (int i = 0; i < length; i++)
            res[i] = readOctet(offset + i);
        return res;
    }

    public OctetString readOctetString(int offset, int length) {
        return new OctetString(readOctetArray(offset, length));
    }

    public OctetString readOctetString(int length) {
        return readOctetString(0, length);
    }

    /************ Read Octet ************/

    public int readOctetI(int offset) {
        int res = data[index + offset] & 0xFF;
        index++;
        return res;
    }

    public int readOctetI() {
        return readOctetI(0);
    }

    public Octet readOctet(int offset) {
        return new Octet(readOctetI(offset));
    }

    public Octet readOctet() {
        return new Octet(readOctetI());
    }

    /************ Read Octet 2 ************/

    public int readOctet2I(int offset) {
        int big = readOctetI(isBigEndian ? offset : offset + 1);
        int little = readOctetI(isBigEndian ? offset + 1 : offset);
        return (big << 8) | little;
    }

    public int readOctet2I() {
        return readOctet2I(0);
    }

    public Octet2 readOctet2(int offset) {
        return new Octet2(readOctet2I(offset));
    }

    public Octet2 readOctet2() {
        return readOctet2(0);
    }

    /************ Others ************/

    public boolean hasNext() {
        return index < length;
    }
}
