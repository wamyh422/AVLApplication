# AVLApplication
以AVL-tree實作一資料查詢應用程式。
一測試資料有5000筆數據，定義一格式Record。
內部目標資料型態為Record，定義如下：
```c++
Record
{
(10 chars) ID, (6 chars) item_class,
(13 chars) Item, (interger) price
}
```
會提供以下功能：
* **Insert**(data_record)：插入一筆record資料進AVL-tree，並以key為主鍵。
* **Search**(key)：以key來搜尋指定record，並記錄下目標record的內容。

## AVL-tree
AVLTree 類別主要以BST(Binary Search Tree)配合 AVL 的規則實作。
實作上會以一個node存放一筆record，Node型態定義如下：
```c++
struct Node
{
  Record data;
  int height;
  node* left;
  node* right;
};
```
AVLTree ADT：
```C++
AVLTree class elements:
public:
  void insert(Record x);
  void remove(Record x); // bonus function
  void show();
  vector<node*> search(string x);
private:
  node* root=NULL; // root of AVL-tree initial is NULL
  node* insert(Record x, node* rt);
  node* RotateRR(node* &rt);
  node* RotateLL(node* &rt);
  node* RotateLR(node* &rt);
  node* RotateRL(node* &rt);
  int height(node* rt); // solve NULL node
  int balance(node* rt);
  node* remove(Record x,node* &rt);<-Bonus function
  node* minNode(node* rt) // for remove function
  void search(node* rt,string key);
  void inorder(node* rt); // View data in tree
```
## AVL rules
AVL 的規則主要有4種： **RR**、**LL**、**LR**和**RL**。
