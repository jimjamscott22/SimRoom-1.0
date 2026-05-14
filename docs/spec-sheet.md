# SimRoom 1.0 Spec Sheet

**Status:** Planning and foundation  
**Engine:** Unreal Engine 5.x  
**Implementation:** Blueprint-first  
**Source Blueprint:** `simroom_project_blueprint.md`  
**Last Updated:** May 13, 2026

## Product Summary

SimRoom 1.0 is a first-person puzzle explorer set inside a sci-fi research facility. The player escapes a sequence of themed rooms by learning and combining environmental puzzle mechanics, ending with a distinctive visual programming puzzle.

The target experience is a compact, Portal-inspired learning project that prioritizes clear puzzle readability, modular Blueprint systems, and a shippable 5-room vertical slice before optional expansion.

## Target Experience

- **Genre:** First-person environmental puzzle game
- **Perspective:** First-person
- **Tone:** Sci-fi research facility, lightly tense, readable, and systems-driven
- **Session Shape:** Linear room progression with escalating puzzle mechanics
- **Core Fantasy:** Learn a system, solve the room, unlock the next space
- **Primary Inspiration:** Portal-style spatial puzzle progression with a custom logic-programming room

## Development Scope

### Target Release Scope

- 5 playable puzzle rooms plus tutorial/spawn room
- 1 optional combination room if schedule allows
- First-person movement and interaction
- Doors, buttons, pressure plates, pushable boxes, and timed doors
- One visual programming puzzle room
- Basic HUD, interaction prompt, pause menu, and main menu
- Atmospheric lighting and essential sound feedback

### Out of Scope for Version 1.0

- Multiplayer
- Combat
- Full narrative campaign
- Room editor or level creator
- Multiple solution paths for every puzzle
- Advanced physics puzzles beyond boxes and triggers
- Procedural level generation

### Optional Version 2.0 Ideas

- Multiple solution paths
- Collectibles and hidden areas
- Audio-log story delivery
- Speed-run timer
- Room editor
- Gravity, color-circuit, or mirror-based puzzle mechanics

## Audience and Goals

### Player Audience

- Players who enjoy concise puzzle rooms and logic challenges
- Players familiar with first-person controls
- Players interested in programming-adjacent puzzles without needing real code syntax

### Project Goals

- Learn Unreal Engine 5 Blueprint workflows
- Build a reusable event-driven interactable framework
- Practice level design through escalating puzzle rooms
- Deliver a small but complete playable experience
- Keep systems modular enough for later room expansion

## Core Gameplay Loop

1. Enter a room.
2. Observe the door, interactables, and environmental clues.
3. Experiment with objects and triggers.
4. Solve the room mechanic.
5. Unlock the exit.
6. Move to the next room, where the mechanic is expanded or combined.

## Player Capabilities

- Move with WASD.
- Look with mouse.
- Jump.
- Aim at objects from the camera center.
- Interact with valid objects using the E key.
- Push physics boxes through movement/contact.
- Read interaction prompts and puzzle feedback.
- Pause and resume play.

## Required Game Systems

### Player Controller

The player character is based on the Unreal First Person Template and must support movement, mouse look, jumping, crosshair display, and camera-centered interaction.

**Primary Blueprint:** `BP_SimRoomCharacter`  
**Priority:** Critical  
**Acceptance Criteria:**

- Player can move, look, and jump reliably.
- Camera center can drive interaction traces.
- Crosshair is visible and unobtrusive.
- Movement works in all planned room layouts.

### Interaction System

The interaction system handles raycast detection, interactable highlighting, prompt display, and interaction event dispatch.

**Primary Blueprints:** `BP_InteractionComponent`, `BPI_Interactable`  
**Priority:** Critical  
**Acceptance Criteria:**

- Camera trace detects interactables in front of the player.
- Valid targets can show highlight or other readable affordance.
- HUD shows a "Press E to interact" prompt only for valid targets.
- Pressing E calls the target object's interaction behavior.
- Non-interactable objects do not show prompts or consume interaction input.

### Door System

Doors serve as room gates and puzzle outputs. Doors can be locked, unlocked, opened, closed, and triggered by other puzzle systems.

**Primary Blueprint:** `BP_Door`  
**Priority:** High  
**Acceptance Criteria:**

- Door supports open and close animation.
- Door supports locked and unlocked states.
- Door can be controlled by buttons, pressure plates, timed logic, or puzzle validation.
- Door gives clear visual and audio feedback when opened, closed, or locked.

### Button and Switch System

Buttons provide simple player-triggered puzzle inputs. They can operate as one-shot, toggle, or hold-style controls depending on room needs.

**Primary Blueprint:** `BP_Button`  
**Priority:** High  
**Acceptance Criteria:**

- Player can interact with a button.
- Button plays readable press feedback.
- Button can activate one or more linked triggerable targets.
- Button state is visually readable through color, glow, position, or animation.

### Pushable Box System

Pushable boxes are physics-driven puzzle objects used to activate pressure plates or block/unblock routes.

**Primary Blueprint:** `BP_PushableBox`  
**Priority:** Medium  
**Acceptance Criteria:**

- Box is physics-enabled and moves when pushed by the player.
- Box mass can be tuned per instance.
- Box can activate pressure plates.
- Box does not easily leave intended puzzle bounds during normal play.

### Pressure Plate System

Pressure plates detect overlap from the player or boxes, evaluate weight thresholds, and trigger linked targets while active.

**Primary Blueprint:** `BP_PressurePlate`  
**Priority:** Medium  
**Acceptance Criteria:**

- Plate detects valid overlapping actors.
- Plate can require a configurable weight threshold.
- Plate broadcasts activate and deactivate events.
- Plate has readable depressed/resting visual states.

### Timed Door System

Timed doors open for a configured duration after activation, then close automatically.

**Primary Blueprint:** `BP_TimedDoor`, child of `BP_Door`  
**Priority:** Medium  
**Acceptance Criteria:**

- Timed door opens on trigger.
- Door remains open for configurable duration.
- Countdown or warning feedback communicates remaining time.
- Door can be retriggered without breaking state.

### Visual Programming Puzzle

The visual programming puzzle is the signature room mechanic. The player arranges and connects simple logic nodes to satisfy a target pattern.

**Primary Blueprints:** `BP_LogicPuzzle`, `BP_LogicNode`  
**Primary Widget:** `WBP_LogicInterface`  
**Priority:** Low until core mechanics are stable  
**Acceptance Criteria:**

- Player can open the puzzle interface from an in-world object.
- Player can manipulate a small set of logic nodes.
- Puzzle can validate a submitted solution.
- Correct solution unlocks or opens the room exit.
- Incorrect solution provides readable feedback without blocking retry.

## UI Requirements

### Required UI

- Crosshair
- Interaction prompt
- Main menu
- Pause menu
- Basic visual programming interface

### Optional UI

- Hint system
- Puzzle progress tracker
- Timed door countdown indicator

## Audio and Visual Requirements

### Lighting

- Each room should have distinct atmospheric lighting.
- Interactive objects should use consistent glow, color, or material language.
- Emergency or warning lighting may be used for timed challenges.

### Sound

- Footsteps
- Door open, close, and locked feedback
- Button and pressure plate activation
- Puzzle success and failure feedback
- Ambient room loops
- Optional background music

## Room Specification

### Room 0: Tutorial / Spawn

**Purpose:** Teach movement, looking, and interaction.  
**Mechanic:** Button opens door.  
**Required Systems:** Player controller, interaction, button, door.  
**Completion Condition:** Player presses a button and exits through the opened door.

### Room 1: Box Pushing Basics

**Purpose:** Introduce physics boxes and pressure plates.  
**Mechanic:** Push box onto pressure plate to open door.  
**Required Systems:** Pushable box, pressure plate, door.  
**Completion Condition:** Box activates plate and unlocks exit.

### Room 2: Pressure Plate Combinations

**Purpose:** Require simultaneous trigger logic.  
**Mechanic:** Multiple plates must be active at once, usually with boxes.  
**Required Systems:** Multiple pressure plates, boxes, trigger aggregation.  
**Completion Condition:** All required plates are active and the exit opens.

### Room 3: Timed Challenge

**Purpose:** Introduce time pressure.  
**Mechanic:** Press button, sprint through timed door.  
**Required Systems:** Button, timed door, warning feedback.  
**Completion Condition:** Player reaches exit before timed door closes.

### Room 4: Coding Puzzle Room

**Purpose:** Deliver the unique visual programming challenge.  
**Mechanic:** Arrange and connect logic nodes to match a target solution.  
**Required Systems:** Logic puzzle Blueprint, UMG interface, validation.  
**Completion Condition:** Correct logic solution unlocks the exit.

### Room 5: Combination Room

**Purpose:** Test mastery of learned mechanics.  
**Mechanic:** Buttons, boxes, plates, and timed doors combined.  
**Required Systems:** All core puzzle systems.  
**Completion Condition:** Player solves a multi-step puzzle using multiple mechanics.

### Rooms 6-8: Optional Expansion

**Purpose:** Extend the game if time remains.  
**Mechanic:** To be determined after Room 5 is playable.  
**Completion Condition:** Future scope.

## Technical Architecture

### Blueprint Class Targets

```text
GameMode: BP_SimRoomGameMode
PlayerController: BP_SimRoomPlayerController
Character: BP_SimRoomCharacter

Interactables:
- BPI_Interactable
- BPI_Triggerable
- BP_Door
- BP_TimedDoor
- BP_Button
- BP_PressurePlate
- BP_PushableBox

Special:
- BP_LogicPuzzle
- BP_LogicNode
- WBP_LogicInterface
```

### Key Interfaces

- `BPI_Interactable`: exposes `Interact`.
- `BPI_Triggerable`: exposes `Activate` and `Deactivate`.

### Content Organization

```text
Content/
  Blueprints/
    Player/
    Interactables/
    Puzzles/
  Maps/
  UI/
  Materials/
  Audio/
Config/
docs/
```

## Schedule Targets

| Phase | Target | Outcome |
| --- | --- | --- |
| Phase 1 | Weeks 1-2 | Foundation systems and button-door tutorial |
| Phase 2 | Weeks 3-4 | Core puzzle mechanics and Rooms 1-3 |
| Phase 3 | Weeks 5-6 | Visual programming puzzle and Room 4 |
| Phase 4 | Week 7 | Combination room, menus, lighting integration |
| Phase 5 | Week 8 | Audio, polish, playtesting, bug fixes |

## Release Criteria

Version 1.0 is considered shippable when:

- The player can complete Room 0 through Room 4 without editor intervention.
- Room 5 is complete or intentionally deferred.
- All required interactable systems are reusable and instance-configurable.
- UI prompts are clear and do not linger incorrectly.
- Puzzle success and failure states are readable.
- Doors and triggers do not enter broken states during normal play.
- Basic sound and lighting polish is present.
- The project opens cleanly in Unreal Engine 5.x.

## Primary Risks

- Visual programming UI scope may grow beyond the timeline.
- Blueprint references between triggers and doors can become hard to manage without consistent interfaces.
- Physics boxes may create puzzle-breaking edge cases.
- Room count may exceed available polish time.
- Asset and audio sourcing may be underestimated.

## Risk Controls

- Build and test the button-door loop first.
- Keep every puzzle object instance-configurable.
- Defer the visual programming room until Rooms 0-3 are reliable.
- Start the logic puzzle with only 3-4 node types.
- Treat Room 5 and optional Rooms 6-8 as stretch scope until the core path is playable.
