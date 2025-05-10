# password-based lock for bike ignition key System using 8051 Microcontroller



This project implements a secure ignition system for a bike using a password-based locking mechanism. Built in **Keil uVision (C for 8051)** and simulated in **Proteus**, the system ensures that only users with the correct password can start the bike. It includes a buzzer and LCD for feedback and enhanced security.

---

## 🚀 Features

- ✅ **Password-protected ignition**
- ✅ **"Enjoy The Ride" display on successful login**
- ❌ **Three consecutive wrong attempts lock the bike**
- ⏳ **LCD countdown warning before locking**
- 🔊 **Buzzer alert after 3 failed attempts**
- 💬 **Attempt reminders on each failed input**
- 🔁 **Returns to odometer display after successful ignition**

---

## 🛠️ Project Components

### 👨‍💻 Software:
- **Keil uVision** – for 8051 coding and HEX generation
- **Proteus Design Suite** – for simulating microcontroller circuit

### 🧩 Hardware Simulated:
- 8051 Microcontroller (AT89C51/52)
- 16x2 LCD Display
- 4x4 Keypad
- Buzzer
- Ignition LED
- Power Source

---

## 📁 File Structure
  BikeSecuritySystem/
  ├── main.c # Main program source code
  ├── BikeLock.uvproj # Keil project file
  ├── BikeLock.uvopt # Keil options file
  ├── BikeLock.hex # Compiled hex file for Proteus
  ├── Circuit.dsn # Proteus simulation file
  ├── README.md # Project description

  
---

## 🔧 How to Run

1. Open `BikeLock.uvproj` in **Keil**.
2. Build the project to generate `BikeLock.hex`.
3. Open `Circuit.dsn` in **Proteus**.
4. Load the `BikeLock.hex` into the 8051 microcontroller in the Proteus design.
5. Run the simulation and test the system using the keypad.

---

## 📝 Password Logic

- Default password: `1234`
- If entered correctly:
  - Displays: `Bike On`, then `Enjoy The Ride`
  - Returns to odometer screen
- If entered incorrectly:
  - Displays remaining attempts (e.g., `2 attempts left`)
  - After 3 failed attempts:
    - LCD shows countdown
    - Buzzer activates
    - System locks

---

## 📸 Screenshots

*(Include if you want — like LCD output or Proteus simulation view)*

---

## 📜 License

This project is for educational purposes. Feel free to modify and enhance it.

---

## 👤 Author

Developed by: Tasnim Ul Islam
Department : Bioinformatics Engineering,AET
Institution: Bangladesh Agricultural University  
Supervisor: [Your Supervisor, if applicable]


