/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.app.common.enums;

public enum EMmSubState {
    MM_NULL__NA,

    MM_DEREGISTERED__NA,
    MM_DEREGISTERED__NORMAL_SERVICE,
    MM_DEREGISTERED__LIMITED_SERVICE,
    MM_DEREGISTERED__ATTEMPTING_REGISTRATION,
    MM_DEREGISTERED__PLMN_SEARCH,
    MM_DEREGISTERED__NO_SUPI,
    MM_DEREGISTERED__NO_CELL_AVAILABLE,
    MM_DEREGISTERED__ECALL_INACTIVE,
    MM_DEREGISTERED__INITIAL_REGISTRATION_NEEDED,

    MM_REGISTERED_INITIATED__NA,

    MM_REGISTERED__NA,
    MM_REGISTERED__NORMAL_SERVICE,
    MM_REGISTERED__NON_ALLOWED_SERVICE,
    MM_REGISTERED__ATTEMPTING_REGISTRATION_UPDATE,
    MM_REGISTERED__LIMITED_SERVICE,
    MM_REGISTERED__PLMN_SEARCH,
    MM_REGISTERED__NO_CELL_AVAILABLE,
    MM_REGISTERED__UPDATE_NEEDED,

    MM_DEREGISTERED_INITIATED__NA,

    MM_SERVICE_REQUEST_INITIATED__NA;
}
