# PRIM PSEUDOCODE
---
- Given a graph G with edges E of the form (v1,v2) and vertices V:
    - dist: Array fo distances from the source to each vertex.
    - edges: Array indicating, for a given vertex, the closest adjacent
        vertex.
    - ii: loop index.
    - MST: List of *finished* vertices.
    - U: List or heap of unfinished vertices.
- **Initialization:**
    - Set every distance to **INFINITY** until linking a vertex to ST
        is possible.

    ```
    for (ii = 0 to |V| - 1)
        dist = INFINITY
        edge[ii] = NULL;
    ```

    - End Program.
