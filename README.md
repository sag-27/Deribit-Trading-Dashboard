# Deribit-Trading-Dashboard

## Overview

The Deribit API Trading Dashboard is a comprehensive web-based application designed for cryptocurrency derivatives trading. Built with C++ for the backend and modern web technologies, this dashboard provides real-time trading functionality through the Deribit API, allowing users to manage orders, view positions, and interact with the cryptocurrency derivatives market.


### Key Features
- **Secure Authentication**: Direct API key authentication
- **Order Management**: 
  - Place new orders
  - Cancel existing orders
  - Modify order parameters
- **Market Insights**:
  - Real-time order book retrieval
  - Current position tracking
- **WebSocket Integration**: Live market data updates

## Technology Stack

- **Backend**: 
  - C++
  - Crow Web Framework
  - WebSocket++
  - libcurl
  - JsonCpp

- **Frontend**:
  - HTML
  - JavaScript
  - CSS

- **Dependencies**:
  - Boost
  - CURL
  - WebSocket++
  - JsonCpp

## Prerequisites

Before you begin, ensure you have the following installed:

- CMake (Version 3.10 or higher)
- C++ Compiler (Supporting C++17)
- vcpkg Package Manager
- Required libraries:
  - Boost
  - CURL
  - WebSocket++
  - JsonCpp
  - Crow Web Framework

## Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/sag-27/Deribit-Trading-Dashboard.git
cd DeribitAPIDeribit-Trading-Dashboard
```

### 2. Install Dependencies with vcpkg
```bash
# Install required packages
vcpkg install curl:x64-windows
vcpkg install websocketpp:x64-windows
vcpkg install boost:x64-windows
vcpkg install jsoncpp:x64-windows
vcpkg install crow:x64-windows
```

### 4. Build the Project
```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=[vcpkg_root]/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Release
```

### 5. Run the Application
```bash
# Navigate to the build directory
cd Release
./DeribitAPI.exe
```

## Usage Instructions

1. Open a web browser and navigate to `http://localhost:3000`
2. Log in using your Deribit API credentials (API key and Secret Key)
3. Use the dashboard to:
   - Place new orders
   - Cancel existing orders
   - Modify order parameters
   - View current positions
   - Check real-time order books

## Troubleshooting

### Common Issues
- Verify API credentials
- Check internet connectivity
- Ensure all dependencies are correctly installed
- Validate vcpkg installation path

### Logging
The application provides console logging for authentication and server events.

## Disclaimer

This project is for educational and personal use. It is not affiliated with or endorsed by Deribit. Use at your own risk, and always be cautious when trading cryptocurrencies.


## Screenshots

### Login Page
![image](https://github.com/user-attachments/assets/263bed9c-8a5d-4a63-815b-0857c2b93c02)

### Dashboard
![image](https://github.com/user-attachments/assets/54e3f34b-2d35-46e9-9a36-eeaa8b22122d)

## Contact

For issues, questions, or contributions:
- Email: sagnik004sen@gmail.com
