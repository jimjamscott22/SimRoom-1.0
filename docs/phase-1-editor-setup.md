# Phase 1 Editor Setup

This project now has native, Blueprintable C++ bases for the Phase 1 button-door loop.

## Build Prerequisite

Unreal Engine 5.7 is installed on this machine, but the local build check could not compile because Visual Studio 2022 C++ build tools were missing.

Required component:

- Visual Studio 2022 17.8 or later
- MSVC v143 VS 2022 C++ x64/x86 build tools

After installing the toolchain, open `SimRoom1.0.uproject` or run the Unreal build for `SimRoomEditor`.

## Native Classes Added

- `ASimRoomGameMode`
- `ASimRoomCharacter`
- `ASimRoomPlayerController`
- `ASimRoomHUD`
- `USimRoomInteractionComponent`
- `UInteractableInterface`
- `UTriggerableInterface`
- `ASimRoomDoor`
- `ASimRoomButton`

## Recommended Blueprint Assets

Create these Blueprint assets in the editor as children of the native classes:

```text
Content/Blueprints/Core/BP_SimRoomGameMode
Content/Blueprints/Player/BP_SimRoomCharacter
Content/Blueprints/Player/BP_SimRoomPlayerController
Content/Blueprints/Player/BP_InteractionComponent
Content/Blueprints/Interactables/BP_Door
Content/Blueprints/Interactables/BP_Button
Content/UI/WBP_HUD
Content/Maps/M_Room00_Tutorial
```

`BP_InteractionComponent` is optional because `ASimRoomCharacter` already owns a native `InteractionComponent`.

## Room 0 Assembly

1. Create `M_Room00_Tutorial`.
2. Add a `PlayerStart`.
3. Add a `BP_Button` instance.
4. Add a `BP_Door` instance.
5. Assign the door actor to the button instance's `LinkedTargets` array.
6. Press Play and verify that aiming at the button shows the HUD prompt.
7. Press `E` to activate the button and open the door.

## Current Config

- Default game mode points to `/Script/SimRoom.SimRoomGameMode`.
- Input mappings exist for WASD movement, mouse look, Space jump, `E` interact, and Escape pause.
- Default map is still unset until `M_Room00_Tutorial` exists.
