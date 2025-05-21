# 🗜️ Huffman File Compressor

A **file compression and decompression tool** built using the **Huffman Encoding Algorithm** – one of the most efficient ways to reduce file size without losing any data (lossless compression). This project demonstrates how data can be compressed using frequency-based encoding and highlights the power of trees and priority queues in real-world applications.

---

## 🚀 Features

- Compress any text-based file using Huffman Encoding  
- Decompress it back to the original file with perfect accuracy  
- View the compression ratio achieved  
- Simple command-line interface for quick usage  

---

## 🧠 Concepts Used

This project is based on the **Huffman Encoding Algorithm**, which is a **greedy algorithm** used to compress data by assigning **shorter binary codes to more frequent characters** and longer codes to less frequent ones.

The process involves:
1. Counting frequency of each character in the input file  
2. Building a **Huffman Tree** based on character frequencies  
3. Traversing the tree to assign binary codes  
4. Writing the encoded data to a compressed binary file  
5. Storing metadata (Huffman tree) for decompression  
6. Decoding the binary file using the stored tree  

---

## 🧰 Data Structures Used

- **Hash Map** (`unordered_map`) – for character frequency table and Huffman codes  
- **Priority Queue / Min-Heap** – to build the Huffman Tree based on minimum frequency  
- **Binary Tree** – to represent the Huffman Tree  
- **Bit Manipulation** – to efficiently store and read bits from binary files  
- **Custom Structures** – to define Huffman Tree nodes and manage I/O logic  

---

## 📦 File Structure

```bash
.
├── compressor.cpp       # Compression logic
├── decompressor.cpp     # Decompression logic
├── input.txt            # Sample input file
├── decompressed.txt     # Output of decompression
```
---

## ⚙️ How to Run

### 🧩 Prerequisites

- C++ compiler (e.g., `g++`)
- Terminal or Command Prompt

### 🔧 Compilation

```bash
g++ compressor.cpp -o compress


