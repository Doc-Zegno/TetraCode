# TetraCode
Core and infrastructure for TetraCode utility

![Example of TetraCode](https://i.imgur.com/XQp5HHn.png)

*Encoded phrase "TetraCode Utility by Handmada"*

## Project Status
- [x] Core: TetraTree, byte sequence Encoder/Decoder
- [ ] String-to-Byte (and vice versa) Interpreter with UTF-8 support
- [ ] Iterator and Scrambler interfaces
- [ ] Cross-platform image library integration
- [ ] CMake support
- [ ] Remove input text size limitations

## Prerequisites
For now package is available only for Windows users with VS 2017 on board

## How to use
### Windows
Open and build project within `TetraCodeProject` folder.

To encode ASCII text from file `input.txt` and save the resulting image
to file `output.png` enter the following into Command Prompt:
```
.\TetraCodeProject.exe < input.txt output.png
```

In order to decode text from image use:
```
.\TetraCodeProject.exe > output.txt image.png -d
```
