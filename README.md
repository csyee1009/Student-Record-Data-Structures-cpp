<div align="center">

# Student Record Management System

### C++ Data Structures & Algorithm Implementation

A console-based student record system demonstrating the practical implementation of **Linked Lists, Binary Search Trees, Queues, recursion, tree traversal, and file processing**.

![C++](https://img.shields.io/badge/C++-17-blue)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Linked%20List%20%7C%20BST%20%7C%20Queue-orange)
![Project](https://img.shields.io/badge/Project-Academic-green)

</div>

---

## Overview

This project was developed for **UCCD1024 – Data Structure and Algorithmic Problem Solving** at Universiti Tunku Abdul Rahman (UTAR).

It consists of two C++ implementations of a student record management system:

| Part | Main Data Structure | Purpose |
|---|---|---|
| **Part 1** | Linked List | Student and examination record processing |
| **Part 2** | Binary Search Tree & Queue | Student record organisation and tree-based operations |

Rather than relying on STL containers, the core data structures were implemented manually to demonstrate understanding of **nodes, pointers, recursion, dynamic memory management, and algorithm design**.

---

## Part 1 — Linked List

The first implementation manages student and examination records using a custom linked-list structure.

### Features

- Load student records from text files
- Insert and remove student records
- Detect duplicate student IDs
- Store examination results
- Calculate GPA and CGPA
- Generate academic statistics
- Filter students by course, year, and credit hours
- Update student ID and phone-number formats
- Identify potential First Class students
- Display or export processed records

### Structure

```text
List
└── Node
    └── Student
        └── Exam
            └── Subject
```

The custom `List` implementation handles operations such as insertion, deletion, searching, retrieval, and ordered record management.

---

## Part 2 — Binary Search Tree

The second implementation stores student records in a **Binary Search Tree (BST)** and applies tree-based algorithms to retrieve and organise records.

### Features

- Insert student records into a BST
- Remove BST nodes
- Search and retrieve student information
- Display records in ascending and descending order
- Find nodes at the deepest tree level
- Clone selected subtrees
- Display nodes by tree level
- Generate root-to-leaf paths
- Export student records to files

---

## Tree Traversal Algorithms

The BST implementation includes:

| Traversal | Description |
|---|---|
| **In-order** | Visits records according to BST ordering |
| **Pre-order** | Visits the root before its subtrees |
| **Post-order** | Visits subtrees before the root |
| **Level-order** | Traverses the tree level by level |
| **Root-to-Leaf** | Generates paths from the root to leaf nodes |

A custom **Queue** implementation is used to support level-order traversal.

---

## Data Structures Implemented

```text
Linked List
├── Node
└── List

Binary Search Tree
├── BTNode
└── BST

Queue
├── Node
└── Queue
```

---

## Concepts Demonstrated

- Linked Lists
- Binary Search Trees
- Queues
- Nodes and Pointers
- Dynamic Memory Allocation
- Recursion
- Tree Traversal
- Searching
- Insertion and Deletion
- File I/O
- Record Filtering
- Object-Oriented Programming

---

## Example Operations

### Linked List

```text
Student Records
      │
      ▼
Load from File
      │
      ▼
Linked List
      │
      ├── Search
      ├── Insert
      ├── Delete
      ├── Filter
      └── Academic Analysis
```

### Binary Search Tree

```text
                 Student
                    │
             ┌──────┴──────┐
          Student        Student
             │               │
        ┌────┴────┐     ┌────┴────┐
      Node       Node  Node       Node
```

Student records are organised according to their identifiers, allowing tree-based searching and traversal operations.

---

## Build & Run

### Requirements

- C++17-compatible compiler
- Windows recommended for the original console interface

### Compile

Using `g++`:

```bash
g++ -std=c++17 *.cpp -o student-record-system
```

### Run

Windows:

```bash
student-record-system.exe
```

Linux / macOS:

```bash
./student-record-system
```

> Some console commands in the original implementation, such as `cls` and `pause`, are Windows-specific.

---

## Technologies

| Category | Technology |
|---|---|
| Language | C++ |
| Standard | C++17 |
| Data Structures | Linked List, Binary Search Tree, Queue |
| Algorithms | Searching, Traversal, Insertion, Deletion |
| Storage | Text File I/O |
| Programming Style | Object-Oriented Programming |

---

## Academic Context

**Course:** UCCD1024 – Data Structure and Algorithmic Problem Solving  
**Institution:** Universiti Tunku Abdul Rahman (UTAR)  
**Project Type:** Academic Group Project

The project focuses on applying fundamental data-structure concepts to a practical student-record management scenario while implementing the core structures manually in C++.

---

## Key Learning Outcomes

Through this project, we applied:

- Manual implementation of dynamic data structures
- Pointer-based node manipulation
- Recursive tree algorithms
- Breadth-first traversal using queues
- File-based record processing
- Object-oriented program organisation
- Application of data structures to real-world records

---

<div align="center">

### Built with C++ to explore how data structures work beyond standard library containers.

</div>
