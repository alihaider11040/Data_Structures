#include<stack>
#include<vector>
#include<iostream>
using namespace std;
template <typename T>
class bst {
	struct treeNode {
		T data;
		int height;
		treeNode* lchild, * rchild;
		treeNode(const T& obj) {
			data = obj;//deep copy
			height = 0;
			lchild = rchild = nullptr;
		}



	};
	treeNode* root;
	int n;

	////////////////////Excess family////////////////////
	bool getAccess(const T& key, treeNode*& par) {
		//returns false if key exists
		par = nullptr;
		treeNode* curr = root;
		while (curr != nullptr) {
			if (key == curr->data)
				return true;
			else {
				par = curr;
				if (key < curr->data) {
					curr = curr->lchild;
				}
				else {
					curr = curr->rchild;
				}
			}
		}
		return false;
	}
	bool searchInTree(const T& key, treeNode* node) {
		while (node != nullptr) {
			if (node->data == key) {
				return true;
			}
			else if (key < node->data) {
				node = node->lchild;
			}
			else if (key > node->data) {
				node = node->rchild;
			}
		}
		return false;
	}
	bool getAccess(const T& key, treeNode*& curr, stack<treeNode*>& ancestors) {
		//ancestors.clear();

		/*
			>If tree is empty: ancestors stack is empty, and curr==nullptr
			>If curr is at root: acnestors stack is emptu, and curr==root
			>If curr is elsewhere is the tree,
			   ancestors stack contains ancestor pointers
			   curr is pointing to that node
			>If tree is not empty but curr does not exit: curr==nullptr,
			ancestors stack contains ancestor pointers
*/
		curr = root;
		if (curr == nullptr)
			return false;

		if (key == root->data)
			return true;

		while (curr != nullptr) {
			ancestors.push(curr);
			if (key == curr->data)
				return true;
			else if (key < curr->data) {
				curr = curr->lchild;
			}
			else {
				curr = curr->rchild;
			}
		}
		return false;
	}
	int numOfChild(treeNode* curr) {
		if (curr == nullptr)
			return -1;
		else
			return
			int(curr->lchild != nullptr) +
			int(curr->rchild != nullptr);
	}
	////////////////Printing/////////////
	void printInOrder(treeNode* curr) {
		if (curr != nullptr) {
			//LNR
			printInOrder(curr->lchild);
			cout << (curr->data) << " ";
			printInOrder(curr->rchild);
		}
	}
	void printPostOrder(treeNode* curr) {
		if (curr != nullptr) {
			//LRN
			printPostOrder(curr->lchild);
			printPostOrder(curr->rchild);
			cout << (curr->data) << " ";
		}
	}
	void printNodes(treeNode* curr, int factor = 0) {
		if (curr != nullptr) {
			printNodes(curr->rchild, factor + 4);
			for (int i = 0; i < factor; i++) {
				cout << "  ";
			}
			cout << curr->data << endl;
			printNodes(curr->lchild, factor + 4);
		}
	}
	//////////////////////Laundry///////////////////
	void cleanup(treeNode* curr) {
		if (curr != nullptr) {//post order
			cleanup(curr->lchild);
			cleanup(curr->rchild);
			delete curr;
		}
	}
	void copy(treeNode*& curr, treeNode* objptr) {
		//Using Pre-order
		if (objptr != nullptr) {
			curr = new treeNode(objptr->data);
			copy(curr->lchild, objptr->lchild);
			copy(curr->rchild, objptr->rchild);
		}
	}
	////////////////////////////Erase cases/////////////////
	void eraseCase0(treeNode*& curr, treeNode*& par) {
		if (curr == root) {
			root = nullptr;
		}
		else {
			if (curr == par->lchild)
				par->lchild = nullptr;
			else
				par->rchild = nullptr;
		}
		delete curr;
	}
	void eraseCase1(treeNode*& curr, treeNode*& par) {
		if (curr == root) {
			root = (curr->lchild != nullptr) ? curr->lchild : curr->rchild;
		}
		else {
			if (curr == par->lchild) {
				par->lchild = (curr->lchild != nullptr) ? curr->lchild : curr->rchild;
			}
			else {//par->rchild==curr
				par->rchild = (curr->lchild != nullptr) ? curr->lchild : curr->rchild;
			}
		}

		delete curr;
	}
	void eraseCase2(treeNode*& curr, treeNode*& par,stack<treeNode*>& ancestors) {

		treeNode* left = curr->rchild;
		treeNode* leftPar = curr;
		ancestors.push(leftPar);
		while (left->lchild != nullptr) {
			leftPar = left;
			ancestors.push(leftPar);
			left = left->lchild;	
		}
		curr->data = left->data;
		(numOfChild(left) == 0) ? eraseCase0(left, leftPar) : eraseCase1(left, leftPar);
	}
	//height//
	int height(treeNode*& root) {

		if (root == nullptr)
			return -1;
		else {

			return root->height;
		}
	}
	int depth(const T& key, treeNode*& root) {
		if (root->data == key) {
			return 0;
		}
		else {

			return 1 + ((key > root->data) ? depth(key, root->rchild) : depth(key, root->lchild));
		}


	}
	int isBalanced(treeNode*& root, bool& balanceCheck) {
		if (balanceCheck == false) {
			return 0;
		}
		else {
			if (root == nullptr) {
				return -1;
			}
			else {

				int l = isBalanced(root->lchild, balanceCheck);
				int r = isBalanced(root->rchild, balanceCheck);
				if (balanceCheck == true) {
					balanceCheck = ((r - l == 1) || (r - l == 0) || (r - l == -1));
					return 1 + max(l, r);
				}
			}
		}
		return balanceCheck;
	}
	void copy(T sortedData[], int start, int end, treeNode*& root) {
		if (start > end) {

		}
		else {
			int mid = (start + end) / 2;//first mid
			root = new treeNode(sortedData[mid]);
			n++;
			copy(sortedData, start, mid - 1, root->lchild);//while movinf left
			copy(sortedData, mid + 1, end, root->rchild);//reverse for right
		}
	}
	//== operator //
	void add_Stack(treeNode*& root, stack<int>& saver) {
		if (root != nullptr) {
			add_Stack(root->lchild, saver);
			saver.push(root->data);
			add_Stack(root->rchild, saver);
		}
	}
	void pathSum(treeNode*& root, vector<T>& sum, T temp) {
		if (numOfChild(root) == 0 || root == nullptr) {
			if (root != nullptr) {
				sum.push_back(temp + root->data);
			}
		}
		else {
			pathSum(root->lchild, sum, temp + (root->data));
			pathSum(root->rchild, sum, temp + root->data);
		}
	}
	//SubTree Match Function//	
	void match_SubTree(treeNode* operandRoot, treeNode* key_InSource, bool& match) {
		if (match) {
			if (operandRoot == nullptr && key_InSource == nullptr) {

			}
			else if (key_InSource == nullptr && operandRoot != nullptr) {
				match = false;
			}
			else if (operandRoot == nullptr && key_InSource != nullptr) {

			}
			else if (operandRoot->data != key_InSource->data) {
				match = false;
			}
			else {
				match = (operandRoot->data == key_InSource->data);
				match_SubTree(operandRoot->lchild, key_InSource->lchild, match);
				match_SubTree(operandRoot->rchild, key_InSource->rchild, match);
			}
		}
	}

	void breadth(treeNode*& root, int* arr, int i) {
		if (root != nullptr) {

			arr[i] = arr[i] + 1;
			breadth(root->lchild, arr, i + 1);
			breadth(root->rchild, arr, i + 1);
		}
	}
	//Trim//
	void Trim(treeNode*& root, int trimKey, int lev = 0) {
		if (root == nullptr) {

		}
		else if (lev > trimKey) {
			cleanup(root);
			root = nullptr;
		}
		else {
			Trim(root->lchild, trimKey, lev + 1);
			Trim(root->rchild, trimKey, lev + 1);
		}
	}
	void lowestCommonAncestor(treeNode* node, const T& key1, const T& key2, bool& match, T& key) {
		if (node == nullptr) {

		}
		else if (key1< node->data && key2>node->data) {
			if (searchInTree(key1, node->lchild) && searchInTree(key2, node->rchild)) {
				match = true;
				key = node->data;
			}
		}
		else if (key1 > node->data && key2 < node->data) {
			if (searchInTree(key1, node->rchild) && searchInTree(key2, node->lchild)) {
				match = true;
				key = node->data;

			}
		}
		else if ((key1 == node->data) && (searchInTree(key2, node->lchild) || searchInTree(key2, node->rchild))) {
			match = true;
			key = node->data;

		}
		else if ((key2 == node->data) && (searchInTree(key1, node->lchild) || searchInTree(key1, node->rchild))) {
			match = true;
			key = node->data;

		}
		else {
			if (!match) {
				lowestCommonAncestor(node->lchild, key1, key2, match, key);
				if (!match) {
					lowestCommonAncestor(node->rchild, key1, key2, match, key);
				}
			}
		}
	}
public:
	//----------------------------Constructors---------------------------------//
	bst() {
		root = nullptr;
		n = 0;
	}
	bst(const bst<T>& obj) {
		//copy constructor
		copy(root, obj.root);
	}
	bst(T sortedData[], int n) {
		copy(sortedData, 0, n - 1, root);
	}

	//---------------------Addition And removal------------------------------//
	void erase(const T& key) {
		treeNode* par;
		stack<treeNode*> ancestors;
		if (getAccess(key, par,ancestors)) {

			//key found
			treeNode* curr = nullptr;
			if (par == nullptr) {
				curr = root;
			}
			else {
				curr = par;
				if (!ancestors.empty()) {
					ancestors.pop();
					par = ancestors.top();
				}
					
			}
			if (numOfChild(curr) == 0) {
				//case 0
				eraseCase0(curr, par);
			}
			else if (numOfChild(curr) == 1) {
				//case 1
				eraseCase1(curr, par);
			}
			else {
				//case 2
				eraseCase2(curr, par,ancestors);
			}
			update_AncestorHeight(ancestors);
		}
	}
	void rotateLeft(treeNode*& node, treeNode*& par) {
		if (node->rchild != nullptr) {
			treeNode* promote = node->rchild;
			treeNode* demote = node;
			treeNode* orphan = promote->lchild;

			promote->lchild = demote;
			demote->rchild = orphan;
			if (par == nullptr) {
				root = promote;
			}
			else {
				if (node->data < par->data) {
					par->lchild = promote;
				}
				else {
					par->rchild = promote;
				}
			}
			update_Height(demote);
			update_Height(promote);
		}
	}
	void rotateRight(treeNode*& node, treeNode*& par) {
		if (node->lchild != nullptr) {
			treeNode* promote = node->lchild;
			treeNode* demote = node;
			treeNode* orphan = promote->rchild;

			promote->rchild = demote;
			demote->lchild = orphan;
			if (par == nullptr) {
				root = promote;
			}
			else {
				if (node->data < par->data) {
					par->lchild = promote;
				}
				else {
					par->rchild = promote;
				}
			}
			update_Height(demote);
			update_Height(promote);

		}
	}
	void update_Height(treeNode*& root) {
		root->height = max(height(root->lchild),height( root->rchild)) + 1;
	}
	int get_BalanceFactor(treeNode* root) {
		return(height(root->rchild) - height(root->lchild));
	}
	void right_Heavy(treeNode*& node, treeNode*& par) //left rotation
	{
		if (get_BalanceFactor(node->rchild) ==- 1)//RL case
		{
			rotateRight(node->rchild, node);
		}
		rotateLeft(node, par);
	}
	void left_Heavy(treeNode*& node, treeNode*& par) //right rotation
	{

		if (get_BalanceFactor(node->lchild) == 1)//LR case
		{
			rotateLeft(node->lchild, node);
		}
		rotateRight(node, par);
	}
	void balanceNode(treeNode*& node, treeNode*& par) {
		if (get_BalanceFactor(node) > 1)//right heavy case
		{
			right_Heavy(node, par);
		}
		else if (get_BalanceFactor(node) < -1) {
			left_Heavy(node, par);
		}
	}
	void update_AncestorHeight(stack<treeNode*>& ancestor) {
		while (!ancestor.empty()) {
			treeNode* temp = ancestor.top();//new added
			ancestor.pop();
			if (ancestor.empty() == false) {
				update_Height(temp);
				balanceNode(temp, ancestor.top());//new aded,par
				//update_Height(ancestor.top());//update par
			}
		}
		update_Height(root);
		if ((get_BalanceFactor(root)<-1) || (get_BalanceFactor(root)>1)) {
			treeNode* dummy = nullptr;
			balanceNode(root, dummy);
			update_Height(root);
		}
	}

	void insert(const T& data) {
		treeNode* par;
		stack<treeNode*> ancestor;
		if (getAccess(data, par, ancestor) == false) {
			//add new node as a child of parent
			//par contains the parent pointer
			treeNode* temp = new treeNode(data);
			if (ancestor.empty()) {//tree is empty
				root = temp;
			}
			else {
				if (ancestor.top()->data < data) {
					ancestor.top()->rchild = temp;
				}
				else {
					ancestor.top()->lchild = temp;
				}
			}
			n++;
			update_AncestorHeight(ancestor);
		}
	}
	//----------------------------Operator----------//
	const bst<T>& operator = (const bst<T>& obj) {
		cleanup(root);//uses post order
		copy(root, obj.root);//uses preorder
	}
	//------------------Sucessor and Predecessor-------------------------//
	const T& sucessor(const T& key) {
		stack<treeNode*> ancestors;
		treeNode* curr = nullptr;
		if (getAccess(key, curr, ancestors)) {
			if (curr->rchild != nullptr) {
				curr = curr->rchild;
				while (curr->lchild != nullptr) {
					curr = curr->lchild;
				}
				return curr->data;
			}
			//Case B: curr has no right subtree
			else {
				treeNode* child = ancestors.top();
				ancestors.pop();
				treeNode* parent = ancestors.top();
				ancestors.pop();
				while (ancestors.empty() == false) {
					if (parent->data < child->data) {
						child = parent;
						parent = ancestors.top();
						ancestors.pop();

					}
					else {
						return parent->data;
					}
				}
				if (parent->data > child->data)
					return parent->data;
				return NULL;
			}
		}
		return NULL;
	}
	const T& predecessor(const T& key) {
		stack<treeNode*> ancestors;
		treeNode* curr = nullptr;
		if (getAccess(key, curr, ancestors)) {
			//Case A: curr has a left subtree
			// left and all the way right
			if (curr->lchild != nullptr) {
				curr = curr->lchild;
				while (curr->rchild != nullptr) {
					curr = curr->rchild;
				}
				return curr->data;
			}
			//Case B: curr has no left subtree
			else {
				treeNode* child = ancestors.top();
				ancestors.pop();
				treeNode* parent = ancestors.top();
				ancestors.pop();
				while (ancestors.empty() == false) {
					if (parent->data > child->data) {
						child = parent;
						parent = ancestors.top();
						ancestors.pop();

					}
					else {
						return parent->data;
					}
				}
				if (parent->data < child->data)
					return parent->data;
				return NULL;
			}
		}
		return NULL;
	}
	//Printing//
	void printInOrder() {
		printInOrder(root);
	}
	void printPostOrder() {
		printPostOrder(root);
	}
	void printNodes() {
		printNodes(root);
	}
	//Efficieny //
//--------------------------Height and Depth-------------------------//
	int height() {
		return height(root);
	}
	int depth(const T& key) {
		treeNode* ptr = nullptr;
		if (getAccess(key, ptr) == true) {
			return depth(key, root);
		}
		return NULL;
	}
	bool isBalanced() {
		bool balanceCheck = true;
		return isBalanced(root, balanceCheck);
	}
	//path sum//
	vector<T> pathSum() {
		vector<T> sum;
		T temp = 0;
		pathSum(root, sum, temp);
		return sum;
	}
	int breadth() {
		int size = height() + 1;
		int* counter = new int[size];
		for (int i = 0; i < size; i++) {
			counter[i] = 0;
		}
		breadth(root, counter, 0);
		int max = 0;
		for (int i = 0; i < size; i++) {
			if (counter[i] > max) {
				max = counter[i];
			}
		}
		return max;
	}

	//bool operator//
	bool operator==(bst<T>& obj) {
		if (n != obj.n) {
			return false;
		}
		else {
			stack<int> source;
			add_Stack(root, source);//o(n)
			stack<int> parameter;
			add_Stack(obj.root, parameter);//o(n)
			int size = parameter.size();
			for (int i = 0; i < size; i++) {//n times=o(n)
				if (source.top() == parameter.top()) {
					source.pop();
					parameter.pop();
				}
				else {
					return false;
				}//overall time n+n+n=3n=o(n)
			}
			return true;
		}
	}
	//isSubTree//
	bool isSubTree(bst<T>& obj) {//take const time
		treeNode* root_match = nullptr;
		if (getAccess(obj.root->data, root_match)) {
			if (root_match != nullptr) {
				root_match = (obj.root->data > root_match->data) ? root_match->rchild : root_match->lchild;
			}
			else {
				root_match = root;
			}
			bool match = true;
			match_SubTree(obj.root, root_match, match);//Tree match n
			return match;
		}
		return false;
	}

	bool isSubSet(bst<T>& obj) {
		if (obj.root == nullptr)
			return true;
		stack<int> saver;
		stack<int> source;
		if (root == nullptr)
			return false;
		add_Stack(obj.root, saver);
		add_Stack(root, source);
		bool misMatch = false;
		while (!source.empty() && misMatch == false) {
			if (source.top() < saver.top()) {
				source.pop();
			}
			else if (source.top() == saver.top()) {
				source.pop();
				saver.pop();
			}
			else {
				misMatch = true;
			}
		}
		return !misMatch;
	}
	//Destructor//
	void searchAndPromote(const T& key) {
		stack<treeNode*> ancestors;
		treeNode* curr = nullptr;
		if (getAccess(key, curr, ancestors)) {

			ancestors.pop();
			while (!ancestors.empty()) {
				treeNode* pivot = ancestors.top();
				ancestors.pop();
				treeNode* dummy = nullptr;
				if (pivot->data < key) {
					rotateLeft(pivot, (ancestors.empty()) ? dummy : ancestors.top());
				}
				else {
					rotateRight(pivot, (ancestors.empty()) ? dummy : ancestors.top());
				}
			}

		}
	}
	~bst() {
		cleanup(root);
	}

	void trimBelowK(int K) {

		if (K > 0) {
			Trim(root, K);
		}
	}
	T lowestCommonAncestor(const T& key1, const T& key2) {
		bool match = false;
		T key = NULL;
		lowestCommonAncestor(root, key1, key2, match, key);
		return key;
	}
	void print_balance() {
		print_balance(root);
	}
	void print_balance(treeNode* root) {
		if (root != nullptr) {
			print_balance(root->lchild);
			cout << "Balance factor of " << root->data << " is: " << get_BalanceFactor(root) << endl;
			print_balance(root->rchild);
		}
	}
	void print_height() {
		print_height(root);
	}
	void print_height(treeNode*& root) {
		if (root != nullptr) {
			print_height(root->lchild);
			cout << "height of " << root->data << " is: " << root->height << endl;
			print_height(root->rchild);
		}
	}
};
int main() {

	bst<int> tree;
	srand(time(0));
	for (int i = 0; i < 10000; i++) {
		tree.insert(rand()% 1000000);
	}

	tree.printNodes();

	cout << endl;
	tree.erase(7);
	//tree.print_balance();
	cout << endl;
	tree.printNodes();

	cout << endl;
	tree.print_balance();
	cout << endl;
	tree.print_height();
	system("pause");
	return 0;
}