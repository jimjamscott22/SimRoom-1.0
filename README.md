# SimRoom 1.0

A first-person puzzle game built in Unreal Engine where players escape a series of themed rooms by solving environmental and logic puzzles.

![Development Status](https://img.shields.io/badge/status-in%20development-yellow)
![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.x-blue)
![License](https://img.shields.io/badge/license-MIT-green)

## 🎮 About

SimRoom 1.0 is a Portal-inspired puzzle game featuring:
- Environmental puzzles (pressure plates, pushable boxes, timed doors)
- A unique **visual programming puzzle room** where players solve logic challenges
- Atmospheric sci-fi research facility setting
- 5-8 interconnected puzzle rooms

This is a learning project focused on mastering Unreal Engine's Blueprint system and level design.

## 🚀 Current Status

**Phase:** Planning & Foundation  
**Completed Rooms:** 0/5  
**Core Mechanics Implemented:** Native Phase 1 foundations added, pending Unreal compile and editor asset setup

See [BLUEPRINT.md](BLUEPRINT.md) for detailed project roadmap.
See [Development State](docs/dev-state.md) for the latest handoff notes.

## 🎯 Features

### Implemented
- [x] Native first-person movement and camera foundation
- [x] Native object interaction system foundation
- [x] Native button → door mechanics foundation
- [ ] Pushable boxes
- [ ] Pressure plates
- [ ] Timed doors
- [ ] Visual programming puzzle

### Planned
- [ ] Multiple themed puzzle rooms
- [ ] Atmospheric lighting and sound design
- [ ] UI/Menu system
- [ ] Hint system (optional)

## 🛠️ Built With

- **Engine:** Unreal Engine 5.x
- **Language:** Blueprints (visual scripting)
- **Base Template:** First Person Template
- **Assets:** Unreal Starter Content + [list additions as added]

## 📋 Prerequisites

- Unreal Engine 5.x (Download from [Epic Games Launcher](https://www.unrealengine.com/))
- Windows 10/11, macOS, or Linux
- ~10GB free disk space
- GPU: GTX 1060 / RX 580 or better recommended

## 🎮 How to Run

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/SimRoom1.0.git
   cd SimRoom1.0
   ```

2. Install Visual Studio 2022 C++ build tools if opening the C++ project for the first time

3. Open `SimRoom1.0.uproject` with Unreal Engine

4. See [Phase 1 Editor Setup](docs/phase-1-editor-setup.md) to create the Room 0 Blueprint assets

5. Press **Play** in the editor to test current build

## 📁 Project Structure

```
SimRoom1.0/
├── Content/
│   ├── Blueprints/        # All Blueprint classes
│   │   ├── Player/        # Player character & controller
│   │   ├── Interactables/ # Doors, buttons, boxes, etc.
│   │   └── Puzzles/       # Special puzzle mechanics
│   ├── Maps/              # Level files
│   ├── UI/                # UMG widgets
│   ├── Materials/         # Custom materials
│   └── Audio/             # Sound effects and music
├── Config/                # Project configuration
├── BLUEPRINT.md           # Detailed project roadmap
└── README.md              # This file
```

## 🎓 Learning Goals

This project is designed to teach:
- Unreal Engine Blueprint system
- Level design principles
- Puzzle game mechanics
- Event-driven architecture
- UI/UX in games
- Git workflow for game development

## 🤝 Contributing

This is a personal learning project, but feedback and suggestions are welcome! Feel free to:
- Open issues for bugs or suggestions
- Fork the repo and experiment
- Share your own puzzle room designs

## 📝 Development Log

### 2025-12-18
- Initial project planning
- Created project blueprint and documentation
- Set up GitHub repository

[See full changelog in BLUEPRINT.md]

## 📸 Screenshots

*Screenshots will be added as development progresses*

## 🎯 Roadmap

- **Week 1-2:** Foundation (player movement, interaction system)
- **Week 3-4:** Core puzzle mechanics (boxes, pressure plates, doors)
- **Week 5-6:** Visual programming puzzle room
- **Week 7:** Room integration and expansion
- **Week 8:** Polish, sound design, and release

See [BLUEPRINT.md](BLUEPRINT.md) for detailed breakdown.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by Portal and The Talos Principle
- Unreal Engine by Epic Games
- [List tutorials and resources as you use them]

## 📧 Contact

**Project Creator:** [Your Name]  
**GitHub:** [@yourusername](https://github.com/yourusername)  
**Email:** your.email@example.com

---

**Note:** This is an active learning project. Expect frequent updates and changes as development progresses!
