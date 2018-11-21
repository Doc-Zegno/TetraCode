# TetraCode
Core and infrastructure for TetraCode utility.
Starting with version 0.1.0, it's fully OOP!

![Example of TetraCode](https://i.imgur.com/lMgDldR.png)

*Encoded phrase "TetraCode Utility by Handmada" (UTF-8)*



## Project Status
### TODO List
- [x] Core: TetraTree, byte sequence Encoder/Decoder
- [x] Iterator and Scrambler interfaces
- [x] MatrixView and Converter interfaces
- [ ] Specifications for scramblers and converters
- [ ] Cross-platform image library integration
- [ ] CMake support
- [x] Remove input text size limitations


### Version 0.1.0 is finally released!
Project specifications are rather unstable now though
so compatibility with either future or previous versions is not guaranteed



## Prerequisites
For now package is available only for Windows users with VS 2017 on board



## How to use
### Windows
Download all files from this repository,
open and build project within `TetraCodeProject` folder.

To encode text from file `input.txt` and save the resulting image
to file `output.png` enter the following into Command Prompt:
```
.\TetraCodeProject.exe input.txt output.png
```

In order to decode text from image use:
```
.\TetraCodeProject.exe image.png output.txt
```


### Possible troubleshooting
* Make sure input text file has a `.txt` extension otherwise it won't be
  recognized by a program
* Recommended image extensions are `.png` and `.jpg`
* Program knows nothing about encoding of text file
  since it treats the file like a byte sequence. Users are responsible for
  setting the same encoding of both input and output text files



## License
You can do what the fuck you want with this program
  
