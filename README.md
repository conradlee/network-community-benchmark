network-community-benchmark
===========================

This repository contains a set of command-line utilities useful for benchmaring
community detection algorithms on social networks with meta-data. This document
includes instructions on how to benchmark a community detection algorithm on
Facebook data.

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