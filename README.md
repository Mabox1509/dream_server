# Dream Server

**Dream Server** is a private backend server developed under the **DreamDog** label.

It provides infrastructure for **private chat**, **demo distribution**, **file upload/download**, and **debugging tools** used during the development of DreamDog projects.

The server is intended for internal use and experimentation rather than public deployment.

---

## Purpose

Dream Server acts as a centralized private service for:

- Internal chat between developers and testers
- Distribution of game demos and builds
- File upload and download
- Debugging and logging utilities
- Experimental networking features

---

## Architecture

The server uses two main ports:

- **TCP Port**
  - Persistent client connections
  - Chat and real-time communication
  - Debug and control commands

- **HTTP Port**
  - File uploads
  - File downloads
  - Demo distribution

This separation keeps real-time networking isolated from file transfer logic.

---

## Team

**DreamDog Studio**

- **Mabox1509** — Programmer  
- *(Currently a solo project)*

---

## Technology

- **Language:** C++
- **Networking:** Raw TCP sockets + HTTP
- **Architecture:** Multi-threaded server
- **Logging:** In-memory structured logging system
- **Target Platform:** Linux

---

## Planned Features

- Private chat system
- Demo and build distribution
- File upload/download via HTTP
- Session-based connections
- Structured server logs
- Remote debug commands
- Basic authentication system

---

## Development Status

**In active development.**  
Alpha state

---

## Notes

This project is intended for internal use.  
Protocols, APIs, and features may change without notice.
