# SimRoom 1.0 - Project Blueprint

**Last Updated:** December 18, 2025  
**Status:** Planning Phase  
**Engine:** Unreal Engine 5.x (Blueprint)

---

## Project Overview

**Concept:** First-person puzzle explorer set in a sci-fi research facility. Players solve environmental and logic puzzles to escape themed rooms.

**Core Experience:** Portal-lite puzzle solving with a unique coding challenge room.

**Target Scope:** 5-8 puzzle rooms, 8-12 week development time

---

## Feature Modules

### ✅ CORE MECHANICS (Required)

#### Player Controller
- [ ] First-person movement (WASD)
- [ ] Mouse look camera
- [ ] Jump mechanic
- [ ] Interaction system (raycast + E key)
- [ ] Crosshair UI

**Dependencies:** Unreal First Person Template (baseline)  
**Blueprints Needed:** BP_PlayerCharacter (modify template)  
**Priority:** CRITICAL - Week 1

---

#### Interaction System
- [ ] Raycast from camera center
- [ ] Highlight interactable objects
- [ ] "Press E to interact" prompt
- [ ] Event system for triggering actions

**Dependencies:** Player Controller  
**Blueprints Needed:** BP_InteractionComponent, BPI_Interactable (interface)  
**Priority:** CRITICAL - Week 1-2

---

### 🧩 PUZZLE MECHANICS

#### Door System
- [ ] Open/close animations (Timeline)
- [ ] Locked/unlocked states
- [ ] Can be triggered by buttons, pressure plates, or code
- [ ] Sound effects (open/close/locked)

**Dependencies:** Interaction System  
**Blueprints Needed:** BP_Door  
**Priority:** HIGH - Week 2

---

#### Button/Switch System
- [ ] Press animation
- [ ] Toggle or hold modes
- [ ] Link to doors or other objects
- [ ] Visual feedback (color change, glow)

**Dependencies:** Interaction System, Door System  
**Blueprints Needed:** BP_Button  
**Priority:** HIGH - Week 2

---

#### Pushable Box System
- [ ] Physics-enabled cube
- [ ] Player can push (apply force)
- [ ] Weight affects push difficulty
- [ ] Can trigger pressure plates

**Dependencies:** Physics system (built-in)  
**Blueprints Needed:** BP_PushableBox  
**Priority:** MEDIUM - Week 3

---

#### Pressure Plate System
- [ ] Detects overlapping objects (player or boxes)
- [ ] Weight threshold system
- [ ] Visual feedback (depression animation)
- [ ] Triggers events when activated/deactivated

**Dependencies:** Door System  
**Blueprints Needed:** BP_PressurePlate  
**Priority:** MEDIUM - Week 3

---

#### Timed Door System
- [ ] Door opens, waits X seconds, closes
- [ ] Visual countdown indicator
- [ ] Warning sound before closing
- [ ] Player can re-trigger

**Dependencies:** Door System  
**Blueprints Needed:** BP_TimedDoor (child of BP_Door)  
**Priority:** MEDIUM - Week 4

---

### 💻 SPECIAL: Visual Programming Puzzle

#### Node-Based Logic System
- [ ] Draggable logic blocks (IF, THEN, AND, OR, LOOP)
- [ ] Connection system (wire nodes together)
- [ ] Input/Output nodes
- [ ] Validation system (checks if logic is correct)
- [ ] Success triggers door unlock

**Dependencies:** Custom UI Widget, Interaction System  
**Blueprints Needed:** BP_LogicPuzzle, WBP_LogicInterface, BP_LogicNode (parent class)  
**Priority:** LOW - Week 6-7 (save for later)

**Implementation Notes:**
- Use UMG widgets for draggable nodes
- Store node connections in arrays/maps
- Simple validator checks connection pattern against solution
- Start simple: just 3-4 node types

---

### 🎨 ENVIRONMENTAL

#### Lighting System
- [ ] Atmospheric lighting per room
- [ ] Dynamic lights (triggered by puzzles)
- [ ] Emergency lighting for tension
- [ ] Glow materials for interactive objects

**Dependencies:** None  
**Priority:** LOW - Week 7 (polish phase)

---

#### Sound Design
- [ ] Ambient room sounds
- [ ] Footstep sounds
- [ ] Door/button/mechanism SFX
- [ ] Success/failure audio feedback
- [ ] Background music (optional)

**Dependencies:** None  
**Priority:** LOW - Week 7-8 (polish phase)

---

#### UI System
- [ ] Main menu
- [ ] Pause menu
- [ ] Interaction prompts
- [ ] Optional: hint system
- [ ] Optional: puzzle progress tracker

**Dependencies:** None  
**Blueprints Needed:** WBP_MainMenu, WBP_HUD, WBP_PauseMenu  
**Priority:** MEDIUM - Week 5

---

## Room Design Plan

### Room 0: Tutorial/Spawn
- **Purpose:** Teach basic movement and interaction
- **Mechanics:** Button → Door (simplest puzzle)
- **Status:** Not Started

---

### Room 1: Box Pushing Basics
- **Purpose:** Introduce pushable boxes
- **Mechanics:** Push box onto pressure plate → Door opens
- **Status:** Not Started

---

### Room 2: Pressure Plate Combinations
- **Purpose:** Multiple pressure plates
- **Mechanics:** Need 2+ plates activated simultaneously (use boxes)
- **Status:** Not Started

---

### Room 3: Timed Challenge
- **Purpose:** Introduce time pressure
- **Mechanics:** Hit button, sprint through timed door
- **Status:** Not Started

---

### Room 4: **CODING PUZZLE ROOM**
- **Purpose:** Visual programming challenge
- **Mechanics:** Arrange logic nodes to solve problem
- **Status:** Design Phase
- **Notes:** Save this for after core mechanics are solid

---

### Room 5: Combination Room
- **Purpose:** Use all learned mechanics
- **Mechanics:** Boxes + pressure plates + timed doors + buttons
- **Status:** Not Started

---

### Room 6-8: (Optional Expansion)
- **Status:** Future content

---

## Technical Architecture

### Blueprint Hierarchy
```
GameMode: BP_SimRoomGameMode
PlayerController: BP_SimRoomPlayerController
Character: BP_SimRoomCharacter (from FP template)

Interactables (all implement BPI_Interactable):
├── BP_Door
│   └── BP_TimedDoor
├── BP_Button
├── BP_PressurePlate
└── BP_PushableBox

Special:
└── BP_LogicPuzzle
    └── BP_LogicNode (parent for node types)
```

### Key Interfaces
- **BPI_Interactable:** Interact() event
- **BPI_Triggerable:** Activate(), Deactivate() events

---

## Development Phases

### Phase 1: Foundation (Week 1-2)
- Set up project from FP template
- Implement interaction system
- Create basic button → door puzzle
- **Milestone:** Can press button, door opens

### Phase 2: Core Puzzles (Week 3-4)
- Pushable boxes
- Pressure plates
- Timed doors
- Build Rooms 1-3
- **Milestone:** 3 playable rooms with different mechanics

### Phase 3: Visual Programming (Week 5-6)
- Design logic puzzle system
- Build UI for node manipulation
- Implement validation
- Create Room 4
- **Milestone:** Coding puzzle room functional

### Phase 4: Integration & Expansion (Week 7)
- Build combination room (Room 5)
- Add lighting and atmosphere
- Create UI menus
- **Milestone:** Full playable experience

### Phase 5: Polish (Week 8)
- Sound design
- Visual effects
- Playtesting and bug fixes
- Balance puzzle difficulty
- **Milestone:** Shippable v1.0

---

## Resources & Assets

### Free Asset Packs (Unreal Marketplace)
- Starter Content (included)
- [Add specific packs as you find them]

### Audio
- [List sound sources as you add them]

### Learning Resources
- Unreal Engine Documentation: Blueprints
- YouTube: Unreal Engine First Person Tutorial
- [Add specific tutorials you find helpful]

---

## Git Integration Notes

### Repository Structure
```
SimRoom1.0/
├── Content/
│   ├── Blueprints/
│   ├── Maps/
│   ├── UI/
│   └── Materials/
├── Config/
└── README.md
```

### Branch Strategy
- `main` - stable builds only
- `dev` - active development
- `feature/[feature-name]` - individual features
- `experiment/[idea]` - testing wild ideas

### Important: Unreal + Git
- Use `.gitignore` for Unreal (large binary files)
- Consider Git LFS for assets
- Commit blueprint changes with clear messages

---

## Notes & Ideas

### Future Features (Maybe v2.0)
- [ ] Multiple solution paths per puzzle
- [ ] Collectibles/hidden areas
- [ ] Story elements via audio logs
- [ ] Speed-run timer
- [ ] Room editor/level creator

### Random Ideas Parking Lot
- Gravity manipulation mechanic?
- Color-coded circuits puzzle?
- Mirror/reflection puzzle?

---

## Changelog

**2025-12-18:** Initial blueprint created, project scoped, visual programming puzzle selected for Room 4