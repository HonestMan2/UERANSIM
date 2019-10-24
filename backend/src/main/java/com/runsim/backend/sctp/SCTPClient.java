package com.runsim.backend.sctp;

import com.sun.nio.sctp.MessageInfo;
import com.sun.nio.sctp.SctpChannel;

import java.net.InetSocketAddress;
import java.nio.ByteBuffer;

public class SCTPClient {
    private static final int RECEIVER_BUFFER_SIZE = 1073741824;

    private final String host;
    private final int port;
    private final int protocolId;

    private SctpChannel channel;
    private AssociationHandler associationHandler;

    public SCTPClient(String host, int port, int protocolId) {
        this.host = host;
        this.port = port;
        this.protocolId = protocolId;
    }

    public void start() throws Exception {
        if (this.channel != null) throw new RuntimeException("start was already called");
        var serverAddress = new InetSocketAddress(host, port);
        this.channel = SctpChannel.open(serverAddress, 0, 0);
        this.associationHandler = new AssociationHandler();
    }

    public void send(int streamNumber, byte[] data) throws Exception {
        ByteBuffer outgoingBuffer = ByteBuffer.wrap(data);
        MessageInfo outgoingMessage = MessageInfo.createOutgoing(null, streamNumber);
        outgoingMessage.payloadProtocolID(protocolId);
        channel.send(outgoingBuffer, outgoingMessage);
    }

    public void receiverLoop(ISCTPHandler handler) throws Exception {
        ByteBuffer incomingBuffer = ByteBuffer.allocate(RECEIVER_BUFFER_SIZE);

        MessageInfo messageInfo;
        while (channel.isOpen()) {
            messageInfo = channel.receive(incomingBuffer, System.out, associationHandler);
            if (messageInfo == null || messageInfo.bytes() == -1) break;

            byte[] receivedBytes = new byte[messageInfo.bytes()];
            for (int i = 0; i < receivedBytes.length; i++) {
                receivedBytes[i] = incomingBuffer.get(i);
            }
            handler.handleSCTPMessage(receivedBytes, messageInfo, channel);
        }

        channel.close();
    }
}
