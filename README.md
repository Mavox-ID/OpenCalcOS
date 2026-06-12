# OpenCalcOS

[![Build OCOS](https://github.com/Mavox-ID/OpenCalcOS/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/Mavox-ID/OpenCalcOS/actions/workflows/build.yml)
[![Latest Release](https://img.shields.io/github/v/release/Mavox-ID/OpenCalcOS?color=blue)](https://github.com/Mavox-ID/OpenCalcOS/releases)
[![Downloads](https://img.shields.io/github/downloads/Mavox-ID/OpenCalcOS/total?color=brightgreen)](https://github.com/Mavox-ID/OpenCalcOS/releases)
[![Repo Size](https://img.shields.io/github/repo-size/Mavox-ID/OpenCalcOS?color=orange)](https://github.com/Mavox-ID/OpenCalcOS)

Have a TI-NSPIRE CX? Why not use it for Beep?

OpenCalcOS is a complete, all-in-one toolkit designed to turn your TI-Nspire CX calculator into a fully working Beep machine. It features a cloned and slightly modified Beep port tailored for the calculator, integrated BusyBox for ARM, a custom temporary file system (CalcFS), a dedicated bootloader, and a ready-to-use Ndless toolkit for jailbreaking any version of the TI-Nspire CX.

## Features

* **Beep (`zCalc.tns`)**: A modified Beep kernel optimized specifically for the TI-Nspire CX architecture.
* **CalcFS (`CalcFS.tns`)**: A custom, temporary file system packed with a ready-to-build **BusyBox**, providing a full suite of POSIX commands.
* **Custom Loader (`Loader.tns`)**: A smart bootloader that prepares the environment, maps memory addresses, unpacks the file system, and safely boots the kernel.
* **Integrated Ndless**: Comes with a fully automated build environment for Ndless, allowing you to easily jailbreak your calculator and run unofficial compiled `.tns` packages.

## Build Instructions

### Prerequisites
Ensure you have **GCC version 13 or 14** installed on your system. Modern GCC versions (like GCC 15/16) may cause compilation conflicts with the older toolchain components. You may need to export the correct compiler version before building:

```bash
export CC=gcc-13
export CXX=g++-13

```

OR

```bash
export CC=gcc-14
export CXX=g++-14

```

### Compiling from Source

The build system is fully automated. **Do not** run individual subscripts (e.g., `busybox.sh`, `kernel.sh`, etc.) separately from the root directory, as they depend on core environment variables. (However, if you only want to build one thing or if you encounter a problem at any step, create an Issue and build the specific component with output. Example with BusyBox: `cd tools && bash busybox.sh`)

```bash
# 1. Clone the repository
git clone https://github.com/Mavox-ID/OpenCalcOS.git
cd OpenCalcOS

# 2. Unpack the calcfs folder
unzip calcfs.zip

# 3. Start the automated build process
bash build.sh

```

If you need to perform a clean build, use the dedicated clean script located in the tools directory:

```bash
cd tools
bash clean.sh
cd ..

```

Once the build is successful, a new `build/` directory will be created. This folder will contain all the `.tns` files needed for your calculator.

## Installation & Usage

### Step 1: Jailbreak with Ndless

Ndless is required to jailbreak the calculator's firmware so it can run unofficial compiled `.tns` packages (like Beep and Loader).

1. Navigate to the compiled `build/NDless` folder.
2. Find the Ndless installer file that matches your calculator's exact firmware version.
3. Transfer this file anywhere on your calculator and run it.
4. Upon success, Ndless will be active in the background.

### Step 2: Transfer OpenCalcOS Files

Once Ndless has successfully executed, transfer the following three files from your `build/` folder **directly to the root directory** of your calculator:

* `zCalc.tns` (The modified Beep Kernel)
* `CalcFS.tns` (The temporary File System with BusyBox and POSIX commands)
* `Loader.tns` (The bootloader and environment preparer)

### Step 3: Booting Beep (WARNING)

**DO NOT run `zCalc.tns` or `CalcFS.tns` directly!**

* If you run `zCalc.tns` manually, the kernel expects a file system with an `init` file. Without it, the system will crash, resulting in a black screen (requiring a reboot of the calculator).
* `CalcFS.tns` is merely a compressed archive containing BusyBox, configurations, and the `init` file. Opening it directly will do nothing or may crash the system.

**[!]** ONLY RUN `Loader.tns**`
To boot Beep, launch `Loader.tns`. The loader handles the entire boot sequence automatically:

1. It prepares the system environment.
2. It hooks `zCalc.tns` and `CalcFS.tns` into the correct memory addresses.
3. It informs the kernel of the exact address where the unpacked CalcFS archive is located.
4. It launches `zCalc.tns`, successfully booting Beep!
5. To leave run `off` or `reboot` or just reboot calculator

## Features of OpenCalcOS

### What's New & Exciting in the Latest Update!
- **Brand New Apps in `/bin`:**
  - **`calc`**: A powerful, shell-style calculator right in your terminal! It perfectly understands arithmetic precedence, roots, and parentheses. Just type `3 * (2+ 2)` and get `12` instantly! 
  - **`pipes`**: A fun, classic Bash script screensaver for your calculator! Want to tweak it? It's completely open source—just edit it directly on the device using `nano /bin/pipes` (I didn't build you the convenient nano editor for nothing, did I? 🫣).
  - **`beep`**: Instantly displays a stunning full-screen RAW image of the Beep kernel logo. Any key returns you to the terminal!
- **Massive Core Overhaul — Pure Beep Kernel:** We have completely migrated from the Linux kernel to the **Beep kernel**! CalcFS, BusyBox, and our compilers are now built natively for Beep, making the system incredibly fast and lightweight.
- **Extreme System Optimization:**
  - **Bloat-free CalcFS & BusyBox:** We stripped out unnecessary libraries and utilities (like internet tools), leaving only the pure, essential system tools.
  - Added `/dev` (devfs) mounting and switched the default shell from `ash` to the smoother `hush`.
  - **Slim Nano Editor:** We shaved off ~250 KB by removing heavy syntax highlighting, keeping it incredibly fast and efficient for the calculator!
- **Next-Level NDless Toolchain:** The build method is entirely revamped! It now includes a ready-to-use ARM compiler for building Beep programs. We've upgraded the toolchain (`arm-none-linux-gnueabihf`) from soft-float to **hard-float** for better performance, outputting to `ld-beep-armhf.so.3`.

### Core Features
- **Full support** for **Beep programs**, runtime, proc, etc. **(But not beep :)** [*xq* Attention! This kernel, although it was made based on 50% of Beep files and has things like Ext from Beep or ELF, is a completely different kernel (Calc Kernel - calck) and has nothing to do with Beep, although you can call it Beep because it has full Beep support, just like the original kernel.]
- Ready-to-use POSIX utilities with BusyBox such as 'gold standard', **i2c**, **disks** and **hex code**.
- Full `nano` support now builds seamlessly with BusyBox, right in `/bin`! Enjoy!
- The build script is ready. After running `bash build.sh`, you'll have a built folder containing the files you need to place on the calculator. Follow the instructions and everything will work!
- I can help with calculator support for any bug!
- Completely open source! Fork it, modify it, and do whatever you want. This is code that took one person about three months to build! This is BusyBox, Beep, and so on. Where there's a `.config` file, just type `make menuconfig` and tweak it however you like!


## LICENSE
The project uses other projects, such as BusyBox and NDless, and they are distributed under their own licenses. Also, please note that I have heavily modified the BusyBox and NDless projects, so downloading them from the internet and building them using bash busybox.sh or bash build.sh will not work and will result in errors (the same applies to NDless).

### Licenses:

- OpenCalcOS (Includes Beep kernel, CalcFS, and Loader): [GNU GPL v2.0](https://github.com/Mavox-ID/OpenCalcOS/blob/main/LICENSE)
- BusyBox: [GNU GPL v2.0](https://github.com/Mavox-ID/OpenCalcOS/blob/main/busybox/LICENSE)
- NDless: [Mozilla PL v1.1](https://github.com/Mavox-ID/OpenCalcOS/blob/main/ndless/Mozilla-Public-License-v1.1.html) (Download HTML & Open)

---

*Happy Hacking!*


