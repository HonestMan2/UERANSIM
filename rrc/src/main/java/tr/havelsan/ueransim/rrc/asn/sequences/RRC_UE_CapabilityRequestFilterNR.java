/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.sequence_ofs.RRC_FreqBandList;

public class RRC_UE_CapabilityRequestFilterNR extends AsnSequence {
    public RRC_FreqBandList frequencyBandListFilter; // optional
    public RRC_UE_CapabilityRequestFilterNR_v1540 nonCriticalExtension; // optional
}

