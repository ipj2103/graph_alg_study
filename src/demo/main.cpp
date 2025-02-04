
#include<iostream>
#include<vector>
#include "Algorithms.h"




/////////////////////////////////////////////////////////////////////////////
// unit test
/////////////////////////////////////////////////////////////////////////////


// test the functionality of nodes
//		should contain a value and a list of in/out neighbors
int test_node() {

	try
	{
		Node n;
		n.set_val(1.1);

		if (n.get_val() != 1.1) { throw 0; }

		Node m = Node::Node(100.0);
		n.add_in_neighbor(&m);
		m.add_out_neighbor(&n);

		double nx = n.get_val();
		double mx = m.get_val();

		if (nx > mx) { throw 1; }

		//std::cout << nx << std::endl;
		//std::cout << mx << std::endl;
		//std::cout << std::endl;

		Node* mm = m.get_out_neighbors().back();
		Node* nn = n.get_in_neighbors().back();

		double nnx = (*mm).get_val();
		double mmx = (*nn).get_val();
		//std::cout << nnx << std::endl;
		//std::cout << mmx << std::endl;

		if (nnx > mmx) { throw 1; }

	}
	catch (int e)
	{
		std::cout << "Node test failed " << e << '\n';
		return 1;
	}

	return 0;
}



// basic directed an undirected graph functionality 
//		adding an edge should change both the neighbors of both nodes involed witht aht  
int test_graph() {

	try 
	{
		Node n = Node::Node(1.0);
		Node m = Node::Node(2.0);
		Graph G;
		G.add_edge(&n, &m);
		//G.draw();
		std::cout << std::endl;

		if (n.get_out_neighbors()[0] != &m) { throw 0; }

		n.~Node();
		m.~Node();
		n = Node::Node(1.0);
		m = Node::Node(2.0);
		UndirectedGraph UG;
		UG.add_edge(&n, &m);
		//UG.draw();
		std::cout << std::endl;
		if (n.get_out_neighbors()[0] != &m) { throw 1; }
		if (n.get_in_neighbors()[0] != &m ) { throw 2; }


		// Dense graph not dense ?? 
		//n.~Node();
		//m.~Node();
		//n = Node::Node(1.0);
		//m = Node::Node(2.0);
		//Node l = Node::Node(3.0);
		//DenseGraph DG;
		//DG.add_node(&n);
		//DG.add_node(&m);
		//DG.add_node(&l);
		//DG.draw();
		//std::cout << " "  << std::endl;
		//std::cout << std::endl;
	}
	catch (int e)
	{
		std::cout << "Basic graph test failed " << e << '\n';
		return 1;
	}

	return 0;
}




// test s-t connectivity algorithm 
//		should return 1 (true) if two
int test_st_con() {
	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	Node o = Node::Node(4.0);
	Node foo = Node::Node(5.0);

	Graph G;
	G.add_edge(&n, &m);
	G.add_edge(&m, &l);
	G.add_edge(&l, &o);
	G.add_node(&foo);
	//G.draw();
	//std::cout << std::endl;

	//std::cout << st_connectivity(&G, &n, &l) << std::endl;
	//std::cout << st_connectivity(&G, &foo, &l) << std::endl;
	//std::cout << st_connectivity(&G, &l, &foo) << std::endl;

	try
	{
		if (!st_connectivity(&G, &n, &l)) { throw 0; }
		if (st_connectivity(&G, &foo, &l)) { throw 1; }
		if (st_connectivity(&G, &l, &foo)) { throw 2; }
	}
	catch (int e)
	{
		std::cout << "s-t connectivity test failed " << e << '\n';
		return 1;
	}


	return 0;
}


int test_dfs() {
	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	Node o = Node::Node(4.0);
	Node foo = Node::Node(5.0);

	Graph G;
	G.add_edge(&n, &m);
	G.add_edge(&m, &l);
	G.add_edge(&l, &o);
	G.add_node(&foo);
	//G.draw();

	std::vector<Node*> parents = DFS(&G);
	//G_tree.draw();

	try
	{
		if (parents[0] != parents[parents.size() - 1]) { throw 0; }
		if (parents[get_index(G.get_nodes(), &m)] != &n) { throw 1; }
		if (parents[get_index(G.get_nodes(), &l)] != &m) { throw 2; }
		if (parents[get_index(G.get_nodes(), &o)] != &l) { throw 3; }
	}
	catch (int e)
	{
		std::cout << "The DFS tree should be the same as the originial graph for this test : " << e << std::endl;
		return 1;
	}



	return 0;
}


int test_weighted_graph() {
	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	WeightedGraph<double> WG;
	//WeightedEdge e1 = WeightedEdge::WeightedEdge(&n, &m, 10.0);
	//WeightedEdge e2 = WeightedEdge::WeightedEdge(&m, &l, 11.0);
	//WG.add_edge(&e1);
	//WG.add_edge(&e2);
	//WG.draw();

	WG.add_edge(&n, &m, 10.0);
	WG.add_edge(&m, &l, 11.0);
	
	try
	{
		//if ((*WG.get_edges()[0]).get_weight() != 10.0) { throw 0; }
		//if ((*WG.get_edges()[1]).get_weight() != 11.0) { throw 1; }
		if (WG.get_edge_weight(&n, &m) != 10.0) { throw 0; }
		if (WG.get_edge_weight(&m, &l) != 11.0) { throw 0; }
		if (n.get_out_neighbors()[0] != &m) { throw 2; }
		if (m.get_out_neighbors()[0] != &l) { throw 3; }
		if (l.get_in_neighbors()[0] != &m) { throw 4; }

	}
	catch (int e)
	{
		std::cout << "something doesn't seem right with test : " << e << std::endl;
		return 1;
	}

	return 0;
}


int test_bfs() {

	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	Node o = Node::Node(4.0);

	Graph G;
	G.add_edge(&n, &m);
	G.add_edge(&m, &l);
	G.add_edge(&l, &o);
	//G.draw();

	Graph G_tree = BFS(&G, &n);
	//G_tree.draw();

	int i = 0;

	try
	{
		for (auto& n : G.get_nodes()) {
			if (n != G_tree.get_nodes()[i]) { throw i; }
			i += 1;
		}
	}
	catch (int e)
	{
		std::cout << "The BFS tree should be the same as the originial graph for this test : " << e << std::endl;
		return 1;
	}

	return 0;
}



// TODO : change to undirected weighted graph
int test_prims() {

	Node a = Node::Node(0.0);
	Node b = Node::Node(1.0);
	Node c = Node::Node(2.0);
	Node d = Node::Node(3.0);
	Node e = Node::Node(4.0);
	Node f = Node::Node(5.0);
	Node g = Node::Node(6.0);
	Node h = Node::Node(7.0);
	Node i = Node::Node(8.0);

	// should be undirected 
	WeightedGraph<int> G;

	G.add_edge(&a, &b, 4);
	G.add_edge(&a, &h, 8);
	
	G.add_edge(&b, &a, 4);
	G.add_edge(&b, &h, 11);
	G.add_edge(&b, &c, 8);
	
	G.add_edge(&c, &i, 2);
	G.add_edge(&c, &b, 8);
	G.add_edge(&c, &f, 4);
	G.add_edge(&c, &d, 7);

	G.add_edge(&d, &c, 7);
	G.add_edge(&d, &f, 14);
	G.add_edge(&d, &e, 9);

	G.add_edge(&e, &d, 9);
	G.add_edge(&e, &f, 10);

	G.add_edge(&f, &e, 10);
	G.add_edge(&f, &d, 14);
	G.add_edge(&f, &c, 4);
	G.add_edge(&f, &g, 2);

	G.add_edge(&g, &f, 2);
	G.add_edge(&g, &i, 6);
	G.add_edge(&g, &h, 1);

	G.add_edge(&h, &g, 1);
	G.add_edge(&h, &i, 7);
	G.add_edge(&h, &a, 8);
	G.add_edge(&h, &b, 11);

	G.add_edge(&i, &h, 7);
	G.add_edge(&i, &g, 6);
	G.add_edge(&i, &c, 2);

	WeightedGraph<int> MST = Prim_MST(&G, &a);

	int foo = 0;

	try
	{
		if (true) { throw foo; }
	}
	catch (int e)
	{
		std::cout << "Prim's failed this test : " << e << std::endl;
		return 1; 
	}

	return 0;
}





int test_dijkstras() {

	Node s = Node::Node(0.0);
	Node t = Node::Node(1.0);
	Node x = Node::Node(2.0);
	Node y = Node::Node(3.0);
	Node z = Node::Node(4.0);
	
	WeightedGraph<unsigned int> G;

	G.add_edge(&s, &y, 5);
	G.add_edge(&s, &t, 3);

	G.add_edge(&t, &y, 2);
	G.add_edge(&t, &x, 6);

	G.add_edge(&y, &t, 1);
	G.add_edge(&y, &x, 4);
	G.add_edge(&y, &z, 6);

	G.add_edge(&x, &z, 2);

	G.add_edge(&z, &s, 3);
	G.add_edge(&z, &x, 7);


	std::map<Node*, unsigned int> a_path_lenghts = Dijkstras(&G, &s);

	int foo = 0;

	try
	{
		if (false) { throw foo; }
	}
	catch (int e)
	{
		std::cout << "Prim's failed this test : " << e << std::endl;
		return 1;
	}

	return 0;
}




/////////////////////////////////////////////////////////////////////////////
// Demos
/////////////////////////////////////////////////////////////////////////////


void demo_dfs() {

	std::cout << "@@@  DFS Demo  @@@" << std::endl;

	Graph G;

	Node a = Node::Node(0);
	Node b = Node::Node(1);
	Node c = Node::Node(2);
	Node d = Node::Node(3);
	Node e = Node::Node(4);
	Node f = Node::Node(5);
	Node g = Node::Node(6);
	Node h = Node::Node(7);

	G.add_edge(&a, &e);
	G.add_edge(&b, &a);
	G.add_edge(&b, &c);
	G.add_edge(&c, &a);
	G.add_edge(&c, &g);
	G.add_edge(&d, &f);
	G.add_edge(&f, &g);
	G.add_edge(&f, &h);
	G.add_edge(&g, &e);


	std::cout << "G's adjacency list : " << std::endl;
	G.draw();
	std::vector<Node*> parents = DFS(&G);
	std::vector<Node*> nodes = G.get_nodes();

	std::cout << std::endl;
	std::cout << "DFS result : " << std::endl;
	std::cout << "Node ~~~ Parent" << std::endl;

	for (unsigned int i = 0; i < parents.size(); i++) {
		std::cout << (*nodes[i]).get_val() << "~~~" << std::flush;
		if (parents[i] != nullptr) {
			std::cout << (*parents[i]).get_val() << std::endl;
		}
		else {
			std::cout << "null" << std::endl;
		}
	}

	std::cout << std::endl;

};




// should probably change the demo to be on an Undirected version ...
void demo_bfs() {

	std::cout << "@@@  BFS Demo  @@@" << std::endl;

	UndirectedGraph G;

	Node a = Node::Node(0);
	Node b = Node::Node(1);
	Node c = Node::Node(2);
	Node d = Node::Node(3);
	Node e = Node::Node(4);
	Node f = Node::Node(5);
	Node g = Node::Node(6);
	Node h = Node::Node(7);

	G.add_edge(&a, &e);
	G.add_edge(&b, &a);
	G.add_edge(&b, &c);
	G.add_edge(&c, &a);
	G.add_edge(&c, &g);
	G.add_edge(&d, &f);
	G.add_edge(&f, &g);
	G.add_edge(&f, &h);
	G.add_edge(&g, &e);

	std::cout << "G's adjacency list : " << std::endl;
	G.draw();

	std::cout << std::endl;
	std::cout << "G's BFS Tree starting from 0: " << std::endl;
	Graph bfs_tree_a = BFS(&G, &a);
	bfs_tree_a.draw();

	//std::cout << std::endl;
	//std::cout << "G's BFS Tree starting from 1: " << std::endl;
	//Graph bfs_tree_b = BFS(&G, &b);
	//bfs_tree_b.draw();

};


void demo_dijkstras() {

	std::cout << std::endl <<  "@@@  Dijkstra's Demo  @@@" << std::endl;


	Node s = Node::Node(0.0);
	Node t = Node::Node(1.0);
	Node x = Node::Node(2.0);
	Node y = Node::Node(3.0);
	Node z = Node::Node(4.0);

	WeightedGraph<unsigned int> G;

	G.add_edge(&s, &y, 5);
	G.add_edge(&s, &t, 3);

	G.add_edge(&t, &y, 2);
	G.add_edge(&t, &x, 6);

	G.add_edge(&y, &t, 1);
	G.add_edge(&y, &x, 4);
	G.add_edge(&y, &z, 6);

	G.add_edge(&x, &z, 2);

	G.add_edge(&z, &s, 3);
	G.add_edge(&z, &x, 7);


	std::cout << "G's adjacency list : " << std::endl;
	G.draw();

	std::map<Node*, unsigned int> a_path_lengths = Dijkstras(&G, &s);


	std::cout << std::endl; 
	for (auto& n : G.get_nodes()) {
		std::cout << s.get_val() << " --- " << a_path_lengths[n] << " ---> " << (*n).get_val() << std::endl;
	};

}



/////////////////////////////////////////////////////////////////////////////
// Main 
/////////////////////////////////////////////////////////////////////////////



//  test everything here
//	demo case studies of graph algorithms 
int main() {


	// unit tests 
	int test = 0;
	try
	{
		test += test_node();
		test += test_graph();
		test += test_weighted_graph();
		test += test_st_con();
		test += test_dfs();
		test += test_bfs();
		//test += test_prims(); // TODO: fix actually forming the MST and implement a real test ... 
		test += test_dijkstras();

		if (test > 0 ) { throw test; }
	}
	catch (int e)
	{
		std::cout << "Number of failed tests : " << e << std::endl;
		return 1;
	}

	demo_dfs();
	demo_bfs();
	demo_dijkstras();
	return 0;

}



