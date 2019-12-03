package com.runsim.backend.nas.impl.values;

import com.runsim.backend.nas.core.NasValue;
import com.runsim.backend.utils.OctetInputStream;
import com.runsim.backend.utils.OctetOutputStream;
import com.runsim.backend.utils.octets.Octet;

public class VHomeNetworkPki extends NasValue {
    public Octet value;

    public VHomeNetworkPki() {
    }

    public VHomeNetworkPki(Octet value) {
        this.value = value;
    }

    public VHomeNetworkPki(int value) {
        this(new Octet(value));
    }

    public VHomeNetworkPki(String hex) {
        this(new Octet(hex));
    }

    @Override
    public VHomeNetworkPki decode(OctetInputStream stream) {
        var res = new VHomeNetworkPki();
        res.value = stream.readOctet();
        return res;
    }

    public boolean isReserved() {
        return value.intValue() == 0b11111111;
    }

    @Override
    public String toString() {
        return value.toString();
    }

    @Override
    public void encode(OctetOutputStream stream) {
        stream.writeOctet(value);
    }
}
