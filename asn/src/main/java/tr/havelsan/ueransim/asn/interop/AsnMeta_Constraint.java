/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.asn.interop;

public class AsnMeta_Constraint {
    public int type;
    public boolean is_extensible;
    public int range_bits;
    public int effective_bits;
    public long lb;
    public long ub;
}
