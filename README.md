# MST
Experimenting Prim's Minimum Spanning Tree Algorithm on randomly generated 0D to 4D cubes

# Introduction

In this report, we explore the behavior of minimum spanning trees in
random graphs. To be specific, we are interested in how the weights of
minimum spanning trees in complete, undirected graphs grow as a function
*f*(*n*) of the number of vertices *n*. We consider the following four
types of graphs

1.  Complete graphs on *n* vertices, where the weight of each edge is a
    real number chosen uniformly at random on \[0, 1\]. <span
    id="graph0D" label="graph0D">\[graph0D\]</span>

2.  Complete graphs on *n* vertices, where the vertices are points
    chosen uniformly at random inside the unit square. (That is, the
    points are (*x*, *y*), with *x* and *y* each a real number chosen
    uniformly at random from \[0, 1\].) The weight of an edge is just
    the Euclidean distance between its endpoints. <span id="graph2D"
    label="graph2D">\[graph2D\]</span>

3.  Complete graphs on *n* vertices, where the vertices are points
    chosen uniformly at random inside the unit cube and the weight of an
    edge is just the Euclidean distance between its endpoints. <span
    id="graph3D" label="graph3D">\[graph3D\]</span>

4.  Complete graphs on *n* vertices, where the vertices are points
    chosen uniformly at random inside the unit hypercube and the weight
    of an edge is just the Euclidean distance between its endpoints.
    <span id="graph4D" label="graph4D">\[graph4D\]</span>

We have two tasks: first, to generate the graph and second, to generate
a minimum spanning tree and calculate the sum of the weights of this
minimum spanning tree.  
For graph [\[graph0D\]][1], since the vertices have no locations, we
initialize the graph by initializing the edges. For graph
[\[graph2D\]][2] ,[\[graph3D\]][3] and [\[graph4D\]][4], we initialize
the graph by initializing vertices with 2,3 and 4 coordinates,
respectively. The weight of edges can then be calculated as the
euclidean distance between vertices.  
To generate a minimum spanning tree, we use a modified Prim’s algorithm
because of its simplicity and efficiency. The modified Prim’s algorithm
keeps Prim’s property of growing a MST as a single tree and add vertices
to the tree when their edges crossing *V* and *V* − *S* are safe.
Several modifications are made to the original Prim’s algorithm because:

1.  we need to generate (for graph [\[graph0D\]][1]) or calculate (for
    graph [\[graph2D\]][2]-[\[graph4D\]][4]) edge weights as we grow the
    MST;

2.  we need to keep track of total weights of the MST;

3.  we don’t need a priority heap to keep track of which node to explore
    next;

4.  we don’t need to keep track of each vertex’s parent.

For graph [\[graph0D\]][1], we start with a float number
*s**u**m* = 0,representing the total weight of the MST an array *W* of
*n* − 1 elements, where each element is assigned a random number between
0 and 1. *W*, indexed from 1, 2, 3...*i*...*n* − 1 contain the weights
of edges
*w*<sub>1</sub>, *w*<sub>2</sub>..*w*<sub>*i*</sub>..*w*<sub>*n* − 1</sub>
from vertex *v*<sub>0</sub> to all other vertices
*v*<sub>1</sub>, *v*<sub>2</sub>..*v*<sub>*i*</sub>..*v*<sub>*n* − 1</sub>.
Then we loop through *W*, find the *w*<sub>*i*</sub> that gives the
minimum weight,add that to *s**u**m*, and store the index *i*. Next we
pop *w*<sub>*i*</sub> from *W*,whose length then becomes *n* − 2. We then loop through *W* again. As we
loop through the indices, we generate new weights, representing the edge
weights from *v*<sub>*i*</sub> to other *n* − 2 vertices. Because we
utilize the cut property when we connect *v*<sub>*i*</sub> to
*v*<sub>0</sub>, we don’t need to consider updating the weight from
*v*<sub>*i*</sub> to *v*<sub>0</sub>. For the elements in *W*, if the
newly generated weights are smaller than those that are already in *W*,
we update the elements in *W* with the newly generated weights. We
repeat this process until *W* is empty. Overall, we pop elements from
*W* *n* times, and for each pop, we generate and compare weights
*n* − *i* times, where *i* is the number of elements that have already
been popped. So this is *O*(*n*<sup>2</sup>) operations.  
For graphs [\[graph2D\]][2] to [\[graph4D\]][4], we start with
initializing a float number *s**u**m* = 0 to account for total weight,
and an array *W* of length *n*, with each element being the coordinates
of a vertex and an edge weight of ∞. Then, we set an arbitrary vertex’s
weight to 0, pop it from *W*, and start calculating the distances
between the popped vertex *v*<sub>0</sub> and other vertices. We keep
track of smallest distance and the vertex *v*<sub>*i*</sub> that gives
this smallest distance *w*<sub>*i*</sub>. *w*<sub>*i*</sub> is then
added to *s**u**m* and *v*<sub>*i*</sub> is popped from *W*, leaving *W*
with *n* − 2 elements. Then we loop through *W*, calculate the distance
between *v*<sub>*i*</sub> and other elements, update the edge weight if
the newly calculated edge weight is smaller than what’s stored in *W*
and find the vertex *v*<sub>*j*</sub> that gives the smallest weight
*w*<sub>*j*</sub>. This process is repeated until *W* is empty. Like the
graph [\[graph0D\]][1] case, this algorithm would take
*O*(*n*<sup>2</sup>) time.

The results plotted and saved in the ‘plot‘ folder


  [1]: #graph0D
  [2]: #graph2D
  [3]: #graph3D
  [4]: #graph4D
