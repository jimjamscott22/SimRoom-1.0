# Interactable Blueprints

Planned assets:

- `BPI_Interactable`
- `BPI_Triggerable`
- `BP_Door`
- `BP_TimedDoor`
- `BP_Button`
- `BP_PressurePlate`
- `BP_PushableBox`

Implementation notes:

- Use `BPI_Interactable` for player-facing objects.
- Use `BPI_Triggerable` for objects activated by buttons, plates, puzzle validation, or relays.
- Avoid direct casts between puzzle inputs and outputs when an interface call is enough.
- Expose linked targets, activation modes, timing, and feedback settings per instance.
