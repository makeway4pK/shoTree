#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shoTree"

#define FILE "DS/sem4/BSTree.2.in"
using namespace std;

template <class T>
struct tnode
{
	T data;
	struct tnode<T> *left, *right;
};

template <class T = int, class Compare = less<T>>
class BSTree
{ // T must be assignable(=),insertable(<<),comparable(<)
	tnode<T> *root;
	shoTree<tnode<T>> sho;
	tnode<T> *delRoot(tnode<T> *root)
	{ // deletes subroot and manages subtree, returns new subroot
		tnode<T> *pn;
		if (root->right)
		{
			pn = root->right;
			while (pn->left)
				pn = pn->left;
			pn->left = root->left;
			pn = root;
			root = root->right;
			delete pn;
			return root;
		}
		else if (root->left)
		{
			pn = root->left;
			while (pn->right)
				pn = pn->right;
			pn->right = root->right;
			pn = root;
			root = root->left;
			delete pn;
			return root;
		}
		else
		{
			delete root;
			return NULL;
		}
	}

  public:
	BSTree(vector<T> v)
	{
		root = NULL;
		insert(v);
	}

	void clear() { clear(root); }
	void clear(tnode<T> *&rut)
	{
		if (!rut)
			return;
		clear(rut->left);
		clear(rut->right);
		delete rut;
		rut = NULL;
	}
	void insert(vector<T> v)
	{
		int i = 0;
		if (!root && v.size())
		{
			root = new tnode<T>;
			root->right = root->left = NULL;
			root->data = v[i++];
		}
		tnode<T> *nn, *pn;
		bool r = 1;
		Compare c;
		while (i < v.size())
		{
			nn = new tnode<T>;
			nn->left = nn->right = NULL;
			nn->data = v[i++];
			pn = root;
			while (r = 1)
				if (c(nn->data, pn->data))
				{
					r = 0;
					if (pn->left)
						pn = pn->left;
					else
						break;
				}
				else if (pn->right)
					pn = pn->right;
				else
					break;
			if (r)
				pn->right = nn;
			else
				pn->left = nn;
		}
	}

	void insert(T v)
	{
		if (!root)
		{
			root = new tnode<T>;
			root->data = v;
			root->right = root->left = NULL;
			return;
		}
		tnode<T> *nn, *pn;
		bool r = 1;
		nn = new tnode<T>;
		nn->left = nn->right = NULL;
		nn->data = v;
		pn = root;

		Compare comp; // declare an obj(functor)

		while (r = 1)
			if (comp(nn->data, pn->data)) // usage of functor
			{
				r = 0;
				if (pn->left)
					pn = pn->left;
				else
					break;
			}
			else if (pn->right)
				pn = pn->right;
			else
				break;
		if (r)
			pn->right = nn;
		else
			pn->left = nn;
	}

	const tnode<T> *search(T key)
	{
		if (!root)
			return NULL;
		tnode<T> *tn = root;
		Compare c;
		while (1)
			if (c(key, tn->data))
				if (tn->left)
					tn = tn->left;
				else
					return NULL;
			else if (c(tn->data, key))
				if (tn->right)
					tn = tn->right;
				else
					return NULL;
			else
				return tn;
	}

	void del(T key)
	{ // search key node and pass to delRoot()
		if (!root)
			return;
		tnode<T> *pn = root;
		bool r;
		Compare c;

		if (c(key, root->data))
			r = 0;
		else if (c(root->data, key))
			r = 1;
		else
		{
			this->root = delRoot(root);
			return;
		}
		while (1)
			if (r)
			{
				if (!pn->right)
				{
					cout << "error in BSTree::del(): Node not found in tree";
					return; // not found
				}
				if (c(key, pn->right->data))
				{
					r = 0;
					pn = pn->right;
				}
				else if (c(pn->right->data, key))
				{
					r = 1;
					pn = pn->right;
				}
				else
				{
					pn->right = delRoot(pn->right);
					return;
				}
			}
			else
			{
				if (!pn->left)
				{
					cout << "error in BSTree::del(): Node not found in tree";
					return; // not found
				}
				if (c(key, pn->left->data))
				{
					r = 0;
					pn = pn->left;
				}
				else if (c(pn->left->data, key))
				{
					r = 1;
					pn = pn->left;
				}
				else
				{
					pn->left = delRoot(pn->left);
					return;
				}
			}
	}

	string shoInorder() { return shoInorder(root); }
	string shoInorder(tnode<T> *root)
	{ // T must be operable by <<
		if (!root)
			return "";
		stringstream out;
		if (root->left)
			out << shoInorder(root->left);
		out << ", " << root->data;
		if (root->right)
			out << shoInorder(root->right);
		return out.str();
	}

	int getHeight() { return getHeight(root); }
	int getHeight(tnode<T> *root)
	{ // calculates height of tree by recursion
		if (!root)
			return 0;
		return 1 + max(getHeight(root->right), getHeight(root->left));
	}

	void shoTree() { sho(root); }

	void sideWays()
	{
		string spacer;
		return sideWays(root, 0, spacer);
	}
	void sideWays(tnode<T> *root, int depth, string &spacer)
	{ // T must be operable by <<
		if (!root)
			return;
		spacer.assign(2 * depth, ' ');
		cout << spacer;
		spacer.assign(2 * getHeight(root), '-');
		cout << spacer << endl;

		sideWays(root->right, depth + 1, spacer);

		spacer.assign(2 * depth, ' ');
		cout << spacer << root->data << endl;

		sideWays(root->left, depth + 1, spacer);

		spacer.assign(2 * depth, ' ');
		cout << spacer;
		spacer.assign(2 * getHeight(root), '-');
		cout << spacer << endl;
	}
};

int main()
{
	ifstream fin(FILE);
	vector<string> v;
	string c;
	int ch;
	fin >> c;
	while (fin)
	{
		v.push_back(c);
		fin >> c;
	}
	BSTree<string> tree = v; // by default, ascending order
	while (1)
	{

		cout << "\n\n\n======================="
				"\n\tTree ops"
				"\n======================="
				"\n Height: "
			 << tree.getHeight()
			 << "\n Current tree In-order:\n"
			 << tree.shoInorder();
		cout << "\n Proper Tree:";
		tree.shoTree();
		cout << "\n 1 - Insert one"
				"\n 2 - Insert more"
				"\n\n 3 - Search"
				"\n 4 - Delete"
				"\n 5 - sideWays"
				"\n 6 - Clear Tree"
				"\n\n 0 - Exit\n>";
		cin >> ch;
		switch (ch)
		{
		case 0:
			return 0;
		case 1:
			cout << " Element:";
			cin >> c;
			tree.insert(c);
			break;
		case 2:
			cout << " How many? ";
			cin >> ch;
			v.resize(ch);
			cout << " Elements:\n";
			for (int i = 0; i < v.size(); i++)
				cin >> v[i];
			tree.insert(v);
			break;
		case 3:
			cout << " Key element:";
			cin >> c;
			if (tree.search(c))
				cout << " Found!";
			else
				cout << " Not Found!";
			break;
		case 4:
			cout << "Key element";
			cin >> c;
			tree.del(c);
			break;
		case 5:
			tree.sideWays();
			break;
		case 6:
			tree.clear();
			break;
		default:
			cout << "\aInvalid Choice!";
		}
	}
	return 0;
}
