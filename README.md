# CC2023_LostInTheStars
Team: TripleChickens
Decription: strategy to play the game 'Lost in the Stars' in the final round of Coding Challenge 2023 - fit@HCMUS. 

## About the game:
- Similar to `Paper.io`
- Given a `m x n` board map with obstacles, players (up to 4) try to expand their territory as much as possible to win. 
- Stepping to a cell without obstacle, player will mark it by the `color` which represents their territory.
- Every cell in a player's`closed_path` (no existed paths to travel from those cells to the borders of the map without touching the `closed_path`) will be marked as the player's territory right after that `closed_path` is formed.
- Others will die if they are standing inside enemy's `closed_path`
- After `k` moves, the border of the map will shrink up `1 unit`

## Team's strategy:
### Check `safe` cell:
- A cell is call `safe` if this scenario happens: player travels to that cells, then there exists a path to travel to ensure that player will be safe at the next shrinking phase.
- Always check before other strategies.
### Initial Position Picking: 
(ideal position)
- At the map's edge, away from a `corner` which is possible to travel to that in `k/2` moves along the borders
- Claim the `corner` and other cells along the borders, then move to safe position sucessfully right after the board shrinks.
=> Claim as much cells along the borders as possible, especially the `corner` - enhance the possibility and decrease required steps to form `closed_path`
### Moving strategy:
The `next-cell-to-travel` criterias:
- Is a `safe` cell
- Closest to the current borders
- Different color from the team
### See the future:
When there is more than `1/3` obstable cells in the standing round, we will travel to the next round `1 moves` faster
### A team is chasing us!
- They will fail as according to `Moving strategy`, we will return and chase them!
