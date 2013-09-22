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
./fb_edges Caltech36 | .comm_algs/louvain_wrapper --markovtime=0.5 --multilevel | ./label_feature_matrix Caltech36 year | ./infer 10 > LouvainCaltech36.results
```

The above example first generates the edgelist of the Caltech facebook network, which is fed into the Louvain method of community detection. The detected communities are then turned into a community assignment matrix, which is labelled with Caltech's 'year' attribute (year of graduation). This matrix and label vector are then piped into a machine learning classifier. The end result is a number that indicates the accuracy with which the year attribute can be inferred from the communities produced by the Louvain method. Thus if we examine the contents of the `LouvainCaltech36.results` file, we see

```bash
$ cat LouvainCaltech36.results
0.367708333333
```