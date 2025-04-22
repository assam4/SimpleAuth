# User Account Management System

This project is a simple **User Account Management System** written in **C++20**. It provides functionality for user **registration**, **sign in**, **password recovery**, and **password change** using a command-line interface.

## 🚀 Features

- Register a new user with login, password, and a secret word.
- Sign in with existing credentials.
- Recover a forgotten password using the secret word.
- Change the password after signing in.
- Uses modern C++20 features.
- Minimal and clean I/O system.
- Lightweight with no external dependencies.

  ## 🛠️ Tools and C++ Features Used

This project uses the following C++ features and tools:

  -**C++20**: The project takes advantage of C++20 features, including:
  - `constexpr` functions for compile-time computations.
  - **Structured bindings** for more readable and concise code.
  - **Concepts**: Enforced type constraints using `std::concepts`.
  - **Lambda expressions** for functional programming style in logic processing.
  - **std::function** for passing function pointers as arguments.
  - **Nlohmann JSON Library**: For handling and parsing JSON formatted user data in a simple way. The `nlohmann/json.hpp` header is used for serialization and deserialization of user accounts.
  - **I/O Streams**: Extensive use of `std::ostream` and `std::istream` for user interaction and input/output management.
  - **Random Number Generation**: Utilized the C++ `<random>` library to generate dynamic coefficients for password encryption and decryption.

  ## 🛠️ Build Instructions

For correct operation you must install the json package if you don't have it.

  ````bash
  sudo apt-get install nlohmann-json3-dev
  ````

You need a C++20-compatible compiler (e.g., `g++-10` or later).

  ```bash
  make
  ./authentication
  ````
