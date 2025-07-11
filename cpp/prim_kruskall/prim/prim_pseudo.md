# PRIM PSEUDOCODE
---
## Initialization of Graph
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
---
## Prim's Algorithm for MST
- Pick random vertex *s* inside graph, set vertex = 0.
    - `dist[s] = 0;`
- While (MST is missing a vertex)
    - Pick vertex *v* with shortest edge in group of adjacent edges.
    - Add *v* to MST.
    ```
    for each edge of *v*, (v1,v2)
        if (length(v1,v2) < dist[v2])
            dist[v2] = length(v1,v2)
            edges[v2] = v1
    ```
    - Possibly update U depending on implementation.
        - End if
    - End for
- End while
