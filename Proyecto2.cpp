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

    //Menu y selección sobre que hacer a continuación.
    do
    {
        cout << "\nWelcome to the Rise of the guardians!\n Please select what you would like to do(Using values from 1 to 5):\n1)See the list of candidates.\n2)See the guardian.\n3)Meet the Kingdom.\n4)Watch a battle.\n5)Exit the game." << endl;
        cin >> select;
        switch (select)
        {
            case 1: //Se imprimira en la consola los guardianes que son candidatos(Tienen que tener entre 90 y 99 puntos de poder).
                cout << "The list of candidates will be shown below:";
                for (int i = 0; i < guardcount; i++)
                {
                    if(nguardian[i].PowerLevel >= 90 && nguardian[i].PowerLevel <= 99)
                    {
                        printf("%s %d" ,nguardian[i].Name , nguardian[i].PowerLevel);
                    }
                }
                cout << endl;
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