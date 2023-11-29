#include <iostream>
#include <vector>
#include <string.h>
#include <windows.h>

using namespace std;

struct Guardian{   //Definición de guardian y sus caracteristicas, como nombre, NivelDePoder, ciudad, maestro y aprendices.
    char Name[20];
    int PowerLevel;
    char Master[20];
    char City[20];
    string Apprentice[20];
};
struct Node { //Nodo para el arbol binario
    string ByName;    
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(string strValue, int value) : ByName(strValue), data(value), left(nullptr), right(nullptr) {}
};

// Funcion para ingresar un nuevo nodo al arbol binario
Node* insert(Node* root, string strValue,int value) {
    // Si el arbol esta vacio, añade un nuevo nodo y lo convierte en raiz
    if (root == nullptr) {
        return new Node(strValue, value);
    }

    // Si no es asi, recorre el arbol.
    if (value < root->data) {
        root->left = insert(root->left, strValue,value);
    } else if (value > root->data) {
        root->right = insert(root->right, strValue, value);
    }

    return root;
}

void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        if (root->data >= 90 && root->data < 100) {
            cout <<  root->ByName  << " " << root->data;
        }
        inorderTraversal(root->right);
    }
}

template <typename T>
class TreeNode {
public:
    T data;
    vector<TreeNode*> children;

    // Constructor
    TreeNode(T value) : data(value) {}

    // Destructor to free allocated memory
    ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }
    }
};

// General Tree class to manage the general tree
template <typename T>
class GeneralTree {
private:
    TreeNode<T>* root;

public:
    // Constructor
    GeneralTree(T rootData) {
        root = new TreeNode<T>(rootData);
    }

    // Destructor to free allocated memory
    ~GeneralTree() {
        delete root;
    }

    // Function to add a child to a node
    void addChild(TreeNode<T>* parent, T childData) {
        TreeNode<T>* child = new TreeNode<T>(childData);
        parent->children.push_back(child);
    }

    // Function to print the tree using depth-first traversal
    void printTree(TreeNode<T>* node, int depth = 0) {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";  // Indentation for better visualization
        }
        std::cout << node->data << std::endl;

        for (TreeNode<T>* child : node->children) {
            printTree(child, depth + 1);
        }
    }

    // Public function to print the entire general tree
    void printTree() {
        printTree(root);
    }
};

int main()
{
    //Definición de parametros que se usaran en el futuro.
    int gameon = 1;
    int select;
    FILE *file = fopen("guardians.conf", "r");
    if(file == NULL) {
        perror("Error opening file.");
        return 0;
    }
    
    struct Guardian nguardian[50];

    int guardcount = 0;
    //Se ingresan los guardianes dentro del struct
    while (fscanf(file, "%[^,],%d,%[^,],%[^\n]" , nguardian[guardcount].Name ,&nguardian[guardcount].PowerLevel,
    nguardian[guardcount].Master,nguardian[guardcount].City) == 4) {
        guardcount++;
        if (guardcount >= 35)
        {
            cout << "Max guardians reached." << endl;
            break;
        }            
    }
    fclose(file);

    // Crear un arbol binario vacio
    Node* root = nullptr;

    // Ingresar PowerLevel y Nombre de los guardianes al arbol binario
    root = insert(root, nguardian[0].Name, nguardian[0].PowerLevel);
    for (int i = 1; i < guardcount; i++)
    {
        insert(root, nguardian[i].Name,nguardian[i].PowerLevel);
    }

    
    //Menu y selección sobre que hacer a continuación.
    do
    {
        cout << "\nWelcome to the Rise of the guardians!\n Please select what you would like to do(Using values from 1 to 5):\n1)See the list of candidates.\n2)See the guardian.\n3)Meet the Kingdom.\n4)Watch a battle.\n5)Exit the game." << endl;
        cin >> select;
        switch (select)
        {
            case 1: //Se imprimira en la consola los guardianes que son candidatos(Tienen que tener entre 90 y 99 puntos de poder).
                cout << "The list of candidates will be shown below:";
                inorderTraversal(root);
                system("pause");
                system("cls");
                break;
            case 2:
                cout << "Showing all guardians: " << endl;
                for (int i = 0; i < guardcount; i++)
                {
                    cout << i << ") " << nguardian[i].Name << "\n";
                }

                cout << "\nSelect the guardian that you want to see more info. (Using positive numbers)";
                cin >> select;
                while(select >= guardcount || select < 0)
                {
                    cout << "That's not a valid option, try again." << endl;
                    cin >> select;
                }                
                cout << "Name: " << nguardian[select].Name << " PowerLevel: " <<nguardian[select].PowerLevel <<
                " Master: " << nguardian[select].Master << " City: " << nguardian[select].City << endl;
                system("pause");
                break;
            case 3:
                cout << "Meet the kingdom" << endl;
                break;
            case 4:
                cout << "Watch a battle." << endl;
                break;
            case 5:
                cout << "Exit the game." << endl;
                return 0;                
            default:
                break;
        }
    } while (gameon == 1);
}