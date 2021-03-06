#include "vector.h"
#include "foreach.h"
#include "queue.h"
#include "map.h"
//#include "console.h"
#include "set.h"

struct Node;
struct Arc {
	Node *start;
	Node *finish;
};
struct Node {
	Vector<Arc> ways;
};

Vector<Arc*> deleteArcs(Vector<Node*> graph);
bool checkConnected(Vector<Node*> graph, Set<Arc*> & deletedArcs);
void searchGraph(Vector<Node*> & graph, Queue<Node*> & q, Set<Node*> & visited, Set<Arc*> & deletedArcs);
void deleteArcsRecursive(Vector<Node*> & graph, Set<Arc*> & deleted, Set<Arc*> & usedArcs, Vector<Arc*> & result);
void removeArc(Vector<Node*> & graph, Set<Arc*> & usedArcs, Set<Arc*> & deleted, Vector<Arc*> & result);
void addToUsed(Vector<Node*> & graph, Set<Arc*> & usedArcs, Set<Arc*> & deleted);
int countArcs(Vector<Node*> & graph, Set<Arc*> deleted);
bool setContainsArc(Set<Arc*> & set, Arc* & arc);

int main() {
	Node *first = new Node;
	Node *second = new Node;
	Node *third = new Node;
	Node *fourth = new Node;

	Arc a1;
	a1.start = first;
	a1.finish = second;

	Arc a2;
	a2.start = second;
	a2.finish = third;

	Arc a3;
	a3.start = third;
	a3.finish = fourth;

	Arc a4;
	a4.start = first;
	a4.finish = fourth;

	Arc a5;
	a5.start = third;
	a5.finish = first;

	Arc a6;
	a6.start = second;
	a6.finish = fourth;

	Vector<Node*> graph;
	graph.add(first);
	graph.add(second);
	graph.add(third);
	graph.add(fourth);

	Vector<Arc> firstWays;
	firstWays.add(a1);
	firstWays.add(a5);
	firstWays.add(a4);
	first->ways = firstWays;

	Vector<Arc> secondWays;
	secondWays.add(a1);
	secondWays.add(a2);
	secondWays.add(a6);
	second->ways = secondWays;

	Vector<Arc> thirdWays;
	thirdWays.add(a2);
	thirdWays.add(a3);
	thirdWays.add(a5);
	third->ways = thirdWays;

	Vector<Arc> fourthWays;
	fourthWays.add(a3);
	fourthWays.add(a6);
	fourthWays.add(a4);
	fourth->ways = fourthWays;

	// List nodes
	for (int i = 0; i < graph.size(); i++) {
		Node *n = graph[i];
		cout << n << endl;
	}

	Vector<Arc*> deletedArcs;
	deletedArcs = deleteArcs(graph);

	// List edges to remove
	foreach (Arc *a in deletedArcs) {
		cout << a->start << " " << a->finish << endl;
	}

	system("pause");
	return 0;
}

Vector<Arc*> deleteArcs(Vector<Node*> graph) {
	Set<Arc*> deleted;
	Vector<Arc*> result;
	Set<Arc*> usedArcs;

	deleteArcsRecursive(graph, deleted, usedArcs, result);
	return result;
}

bool checkConnected(Vector<Node*> graph, Set<Arc*> & deletedArcs) {
	Node *firstNode = graph.get(0);

	Queue<Node*> q;
	q.enqueue(firstNode);

	Set<Node*> visited;
	searchGraph(graph, q, visited, deletedArcs);

	return visited.size() == graph.size();
}

void searchGraph(Vector<Node*> & graph, Queue<Node*> & q, Set<Node*> & visited, Set<Arc*> & deletedArcs) {
	if (q.isEmpty()) {
		return;
	} else {
		Node *node = q.dequeue();
		visited.add(node);

		Vector<Node*> neighbours;
		for (int i = 0; i < node->ways.size(); i++) {
			Arc *arc = &(node->ways[i]);
			if (setContainsArc(deletedArcs, arc)) {
				continue;
			}
			Node *neighbour = (arc->start == node) ? arc->finish : arc->start;
			neighbours.add(neighbour);
		}

		foreach(Node* nb in neighbours) {
			if (visited.contains(nb)) continue;
			q.enqueue(nb);
		}

		searchGraph(graph, q, visited, deletedArcs);
	}
}

void deleteArcsRecursive(Vector<Node*> & graph, Set<Arc*> & deleted, Set<Arc*> & usedArcs, Vector<Arc*> & result) {
	if (!checkConnected(graph, deleted)) {
		Vector<Arc*> null;
		result = null;
	} else if (usedArcs.size() == countArcs(graph, deleted)) {
		return;
	} else {
		// Copy current state
		Set<Arc*> deletedNew;
		Vector<Arc*> resultNew;
		Set<Arc*> usedArcsNew;
		
		deletedNew = deleted;
		resultNew = result;
		usedArcsNew = usedArcs;

		addToUsed(graph, usedArcs, deleted);
		deleteArcsRecursive(graph, deleted, usedArcs, result);

		removeArc(graph, usedArcsNew, deletedNew, resultNew);
		deleteArcsRecursive(graph, deletedNew, usedArcsNew, resultNew);

		if (resultNew.size() > result.size()) {
			result = resultNew;
		}
	}
}

int countArcs(Vector<Node*> & graph, Set<Arc*> deleted) {
	int count = 0;
	foreach (Node* n in graph) {
		for (int i = 0; i < n->ways.size(); i++) {
			Arc *a = &(n->ways[i]);
			if (!setContainsArc(deleted, a)) {
				count++;
			}
		}
	}
	return count / 2;
}

void removeArc(Vector<Node*> & graph, Set<Arc*> & usedArcs, Set<Arc*> & deleted, Vector<Arc*> & result) {
	// Find first unused arc and remove it
	Arc *arc;
	bool found = false;
	foreach (Node* n in graph) {
		// Remove arc if you haven't removed it yet
		if (!found) {
			for (int i = 0; i < n->ways.size(); i++) {
				arc = &(n->ways[i]);
				if (!setContainsArc(usedArcs, arc) && !setContainsArc(deleted, arc)) {
					deleted.add(arc);
					result.add(arc);
					found = true;
					break;
				}
			}
		}
	}
}

void addToUsed(Vector<Node*> & graph, Set<Arc*> & usedArcs, Set<Arc*> & deleted) {
	foreach (Node* n in graph) {
		for (int i = 0; i < n->ways.size(); i++) {
			Arc *a = &(n->ways[i]);
			if (!setContainsArc(usedArcs, a) && !setContainsArc(deleted, a)) {
				usedArcs.add(a);
				return;
			}
		}
	}
}

bool setContainsArc(Set<Arc*> & set, Arc* & arc) {
	foreach (Arc* a in set) {
		if (a->start == arc->start && a->finish == arc->finish) {
			return true;
		}
	}
	return false;
}