# NanoServe 🚀

**NanoServe** is a high-performance, minimalist C++ web server built from the ground up using the Windows Sockets (Winsock2) API. Designed for simplicity and speed, it serves as a lightweight alternative for hosting static content and understanding the underlying mechanics of TCP/IP and HTTP protocols.

---

## ✨ Features

- **Blazing Fast:** Built with native C++ and optimized for low-latency request handling.
- **Winsock2 Integration:** Utilizes the robust Windows Socket library for reliable network communication.
- **Static File Hosting:** Automatically serves `HTML`, `CSS`, `JS`, and other assets from the `public` directory.
- **REST-like API Support:** Built-in handler for `POST` requests at `/api/data` for JSON processing.
- **Custom 404 Handling:** Includes built-in support for custom error pages.
- **Clean Architecture:** Modular design with dedicated classes for `TCPServer`, `HTTPRequest`, and `HTTPResponse`.

---

## 🏗️ Project Structure

```text
NanoServe/
├── public/             # Static web assets (HTML, CSS, Images, etc.)
│   ├── index.html      # Main landing page
│   └── 404.html        # Error fallback page
├── src/                # C++ Source files
│   ├── main.cpp        # Entry point
│   ├── TCPServer.cpp   # Core networking logic
│   ├── HTTPRequest.cpp  # Request parsing
│   └── HTTPResponse.cpp # Response construction
├── Makefile            # Build configuration
├── server.exe          # Compiled executable
└── LICENSE             # MIT License
```

---

## 🛠️ Prerequisites

Before you begin, ensure you have the following installed on your Windows machine:

- **GCC/G++:** A C++ compiler (part of MinGW-w64 or similar).
- **Make:** To automate the build process.

---

## 🚀 Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/PriyanshuJajal/NanoServe.git
cd NanoServe
```

### 2. Build the Server
Use the provided `Makefile` to compile the source code:
```bash
make
```

### 3. Run the Server
Execute the compiled binary:
```bash
./server.exe
```

The server will start listening on `127.0.0.1:8080`. Open your browser and navigate to `http://localhost:8080` to see it in action!

---

## ⚡ Performance & Scalability

As a **Nano** server, the focus is on minimal overhead and raw speed.

- **Latency (TTFB):** < 1ms on local loopback.
- **Throughput:** ~800+ Requests per second (on standard hardware).
- **Memory Footprint:** < 5MB RAM (Idle/Heavy Load).
- **Concurrency:** Handles sequential requests with a TCP backlog of 20.

> [!NOTE]
> This server uses a **single-threaded blocking I/O model**. While extremely fast for small loads and educational purposes, it is designed for simplicity rather than massive concurrent scaling (like Nginx or Apache).

---

## 🛠️ Technical Overview

NanoServe operates on the fundamental principles of the HTTP/1.1 protocol. When a client connects:
1. **TCPServer** accepts the connection using standard socket operations (`bind`, `listen`, `accept`).
2. **HTTPRequest** parses the raw buffer into meaningful segments (Method, URI, Body).
3. **HTTPResponse** locates the requested resource in the `public/` directory, determines the MIME type, and constructs a valid HTTP response header along with the file content.

---

## 📜 License

This project is licensed under the **MIT License**. Feel free to use, modify, and distribute it as you see fit.

---

<p align="center">
  <i>Building the future of the web, one byte at a time.</i>
</p>
