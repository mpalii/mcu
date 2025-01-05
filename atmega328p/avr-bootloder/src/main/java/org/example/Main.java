package org.example;

import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortList;
import jssc.SerialPortTimeoutException;
import lombok.extern.slf4j.Slf4j;

import java.util.stream.Stream;

@Slf4j
public class Main {

    private static final int BAUD_RATE = 9600;
    private static final int DATA_BITS = 8;
    private static final int STOP_BITS = 1;
    private static final int PARITY = 0;

    private static boolean result = false;
    private static byte[] response = null;

    public static void main(String[] args) throws SerialPortException, SerialPortTimeoutException, InterruptedException {
        // See the list of available devices
        String[] portNames = SerialPortList.getPortNames();
        Stream.of(portNames).forEach(System.out::println);

        // Open port
        SerialPort serialPort = new SerialPort("/dev/ttyUSB0");

        boolean openPortStatus = serialPort.openPort();
        log.info("Serial port opened");

        boolean parametersStatus = serialPort.setParams(BAUD_RATE, DATA_BITS, STOP_BITS, PARITY);
        log.info("Serial configuration: baud rate {}, frame size {}, stop bits {}, parity {}",
                BAUD_RATE, DATA_BITS, STOP_BITS, PARITY);

        // Read $ACK
        String check = serialPort.readString(4, 15000);
        log.info("{}", check);

        // Artificial delay
        Thread.sleep(1000);

        // Write command #1
        result = serialPort.writeByte((byte) 32);
        log.info("{}", result);

        // Read response #1
        response = serialPort.readBytes(1, 1000);
        log.info("{}", (char) response[0]);

        //================================================================

        // Write command #2
        result = serialPort.writeByte((byte) 'e');
        log.info("{}", result);

        // Artificial delay
        Thread.sleep(1000);

        // Write command #3
        result = serialPort.writeByte((byte) 'd');
        log.info("{}", result);

        // Artificial delay
        Thread.sleep(1000);

        //================================================================

        // Write command #4
        result = serialPort.writeByte((byte) 'e');
        log.info("{}", result);

        // Artificial delay
        Thread.sleep(1000);

        // Write command #5
        result = serialPort.writeByte((byte) 'd');
        log.info("{}", result);

        // Close port
        result = serialPort.closePort();
        log.info("{}", result);
    }
}