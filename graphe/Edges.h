#pragma once
#include <string>
#include<iostream>

using namespace std;

typedef struct node {
	int n_id{};
	string p_area{};
}node;

typedef struct edge {
	node* p_node;
	edge* p_connectedEdge;
}edge;

typedef struct network {
	int n_sumEdges;
	edge* p_edgeTab;
	int** n_matrixNetwork;
}network;