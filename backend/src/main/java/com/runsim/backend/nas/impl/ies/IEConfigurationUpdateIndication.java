package com.runsim.backend.nas.impl.ies;

import com.runsim.backend.nas.core.ProtocolEnum;
import com.runsim.backend.nas.core.ies.InformationElement1;
import com.runsim.backend.utils.bits.Bit4;

public class IEConfigurationUpdateIndication extends InformationElement1 {
    public EAcknowledgement ack;
    public ERegistrationRequested red;

    @Override
    public IEConfigurationUpdateIndication decodeIE1(Bit4 value) {
        var res = new IEConfigurationUpdateIndication();
        res.ack = EAcknowledgement.fromValue(value.getBitI(0));
        res.red = ERegistrationRequested.fromValue(value.getBitI(1));
        return res;
    }

    @Override
    public int encodeIE1() {
        return red.intValue() << 1 | ack.intValue();
    }

    public static class EAcknowledgement extends ProtocolEnum {
        public static final EAcknowledgement NOT_REQUESTED
                = new EAcknowledgement(0b0, "acknowledgement not requested");
        public static final EAcknowledgement REQUESTED
                = new EAcknowledgement(0b1, "acknowledgement requested");

        private EAcknowledgement(int value, String name) {
            super(value, name);
        }

        public static EAcknowledgement fromValue(int value) {
            return fromValueGeneric(EAcknowledgement.class, value);
        }
    }

    public static class ERegistrationRequested extends ProtocolEnum {
        public static final ERegistrationRequested NOT_REQUESTED
                = new ERegistrationRequested(0b0, "registration not requested");
        public static final ERegistrationRequested REQUESTED
                = new ERegistrationRequested(0b1, "registration requested");

        private ERegistrationRequested(int value, String name) {
            super(value, name);
        }

        public static ERegistrationRequested fromValue(int value) {
            return fromValueGeneric(ERegistrationRequested.class, value);
        }
    }
}
