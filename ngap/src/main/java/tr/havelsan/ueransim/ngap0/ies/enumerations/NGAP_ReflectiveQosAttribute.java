/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.ngap0.ies.enumerations;

import tr.havelsan.ueransim.ngap0.core.NGAP_Enumerated;

public class NGAP_ReflectiveQosAttribute extends NGAP_Enumerated {

    public static final NGAP_ReflectiveQosAttribute SUBJECT_TO = new NGAP_ReflectiveQosAttribute("subject-to");

    protected NGAP_ReflectiveQosAttribute(String sValue) {
        super(sValue);
    }

    @Override
    public String getAsnName() {
        return "ReflectiveQosAttribute";
    }

    @Override
    public String getXmlTagName() {
        return "ReflectiveQosAttribute";
    }
}
