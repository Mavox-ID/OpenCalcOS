# OpenCalcOS

Have a TI-NSPIRE CX? Why not use it for Linux?

OpenCalcOS is a complete, all-in-one toolkit designed to turn your TI-Nspire CX calculator into a fully working Linux machine. It features a cloned and slightly modified Linux port tailored for the calculator, integrated BusyBox for ARM, a custom temporary file system (CalcFS), a dedicated bootloader, and a ready-to-use Ndless toolkit for jailbreaking any version of the TI-Nspire CX.

## Features

* **CalcKernel (`zCalc.tns`)**: A modified Linux kernel optimized specifically for the TI-Nspire CX architecture.
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

Ndless is required to jailbreak the calculator's firmware so it can run unofficial compiled `.tns` packages (like CalcKernel and Loader).

1. Navigate to the compiled `build/NDless` folder.
2. Find the Ndless installer file that matches your calculator's exact firmware version.
3. Transfer this file anywhere on your calculator and run it.
4. Upon success, Ndless will be active in the background.

### Step 2: Transfer OpenCalcOS Files

Once Ndless has successfully executed, transfer the following three files from your `build/` folder **directly to the root directory** of your calculator:

* `zCalc.tns` (The modified Linux Kernel)
* `CalcFS.tns` (The temporary File System with BusyBox and POSIX commands)
* `Loader.tns` (The bootloader and environment preparer)

### Step 3: Booting Linux (WARNING)

**DO NOT run `zCalc.tns` or `CalcFS.tns` directly!**

* If you run `zCalc.tns` manually, the kernel expects a file system with an `init` file. Without it, the system will crash, resulting in a black screen (requiring a reboot of the calculator).
* `CalcFS.tns` is merely a compressed archive containing BusyBox, configurations, and the `init` file. Opening it directly will do nothing or may crash the system.

**[!]** ONLY RUN `Loader.tns**`
To boot Linux, launch `Loader.tns`. The loader handles the entire boot sequence automatically:

1. It prepares the system environment.
2. It hooks `zCalc.tns` and `CalcFS.tns` into the correct memory addresses.
3. It informs the kernel of the exact address where the unpacked CalcFS archive is located.
4. It launches `zCalc.tns`, successfully booting Linux!
5. To leave run `off` or `reboot` or just reboot calculator

## LICENSE
The project uses other projects, such as BusyBox and NDless, and they are distributed under their own licenses. Also, please note that I have heavily modified the BusyBox and NDless projects, so downloading them from the internet and building them using bash busybox.sh or bash build.sh will not work and will result in errors (the same applies to NDless).

### Licenses:

- OpenCalcOS (Includes CalcKernel, CalcFS, and Loader): [GNU GPL v2.0](https://github.com/Mavox-ID/OpenCalcOS/blob/main/LICENSE)
- BusyBox: [GNU GPL v2.0](https://github.com/Mavox-ID/OpenCalcOS/blob/main/busybox/LICENSE)
- NDless: [Mozilla PL v1.1](https://github.com/Mavox-ID/OpenCalcOS/blob/main/ndless/Mozilla-Public-License-v1.1.html) (Download HTML & Open)

---

*Happy Hacking!*
