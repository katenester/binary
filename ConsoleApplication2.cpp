#include <iostream>
using namespace std;

struct tree
{
	int key;
	tree* left;
	tree* right;
	int balance;
};


int Height(tree* root)
{
	if (root == NULL) return 0;
	int hLeft = Height(root->left), hRight = Height(root->right);
	if (hLeft > hRight)
		return hLeft + 1;
	else
		return hRight + 1;
}
void SetBalance(tree* root)
{
	if (root != NULL) root->balance = Height(root->right) - Height(root->left);

}

void TurnRight(tree*& root)
{
	tree* leftSubtree, * leftSubtreeRightSubtree;
	leftSubtree = root->left;
	leftSubtreeRightSubtree = leftSubtree->right;

	leftSubtree->right = root;
	root->left = leftSubtreeRightSubtree;
	root = leftSubtree;
	SetBalance(root->right);
	SetBalance(root);
}
void TurnLeft(tree*& root)
{
	tree* rightSubtree, * rightSubtreeLeftSubtree;
	rightSubtree = root->right;
	rightSubtreeLeftSubtree = rightSubtree->left;

	rightSubtree->left = root;
	root->right = rightSubtreeLeftSubtree;
	root = rightSubtree;
	SetBalance(root->left);
	SetBalance(root);
}

void insert(tree* (&root), int d)
{
	if (root == NULL)
	{

		root = new tree;
		root->key = d;
		root->balance = 0;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{
		if (d > root->key)
		{
			insert(root->right, d);
			if (Height(root->right) - Height(root->left) > 1)
			{
				if (Height(root->right->right) < Height(root->right->left))
					TurnRight(root->right);
				TurnLeft(root);
			}
		}
		else if (d < root->key)
		{
			insert(root->left, d);
			if (Height(root->left) - Height(root->right) > 1)
			{
				if (Height(root->left->left) < Height(root->left->right))
					TurnLeft(root->left);
				TurnRight(root);
			}

		}
		SetBalance(root);
	}
}
void Print(tree* item)
{
	if (item == NULL)    return;
	cout << item->key << endl;
	Print(item->left);
	Print(item->right);
}
void print_Tree(tree* root, int level)
{
	if (root)
	{
		print_Tree(root->left, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		cout << root->key << endl;
		print_Tree(root->right, level + 1);
	}
}

void deleteALL(tree* item)
{
	if (item->right != NULL) deleteALL(item->right);
	if (item->left != NULL) deleteALL(item->left);
	delete item;
};

tree* deleteElem(tree*& root, int value)
{

	if (root == NULL) {
		return NULL;
	}
	else if (value < root->key) {
		root->left = deleteElem(root->left, value);
	}
	else if (value > root->key) {
		root->right = deleteElem(root->right, value);
	}
	else {
		if (root->left == NULL) {
			tree* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL) {
			tree* temp = root->left;
			delete root;
			return temp;
		}
		else {
			tree* temp = root->right;
			while (temp->left != NULL) {
				temp = temp->left;
			}
			root->key = temp->key;
			root->right = deleteElem(root->right, temp->key);
		}
	}
	if (Height(root->right) - Height(root->left) > 1)
	{
		if (Height(root->right->right) < Height(root->right->left))
			TurnRight(root->right);
		TurnLeft(root);
	}
	if (Height(root->left) - Height(root->right) > 1)
	{
		if (Height(root->left->left) < Height(root->left->right))
			TurnLeft(root->left);
		TurnRight(root);
	}
	return root;
}
bool Search(tree* root, int val) {
	if (root == NULL) { return false; }
	else if (root->key == val) { return true; }
	else if (val < root->key)
		return Search(root->left, val);
	else
		return Search(root->right, val);
}

int menu() {
	int x;
	cout << "1. Создание сбалансированного дерева" << endl;
	cout << "2. Добавление элемента в дерево" << endl;
	cout << "3. Удалить всё дерево" << endl;
	cout << "4. Удаление элемента" << endl;
	cout << "5. Найти элемент ( проверка есть ли такой)" << endl;
	cout << "6. Вывод дерева. Прямой обход" << endl;
	cout << "7. Вывод дерева 2D" << endl;
	cout << "0. Выход" << endl;
	cin >> x;
	return x;

}
int main()
{
	setlocale(LC_ALL, "Russian");
	tree* root = NULL; //root- корень
	bool f = false; //Дерево пока не создано . f- проверка на созданность
	int d;// переменная для операций
	while (true)
	{
		switch (menu())
		{
		case 0: return 0; //Выход из дерева
			break;
		case 1: // Создание дерева
			if (f == true) { cout << "Дерево уже было создано. Для обновления сначало удалите дерево" << endl; }
			else { cout << "Дерево создано" << endl; }
			break;
		case 2: // Добавление элемента в дерево
			if (f) {
				cout << "Введите значение: ";
				cin >> d;
				insert(root, d);
			}
			else
			{
				cout << "Введите значение: ";
				cin >> d;
				insert(root, d);
				f = true;
			}
			break;
		case 3: //Удалить всё дерево
			if (f) {
				deleteALL(root);
				f = false;
			}
			else { cout << "Дерево не создано" << endl; }
			break;
		case 4:// Удаление элемента
			if (f)
			{
				cout << "Какой элемент удалить?" << endl;
				cin >> d;
				root = deleteElem(root, d);//нужно в случае, если удаляем корень
				if (root == NULL) f = false;
			}
			else { cout << "Дерево не создано" << endl; }
			break;
		case 5://Найти элемент
			if (f) {
				cout << "Введите искомый элемент: ";
				cin >> d;
				if (Search(root, d)) {
					cout << "Значение найдено" << endl;
				}
				else {
					cout << "Значение не найдено" << endl;
				}
			}
			else cout << "Дерево не создано " << endl;
			break;
		case 6: //Прямой обход
			if (f) {
				Print(root);
			}
			else { cout << "Дерево не создано" << endl; }
			break;
		case 7://Вывод дерева 2D
			if (f) {
				print_Tree(root, Height(root));
			}
			else { cout << "Дерево не создано" << endl; }
			break;
		}
	}
	return 0;
}
