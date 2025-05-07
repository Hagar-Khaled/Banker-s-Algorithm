# 🏦 Banker's Algorithm Simulation

A C++ implementation of the **Banker's Algorithm**, a classic algorithm in operating systems for **deadlock avoidance**. This project simulates resource allocation among multiple processes and checks if the system is in a safe state.

## 📌 Features

- Supports 5 processes and 3 resource types (customizable in code).
- Three modes of initialization:
  - ✅ **Default Values**
  - 🎲 **Randomly Generated Values**
  - ✍️ **Manual User Input**
- Safety algorithm to check if the system is in a safe or unsafe state.
- Accepts resource requests from the user and simulates their effect.
- Rejects unsafe requests to prevent deadlock.
- Clear matrix output for:
  - Allocation
  - Maximum
  - Need
- Prints the safe sequence (if exists).

## 🧮 What It Does

- Calculates the **Need Matrix**:  
  `Need = Maximum - Allocation`
- Verifies system safety using the Banker's algorithm.
- Accepts resource requests of the form:  
  `Process_ID R0 R1 R2`
- Tests if the request keeps the system in a safe state.

### 👤 User Interaction

1. Choose how to initialize the data:

   * 1: Use predefined default values.
   * 2: Use randomly generated matrices.
   * 3: Enter data manually.
2. If you choose manual input:

   * Enter allocation matrix (5×3)
   * Enter maximum matrix (5×3)
   * Enter available resources (3)
3. The program will calculate the need matrix and show if the system is safe.
4. You’ll be prompted to enter a resource request.

### 💡 Example Request Input

```
Enter a resource request (Process ID followed by R0 R1 R2):
1 1 0 2
```

## 📂 File Structure

* `bankers_algorithm.cpp`: Main source code
* `README.md`: Documentation (this file)
* `Bankers_Algorithm_Features_Report.docx`: Report of features

## 📚 Concepts Covered

* Deadlock avoidance
* Banker's algorithm
* Matrices and safety checks
* Resource management
* C++ input/output and arrays

## ✅ To-Do (Optional Enhancements)

* Allow dynamic number of processes/resources.
* GUI-based interface for better visualization.
* Load/save configurations from a file.
* Continuous request handling loop.

## 👨‍💻 Author

* GitHub: [Hagar-Khaled](https://github.com/Hagar-Khaled)
* linkedin: [Hagar Helmy](https://www.linkedin.com/in/hagar-helmy/)

---

> 💬 *Feel free to fork this project, suggest improvements, or contribute!*

```
