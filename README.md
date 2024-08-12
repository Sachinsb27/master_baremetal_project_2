Project Overview
This project was developed as part of a hackathon challenge, focusing on interfacing an LDR with an embedded system and utilizing UART communication to report light intensity levels.

Problem Statement

The task involves:

-Connecting an LDR to the analog pin P2.1.

-Configuring P2.1 as an analog input.

-Initializing the UART peripheral for communication, with P7.1 as UART TX and P7.0 as UART RX.

-Setting up the ADC peripheral to deliver a 12-bit output with a sampling frequency of 1 MHz.

-Implementing continuous ADC conversion using the polling method.

-The requirements are:

Print the message "Value Greater than 1.5V observed" on the UART channel if the ADC value corresponds to a voltage greater than 1.5V.

Do nothing if the ADC value is less than or equal to 1.5V.

This implementation considers the following:

0V produces an ADC result of 0.

5V produces an ADC result of 4095.

The actual voltage (V) is calculated as:

V = ADC_Result * (5 / 4096).
