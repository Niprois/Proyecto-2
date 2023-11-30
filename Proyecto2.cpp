#include <iostream>
#include <vector>
#include <string.h>
#include <ctime>
#include <windows.h>

using namespace std;

struct Guardian{   //Definición de guardian y sus caracteristicas, como nombre, NivelDePoder, ciudad, maestro y aprendices.
    char Name[20];
    int PowerLevel;
    char Master[20];
    char City[20];
    int type; // 3=GM | 2=GR | 1=GC | 0=NONE
    int ID;
    string Apprentice[100];
};
struct Node { //Nodo para el arbol binario
    string ByName;    
    int data;
    int dataT;
    Node* left;
    Node* right;

    // Constructor
    Node(string strValue, int value, int valuet) : ByName(strValue), data(value), dataT(valuet), left(nullptr), right(nullptr) {}
};
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}


// Funcion para ingresar un nuevo nodo al arbol binario
Node* insert(Node* root, string strValue,int value,int valueT) {
    // Si el arbol esta vacio, añade un nuevo nodo y lo convierte en raiz
    if (root == nullptr) {
        return new Node(strValue, value, valueT);
    }

    // Si no es asi, recorre el arbol.
    if (value < root->data) {
        root->left = insert(root->left, strValue,value,valueT);
    } else if (value > root->data) {
        root->right = insert(root->right, strValue, value,valueT);
    }

    return root;
}

void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        if (root->data >= 90 && root->data < 100 && root->dataT == 1) {
            cout <<  root->ByName  << " " << root->data;
        }
        inorderTraversal(root->right);
    }
}

int main()
{
    //Definición de parametros que se usaran en el futuro.
    srand(static_cast<unsigned int>(time(nullptr)));
    int valuetodelete;
    int gameon = 1;
    int randomNumber;
    int candidatecount = 0;
    int select;
    int guard1 = 0;
    int guard2 = 0;
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
        nguardian[guardcount].ID = guardcount;
        if(nguardian[guardcount].PowerLevel >= 90 && nguardian[guardcount].PowerLevel < 100)
        {
            nguardian[guardcount].type = 2;
        }
        if(nguardian[guardcount].PowerLevel == 100)
        {
            nguardian[guardcount].type = 3;
        }
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
    root = insert(root, nguardian[0].Name, nguardian[0].PowerLevel ,nguardian[0].type);
    for (int i = 1; i < guardcount; i++)
    {
        insert(root, nguardian[i].Name,nguardian[i].PowerLevel,nguardian[i].type);
    }
    
    //Menu y selección sobre que hacer a continuación.
    do
    {
        cout << "\nWelcome to the Rise of the guardians!\n Please select what you would like to do(Using values from 1 to 5):\n1)See the list of candidates.\n2)See the guardian.\n3)Meet the Kingdom(Not implemented).\n4)Watch a battle.\n5)Exit the game." << endl;
        cin >> select;
        switch (select)
        {
            case 1: //Se imprimira en la consola los guardianes que son candidatos(Tienen que tener entre 90 y 99 puntos de poder).
                cout << "The list of candidates will be shown below:";
                inorderTraversal(root);
                system("pause");
                break;
            case 2://Permite ver la información detallada de los guardianes que usted desee.
                cout << "Showing all guardians: " << endl;
                for (int i = 0; i < guardcount; i++)
                {
                    cout << i << ") " << nguardian[i].Name << "\n";
                }                
                cout << "\nSelect the guardian that you want to see more info. (Using positive numbers)";                
                cin >> select;
                cout << "Name: " << nguardian[select].Name << " PowerLevel: " <<nguardian[select].PowerLevel <<
                " Master: " << nguardian[select].Master << " City: " << nguardian[select].City  <<  endl;
                system("pause");
                break;
            case 3:
                cout << "Meet the kingdom (Not implemented.)" << endl;
                break;
            case 4:
                cout << "Watch a battle." << endl;
                cout << "Select your guardian: ";
                for (int i = 0; i < guardcount; i++)
                {
                    if (nguardian[i].type == 0)
                    {
                        cout << i << ") " << nguardian[i].Name << "\n";
                    }
                }
                cin >> guard1;

                cout << "Select your opponent: ";
                for (int i = 0; i < guardcount; i++)
                {
                    cout << i << ") " << nguardian[i].Name << "\n";
                }
                
                cin >> guard2;
                cout << "The guardian " << nguardian[guard1].Name << " will fight against " << nguardian[guard2].Name << endl;
                randomNumber = rand() % 6 + 1;
                //Dependiendo de quien gane, se le suma o quita puntos.
                if (randomNumber >= 5 && randomNumber <= 6)
                { 
                    cout << nguardian[guard1].Name << " wins the battle!" << endl; 
                    valuetodelete = nguardian[guard1].PowerLevel;
                    root = deleteNode(root, valuetodelete);
                    nguardian[guard1].PowerLevel += 3;
                    insert (root, nguardian[guard1].Name, nguardian[guard1].PowerLevel, nguardian[guard1].type);
                    valuetodelete = nguardian[guard2].PowerLevel;
                    root = deleteNode(root, valuetodelete);
                    nguardian[guard2].PowerLevel -= 1;
                    insert (root, nguardian[guard2].Name, nguardian[guard2].PowerLevel, nguardian[guard2].type);                    
                }
                else
                {
                    cout << nguardian[guard2].Name << " wins the battle!" << endl;
                    valuetodelete = nguardian[guard2].PowerLevel;
                    root = deleteNode(root, valuetodelete);
                    nguardian[guard2].PowerLevel += 3;
                    if(nguardian[guard2].PowerLevel >= 90 && nguardian[guard2].PowerLevel <= 99)
                    {
                        nguardian[guard2].type = 1;
                    }
                    insert (root, nguardian[guard2].Name, nguardian[guard2].PowerLevel, nguardian[guard2].type);
                    valuetodelete = nguardian[guard1].PowerLevel;
                    root = deleteNode(root, valuetodelete);
                    nguardian[guard1].PowerLevel -= 1;
                    insert (root, nguardian[guard1].Name, nguardian[guard1].PowerLevel, nguardian[guard1].type);  
                }
                cout << "Updating the ranking..." << endl;
                system("pause");
                break;
            //Salir del juego
            case 5:
                cout << "Exit the game." << endl;
                return 0;                
            default:
                break;
        }
    } while (gameon == 1);
}