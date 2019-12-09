package com.runsim.backend.nas.impl.ies;

import com.runsim.backend.nas.core.ies.InformationElement3;
import com.runsim.backend.utils.OctetInputStream;
import com.runsim.backend.utils.OctetOutputStream;
import com.runsim.backend.utils.octets.OctetString;

public class IEAuthenticationParameterRand extends InformationElement3 {
    public OctetString value;

    public IEAuthenticationParameterRand() {
    }

    public IEAuthenticationParameterRand(OctetString value) {
        this.value = value;
    }

    @Override
    protected InformationElement3 decodeIE3(OctetInputStream stream) {
        var res = new IEAuthenticationParameterRand();
        res.value = stream.readOctetString(16);
        return res;
    }

    @Override
    public void encodeIE3(OctetOutputStream stream) {
        stream.writeOctetString(value);
    }
}