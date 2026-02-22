# 2026-CrimsonCode-Hackathon
# OGRE Encryption

Offline file‑encryption tool built by **Gus Ballman** and **Jameson Scott** for the **2026 CrimsonCode Hackathon** at **Washington State University**.

---

## Overview
OGRE is a lightweight file‑encryption app built from scratch using C++, SFML, and our own integer‑safe math. The goal was to create a simple, fast, fully offline tool where the user can drag in a file, enter a password, and encrypt or decrypt it instantly. The UI stays minimal while all the real work happens under the hood.

---

## Features
+ Offline file encryption and decryption  
+ Custom integer‑safe math for key generation  
+ Deterministic, reproducible transformations  
+ Drag‑and‑drop file selection  
+ Minimal SFML interface  

---

## About the Project
We built this to push ourselves into real low‑level work—writing our own math, handling file I/O directly, and building a clean UI without relying on existing encryption libraries. We learned how to design a full encryption pipeline, integrate it into SFML, and debug the edge cases that show up when you control every step. The biggest challenge was keeping everything deterministic and integer‑safe while still making the tool simple to use.

---

## How It Works
The encryption pipeline uses:
+ A password → hash → integer offset transform  
+ A prime‑bounded offset for fast, safe loops  
+ Modular arithmetic for byte‑level transformations  
+ A reversible process that guarantees consistent output  

All operations are integer‑only and fully deterministic.

---

## Built With
+ **C++**
+ **SFML**
+ **Windows API** (for drag‑and‑drop)
+ **Custom hashing and math functions**

---

## Authors
+ **Gus Ballman**  
+ **Jameson Scott**
+ Copilot (For Portions of UI)

---

## Hackathon
Submission for the **2026 CrimsonCode Hackathon** at **Washington State University**.
