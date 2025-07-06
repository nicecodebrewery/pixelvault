# 🖼️ PixelVault

**PixelVault** is a C++ command-line tool for hiding secret messages inside `.bmp` images using **Least Significant Bit (LSB)** steganography. It optionally integrates with encryption tools like [vencrypt](https://vijayskk.github.io/vencrypt/) to securely hide sensitive data (Coming soon).

---

## 🔧 Features

- Hide any text file inside a BMP image
- Extract hidden messages without image corruption
- Automatically removes intermediate files after use
- Clean, portable CLI interface
- Simple Makefile with install/uninstall support

---

##  Installation

### 1. Build from source

```bash
mkdir build
make
```
### Install globally
```bash
sudo make install
```
This will install the binary to /usr/local/bin/pixelvault.

#### To uninstall:
```bash
sudo make uninstall
```


## Usage

#### Encode
```bash
pixelvault encode <cover.bmp> <output.bmp> <secret.txt> 
```
Arguments:
- cover.bmp — the original BMP image
- output.bmp — the output image with secret data embedded
- secret.txt — text file containing your secret message


Example:
```bash
pixelvault encode cat.bmp hidden.bmp message.txt
```
#### Decode
```bash
pixelvault decode <stego.bmp> 
```
Arguments:
- stego.bmp — BMP image with hidden message

Example:
```bash
pixelvault decode hidden.bmp
```
Output is saved to decoded_secret.txt


## Project Structure
```bash
pixelvault/
├── scripts/
│   ├── encode.h          # LSB encoding/decoding logic
│   └── helpers.h         # BMP utilities and metadata
├── src/
│   └── main.cpp          # Command-line interface
├── Makefile              # Build and install system
├── README.md             # This file
```


### Requirements
- C++11 or later
- A POSIX-like system (Linux/macOS)
- make and g++


### License

View LICENSE file
