/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnEnumerated;
import tr.havelsan.ueransim.asn.core.AsnSequence;

public class RRC_MeasAndMobParametersMRDC_XDD_Diff_v1560 extends AsnSequence {
    public RRC_sftd_MeasPSCell_NEDC sftd_MeasPSCell_NEDC; // optional

    public static class RRC_sftd_MeasPSCell_NEDC extends AsnEnumerated {
        public static final RRC_sftd_MeasPSCell_NEDC SUPPORTED = new RRC_sftd_MeasPSCell_NEDC(0);
    
        private RRC_sftd_MeasPSCell_NEDC(long value) {
            super(value);
        }
    }
}

