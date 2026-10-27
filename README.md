# Student Record Management System – Data Structures



A C++ student record management system developed to demonstrate the practical implementation of fundamental data structures and algorithms, including \*\*linked lists, binary search trees, queues, tree traversal, file processing, and record searching\*\*.



\*\*Course:\*\* UCCD1024 – Data Structure and Algorithmic Problem Solving  

\*\*Language:\*\* C++  

\*\*Project Type:\*\* Academic Group Project



\---



\## Overview



This project consists of two C++ implementations of a student record management system, each applying different data structures to organize and process student information.



The first implementation uses a \*\*custom linked list\*\*, while the second uses a \*\*binary search tree (BST)\*\* together with a queue for tree traversal.



\---



\## Part 1 – Linked List Student Record System



The first implementation uses a custom singly linked list to manage student and examination records.



\### Features



\- Load student records from text files

\- Insert records into a linked list

\- Detect duplicate student IDs

\- Delete student records

\- Import examination results

\- Calculate GPA and CGPA

\- Generate academic statistics

\- Filter students by course, intake year and credit hours

\- Update student ID and phone-number formats

\- Identify potential First Class students

\- Display records on screen or export them to a file



\### Data Structures



```text

List

└── Node

&#x20;   └── Student

&#x20;       └── Exam

&#x20;           └── Subject

```



The linked list implementation includes custom insertion, deletion, searching, retrieval and ordered insertion operations.



\---



\## Part 2 – Binary Search Tree Student Record System



The second implementation stores student records in a \*\*Binary Search Tree\*\*, using student IDs as the basis for tree ordering.



\### Features



\- Load student records into a BST

\- Insert and remove BST nodes

\- Display records in ascending or descending order

\- Find nodes at the deepest tree level

\- Clone a selected subtree

\- Display nodes according to tree level

\- Print root-to-leaf paths

\- Export student information to a file



\### Tree Operations



The implementation includes:



\- Pre-order traversal

\- In-order traversal

\- Post-order traversal

\- Level-order traversal

\- Recursive BST insertion

\- BST deletion

\- Subtree cloning

\- Deepest-node detection

\- Root-to-leaf path traversal



A custom \*\*Queue\*\* implementation is used to support breadth-first and level-order traversal.



\---



\## Data Structures \& Algorithms



The project demonstrates:



\- Singly Linked Lists

\- Binary Search Trees

\- Queues

\- Nodes and pointers

\- Recursion

\- Tree traversal

\- Searching

\- Insertion and deletion

\- File I/O

\- Record filtering

\- Object-oriented data modelling



\---



\## Repository Structure



```text

student-record-data-structures-cpp/

│

├── README.md

│

├── linked-list/

│   ├── src/

│   └── data/

│

└── binary-search-tree/

&#x20;   ├── src/

&#x20;   └── data/

```



\---



\## Building the Project



A C++17-compatible compiler is recommended.



Example using `g++`:



```bash

g++ -std=c++17 \*.cpp -o student-record-system

```



Run the compiled executable:



```bash

./student-record-system

```



The original application uses several Windows console commands such as `cls` and `pause`, so Windows is recommended for the original console experience.



\---



\## Technologies



\- C++

\- Standard File I/O

\- Object-Oriented Programming

\- Dynamic Memory Allocation

\- Linked Lists

\- Binary Search Trees

\- Queue

\- Recursive Algorithms



\---



\## Academic Context



Developed as a two-member group project for \*\*UCCD1024 – Data Structure and Algorithmic Problem Solving\*\* at Universiti Tunku Abdul Rahman (UTAR).



The project focuses on implementing fundamental data structures manually and applying them to student-record processing rather than relying on STL container implementations.

