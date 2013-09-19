-----------------------------------------------------------------------------

Community detection
Based on the articles "Fast unfolding of community hierarchies in large networks", J. Stat. Mech. (2008) P10008
Copyright (C) 2008 V. Blondel, J.-L. Guillaume, R. Lambiotte, E. Lefebvre
and 
"Dynamics and Modular Structure in Networks"
Copyright (C) 2008 R. Lambiotte, J.-C. Delvenne and M. Barahona, arXiv:0812.1770

This program or any part of it must not be distributed without prior agreement of the above mentionned authors.

-----------------------------------------------------------------------------

Author   : E. Lefebvre, adapted by J.-L. Guillaume and then by R. Lambiotte
Email    : r.lambiotte@imperial.ac.uk
Location : London, UK
Time	 : November 2008

-----------------------------------------------------------------------------

Disclaimer:
This is the first public version of this program, if you find a bug, please send a bug report to r.lambiotte@imperial.ac.uk including if necessary the input file and the parameters that caused the bug.

-----------------------------------------------------------------------------

This package offers a set of functions to use in order to compute the optimal partition of a weighted or unweighted network. To do so, the program optimises the quantity Q_t defined in the aforementioned paper of RL, J-C D and MB. If you are interested in optimising modularity (which is the special case Q_1=Q), please use the original version of the program available at findcommunities.googlepages.com. It has more options and certainly contains less bugs than this version!

To install, simply type: 
make

Typical lines of command are:

1) If you're analyzing an unweighted network:
./convert -i graph.txt -o graph.bin
./community graph.bin -l -1 -t 0.5 >> communities.dat

The first line converts a file containing the list of edges (each line contains a couple "src dest"). Note that nodes are renumbered to be consecutive AND starting from 0.

The second line evaluates the optimal partition of the network for some value of t (in the above example, t=0.5). As an output, the following line is printed on the screen:
t N MaxQt Nc seconds
where t is the resolution parameter, N the number of nodes, MaxQt the optimal value of Qt found by the algorithm, Nc the number of communities in the optimal partition and seconds the number of seconds taken to find it. 

Information about the optimal partition found by the algorithm is appended to the file modules.dat, in the following format:
node0 community_of_node0
node1 community_of_node1
node2 community_of_node2
etc.

2) If you're analyzing a weighted network:
./convert -i graph.txt -o graph.bin -w
./community graph.bin -l -1 -w -t 0.5 >> communities.dat

Two simple scripts (one for weighted and one for unweighted networks) can be found in this directory. 



