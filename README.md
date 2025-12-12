# Board Game Collection - CS213 Assignment 3

A comprehensive collection of Tic-Tac-Toe variants implemented using Object-Oriented Programming principles in C++.

## 📋 Project Overview

This project implements 13 different board game variants using a generic, reusable OOP framework. The framework demonstrates key OOP principles including inheritance, polymorphism, abstraction, and encapsulation.

## 🎮 Available Games

### Individual Games
1. **SUS** - Form "S-U-S" sequences on a 3x3 grid
2. **Four-in-a-row** - Connect four marks on a 6x7 grid
3. **5x5 Tic-Tac-Toe** - Most three-in-a-row wins
4. **Word Tic-Tac-Toe** - Form valid 3-letter words
5. **Misère Tic-Tac-Toe** - Avoid getting three-in-a-row
6. **Diamond Tic-Tac-Toe** - Win with two simultaneous lines
7. **4x4 Tic-Tac-Toe** - Move tokens to align three
8. **Pyramid Tic-Tac-Toe** - Play on a pyramid-shaped board

### Group Games
9. **Numerical Tic-Tac-Toe** - Use numbers to sum to 15
10. **Obstacles Tic-Tac-Toe** - Dynamic obstacles on 6x6 grid
11. **Infinity Tic-Tac-Toe** - Oldest marks disappear

### Bonus Games
12. **Ultimate Tic-Tac-Toe** - 3x3 grid of mini Tic-Tac-Toe boards
13. **Memory Tic-Tac-Toe** - Hidden marks challenge memory

## 🛠️ Technical Details

### Framework Components
- **Board<T>**: Abstract base class for game boards
- **Player<T>**: Represents human and computer players
- **Move<T>**: Encapsulates game moves
- **UI<T>**: Abstract class for user interface
- **GameManager<T>**: Controls game flow

### Features
- ✅ Human vs Human gameplay
- ✅ Human vs Random Computer
- ✅ Generic template-based design
- ✅ Extensible architecture

## 📦 Project Structure

```
project/
├── BoardGame_Classes.h      # Core framework classes
├── SUS.h              # Individual game implementations
├── connect4.h
├── ...
├── GameManager.h            # Game controller
├── main.cpp                 # Application entry point
├── dic.txt                  # Dictionary for Word game
├── docs/                    # Doxygen documentation
└── README.md
```


## 👥 Team Members

| Name | ID | Individual Games |
|------|----|----|
| Eyad Hazem | 20240098 | 1. SUS<br>2. Four-in-a-row |
| Abdelhalim Ahmed | 20240288 | 3. 5x5 Tic-Tac-Toe<br>4. Word Tic-Tac-Toe |
| Abdullah Saied | 20240326 | 5. Misère Tic-Tac-Toe<br>6. Diamond Tic-Tac-Toe |
| Mohannad Ashraf | 20240618 | 7. 4x4 Tic-Tac-Toe<br>8. Pyramid Tic-Tac-Toe |

### Team Collaboration Games
- **Group Games**: 9. Numerical Tic-Tac-Toe, 10. Obstacles Tic-Tac-Toe, 11. Infinity Tic-Tac-Toe
- **Bonus Games**: 12. Ultimate Tic Tac Toe, 13. Memory Tic-Tac-Toe

## 🎯 OOP Principles Applied

- **Abstraction**: Abstract base classes (Board, UI)
- **Polymorphism**: Virtual functions for game-specific behavior
- **Inheritance**: Game-specific classes extend framework
- **Encapsulation**: Private data with public interfaces

## 📚 Documentation

Full API documentation is available in the `docs/` directory. Open `docs/html/index.html` in a browser to view.

## 🎓 Course Information

- **Course**: CS213 - Object Oriented Programming
- **Institution**: Cairo University, Faculty of Artificial Intelligence
- **Instructor**: Dr. Mohammad El-Ramly
- **Academic Year**: 2025-2026

## 📝 License

This project is an academic assignment for educational purposes only.

## 🙏 Acknowledgments

- Dr. Mohammad El-Ramly for the framework design
- Course teaching assistants for guidance
- Team members for collaboration

---

**Note**: This project adheres to academic integrity policies. All code is original work by team members.