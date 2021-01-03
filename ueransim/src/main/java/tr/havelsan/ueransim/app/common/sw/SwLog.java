/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.app.common.sw;

import tr.havelsan.ueransim.utils.console.LogEntry;

import java.util.List;

public class SwLog extends SocketWrapper {
    public final List<LogEntry> data;

    public SwLog(List<LogEntry> data) {
        this.data = data;
    }
}
