# ADB Device Manager - Qt Version

This is a Qt C++ conversion of the original C# Android device management tool. It uses ADB (Android Debug Bridge) to manage Android devices and can disable factory reset protection.

## Features

- Check ADB server status
- Search for connected Android devices
- Install APK files via ADB
- Set device owner permissions
- Disable factory reset protection
- Modern Qt GUI with progress tracking and colored logging

## Requirements

- Qt 6.x (Core and Widgets modules)
- ADB (Android Debug Bridge) installed and in PATH
- CMake 3.16+ or qmake
- C++17 compatible compiler

## Building

### Using CMake:
```bash
mkdir build
cd build
cmake ..
make
```

### Using qmake:
```bash
qmake AdbDeviceManager.pro
make
```

## Usage

1. Ensure ADB is installed and in your system PATH
2. Place your APK files in the `data/` directory
3. Connect your Android device with USB debugging enabled
4. Run the application
5. Click "Universal Method - Disable Factory Reset" button

## Directory Structure

```
.
├── main.cpp                    # Application entry point
├── mainwindow.h                # Main window header
├── mainwindow.cpp              # Main window implementation
├── AdbClient.h                 # ADB client interface
├── AdbClient.cpp               # ADB client implementation
├── universalmethodhandler.h    # Universal method handler header
├── universalmethodhandler.cpp  # Universal method handler implementation
├── CMakeLists.txt              # CMake build file
├── AdbDeviceManager.pro        # qmake project file
├── data/                       # Directory for APK files
│   └── adm.apk                # (Place your APK here)
└── README.md                  # This file
```

## Architecture

The application follows your existing pattern with:

- **MainWindow**: UI management and user interaction
- **AdbClient**: Core ADB functionality and device communication
- **UniversalMethodHandler**: State machine for the universal method process
- **State Machine Pattern**: Clean step-by-step execution with progress tracking

## Key Differences from C# Version

- **Architecture**: Clean separation with handler classes and state machines
- **Threading**: Uses Qt's QTimer for async operations without blocking UI
- **Process Execution**: QProcess for all ADB commands
- **Error Handling**: Comprehensive error checking at each step
- **Progress Tracking**: Visual feedback with detailed logging

## Security Note

This tool is designed for legitimate device management purposes. Ensure you have proper authorization before using it on any device.

## License

This project is for educational and legitimate device management purposes only.
