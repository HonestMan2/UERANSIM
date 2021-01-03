/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.ngap0.ies.sequences;

import tr.havelsan.ueransim.ngap0.core.NGAP_Sequence;
import tr.havelsan.ueransim.ngap0.ies.sequence_ofs.NGAP_QoSFlowsUsageReportList;

public class NGAP_SecondaryRATUsageInformation extends NGAP_Sequence {

    public NGAP_PDUSessionUsageReport pDUSessionUsageReport;
    public NGAP_QoSFlowsUsageReportList qosFlowsUsageReportList;

    @Override
    public String getAsnName() {
        return "SecondaryRATUsageInformation";
    }

    @Override
    public String getXmlTagName() {
        return "SecondaryRATUsageInformation";
    }

    @Override
    public String[] getMemberNames() {
        return new String[]{"pDUSessionUsageReport", "qosFlowsUsageReportList"};
    }

    @Override
    public String[] getMemberIdentifiers() {
        return new String[]{"pDUSessionUsageReport", "qosFlowsUsageReportList"};
    }
}
