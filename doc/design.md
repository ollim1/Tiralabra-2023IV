# Design

The AI in this project will be implemented using the Alpha-beta pruning variant of the minimax algorithm and any data structures it requires.

## Data structures

The Alpha-beta algorithm will form an implicit search tree that is explored only partially according to a heuristic.

## Time Complexity

As the algorithm forms a tree structure, it has a time complexity of $O(b^d)$ where $b$ is the number leaf nodes visited and $d$ is the depth of the tree, same as a minimax search.

## Input/Output

The application will use a textual representation of the chess board printed to standard output to visualize game state on a per-move basis. Move input will consist of a pair of board coordinates; e.g. `b2 e3`. AIs will be possible to pit against each other.

## Sources
[Wikipedia on Alpha-beta Pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)
[Guide on implementing Minimax games](https://tiralabra.github.io/2023_p4/fi/aiheet/minimax.pdf)
