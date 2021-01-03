/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.ngap0.ies.sequences;

import tr.havelsan.ueransim.ngap0.core.NGAP_Sequence;
import tr.havelsan.ueransim.ngap0.ies.integers.NGAP_E_RAB_ID;
import tr.havelsan.ueransim.ngap0.ies.integers.NGAP_QosFlowIdentifier;

public class NGAP_QosFlowAddOrModifyRequestItem extends NGAP_Sequence {

    public NGAP_QosFlowIdentifier qosFlowIdentifier;
    public NGAP_QosFlowLevelQosParameters qosFlowLevelQosParameters;
    public NGAP_E_RAB_ID e_RAB_ID;

    @Override
    public String getAsnName() {
        return "QosFlowAddOrModifyRequestItem";
    }

    @Override
    public String getXmlTagName() {
        return "QosFlowAddOrModifyRequestItem";
    }

    @Override
    public String[] getMemberNames() {
        return new String[]{"qosFlowIdentifier", "qosFlowLevelQosParameters", "e-RAB-ID"};
    }

    @Override
    public String[] getMemberIdentifiers() {
        return new String[]{"qosFlowIdentifier", "qosFlowLevelQosParameters", "e_RAB_ID"};
    }
}
