network-community-benchmark
===========================

This repository contains a set of command-line utilities useful for benchmaring
community detection algorithms on social networks with meta-data. This document
includes instructions on how to benchmark a community detection algorithm on
Facebook data.

**An important note on the Facebook100 Data:** To carry out the benchmarks, you will need a copy of the Facebook100 dataset. I am not allowed to distribute that dataset here, so you will have to download it elsewhere. This [blog post](http://sociograph.blogspot.com/2011/03/facebook100-data-and-parser-for-it.html) contains some useful information on obtaining the dataset.

Workflow
--------

The basic concept behind these benchmarking tools can be summarized in the following pipeline:

> generate edgelist -> run community detection algorithm -> generate labelled community assignment matrix -> measure classifier performance

Each of these steps is carried out by a shell script, which means that the workflow can be run with the following command:
 
```bash
./fb_edges Caltech36 | comm_algs/louvain_wrapper --markovtime=0.5 --multilevel | ./label_feature_matrix Caltech36 year | ./infer 10 > LouvainCaltech36.results
```

The above pipeline does the following

 1. `fb_edges Caltech36` generates the edgelist of the Caltech facebook network and spits it out to STDOUT.
 2. `comm_algs/louvain_wrapper --markovtime=0.5 --multilevel` reads in the edgelist from STDIN, detects communities on it using the Louvain method of community detection and supplied parameters, then writes these communities to STDOUT.
 3. `./label_feature_matrix Caltech36 year` reads in the list of communities from STDIN and converts this into a community assignment matrix (indicator matrix), where rows represent nodes and columns represent communities. Each row is also labelled with an attribute value, in this case with the 'year' attribute, which stands for the year of graduation. Note that a label value of 0 (zero) indicates a missing label.
 4. `./infer 10` reads in the labelled community assignment matrix, and measures how accurately a machine learning classifier can infer missing labels using nothing but the community assignment matrix as features. The 10 indicates that all ten folds of the cross fold validation are carried out. This script writes a number to STDOUT that indicates the accuracy with which the year attribute can be inferred from the communities produced by the Louvain method.

Thus if we examine the contents of the `LouvainCaltech36.results` file, we see

```bash
$ cat LouvainCaltech36.results
0.367708333333
```

Configuring the benchmark utility in *settings.py*
-------------------------------------------------
There are a few experiment parameters that can be configured in 'settings.py'.  These are documented in that file.  If you want the classification part of the benchmark to be faster, consider changing the N_FOLDS and CLASSIFIER parameters.


More documentation
------------------

Each script's documentation can be accessed in the usual command-line fashion with the `-h` flag. For example, typing

```bash
./fb_edges -h
```

prints the following help statement

```bash
fb_edges.

Loads network data from Facebook100 dataset and prints them to the command line
as tab-delimited edge lists. Uses path specified by SRC_DATA_DIR variable
in settings.py to locate the Facebook100 dataset.

Usage:
  fb_edges <network_name>

Options:
  -h --help     Show this help message.

Useful properties of the edge lists
* Contiguous integers starting with zero
* Printed in ascending order
* Edges are undirected, and only included in one direction

```

Implemented community detection algorithms
------------------------------------------

 * Louvain method (with optional Markov time resolution parameter). Implementation by E. Lefebvre, adapted by J.-L. Guillaume and then by R. Lambiotte. Implements modularity maximization heuristic described in the paper [Fast unfolding of community hierarchies in large networks](http://http://dx.doi.org/10.1088/1742-5468/2008/10/P10008) by V. Blondel, J.-L. Guillaume, R. Lambiotte, E. Lefebvre. The Markov time parameterization is described in [Stability of graph communities across time scales](http://dx.doi.org/10.1073/pnas.0903215107) by J.-C. Delvenne, S. N. Yaliraki, M. Barahona.
 * Greedy Clique Expansion, described in [Detecting highly overlapping community structure by greedy clique expansion](http://arxiv.org/abs/1002.1827) by C. Lee, F. Reid, A. McDaid, N. Hurley. I used the implementation available [here](https://sites.google.com/site/greedycliqueexpansion/).

If you want to add another algorithm, see the instructions for doing so below in the 'extensibility' section.


Possible attributes
-------------------
The classification task at the core of this benchmark is based on inferring node attributes based on communities.  Various node attributes can be used, but we argue that 'year' and 'dorm' are the best choices.  The possible attributes are:

* dorm
* year
* first_major
* second_major
* high_school
* gender
* student_fac

Note that other than dorm and year, we don't believe any other attributes to be appropriate for this benchmark.


Extensibility (i.e., how to test and add your own algorithms!)
--------------------------------------------------------------

Let's say you have a new community detection algorithm *my_alg* and you want to integrate it into this benchmark. All you need to do is make sure that your implementation takes in a properly-formatted edgelist as input and spits out a properly-formatted line-delimited list of communities.  What do I mean by 'properly-formatted'? Two nodes on each line separated by whitespace, with a line terminated by a UNIX newline (\n).  THus a network that consisted of two disconnected triangles would looke like

   0    1
   0    2
   1    2
   3    4
   3    5
   4    5

Within each line, nodes are separated by a tab.  Note that the node IDs are contiguous integers starting with zero.

The output of of the implementation should be a line-delimited list of communities, where each line is a whitespace separated list of nodes belonging to a community.  Thus if the algorithm took in the two-triangle network above, and detected each traingle as a community, its output should look like

  0 1 2
  3 4 5

Of course, many implementations don't use this format---in that case, just write a wrapper for your implementation. There are two examples of such wrappers in the `comm_algs` folder.

Once you have your compatible community detection algorithm, you can just plug it into the pipeline above as the other community detection algorithms are plugged in.