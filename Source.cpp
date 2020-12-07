#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int number = 0;
struct Record
{
	string ID;
	string Item_class;
	string Item;
	int price;
};

struct node
{
	Record data;
	int height;
	node* left;
	node* right;
};
vector<node*> search_item;

class AVLTree 
{
public :
	void insert(Record x)
	{
		root = insert(x, root);
	}
	void remove(Record x)
	{
		root = remove(x, root);
	}
	void show()
	{
		cout << "ID , Item_class , Item , price\n";
		inorder(root);
		cout << "Root record :\n";
		cout << root->data.ID << " , " << root->data.Item_class << " , " << root->data.Item << " , " << root->data.price << endl;
		cout << "Total record : " << number << endl;
	}
	vector<node*> search(string x)
	{
		search(root, x);
		return search_item;
	}
private:
	node* root = NULL;

	node* insert(Record x, node* rt)
	{
		if (rt == NULL)
		{
			rt = new node;
			rt->data = x;
			rt->height = 0;
			rt->left = rt->right = NULL;
		}
		else if (stoi(x.ID) <= stoi(rt->data.ID))
		{
			//BST rule : less left and more right
			//And self balance tree check height here
			rt->left = insert(x, rt->left);
			if (balance(rt) == 2)
			{
				if (stoi(x.ID) < stoi(rt->left->data.ID))
					rt = RotateLL(rt);
				else
					rt =  RotateLR(rt);
			}
		}
		else if (stoi(x.ID) > stoi(rt->data.ID))
		{
			rt->right = insert(x, rt->right);
			if (balance(rt) == -2)
			{
				if (stoi(x.ID) > stoi(rt->right->data.ID))
					rt = RotateRR(rt);
				else
					rt =  RotateRL(rt);
			}
		}

		rt->height = max(height(rt->left), height(rt->right)) + 1;
		return rt;
	}
	node* RotateLL(node* &rt)
	{
		node* x = rt->left;
		rt->left = x->right;
		x->right = rt;
		rt->height = max(height(rt->left), height(rt->right)) + 1;
		x->height = max(height(x->left), rt->height) + 1;
		return x;
	}
	node* RotateRR(node* &rt)
	{
		node* x = rt->right;
		rt->right = x->left;
		x->left = rt;
		rt->height = max(height(rt->left), height(rt->right));
		x->height = max(height(rt->right), rt->height);
		return x;
	}
	node* RotateLR(node* &rt)
	{
		rt->left = RotateRR(rt->left);
		return RotateLL(rt);
	}
	node*  RotateRL(node*& rt)
	{
		rt->right = RotateLL(rt->right);
		return RotateRR(rt);
	}
	int height(node* rt)
	{
		if (rt == NULL)
			return 0;
		else
			rt->height;
	}
	//balance value > 0 Right heavy and < 0 Left heavy
	int balance(node* rt)
	{
		if (rt == NULL) return 0;
		else return height(rt->left) - height(rt->right);
	}
	node* remove(Record x, node* &rt)
	{
		node* temp;

		if (rt == NULL) return NULL;
		else if (x.ID < rt->data.ID) rt->left = remove(x, rt->left);
		else if (x.ID > rt->data.ID) rt->right = remove(x, rt->right);
		else if (rt->left && rt->right)
		{
			temp = minNode(rt->right);
			rt->data = temp->data;
			rt->right = remove(rt->data, rt->right);
		}
		else
		{
			temp = rt;
			if (rt->left == NULL)
				rt = rt->right;
			else if (rt->right == NULL)
				rt = rt->left;
			delete temp;
		}
		if (rt == NULL) return rt;
		rt->height = max(height(rt->left), height(rt->right)) + 1;

		//balance tree
		if (balance(rt) == 2)
		{
			//RR
			if (balance(rt->right) == 1) return RotateRR(rt);
			//RL
			else return  RotateRL(rt);
		}
		else if (balance(rt) == -2)
		{
			//LL
			if (balance(rt->left) == -1) return RotateLL(rt);
			//LR
			else return  RotateLR(rt);
		}
		return rt;
	}
	node* minNode(node* rt)
	{
		if (rt == NULL)
			return NULL;
		else if (rt->left == NULL)
			return rt;
		else
			return minNode(rt->left);
	}
	void search(node* rt,string key)
	{
		if (rt == NULL) return ;
		else if (stoi(key) < stoi(rt->data.ID))  search(rt->left, key);
		else if (stoi(key) > stoi(rt->data.ID))  search(rt->right, key);
		else
		{
			search_item.push_back(rt);
			search(rt->left, key);
		}
	}
	void inorder(node* rt)
	{
		if (rt == NULL) return;
		number++;
		inorder(rt->left);
		cout << rt->data.ID << " , " << rt->data.Item_class << " , " << rt->data.Item << " , " << rt->data.price << endl;
		inorder(rt->right);
	}
};

int main()
{
	AVLTree tree;
	ifstream fin("Data.txt",ios::in);
	Record buffer;

	cout << "Read data record\n";
	if (fin)
	{
		while (!fin.eof())
		{
			fin >> buffer.ID >> buffer.Item_class >> buffer.Item >> buffer.price;
			tree.insert(buffer);
		}
		tree.show();
		number = 0;
	}
	else cout << "Can't find input data.\n";


	char input;
	do
	{
		cout << "Select function : \n";
		cout << "|- (a). insert data record\n";
		cout << "|- (b). search data record\n";
		cout << "|- (c). delete data record\n";
		cout << "|- (d). show data\n";
		cout << "|- (q). Quit program\n";
		cout << " >> "; cin >> input;
		if (input == 'a' || input == 'A')
		{
			Record temp;
			cout << "Key in your new record (ID Item_class Item price) >>"; cin >> temp.ID >> temp.Item_class >> temp.Item >> temp.price;
			tree.insert(temp);
		}
		else if (input == 'b' || input == 'B')
		{
			string temp;
			cout << "Key in target record ID to search >> "; cin >> temp;
			search_item.clear();
			vector<node*> result = tree.search(temp);
			if (!result.empty())
			{
				cout << "Find ID : " << temp << " records :\n";
				for (node* i : result)
					cout <<"|- "<< i->data.ID << " , " << i->data.Item_class << " , " << i->data.Item << " , " << i->data.price << endl;
				cout << "Total : " << result.size()<<endl;
			}
			else cout << "Can't find ID : " << temp << endl;
		}
		else if (input == 'c' || input == 'C')
		{
			string temp;
			cout << "Key in target record ID to delete >>"; cin >> temp;
			search_item.clear();
			vector<node*> result = tree.search(temp);
			if (result.empty())
				cout << "Can't find ID : " << temp << endl;
			else
			{
				int select;
				int num = 0;
				for (node* i : result)
				{
					num++;
					cout <<num<<" : " << i->data.ID << " , " << i->data.Item_class << " , " << i->data.Item << " , " << i->data.price << endl;
				}
				cout << "Total : " << result.size() << endl;
				cout << "Select record you want to delete >> "; cin >> select;
				if (select <= 0 || select > result.size())
				{
					cout << "Error input\n";
					exit(1);
				}
				select--;
				tree.remove(result[select]->data);
				cout << "Delete record : " << result[select]->data.ID << " , " << result[select]->data.Item_class << " , " << result[select]->data.Item << " , " << result[select]->data.price << " successfully.\n";
			}
		}
		else if (input == 'd' || input == 'D')
		{
			tree.show();
			number = 0;
		}
	} while (input != 'q' && input != 'Q');

	return 0;
}