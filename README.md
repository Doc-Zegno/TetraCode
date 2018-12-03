# TetraCode
Core and infrastructure for TetraCode utility.
Starting with version 0.1.0, it's fully OOP!

![Example of TetraCode](https://i.imgur.com/eG1qclM.png)

*Encoded phrase "TetraCode Utility by Handmada" (UTF-8)*



## Project Status
### TODO List
- [x] Core: TetraTree, byte sequence Encoder/Decoder
- [x] Iterator and Scrambler interfaces
- [x] MatrixView and Converter interfaces
- [ ] Specifications for scramblers and converters
- [x] Cross-platform image library integration
- [x] Make support
- [x] Remove input text size limitations


### Version 0.1.0 is finally released!
Project specifications are rather unstable now though
so compatibility with either future or previous versions is not guaranteed



## Prerequisites
### Windows
You need VS 2017 on board


### Unix
You need Clang with support for C++17 standard.
Clang-6.0 should be sufficient



## How to use
### Windows
Download all files from this repository,
open and build project within `TetraCodeProject/` folder.

Resulting `.exe` file can be found within nested `Release/` folder.

To encode text from file `input.txt` and save the resulting image
to file `output.png` enter the following into Command Prompt:
```
.\TetraCodeProject.exe input.txt output.png
```

In order to decode text from image use:
```
.\TetraCodeProject.exe image.png output.txt
```


### Unix
Run Make from root directory:
```
make
```

When it's done, go to `Build/` directory.

To encode text from file `input.txt` and save the resulting image
to file `output.png` enter the following into Terminal:
```
./TetraCode input.txt output.png
```

In order to decode text from image use:
```
./TetraCode image.png output.txt
```


### Possible troubleshooting
* Make sure input text file has a `.txt` extension otherwise it won't be
  recognized by a program
* The only supported image extension is `.png`
* Program knows nothing about encoding of text file
  since it treats the file like a byte sequence. Users are responsible for
  setting the same encoding of both input and output text files



## License
You can do what the fuck you want with this program
  
