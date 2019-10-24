package com.runsim.backend;

import com.runsim.backend.sctp.SCTPClient;
import com.runsim.backend.utils.Utils;
import com.sun.nio.sctp.MessageInfo;
import com.sun.nio.sctp.SctpChannel;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@BaseFlow.Flow
public abstract class BaseFlow {
    private SCTPClient sctpClient;
    private boolean started;
    private int streamNumber;
    private State currentState;

    protected final void sendData(byte[] data) {
        try {
            sctpClient.send(this.streamNumber, data);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    protected final void sendData(int... data) {
        byte[] bytes = new byte[data.length];
        for (int i = 0; i < data.length; i++)
            bytes[i] = (byte) data[i];
        sendData(bytes);
    }

    protected final void sendBase16(String hexString) {
        sendData(Utils.hexStringToByteArray(hexString));
    }

    public final void start() throws Exception {
        if (started) throw new RuntimeException("already started");

        this.started = true;
        this.streamNumber = Constants.DEFAULT_STREAM_NUMBER;
        this.sctpClient = new SCTPClient(Constants.AMF_HOST, Constants.AMF_PORT, Constants.NGAP_PROTOCOL_ID);
        this.sctpClient.start();
        this.currentState = main(null);
        this.sctpClient.receiverLoop(this::handleSCTPMessage);
    }

    private void handleSCTPMessage(byte[] receivedBytes, MessageInfo messageInfo, SctpChannel channel) {
        var message = new Message(receivedBytes, messageInfo.streamNumber());
        this.currentState = this.currentState.accept(message);
    }

    public abstract State main(Message message);

    @FunctionalInterface
    protected interface State {
        State accept(Message message);
    }

    @Retention(RetentionPolicy.RUNTIME)
    public @interface Flow {

    }
}
