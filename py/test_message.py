'''
On our honor, as SFSU students, we, Luis Cavinal, Chu Yi Herr,
Ramanuja Mohanty did not give or receive inappropriate help with this assignment.
All group members contributed to this work, and all concur with the submission.
We understand that we will be asked to redo the assignment in person if this work
presents any question of an honor code violation.
'''
from graph import Graph

'''
An instance of HasTwoColorClique has the syntax:
Graph;NodeColorings;Color1;Color2;CliqueSize

where

Graph is an undirected, unweighted graph defined as a white-space
delimited sequence of edges.

NodeColorings is a white-space delimited list of node colors.

Color1 and Color2 are both colors.

CliqueSize is an integer > 1.
'''

Vh2ccv = 'VERBOSE: VfyHasTwoColorClique() '
VERBOSE = True


def printV(text):
    if VERBOSE:
        print(f'{Vh2ccv}{text}')


Vh2ccd = 'DEV: VfyHasTwoColorClique() '
DEV = False


def printD(text):
    if DEV:
        print(f'{Vh2ccd}{text}')


def VfyHasTwoColorClique(I, S, H):
    S_len = len(S)
    H_len = len(H)

    if S_len == 0 or H_len == 0 or S_len > 5:
        s = f'Solution length {S_len} or hint length {H_len}'
        printV(f'{s} is unreasonable')
        return 'unsure'

    if S != 'yes':
        printV(f'The solution "{S}" is not verifying a positive instance')
        return 'unsure'

    graph_str, node_colorings, color1, color2, clique_size = I.split(';')

    color1 = color1.strip()
    color2 = color2.strip()
    clique_size = clique_size.strip()

    try:
        clique_size_int = int(clique_size)

        if clique_size_int <= 1:
            printV(f'clique_size {clique_size_int} must be an integer > 1')
            return 'unsure'

    except ValueError:
        printV(f'clique_size "{clique_size}" is not a valid integer')
        return 'unsure'

    clique = H.split()

    if len(clique) < clique_size_int:
        s = (
            f'{len(clique)} nodes in hint but '
            f'{clique_size_int} is the minimum allowed'
        )
        printV(s)
        return 'unsure'

    clique_set = set(clique)

    if len(clique_set) < len(clique):
        printV(f'Duplicate nodes in hint: {H}')
        return 'unsure'

    node_color_kv = {}
    colorings_list = node_colorings.split()

    for node_color in colorings_list:
        node, color = node_color.split(':')
        node_color_kv[node] = color

    g = Graph(graph_str, directed=False, weighted=False)
    nodes = list(g.nodes.keys())

    for node in clique:
        if node not in nodes:
            printV(f'{node} in hint but not in graph')
            return 'unsure'

        color = node_color_kv[node]

        if color not in (color1, color2):
            printV(
                f'{node} in hint is {color}, but must be either '
                f'{color1} or {color2}'
            )
            return 'unsure'

    edges = graph_str.split()
    adjacency = set()

    for edge in edges:
        u, v = edge.split(',')
        adjacency.add((u, v))
        adjacency.add((v, u))

    for i in range(len(clique)):
        for j in range(i + 1, len(clique)):
            if (clique[i], clique[j]) not in adjacency:
                printV(
                    f'Nodes {clique[i]} and {clique[j]} '
                    f'do not form an edge in the graph'
                )
                return 'unsure'

    printV(f'"{I}" is a positive instance, all verifications succeeded')
    return 'correct'


if __name__ == '__main__':

    def test_case(func, I, S, H, expected, num, comment=''):
        err = '** '
        result = func(I, S, H)
        func_name = str(func).split()[1]
        func_call = f'''{func_name}("{I}","{S}","{H}")'''

        if result == expected:
            err = ''

        print(
            f'{err}test #{num} {func_call}: '
            f'expected "{expected}", received "{result}"'
        )
        print(f'test #{num} Explanation: {comment}\n')

        return num + 1

    F = VfyHasTwoColorClique
    num = 1

    I = (
        'a,b a,c b,c d,e; '
        'a:umber b:beige c:umber d:gray e:gray; '
        'beige; umber;3'
    )
    exp = 'Solution length unreasonable'
    num = test_case(F, I, 'maybe', 'a b c', 'unsure', num, exp)

    I = (
        'a,b a,c b,c d,e; '
        'a:umber b:beige c:umber d:gray e:gray; '
        'beige; umber;0'
    )
    exp = 'clique size is not an int > 1'
    num = test_case(F, I, 'yes', 'a b c', 'unsure', num, exp)

    I = (
        'a,b a,c b,c d,e; '
        'a:umber b:beige c:umber d:gray e:gray; '
        'beige; umber;3'
    )
    exp = 'Cannot verify negative instance'
    num = test_case(F, I, 'no', 'a b c', 'unsure', num, exp)

    I = (
        'a,b a,c b,c d,e; '
        'a:umber b:beige c:umber d:gray e:gray; '
        'beige; umber;3'
    )
    exp = 'Too few nodes in hint'
    num = test_case(F, I, 'yes', 'a b', 'unsure', num, exp)

    I = (
        'a,b a,c b,c d,e; '
        'a:umber b:beige c:umber d:gray e:gray; '
        'beige; umber;3'
    )
    exp = '{a b c} is clique'
    num = test_case(F, I, 'yes', 'a b c', 'correct', num, exp)

    I = (
        'a,b a,c d,e; '
        'a:umber b:beige c:umber d:gray e:gray; '
        'beige; umber;2'
    )
    exp = '{a b} and {a c} are cliques'
    num = test_case(F, I, 'yes', 'a b', 'correct', num, exp)

    I = (
        'a,b a,c d,e; '
        'a:yellow b:beige c:umber d:gray e:gray; '
        'beige; umber;2'
    )
    exp = 'Node a is not the correct color'
    num = test_case(F, I, 'yes', 'a b', 'unsure', num, exp)
