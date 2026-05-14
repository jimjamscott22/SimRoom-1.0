# Puzzle Blueprints

Planned assets:

- `BP_LogicPuzzle`
- `BP_LogicNode`

Implementation notes:

- Defer the visual programming puzzle until Rooms 0-3 are reliable.
- Start with a small pattern-matching validator instead of a general-purpose programming system.
- Initial node set: `Input`, `IF`, `AND`, `OR`, `Output`.
- On success, activate linked room outputs through `BPI_Triggerable`.
