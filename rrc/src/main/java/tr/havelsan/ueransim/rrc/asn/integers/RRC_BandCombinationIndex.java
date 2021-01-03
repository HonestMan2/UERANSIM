/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.rrc.asn.integers;

import tr.havelsan.ueransim.asn.core.AsnInteger;

// VALUE(1..65536)
public class RRC_BandCombinationIndex extends AsnInteger {
    public RRC_BandCombinationIndex() {
    }
    
    public RRC_BandCombinationIndex(long value) {
        super(value);
    }
}

