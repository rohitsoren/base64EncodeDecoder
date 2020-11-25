# base64EncodeDecoder
Base64 encoder and decoder program in c++

Base64 is binary to text encoding scheme which can be used to reliably transfer binary data in the network as particular set of 64 characters.

This program as two APIs
1. encodeBase64
  - This API will convert binary data input to base64 encoded output
2. decodeBase64
  - This API will convert base64 encoded input to binary data.

Note: Currently in the both above API binary input is not supported, but can be easily changed by passing binary input/ouput as vector<uint8_t> to support binary data
