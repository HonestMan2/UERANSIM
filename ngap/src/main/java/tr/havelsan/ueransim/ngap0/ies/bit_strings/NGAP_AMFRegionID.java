/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.ngap0.ies.bit_strings;

import tr.havelsan.ueransim.ngap0.core.NGAP_BitString;
import tr.havelsan.ueransim.utils.bits.BitString;
import tr.havelsan.ueransim.utils.octets.Octet;
import tr.havelsan.ueransim.utils.octets.OctetString;

public class NGAP_AMFRegionID extends NGAP_BitString {

    public NGAP_AMFRegionID(BitString value) {
        super(value);
    }

    public NGAP_AMFRegionID(OctetString octetString, int bitLength) {
        super(octetString, bitLength);
    }

    public NGAP_AMFRegionID(OctetString octetString) {
        super(octetString);
    }

    public NGAP_AMFRegionID(Octet[] octets, int bitLength) {
        super(octets, bitLength);
    }

    public NGAP_AMFRegionID(Octet[] octets) {
        super(octets);
    }

    public NGAP_AMFRegionID(byte[] octets, int bitLength) {
        super(octets, bitLength);
    }

    public NGAP_AMFRegionID(byte[] octets) {
        super(octets);
    }

    public NGAP_AMFRegionID(String hex, int bitLength) {
        super(hex, bitLength);
    }

    public NGAP_AMFRegionID(String bits) {
        super(bits);
    }

    @Override
    public String getAsnName() {
        return "AMFRegionID";
    }

    @Override
    public String getXmlTagName() {
        return "AMFRegionID";
    }
}
