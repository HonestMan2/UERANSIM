/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.app.l2.rlc.entity;

import tr.havelsan.ueransim.utils.octets.OctetString;

public class UmEntity extends RlcEntity {

    @Override
    public OctetString createPdu(OctetString sdu) {
        return null;
    }

    @Override
    public void receivePdu(OctetString data) {

    }

    @Override
    public void receiveSdu(OctetString data) {

    }
}
