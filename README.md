
# **TCP Networking Projects in C**  
*A hands-on collection of socket programming projects—chat apps, file transfer, and reusable utilities—built for learning core networking concepts.*  

## **📌 Key Projects**  

### **1. Multithreaded Chat Application**  
📡 *TCP-based client-server chat with simultaneous read/write threads.*  
**Features**: Graceful shutdown (`q` command), Linux-compatible.  

---

### **2. Multi-Client Calculator Server**  
🧮 *Arithmetic server (+, -, *, /) handling concurrent clients.*  
**Features**: Thread-per-client, input validation.  

---

### **3. File Transfer Tool**  
📂 *Send files over TCP with chunked data streaming.*  
**Features**: File size negotiation, error handling.  

---

### **4. TCP Connection Library (`tcp-utils`)**  
🔌 *Reusable C library for socket setup/teardown.*  
```c
#include "server.h"  // Server-side functions  
#include "client.h"  // Client-side functions  
```  
**Features**: Minimal API, portable socket management.  

---

## **🔧 Experimental Labs (Python)**  
*Simple TCP/UDP examples for quick experiments (e.g., echo servers).*  

*Note: These are minimal demos for testing concepts.*  

---

## **🚀 Usage**  
1. **Clone & Compile**:  
   ```sh
   git clone https://github.com/zarkhodamoradi/tcp-examples.git
   cd tcp-examples/<project> && gcc ...  
   ```  
2. **Run**: Follow project-specific commands above.  

---

## **🎯 Learning Focus**  
✔ **TCP sockets** (connections, streams, ports).  
✔ **Concurrency** (multithreading, parallel clients).  
✔ **Error resilience** (graceful exits, file transfer checks).  
✔ **Reusable design** (via `tcp-utils`).  

---

## **📜 License**  
MIT © [Zahra Khodamoradi] — Free for learning and contributions.  

