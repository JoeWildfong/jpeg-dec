# jpeg-dec

WIP JPEG decoder written in C++.  
Currently only targets JPEG's Sequential DCT-based mode. This is the most commonly used mode.

### TODO - Decoding:  
~~Decode JPEG markers~~ - Done  
~~Parse out Huffman tables from DHT fields~~ - Done  
~~Parse out quantization tables from DQT fields~~ - Done  
~~Parse out metadata from SOS and SOF tags~~ - Done  
Use decoded Huffman tables to decode bitstream.  
Decode DCT coefficients.  
Use decoded quantization tables to dequantize DCT coefficients.  
Implement inverse Discrete Cosine Transform algorithm.  
Convert YCrCb pixel format to RGB.  

### TODO - Performance and Maintenance:  
Stream file rather than storing it all in RAM during decoding.  
Refactor codebase to be more organized.  

### Potential future projects:  
Add support for other JPEG modes such as Progressive DCT, hierarchical or lossless.  
Write an encoder to go alongside the decoder.  
