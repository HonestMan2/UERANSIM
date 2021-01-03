/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.rrc.asn.bit_strings;

import tr.havelsan.ueransim.asn.core.AsnBitString;
import tr.havelsan.ueransim.utils.bits.BitString;

// SIZE(24)
public class RRC_ShortI_RNTI_Value extends AsnBitString {
    public RRC_ShortI_RNTI_Value() {
    }
    
    public RRC_ShortI_RNTI_Value(BitString value) {
        super(value);
    }
}

