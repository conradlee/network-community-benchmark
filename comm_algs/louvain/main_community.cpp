// File: main_community.cpp
// -- community detection, sample main file
//-----------------------------------------------------------------------------
// Community detection 
// Based on the article "Fast unfolding of community hierarchies in large networks"
// by V. Blondel, J.-L. Guillaume, R. Lambiotte, E. Lefebvre
// This program finds the optimal partitions of teh quantity \tilde{Q}_t describred
// in the article "Dynamics and Modular Structure in Networks"
// by R. Lambiotte, J.-C. Delvenne and M. Barahona
// Please cite these papers if you use it.
//
// This program must not be distributed without agreement of the above mentionned authors.
//-----------------------------------------------------------------------------
// Author   : E. Lefebvre, adapted by J.-L. Guillaume (for optimising modularity) and the R. Lambiotte (for optimising Q_t)
// Email    : r.lambiotte@imperial.ac.uk
// Location : London, UK
// Time	    : November 2008
//-----------------------------------------------------------------------------
// see readme.txt for more details

#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "graph_binary.h"
#include "community.h"

using namespace std;

char *filename = NULL;
int type       = UNWEIGHTED;
int nb_pass    = 0;
double precision = 0.000001;
double timet = 1.0;
int display_level = -2;
int k1 = 16;

void
usage(char *prog_name, char *more) {
  cerr << more;
  cerr << "usage: " << prog_name << " input_file [options]" << endl << endl;
  cerr << "input_file: read the graph to partition from this file." << endl;
  cerr << "-w\t read the graph as a weighted one (weights are set to 1 otherwise)." << endl;
  cerr << "-q epsilon\t a given pass stops when the modularity is increased by less than epsilon." << endl;
  cerr << "-t Optimisation of a quantity generalzing modularity in order to uncover smaller communities. Modularity: t=1. t must be smaller than 1." << endl;
  cerr << "-l k\t displays the graph of level k rather than the hierachical structure." << endl;
  cerr << "-h\tshow this usage message." << endl;
  exit(0);
}

void
parse_args(int argc, char **argv) {
  if (argc<2)
    usage(argv[0], "Bad arguments number\n");

  for (int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      switch(argv[i][1]) {
      case 'w':
	type = WEIGHTED;
	break;
      case 'q':
	precision = atof(argv[i+1]);
	i++;
	break;
	  case 't':
	timet = atof(argv[i+1]);
	i++;
	break;
      case 'l':
	display_level = atoi(argv[i+1]);
	i++;
	break;
      case 'k':
	k1 = atoi(argv[i+1]);
	i++;
	break;
      default:
	usage(argv[0], "Unknown option\n");
      }
    } else {
      if (filename==NULL)
        filename = argv[i];
      else
        usage(argv[0], "More than one filename\n");
    }
  }
}

void
display_time(const char *str) {
  time_t rawtime;
  time ( &rawtime );
  cerr << str << " : " << ctime (&rawtime);
}



int
main(int argc, char **argv) {
  srand(time(NULL));

  parse_args(argc, argv);

  time_t time_begin, time_end;
  time(&time_begin);
  //display_time("start");
    
  Community c(filename, type, -1, precision, timet);
  
  int numberinitial=c.g.nb_nodes;
  
  //display_time("file read");

  double mod = c.modularity();

  /*cerr << "network : " 
       << c.g.nb_nodes << " nodes, " 
       << c.g.nb_links << " links, "
       << c.g.total_weight << " weight." << endl;*/
 
  double new_mod = c.one_level();

  //display_time("communities computed");
  //cerr << "modularity increased from " << mod << " to " << new_mod << endl;

  if (display_level==-1)
    c.display_partition();

  Graph g = c.partition2graph_binary();

  //display_time("network of communities computed");

  int level=0;
  
  int numberofcommunities=c.g.nb_nodes;

  
  while(new_mod-mod>precision) {
    mod=new_mod;
    Community c(g, -1, precision, timet);
	
    /*cerr << "\nnetwork : " 
	 << c.g.nb_nodes << " nodes, " 
	 << c.g.nb_links << " links, "
	 << c.g.total_weight << " weight." << endl;*/
	 
	numberofcommunities=c.g.nb_nodes;
    
    new_mod = c.one_level();
    
	//c.display_partitioncerr();
	
    //display_time("communities computed");
    //cerr << "modularity increased from " << mod << " to " << new_mod << endl;
    
    if (display_level==-1)
      c.display_partition();
    
    g = c.partition2graph_binary();
    level++;
    
    if (level==display_level)
      g.display();
    
    //display_time("network of communities computed");
	

  }
  time(&time_end);

	//cout << "i " <<timet << " " << numberinitial << " " << new_mod << " "<< level << " "<< numberofcommunities << endl;
	//c.partition2graph();
	
  cerr << timet << " " << numberinitial << " " << new_mod << " "<< numberofcommunities << " " << (time_end-time_begin) << endl;
	cout << "" << endl;
}
