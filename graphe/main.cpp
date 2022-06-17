#define _CRT_SECURE_NO_DEPRECATE
#include "Edges.h"
#include <fstream>

#define FILE_NAME_EDGE "textfile/edge.txt"
#define FILE_NAME_MATRIX "textfile/matrix.txt"
#define FILE_NAME_SIZE "textfile/size.txt"




void initNetworkEdges(network* p_network, int size);
void initNode(node* p_node, int n_id, string p_area);
edge* addNodeToNetwork(node* p_node[], edge* p_network, edge* p_firstNode, int** n_networkMatrix);
void readNode(edge* p_network);
void deleteNetwork(edge* p_network);
bool isFileExist(const string& fileName);
int initSize(int size, fstream &file);
void initMatrix(int** matrix, int size);
void initMatrixValue(int** matrix, int size, fstream& file);
void initNodeTab(node* nodeTab, fstream &file, int size);
void deleteMatrix(int** matrix, int size);

int main() 
{
	network* p_network = new network;
	//edge* p_network = new edge;
	fstream f_edgeFile;
	fstream f_matrixFile;
	fstream f_sizeFile;
	//int networkSize = 5;
	//int** n_networkMatrix;
	
	
	p_network->n_sumEdges = 5;
	//n_networkMatrix = new int*[networkSize];
	p_network->n_sumEdges = initSize(p_network->n_sumEdges, f_sizeFile);
	p_network->n_matrixNetwork = new int* [p_network->n_sumEdges];

	initMatrix(p_network->n_matrixNetwork, p_network->n_sumEdges);
	initMatrixValue(p_network->n_matrixNetwork, p_network->n_sumEdges, f_matrixFile);
	initNetworkEdges(p_network, p_network->n_sumEdges);

	node* p_tabNode = new node[p_network->n_sumEdges];
	initNodeTab(p_tabNode, f_edgeFile, p_network->n_sumEdges);

	//p_network = addNodeToNetwork(p_tabNode, p_network, p_network, n_networkMatrix);


	

	//readNode(p_network);

	//deleteNetwork(p_network);

	return 0;
}


//Initialisation de la première valeure du réseau
void initNetworkEdges(network* p_network, int size) {
	/*edge* tempEdge = new edge;
	tempEdge->p_node = nullptr;
	tempEdge->p_connectedEdge = nullptr;*/

	p_network->p_edgeTab = new edge[size];
}


//initialisation d'une node
void initNode(node* p_node, int n_id, string p_area) {
	p_node->n_id = n_id;
	p_node->p_area = p_area;
}


//Initialisation du réseau
edge* addNodeToNetwork(node* p_node[], edge* p_network, edge* p_firstNode, int** n_networkMatrix) {
	if (p_network->p_node) {
		if (p_network->p_connectedEdge) {
			addNodeToNetwork(p_node, p_network->p_connectedEdge, p_firstNode, n_networkMatrix);
		}
		else {
			int n_i = 0;
			edge* p_tempEdge = new edge;
			while (n_networkMatrix[p_network->p_node->n_id][n_i] != 1) {
				n_i++;
			};
			p_tempEdge->p_node = p_node[n_i];
			if (n_i == 0) {
				p_tempEdge->p_connectedEdge = p_firstNode;
			}
			else {
				p_tempEdge->p_connectedEdge = nullptr;
			}
			p_network->p_connectedEdge = p_tempEdge;
			if (p_tempEdge->p_connectedEdge == nullptr) {
				addNodeToNetwork(p_node, p_network->p_connectedEdge, p_firstNode, n_networkMatrix);
			}
		}
	}
	else {
		edge* p_tempEdge = new edge;
		p_tempEdge->p_node = p_node[0];
		p_tempEdge->p_connectedEdge = nullptr;
		p_network = p_tempEdge;
		p_firstNode = p_tempEdge;
		addNodeToNetwork(p_node, p_network, p_firstNode, n_networkMatrix);
	}
	return p_firstNode;
}


void readNode(edge* p_network) {
	if (p_network->p_connectedEdge->p_node->p_area != "Marseille") {
		std::cout << "La zone de cette node est : " << p_network->p_node->p_area << "." << endl;
		readNode(p_network->p_connectedEdge);
	}
	else {
		std::cout << "La zone de cette node est : " << p_network->p_node->p_area << "." << endl;
	}
}

void deleteNetwork(edge* p_network) {
	if (p_network->p_connectedEdge->p_node->p_area != "Marseille") {
		deleteNetwork(p_network->p_connectedEdge);
		delete(p_network);
	}
	else {
		delete(p_network);
	}
}

int initSize(int size, fstream &file) {
	if (isFileExist(FILE_NAME_SIZE)) {
		char tempChar;
		file.open(FILE_NAME_SIZE);
		if (file.is_open()) {
			file >> tempChar;
			size = (int)tempChar;
			file.close();
		}
	}
	else {
		ofstream o_sizeFile(FILE_NAME_SIZE);
		o_sizeFile << size;
		o_sizeFile.close();
	}

	return size;
}

void initMatrix(int** matrix, int size) {
	for (int n_i = 0; n_i < size; n_i++) {
		matrix[n_i] = new int[size];
	}
}

void initMatrixValue(int** matrix, int size, fstream &file) {
	int tempTab[5][5] = { {0, 0, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 1}, {0, 1, 0, 0, 0}, {1, 0, 0, 0, 0} };
	if (isFileExist(FILE_NAME_MATRIX)) {
		file.open(FILE_NAME_MATRIX);
		if (file) {
			string tempString;
			int n_i = 0;
			while (getline(file, tempString)) {
				n_i++;
				tempString.erase(remove_if(tempString.begin(), tempString.end(), isspace));
				for (int n_j = 0; n_j < tempString.size(); n_j++) {
					matrix[n_i - 1][n_j] = tempString[n_j] - '0';
				}

			}
		}
		file.close();
	}
	else {
		for (int n_i = 0; n_i < 5; n_i++) {
			for (int n_j = 0; n_j < 5; n_j++) {
				matrix[n_i][n_j] = tempTab[n_i][n_j];
			}
		}
	}
	
}

void initNodeTab(node* nodeTab, fstream &file, int size) {
	node *tempNode = new node[size];
	if (isFileExist(FILE_NAME_EDGE)) {
		string tempString = "";
		file.open(FILE_NAME_EDGE);
		int n_i = 0;
		while (getline(file, tempString)) {
			tempString.erase(remove_if(tempString.begin(), tempString.end(), isspace));
			if (n_i % 2 == 0) {
				tempNode[n_i / 2].n_id = tempString[0] - '0';
			}
			else {
				tempNode[n_i / 2].p_area = tempString;
			}
			n_i++;
		}
		file.close();
	}
	else {
		node* node1 = new node;
		node* node2 = new node;
		node* node3 = new node;
		node* node4 = new node;
		node* node5 = new node;

		//node* tempTab[5];

		initNode(node1, 0, "Marseille");
		initNode(node2, 1, "Paris");
		initNode(node3, 2, "Strasbourg");
		initNode(node4, 3, "Lille");
		initNode(node5, 4, "Nice");

		node* tempTab[5] { node1, node2, node3, node4, node5 };

		//tempNode = tempTab;
		for (int n_i = 0; n_i < size; n_i++) {
			tempNode[n_i].n_id = tempTab[n_i]->n_id;
			tempNode[n_i].p_area = tempTab[n_i]->p_area;
		}
	}
	nodeTab = tempNode;
	delete[] tempNode;
}

void deleteMatrix(int** matrix, int size) {
	for (int n_i = 0; n_i < size; n_i++) {
		delete matrix[n_i];
	}
	delete matrix;
}

void deleteEdge(network* p_network) {

}

bool isFileExist(const string& fileName) {
	if (FILE* file = fopen(fileName.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
