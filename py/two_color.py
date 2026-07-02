from graph import Graph

'''
An instance of HasTwoColorClique has the syntax:
Graph;NodeColorings;Color1;Color2;CliqueSize

where

Graph is an undirected, unweighted graph defind as a white-space
delimited sequence of edges (for example: a,b a,c b,c d,e )

NodeColorings is a white-space delimited list of node colors (for
example: a:umber b:beige c:purple d:gray e:gray)

Color1 and Color2 are both colors (for example: beige; umber)

CliqueSize is an integer > 1

'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber; 3' is an
instance of HasTwoColorClique.

A HasTwoColorClique instance is a positive instance if it has a clique
with at least CliqueSize nodes, and every node in that clique is colored
either Color1 or Color2.

'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;3'
is a positive instance of HasTwoColorClique.

'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;4'
is a negative instance of HasTwoColorClique because the largest beige/umber
clique is size 3.

'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; gray; gray;3'
is a negative instance of HasTwoColorClique because the largest all gray
clique is size 3.

'''

Vh2ccv = 'VERBOSE: VfyHasTwoColorClique() '
VERBOSE = True
def printV(text):
    if VERBOSE: print(f'{Vh2ccv}{text}')

Vh2ccd = 'DEV: VfyHasTwoColorClique() '
DEV = False
def printD(text):
    if DEV: print(f'{Vh2ccd}{text}')

def VfyHasTwoColorClique(I,S,H):
    S_len = len(S)
    H_len = len(H)
    if S_len == 0 or H_len == 0 or S_len > 5: #** L0702 -- Change to reasonable length test
        s = f'Solution length {S_len} or hint length {H_len}'
        printV(f'{s} is unreasonable')
        return 'unsure'

    if S != 'yes':
        printV(f'The solution "{S}" is not verifying a positive instance')
        return 'unsure'

    (graph_str,node_colorings,color1,color2,clique_size) = I.split(';')
    # squeeze out white space
    color1 = color1.strip()
    color2 = color2.strip()
    clique_size = clique_size.strip()

    #** LO702 -- verify that clique_size is the string representation of
    #** an integer greater than 1.
    try:
        clique_size_int = int(clique_size)
        if clique_size_int <= 1:
            printV(f'clique_size {clique_size_int} must be an integer > 1')
            return 'unsure'
    except ValueError:
        printV(f'clique_size "{clique_size}" is not a valid integer')
        return 'unsure'

    clique = H.split() # H is a white-spaced delimited list of nodes
    if len(clique) < clique_size_int: #** L0702 -- Change to valid clique_size teszt
        s = f'{len(clique)} nodes in hint but {clique_size_int} is the minimum allowed'
        printV(f'{s}')
        return 'unsure'

    clique_set = set(clique)
    if len(clique_set) < len(clique):
        printV(f'Duplicate nodes in hint: {H}')

    node_color_kv = {}  # node->color key/value pairs
    colorings_list = node_colorings.split()
    for node_color in colorings_list:
        node,color = node_color.split(':')
        node_color_kv[node] = color


    g = Graph(graph_str, directed=False, weighted=False)
    nodes = list(g.nodes.keys()) # create list of graph's node names
    colors = [color1,color2]
    for node in clique:
        if node not in nodes:
            printV(f'{node} in hint but not in graph')
            return 'unsure'
        color = node_color_kv[node]
        if color not in (color1, color2): #** L0702 -- Change to valid hint node color test
             printV(f'{node} in hint is {color}, but must be either {color1} or {color2}')
             return 'unsure'

    #** L0702 -- check with nodes in hint form a clique
    edges = graph_str.split()
    adjacency = set()
    for edge in edges:
        u, v = edge.split(',')
        adjacency.add((u, v))
        adjacency.add((v, u))

    for i in range(len(clique)):
        for j in range(i + 1, len(clique)):
            if (clique[i], clique[j]) not in adjacency:
                printV(f'Nodes {clique[i]} and {clique[j]} do not form an edge in the graph')
                return 'unsure'

    printV(f'"{I}" is a positive instance, all verifications succeeded')
    return 'correct'

if __name__ == '__main__':

    def test_case(func,I,S,H,expected,num,comment=''):
        err = '** '
        result = func(I,S,H)
        func_name = str(func).split()[1]
        func_call = f'''{func_name}("{I}","{S}","{H}")'''
        if result == expected: err = ''
        e = expected
        print (f'{err}test #{num} {func_call}: expected "{e}", received "{result}"')
        print (f'test #{num} Explanation: {comment}\n')
        return num + 1

    F = VfyHasTwoColorClique
    num = 1

    I = 'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;3'
    exp = 'Solution length unreasonable'
    num = test_case(F,I,'maybe','a b c','unsure',num,exp)

    I = 'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;0'
    exp = 'clique size is not an int > 1'
    num = test_case(F,I,'yes','a b c','unsure',num,exp)

    I = 'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;3'
    exp = 'Cannot verify negative instance'
    num = test_case(F,I,'no','a b c','unsure',num,exp)

    I = 'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;3'
    exp = 'Too few nodes in hint'
    num = test_case(F,I,'yes','a b','unsure',num,exp)

    I = 'a,b a,c b,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;3'
    exp = '{a b c} is clique'
    num = test_case(F,I,'yes','a b c','correct',num,exp)

    I = 'a,b a,c d,e; a:umber b:beige c:umber d:gray e:gray; beige; umber;2'
    exp = '{a b} and {a c} are cliques'
    num = test_case(F,I,'yes','a b','correct',num,exp)
