#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Guardian{   //Definición de guardian y sus caracteristicas, como nombre, NivelDePoder, ciudad, maestro y aprendices.
string Name;
int PowerLevel;
string City;
string Master;
string Apprentice[8];
};

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
};
Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
       root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

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
    
    //Menu y selección sobre que hacer a continuación.
    do
    {
        cout << "Welcome to the Rise of the guardians!\n Please select what you would like to do(Using values from 1 to 5):\n1)See the list of candidates.\n2)See the guardian.\n3)Meet the Kingdom.\n4)Watch a battle.\n5)Exit the game." << endl;
        cin >> select;
        switch (select)
        {
            case 1: //Se imprimira en la consola los guardianes que son candidatos.
                cout << "The list of candidates will be shown below:" << endl;

                break;
            case 2:
                cout << "See the guardian." << endl;
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