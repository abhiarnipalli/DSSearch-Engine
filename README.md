# Search Engine

## Project Overview
This project involves the development of a high-performance search engine in C++. The search engine is capable of indexing 1000 documents in under 2 minutes and supports fast search and retrieval using AVL trees. Additionally, it includes a query parser to handle various types of searches and features persistence for saving and loading indexes from files.

## Skills Utilized
- Algorithms
- C++
- Data Structures
- Search Engines
- Object-Oriented Programming (OOP)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Results](#results)
- [Conclusion](#conclusion)
- [Acknowledgments](#acknowledgments)
- [References](#references)

## Introduction
Efficient search engines are essential for quickly accessing and retrieving information from large datasets. This project aims to create a search engine in C++ that can index a significant number of documents rapidly while providing fast and accurate search capabilities. The use of AVL trees for indexing ensures quick search and retrieval times, and the query parser enhances the flexibility of search operations.

## Features
- **Fast Indexing:** Capable of indexing 1000 documents in under 2 minutes.
- **Efficient Search and Retrieval:** Utilizes AVL trees for quick search and retrieval of indexed content.
- **Flexible Query Parsing:** Handles text searches as well as searches for specific people and organizations.
- **Persistence:** Enables saving and loading indexes from files for efficient data management.

## Usage
To use the search engine, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/Search-Engine.git
   ```

2. **Navigate to the Project Directory:**
   ```bash
   cd Search-Engine
   ```

3. **Build the Project:**
   Use your preferred build system (e.g., Make, CMake) to compile the project. For example, using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the Search Engine:**
   Execute the compiled binary to start the search engine. Ensure that you have the necessary documents in the correct format for indexing.
   ```bash
   ./search_engine
   ```

## Results
The search engine efficiently indexes and retrieves documents, providing fast search results. The indexed data can be saved and loaded from files, allowing for persistent storage and quick access in subsequent runs.

## Conclusion
This project demonstrates the development of a high-performance search engine using C++. The implementation of AVL trees for indexing and the inclusion of a flexible query parser result in a powerful and efficient search tool. The ability to persist indexes further enhances the utility of the search engine for large datasets.

## Acknowledgments
- The project leverages libraries and tools such as the C++ Standard Library for data structures and file handling.
- Thanks to the contributors and maintainers of these libraries for their valuable work.

## References
- [C++ Standard Library Documentation](https://en.cppreference.com/w/)
- [AVL Tree Data Structure](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
- [Search Engine Algorithms](https://en.wikipedia.org/wiki/Search_engine_indexing)
