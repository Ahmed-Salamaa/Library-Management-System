# 📚 Library Management System

A console-based Library Management System built with C++ that allows administrators to manage books and users, while students can borrow and return books.

## ✨ Features

### 👨‍💼 Admin Features
- Add, update, and delete books
- Add, update, and delete users
- Search and view book/user details
- Manage the entire library catalog

### 👨‍🎓 Student Features
- Search books by title or author
- Borrow available books
- Return borrowed books
- View borrowing history

### 💾 Data Persistence
- Automatic saving of all data on exit
- Automatic loading of data on startup
- Cross-platform file storage support
- CSV-based data serialization

## 🏗️ Project Structure

```
Library-Management-System/
├── main.cpp              # Entry point
├── include/              # Header files
│   ├── Admin.h
│   ├── Book.h
│   ├── Borrow.h
│   ├── DataManager.h
│   ├── LinkedList.h
│   ├── Student.h
│   ├── System.h
│   ├── User.h
│   └── Utilities.h
├── src/                  # Source files
│   ├── Admin.cpp
│   ├── Book.cpp
│   ├── Borrow.cpp
│   ├── DataManager.cpp
│   ├── Student.cpp
│   ├── System.cpp
│   ├── User.cpp
│   └── Utilities.cpp
├── output/               # Compiled binaries
└── data/                 # Data storage (auto-generated)
```

## 🚀 Getting Started

### Prerequisites
- **C++ Compiler** with C++17 support (g++, clang++, or MSVC)
- **Make** (optional, for build automation)

### Compilation

#### Linux / macOS
```bash
# Navigate to project directory
cd Library-Management-System

# Compile the project
g++ -o output/library main.cpp src/*.cpp -std=c++17 -I.

# Run the application
./output/library
```

#### Windows (Command Prompt)
```cmd
:: Navigate to project directory
cd Library-Management-System

:: Compile the project (list all source files explicitly)
g++ -o output\library.exe main.cpp src\Admin.cpp src\Book.cpp src\Borrow.cpp src\DataManager.cpp src\Student.cpp src\System.cpp src\User.cpp src\Utilities.cpp -std=c++17 -I.

:: Run the application
output\library.exe
```

## 🔐 Default Credentials

On first run, the system creates initial test accounts:

| Role    | Username | Password   |
|---------|----------|------------|
| Admin   | admin    | Admin@123  |
| Student | rasha    | Rasha@123  |
| Student | sara     | Sara@123   |

## 📖 Usage

1. **Start the application** using the run commands above
2. **Login** with existing credentials or **Sign up** as a new student
3. **Navigate** through the menu using number keys
4. **Logout** or **Exit** to save all data automatically

### Main Menu Options
```
1. Login
2. Sign Up
3. Exit
```

### Admin Menu
```
1. Add Book
2. Delete Book
3. Update Book
4. View Book
5. Add User
6. Update User Password
7. Delete User
8. View User
9. Logout
```

### Student Menu
```
1. Search Book by Title
2. Search Books by Author
3. Borrow Book
4. Return Book
5. Logout
```

## 🛠️ Technical Details

- **Language:** C++17
- **Data Structure:** Custom LinkedList implementation
- **Storage:** CSV files with unit separator (0x1F) delimiter
- **Architecture:** Object-Oriented with inheritance (User → Admin/Student)

## 📝 License

This project is open source and available for educational purposes.

## 👩‍💻 Team Members

| Name | GitHub Profile |
|------|----------------|
| 🌸 **Roaa Jouda** | [@roaajouda](https://github.com/roaajouda) |
| ✨ **Rasha Jouda** | [@Rashajouda](https://github.com/Rashajouda) |
| 🌼 **Salma Nabil** | [@Salma-Nabil-Afify](https://github.com/Salma-Nabil-Afify) |
| 💫 **Ahemd Salama**| [@Ahmed-Salamaa](https://github.com/Ahmed-Salamaa) |



---

⭐ Star this repository if you find it helpful!
