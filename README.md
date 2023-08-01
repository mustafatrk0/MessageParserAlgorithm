# MessageParserAlgorithm
# USART Message Parser for STM32F Series MCU
This ReadMe file provides an overview and usage guidelines for the USART Message Parser developed for the STM32F series microcontroller using either KEIL or STMCubeIDE environments. The parser is designed to handle messages in the format specified in the table below, receiving and responding to messages with the same structure, while ignoring messages with incorrect formats and generating error codes.

# Message Format
The messages received and processed by the parser should adhere to the following structure:

```cpp
£[Emir No][Emir Adresi][Data Bloğu]%
```
Explanation of message components:

`£`: Start of the message delimiter. <br>
`[Emir No]`: Command number assigned by the master. This will be used by the slave unit in its response to reference the corresponding command.<br>
`[Emir Adresi]`: Address of the command, representing a list of variables running in the main program. For example, an address of `0x00000012` might be related to the Timer 1 counter value.<br>
`[Data Bloğu]`: Data block that may contain relevant information, such as the value to be written to Timer 1 counter or the value read from it.<br>
`%`: End of the message delimiter.<br>

![image](https://github.com/mustafatrk0/MessageParserAlgorithm/assets/66215069/6b115c5b-20ea-4773-b78b-cc280ef883c2)

## Parser Implementation Details
* The parser must be developed as a 15-byte algorithm, capable of processing messages with the specified format.
* The message content should be stored in a global area to be accessible and used by the parser.
* A suitable data structure (e.g., `struct`, `union`, vector) should be defined in a header file to hold the message content, and the purpose of each member should be clearly explained.
* The command number (`Emir No`) should be set by the master and later utilized by the slave unit in its response.
* The parser should count all incoming messages, both correct and incorrect, and prevent the entry of incorrect messages into the system.
* Necessary error definitions should be made to handle possible parser errors effectively.

## Conclusion
The USART Message Parser presented in this ReadMe provides a structured approach to handle incoming messages with specified formats in STM32F series MCU projects. By following the guidelines and implementing the parser, you can achieve efficient and error-resistant message processing for your embedded system.

Note: This ReadMe assumes that the parser implementation details and functions are provided in separate files, such as `parser.c` and `parser.h` , to maintain code modularity and organization.
