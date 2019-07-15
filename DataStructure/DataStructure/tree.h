#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include "common.h"

using namespace std;
using namespace common;

namespace BinaryTree
{
	template <typename T>
	class treeNode
	{
	public:
		treeNode() { leftchild = rightchild = nullptr; }
		treeNode(const treeNode &other):val(other.val), 
			leftchild(other.leftchild), rightchild(other.rightchild) {}
		treeNode(const T &theElement) :val(theElement),
			leftchild(nullptr), rightchild(nullptr) {}
		treeNode(const T &theElement, treeNode *left, treeNode *right):
			val(theElement), leftchild(left), rightchild(right){}
		treeNode(const T &theElement, treeNode *left, treeNode *right, string theTag) :
			val(theElement), leftchild(left), rightchild(right), tag(theTag) {}

		T val;
		string tag;
		treeNode *leftchild;
		treeNode *rightchild;
	};

	template <typename T>
	class tree
	{
	public:
		tree():root(nullptr) {}
		tree(const tree<T> &other):root(other.root) {}
		tree(const treeNode<T> *node):root(node) {}
		tree(const vector<T> &data)
		{
			if (data.empty())
			{
				root = nullptr;
				return;
			}
			
			int index = 1;
			queue<treeNode<T> *> _nodes;
			treeNode<T> *_root = new treeNode<T>(data[0]);
			_root->tag = "N" + to_string(index - 1);
			_nodes.push(_root);
			
			while (index < data.size())
			{
				treeNode<T> *local = _nodes.front();
				_nodes.pop();
				treeNode<T> *leftchild = new treeNode<T>(data[index++]);
				local->leftchild = leftchild;
				local->leftchild->tag = "N" + to_string(index - 1);
				_nodes.push(leftchild);
				if (index < data.size())
				{
					treeNode<T> *rightchild = new treeNode<T>(data[index++]);
					local->rightchild = rightchild;
					local->rightchild->tag = "N" + to_string(index - 1);
					_nodes.push(rightchild);
				}
			}
			root = _root;
		}

		void layerOrder(vector<vector<T>> &data, ostream &out = cout){
			_layerOrderImpl(data, out);
		}
		void preOrder(vector<T> &data, ostream &out = cout){
			_preOrderImpl(data, out);
		}
		void inOrder(vector<T> &data, ostream &out = cout){
			_inOrderImpl(data, out);
		}
		void postOrder(vector<T> &data, ostream &out = cout) {
			_postOrderImpl(data, out);
		}
		void visualize() {
			_visualizeImpl(); //MarkDown Form;
		}

	private:
		treeNode<T> *root;
		static const string visualFile;
		void _layerOrderImpl(vector<vector<T>> &data, ostream &out)
		{
			data.clear();
			if (root == nullptr) return;
			queue<treeNode<T>*> _nodes;
			_nodes.push(root);
			int layerSize = 1;
			while (!_nodes.empty())
			{
				for (auto i = 0; i < layerSize; ++i)
				{
					treeNode<T> *local = _nodes.front();
					_nodes.pop();
					if (local->leftchild != nullptr) _nodes.push(local->leftchild);
					if (local->rightchild != nullptr) _nodes.push(local->rightchild);
					out << local->val << ends;
				}
				layerSize = _nodes.size();
			}
		}

		void _preOrderImpl(vector<T> &data, ostream &out)
		{
			data.clear();
			if (root == nullptr) return;
			stack<treeNode<T>*> _nodes;
			_nodes.push(root);
			while (!_nodes.empty())
			{
				treeNode<T> *local = _nodes.top();
				_nodes.pop();
				out << local->val << ends;
				if (local->rightchild != nullptr) _nodes.push(local->rightchild);
				if (local->leftchild != nullptr) _nodes.push(local->leftchild);
			}
		}

		void _inOrderImpl(vector<T> &data, ostream &out)
		{
			data.clear();
			if (root == nullptr) return;
			stack<treeNode<T> *> _nodes;
			treeNode<T> *p = root;
			while (p != nullptr || !_nodes.empty())
			{
				while (p != nullptr)
				{
					_nodes.push(p);
					p = p->leftchild;
				}
				treeNode<T> *cur = _nodes.top();
				_nodes.pop();
				out << cur->val << ends;
				data.emplace_back(cur->val);
				p = cur->rightchild;
			}
		}

		void _postOrderImpl(vector<T> &data, ostream &out)
		{
			data.clear();
			if (root == nullptr) return;
			stack<treeNode<T>*> _nodes;
			_nodes.push(root);
			while (!_nodes.empty())
			{
				treeNode<T> *local = _nodes.top();
				data.emplace_back(local->val);
				_nodes.pop();
				if (local->leftchild != nullptr) _nodes.push(local->leftchild);
				if (local->rightchild != nullptr) _nodes.push(local->rightchild);
			}
			reverse(data.begin(), data.end());
			for (T &num : data)
				out << num << ends;
		}

		void _preOrderImpl(treeNode<T> *root, vector<T> &data, ostream &out)
		{
			if (root == nullptr) return;
			out << root->val << ends;
			data.emplace_back(root->val);
			_preOrderImpl(root->leftchild, data, out);
			_preOrderImpl(root->rightchild, data, out);
		}

		void _inOrderImpl(treeNode<T> *root, vector<T> &data, ostream &out)
		{
			if (root == nullptr) return;
			_inOrderImpl(root->leftchild, data, out);
			out << root->val << ends;
			data.emplace_back(root->val);
			_inOrderImpl(root->rightchild, data, out);
		}

		void _postOrderImpl(treeNode<T> *root, vector<T> &data, ostream &out)
		{
			if (root == nullptr) return;
			_postOrderImpl(root->leftchild, data, out);
			_postOrderImpl(root->rightchild, data, out);
			out << root->val << ends;
			data.emplace_back(root->val);
		}

		string _desripLine(treeNode<T> *node1, treeNode<T> *node2)
		{
			string sRes;
			stringstream ss;
			ss << node1->tag << "(" << node1->val << ")";
			ss << "-->";
			ss << node2->tag << "(" << node2->val << ")";
			ss >> sRes;
			return sRes;
		}

		string _desripLine(treeNode<T> *node, int child)
		{
			if (child == 0 && node->leftchild != nullptr) return _desripLine(node, node->leftchild);
			if (child == 1 && node->rightchild != nullptr) return _desripLine(node, node->rightchild);
			string child_tag = child == 0 ? node->tag + "_left" : node->tag + "_right";
			string sRes;
			stringstream ss;
			ss << node->tag << "(" << node->val << ")";
			ss << "-->";
			ss << child_tag << "(null)";
			ss >> sRes;
			return sRes;
		}


		void _visualizeImpl()
		{
			ofstream outfile(visualFile);
			if (!outfile)
			{
				cerr << "Open File Failed!" << endl;
				return;
			}
			outfile << "```mermaid" << endl;
			outfile << "graph TD" << endl;
			queue<treeNode<T> *> qNodes;
			qNodes.push(root);
			while (!qNodes.empty())
			{
				treeNode<T> *local = qNodes.front();
				qNodes.pop();
				outfile << _desripLine(local, 0) << endl;
				outfile << _desripLine(local, 1) << endl;
				if (local->leftchild != nullptr)
					qNodes.push(local->leftchild);
				if (local->rightchild != nullptr)
					qNodes.push(local->rightchild);
			}
			outfile.close();
		}
	};

	class treeTest
	{
	private:
		tree<int> *treeInt;
	public:
		void testConstruct()
		{
			vector<int> vData;
			int len = 10, minValue = 0, maxValue = 20;
			common::genRandomInt(vData, len, minValue, maxValue);
			cout << "RawData: " << endl;
			cout << vData;
			treeInt = new tree<int>(vData);
			treeInt->visualize();
		}

		void testOrder()
		{
			vector<int> vData;
			cout << "PreOrder: " << endl;
			treeInt->preOrder(vData);
			cout << endl;
			cout << "inOrder: " << endl;
			treeInt->inOrder(vData);
			cout << endl;
			cout << "PostOrder: " << endl;
			treeInt->postOrder(vData);
			cout << endl;
		}

		void testMain()
		{
			testConstruct();
			testOrder();
		}
	};
}