# Player Blueprints

Planned assets:

- `BP_SimRoomCharacter`
- `BP_SimRoomPlayerController`
- `BP_InteractionComponent`

Implementation notes:

- Derive the character from the Unreal First Person Template.
- Add `BP_InteractionComponent` to the character.
- Support movement, mouse look, jump, crosshair display, E-key interaction, and pause input.
- Keep interaction traces camera-centered with a tunable range.
