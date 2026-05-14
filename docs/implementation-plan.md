# SimRoom 1.0 Implementation Plan

**Status:** Phase 1 foundation in progress  
**Engine:** Unreal Engine 5.x  
**Implementation:** Blueprint-first  
**Primary Reference:** `docs/spec-sheet.md` and `simroom_project_blueprint.md`  
**Last Updated:** May 14, 2026

## Implementation Principles

- Build the smallest playable loop first: player presses a button, a door opens, and the player exits the room.
- Use Blueprint interfaces for communication between puzzle inputs and outputs.
- Keep puzzle actors reusable, instance-configurable, and easy to place in rooms.
- Favor clear player feedback over hidden logic.
- Finish Rooms 0-3 before investing heavily in the visual programming puzzle.
- Treat Room 5 and optional expansion rooms as stretch goals until the core path is stable.

## Target Unreal Project Setup

### Base Project

- Create or open an Unreal Engine 5.x project using the First Person Template.
- Configure the default map to the tutorial/spawn room once Room 0 exists.
- Configure project input for movement, mouse look, jump, interact, and pause.
- Keep implementation Blueprint-first unless a later requirement clearly needs C++.

### Recommended Content Structure

```text
Content/
  Blueprints/
    Player/
      BP_SimRoomCharacter
      BP_SimRoomPlayerController
      BP_InteractionComponent
    Interactables/
      BPI_Interactable
      BPI_Triggerable
      BP_Door
      BP_TimedDoor
      BP_Button
      BP_PressurePlate
      BP_PushableBox
    Puzzles/
      BP_LogicPuzzle
      BP_LogicNode
  Maps/
    M_Room00_Tutorial
    M_Room01_BoxBasics
    M_Room02_PlateCombination
    M_Room03_TimedChallenge
    M_Room04_CodingPuzzle
    M_Room05_Combination
  UI/
    WBP_HUD
    WBP_MainMenu
    WBP_PauseMenu
    WBP_LogicInterface
  Materials/
  Audio/
```

## Blueprint Interfaces

### `BPI_Interactable`

Use this interface for anything the player can directly interact with.

**Functions / Events:**

- `Interact(Interactor)`
- `CanInteract(Interactor) -> Boolean`
- `GetInteractionText() -> Text`
- Optional: `OnFocusStart()`
- Optional: `OnFocusEnd()`

**Usage Notes:**

- `CanInteract` prevents locked or inactive objects from showing misleading prompts.
- `OnFocusStart` and `OnFocusEnd` can drive highlight materials or outline effects.
- Buttons, puzzle terminals, and optionally doors should implement this interface.

### `BPI_Triggerable`

Use this interface for anything that can be activated or deactivated by another system.

**Functions / Events:**

- `Activate(SourceActor)`
- `Deactivate(SourceActor)`
- Optional: `Toggle(SourceActor)`
- Optional: `IsActive() -> Boolean`

**Usage Notes:**

- Doors, timed doors, lights, and puzzle relays can implement this interface.
- Buttons and pressure plates should call this interface on linked target actors.
- Avoid direct casts from buttons to doors when an interface call is sufficient.

## Core Systems

### Player Character and Controller

**Blueprints:** `BP_SimRoomCharacter`, `BP_SimRoomPlayerController`  
**Dependencies:** First Person Template

Implementation steps:

1. Create project from the First Person Template.
2. Rename or derive the template character as `BP_SimRoomCharacter`.
3. Add interact input mapping for E.
4. Add pause input mapping.
5. Add `BP_InteractionComponent` to the character.
6. Add or connect `WBP_HUD` for crosshair and interaction prompt.

Verification:

- Player can move, look, and jump.
- Pressing E calls interaction only when a valid target is in range.
- HUD prompt updates as the player looks at and away from interactables.

### Interaction Component

**Blueprint:** `BP_InteractionComponent`  
**Dependencies:** `BPI_Interactable`, player camera

Suggested variables:

- `InteractionRange`: Float, default 300-500 units
- `TraceChannel`: Trace channel used for interactables
- `FocusedActor`: Actor reference
- `bHasFocusedActor`: Boolean

Implementation steps:

1. On tick or timed interval, trace from the player camera forward.
2. Check whether the hit actor implements `BPI_Interactable`.
3. Call `CanInteract`.
4. If focus changes, call `OnFocusEnd` on old actor and `OnFocusStart` on new actor.
5. Update HUD interaction prompt from `GetInteractionText`.
6. On interact input, call `Interact` on the focused actor.

Verification:

- Focus changes cleanly between actors.
- Prompt disappears when no target is valid.
- Interaction range is predictable and tunable.
- Repeated interactions do not duplicate events unexpectedly.

### Door System

**Blueprint:** `BP_Door`  
**Interfaces:** `BPI_Triggerable`, optionally `BPI_Interactable`

Suggested variables:

- `bIsLocked`: Boolean
- `bIsOpen`: Boolean
- `OpenAngle` or `OpenOffset`
- `OpenDuration`
- `LinkedRequiredActivators`: Optional array for multi-trigger logic
- `OpenSFX`, `CloseSFX`, `LockedSFX`

Implementation steps:

1. Create a door mesh actor with closed and open transforms.
2. Use a Timeline to animate between closed and open state.
3. Implement `Activate` to unlock and/or open the door.
4. Implement `Deactivate` for doors that should close when a trigger is released.
5. Add audio feedback for open, close, and locked attempts.
6. Add editor-exposed variables for room-specific behavior.

Verification:

- Door opens and closes smoothly.
- Door state does not desync when activated repeatedly.
- Locked door gives feedback without opening.
- Door can be triggered by button and pressure plate.

### Button System

**Blueprint:** `BP_Button`  
**Interfaces:** `BPI_Interactable`

Suggested variables:

- `ButtonMode`: Enum, `OneShot`, `Toggle`, `Hold`
- `LinkedTargets`: Array of actors implementing `BPI_Triggerable`
- `bIsPressed`: Boolean
- `PressSFX`
- `PressedMaterial` and `DefaultMaterial`

Implementation steps:

1. Implement `Interact` for press behavior.
2. Animate or offset the button mesh on press.
3. Call `Activate` on linked targets.
4. For toggle mode, alternate between `Activate` and `Deactivate`.
5. For one-shot mode, optionally disable after successful activation.
6. Add material or glow feedback for state.

Verification:

- Button reliably triggers linked door.
- Toggle behavior is readable.
- One-shot behavior cannot spam unintended events.
- Linked targets can be configured per instance in the editor.

### Pushable Box System

**Blueprint:** `BP_PushableBox`

Suggested variables:

- `Mass`
- `FrictionOverride`
- `bCanTriggerPressurePlates`
- Optional: `ResetTransform`

Implementation steps:

1. Create a physics-enabled cube actor.
2. Tune mass, damping, and collision for first-person pushing.
3. Add a simple material or marking that identifies it as pushable.
4. Optionally add a reset behavior for puzzle recovery.
5. Ensure collision works with player capsule and pressure plates.

Verification:

- Player can push the box without special controls.
- Box does not jitter excessively.
- Box can rest on pressure plates.
- Box is hard to lose or wedge in normal room layouts.

### Pressure Plate System

**Blueprint:** `BP_PressurePlate`  
**Interfaces:** `BPI_Triggerable` as needed for chaining

Suggested variables:

- `RequiredWeight`
- `CurrentWeight`
- `ValidActors`
- `LinkedTargets`
- `bIsActivated`
- `ActivationSFX`
- `DeactivationSFX`

Implementation steps:

1. Add collision volume above the plate.
2. Track begin and end overlap for player and boxes.
3. Calculate whether current overlap satisfies `RequiredWeight`.
4. When state changes to active, call `Activate` on linked targets.
5. When state changes to inactive, call `Deactivate` on linked targets.
6. Animate plate depression on activation and return on deactivation.

Verification:

- Player and boxes can activate the plate if allowed.
- Plate deactivates when weight leaves.
- Multiple overlapping actors do not break state.
- Linked door opens and closes according to room design.

### Timed Door System

**Blueprint:** `BP_TimedDoor`, child of `BP_Door`

Suggested variables:

- `OpenTime`
- `WarningTime`
- `RemainingTime`
- `bCanRetrigger`
- `CountdownWidget` or in-world indicator

Implementation steps:

1. Derive from `BP_Door`.
2. Override or extend `Activate` to open the door and start a timer.
3. Play warning feedback near the end of the timer.
4. Close automatically when the timer expires.
5. Decide whether retriggering resets the timer or is ignored.

Verification:

- Door opens on activation.
- Door closes after configured duration.
- Warning feedback plays before close.
- Retrigger behavior is consistent and documented per instance.

## Visual Programming Puzzle

**Blueprints:** `BP_LogicPuzzle`, `BP_LogicNode`  
**Widget:** `WBP_LogicInterface`

### Minimum Viable Version

Start with a small, pattern-matching puzzle instead of a general-purpose programming language.

Initial node types:

- `Input`
- `IF`
- `AND`
- `OR`
- `Output`

Suggested data model:

- `AvailableNodes`: Array of node definitions
- `PlacedNodes`: Array of active node widgets or structs
- `Connections`: Array of source-target node pairs
- `SolutionPattern`: Array or map describing valid connections

Implementation steps:

1. Create an in-world puzzle terminal actor implementing `BPI_Interactable`.
2. On interact, open `WBP_LogicInterface`.
3. Display a small set of draggable or selectable node blocks.
4. Allow player to connect nodes.
5. Add a submit button.
6. Validate current connections against `SolutionPattern`.
7. On success, call `Activate` on the linked room exit.
8. On failure, show feedback and allow retry.

Verification:

- UI opens and closes reliably.
- Player can create and remove connections.
- Incorrect answers do not lock the puzzle.
- Correct answer triggers the linked door exactly once.
- Puzzle can be solved without prior programming knowledge.

## Room Build Plan

### Room 0: Tutorial / Spawn

Build order:

1. Create simple spawn room.
2. Place player start.
3. Place one button and one door.
4. Link button to door.
5. Add prompt text or visual cue for interaction.

Exit criteria:

- New player can learn movement and interaction.
- Button opens the exit door.
- No other mechanics are required.

### Room 1: Box Pushing Basics

Build order:

1. Create box-friendly room layout.
2. Place pressure plate near exit.
3. Place pushable box within clear sightline.
4. Link pressure plate to door.
5. Add visual language that implies "box goes on plate."

Exit criteria:

- Player can solve by pushing the box onto the plate.
- Door opens while plate is active.
- Box cannot easily be lost.

### Room 2: Pressure Plate Combinations

Build order:

1. Create room with at least two pressure plates.
2. Add enough boxes to satisfy all required plates.
3. Link plates through either direct door requirements or a relay Blueprint.
4. Make simultaneous activation readable.

Exit criteria:

- Door opens only when required plates are active.
- Player can understand what changed when each plate activates.
- Puzzle remains recoverable after mistakes.

### Room 3: Timed Challenge

Build order:

1. Create short route from button to timed door.
2. Place button at route start.
3. Link button to timed door.
4. Tune duration until challenge is fair but noticeable.
5. Add countdown, warning light, or warning sound.

Exit criteria:

- Player understands the timed objective.
- Door closes after the timer.
- Player can retry without resetting the level.

### Room 4: Coding Puzzle Room

Build order:

1. Create puzzle terminal.
2. Build `WBP_LogicInterface`.
3. Implement minimum node set.
4. Add one validation pattern.
5. Link success to room exit.
6. Add simple instructions in-world or in UI.

Exit criteria:

- Player opens the interface from the terminal.
- Player can solve by arranging and connecting nodes.
- Correct solution unlocks the exit.

### Room 5: Combination Room

Build order:

1. Select 2-3 already proven systems to combine.
2. Sketch puzzle sequence before building.
3. Add room geometry and reset/recovery paths.
4. Link systems through interfaces or relay actors.
5. Playtest for clarity and backtracking issues.

Exit criteria:

- Room requires mastery, not guessing.
- Systems interact without fragile one-off casts.
- Puzzle can be completed from a fresh playthrough.

## Development Phases

### Phase 1: Foundation, Weeks 1-2

Deliverables:

- Unreal First Person Template baseline
- `BP_SimRoomCharacter`
- `BP_InteractionComponent`
- `BPI_Interactable`
- `BPI_Triggerable`
- `BP_Door`
- `BP_Button`
- `WBP_HUD`
- Room 0

Milestone:

- Player can press a button and open a door.

### Phase 2: Core Puzzles, Weeks 3-4

Deliverables:

- `BP_PushableBox`
- `BP_PressurePlate`
- `BP_TimedDoor`
- Rooms 1-3
- Basic room-to-room progression

Milestone:

- Three playable puzzle rooms demonstrate different mechanics.

### Phase 3: Visual Programming, Weeks 5-6

Deliverables:

- `BP_LogicPuzzle`
- `BP_LogicNode`
- `WBP_LogicInterface`
- Node validation
- Room 4

Milestone:

- Coding puzzle room is functional and unlocks its exit.

### Phase 4: Integration and Expansion, Week 7

Deliverables:

- Room 5 if schedule allows
- Main menu
- Pause menu
- Room lighting pass
- Consistent material language for interactables

Milestone:

- Full intended experience is playable from start to finish.

### Phase 5: Polish, Week 8

Deliverables:

- Sound effects
- Ambient audio
- Visual feedback pass
- Puzzle difficulty pass
- Bug fixes from playtesting

Milestone:

- Shippable version 1.0 candidate.

## Testing and Verification

### Per-System Checklist

- Interaction prompt appears only for valid targets.
- Every interactable can be used repeatedly or disabled intentionally.
- Doors never get stuck halfway through normal activation.
- Buttons trigger all configured targets.
- Pressure plates activate and deactivate correctly.
- Physics boxes can activate plates and remain recoverable.
- Timed doors can be retried.
- Logic puzzle succeeds and fails predictably.

### Per-Room Checklist

- Player start faces a useful first landmark.
- Exit door is visible or discoverable.
- Puzzle goal is readable before or during experimentation.
- Failure states are recoverable without restarting the editor.
- Player cannot bypass the intended puzzle through simple jumping or collision gaps.
- Lighting makes interactables legible.
- Audio feedback supports state changes.

### Build Verification

- Project opens in Unreal Engine 5.x without missing references.
- Default map starts playable flow.
- Play-in-editor works from Room 0.
- Full intended room sequence can be completed.
- Console/log has no recurring Blueprint runtime errors during a normal playthrough.

## Git and Asset Workflow

### Branching

- `main`: stable builds only
- `dev`: active integration branch
- `feature/[feature-name]`: individual mechanics or rooms
- `experiment/[idea]`: isolated prototype work

### Unreal Git Practices

- Keep `.gitignore` configured for Unreal generated files.
- Consider Git LFS before adding large binary assets.
- Commit Blueprint changes with clear messages describing the gameplay change.
- Avoid unrelated Blueprint edits in the same commit when possible.
- Test the affected room before committing a mechanic change.

## Documentation Updates

Update documentation when one of these changes:

- Room count or room order changes.
- A core mechanic is added, removed, or re-scoped.
- Blueprint names or interface contracts change.
- A milestone is completed.
- Visual programming puzzle scope changes.

Recommended files to keep in sync:

- `README.md`
- `simroom_project_blueprint.md`
- `docs/spec-sheet.md`
- `docs/implementation-plan.md`

## Immediate Next Steps

1. Finish installing Visual Studio C++ build tools.
2. Compile `SimRoomEditor`.
3. Create Blueprint children from the native Phase 1 classes.
4. Create Room 0 and verify the button-door loop.
5. Set default maps after `M_Room00_Tutorial` exists.
6. Commit the foundation once the loop works in play-in-editor.
