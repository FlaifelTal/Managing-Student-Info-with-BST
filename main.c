// Tala Flaifel 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXSIZE 100
char buf[512]; // used in trim function


// Information
typedef struct studentInfo
{

    int ID;
    char studentName[MAXSIZE];
    char homeAddress[MAXSIZE];
    char classId[MAXSIZE];
    char enrollment[MAXSIZE];

} info;
// tree node
struct Node
{
    info *data;
    struct Node *left;
    struct Node *right;
};
struct Node *root = NULL;
// create tree
struct Node *createNode(info *data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insert fun
struct Node *insert(struct Node *root, info *data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data->ID < root->data->ID)
    {
        root->left = insert(root->left, data);
    }
    else if (data->ID > root->data->ID)
    {
        root->right = insert(root->right, data);
    }

    return root;
}
// find if exists
struct Node *search(struct Node *root, int id)
{
    if (root == NULL || root->data->ID == id)
    {
        return root;
    }

    if (root->data->ID < id)
    {
        return search(root->right, id);
    }

    return search(root->left, id);
}

// insert fun by user
void insertNodeByUser() // insert a new node by user command
{

    printf("Insert The course information\n");
    info *data = (info *)malloc(sizeof(info));

    printf("Enter student ID: ");
    scanf("%d", &data->ID);
    printf("\n");

    // Check if the entered ID already exists
    if (search(root, data->ID) != NULL)
    {
        printf("ID already exists. Please enter a different ID.\n");
        free(data); // Free the memory allocated for 'data'
        return;     // Return without inserting the node
    }

    printf("Enter Student name: ");
    scanf("%s", data->studentName);
    printf("\n");

    printf("Enter Home address : ");
    scanf("%s", data->homeAddress);
    printf("\n");

    printf("Enter the course ID: ");
    scanf("%s", data->classId);
    printf("\n");

    printf("Enter the data of enrollment : ");
    scanf("%s", data->enrollment);
    printf("\n");

    root = insert(root, data);
}
// in-order print to see the elements
void PrintInOrder(struct Node *root)
{
    if (root != NULL)
    {
        // printf("Student ID\tStudent Name\tHome Address\tClass ID\tEnrollment Date\n");

        PrintInOrder(root->left);
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n", root->data->ID, root->data->studentName, root->data->homeAddress, root->data->classId, root->data->enrollment);
        PrintInOrder(root->right);
    }
}
// Function to search for a node with a specific ID
struct Node *findNode(struct Node *root, int id)
{
    if (root == NULL || root->data->ID == id)
    {
        return root;
    }

    if (root->data->ID < id)
        return findNode(root->right, id);

    return findNode(root->left, id);
}

// function to find the minimum value in a node
struct Node *find_minimum(struct Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
// update node by user command based on id
void updateNode(struct Node *node)
{
    int choice;

    info *newData = (info *)malloc(sizeof(info));
    if (node != NULL)
    {
        char ans[5];

        printf("DO you want to update student information?");
        scanf("%s", ans);
        if (stricmp(ans, "yes") == 0)
        {
            do
            {
                int choice;
                char x[MAXSIZE];
                printf("Which field do you want to update?\n");
                printf("1. ID\n");
                printf("2. Student name\n");
                printf("3. Home address\n");
                printf("4. Class ID\n");
                printf("5. Enrollment\n");
                printf("6. EXIT\n");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    int idd;
                    printf("Enter student ID: ");
                    scanf("%d", &(node->data->ID));
                    break;
                case 2:
                    printf("Enter Student name: ");
                    scanf("%s", x);
                    strcpy(node->data->studentName, x);
                    break;
                case 3:
                    printf("Enter Home address: ");
                    scanf("%s", x);
                    strcpy(node->data->homeAddress, x);

                    break;
                case 4:
                    printf("Enter the course ID: ");
                    scanf("%s", x);
                    strcpy(node->data->classId, x);

                    break;
                case 5:
                    printf("Enter the data of enrollment: ");
                    scanf("%s", x);
                    strcpy(node->data->enrollment, x);

                    break;
                case 6:
                    printf("Exiting.\n");
                    return;
                default:
                    printf("Invalid choice.\n");
                    return;
                }
            } while (choice != 6);
        }
    }
}
// delete node by user command based on id
struct Node *deleteNode(struct Node *root, int id)
{
    if (root == NULL)
        return root;

    if (id < root->data->ID)
        root->left = deleteNode(root->left, id);
    else if (id > root->data->ID)
        root->right = deleteNode(root->right, id);
    else
    {
        // Node to be deleted is found
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            // Node has two children
            struct Node *successor = find_minimum(root->right);
            root->data = successor->data;
            root->right = deleteNode(root->right, successor->data->ID);
        }
    }

    return root;
}
// remove spaces
void trim(char str[])
{
    strcpy(buf, str);
    int i, start = 0, end = strlen(buf);
    for (i = 0; i < end; i++)
    {
        if (buf[i] == ' ')
            start = i + 1;
        else
            break;
    }
    for (i = strlen(buf) - 1; i >= 0; i--)
    {
        if (buf[i] == ' ')
            end = i;
        else
            break;
    }
    for (i = 0; start < end; start++, i++)
    {
        str[i] = buf[start];
    }
    str[i] = '\0';
}

void trimAndRemoveNewLine(char str[])
{
    // remove new line from the value
    int strSize = strlen(str);
    if (strSize > 0 && str[strSize - 1] == '\n')
    {
        if (strSize > 1 && str[strSize - 2] == '\r') // check if there is \r\n
            str[strSize - 2] = '\0';
        else
            str[strSize - 1] = '\0';
    }
    trim(str);
}

void readFile() // read the given file and insert into BST tree
{

    char str[MAXSIZE];
    if (access("student.data", F_OK) != 0)
    {
        printf("File doesn't exist. No data to read.\n");
        return;
    }
    FILE *myfile;
    myfile = fopen("student.data", "r");
    if (myfile == NULL)
    {
        printf("Error opening file");
    }

    while (!feof(myfile))
    {
        info *node = (info *)malloc(sizeof(info));
        fgets(str, MAXSIZE, myfile);
        trimAndRemoveNewLine(str);

        // split each line on null then populate the arrays, use a variable to track the arrays index
        // atoi is used to convert string (char array) to integer

        char *token = strtok(str, ","); // Student ID
        node->ID = atoi(token);
        token = strtok(NULL, ","); // Student name
        strcpy(node->studentName, token);
        trim(node->studentName);

        token = strtok(NULL, ","); // Home address
        strcpy(node->homeAddress, token);
        trim(node->homeAddress);

        token = strtok(NULL, ","); // class ID
        strcpy(node->classId, token);
        trim(node->classId);
        token = strtok(NULL, "NULL"); // Enrollment date
        strcpy(node->enrollment, token);
        trim(node->enrollment);
        trimAndRemoveNewLine(node->enrollment);

        root = insert(root, node);
    }

    fclose(myfile);
}
// count the number of nodes in tree
int countNodes(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}
// helper function for sort names to cope the nodes in an array to compared in lexicographical order
void copyNodesToArray(struct Node *node, info **data, int *index)
{
    if (node == NULL)
        return;

    copyNodesToArray(node->left, data, index);
    data[*index] = node->data;
    (*index)++;
    copyNodesToArray(node->right, data, index);
}
// dort names based on lexicographical orderof names
void sortNames(struct Node *root)
{
    int n = countNodes(root);
    info **data = malloc(n * sizeof(info *));
    int index = 0;
    copyNodesToArray(root, data, &index);

    // Sort the names using bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(data[j]->studentName, data[j + 1]->studentName) > 0)
            {
                // Swap the pointers if names are not in lexicographical order
                info *tempPtr = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tempPtr;
            }
        }
    }

    // Print the sorted student information
    // printf("Student names in lexicographical order:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%s\t%s\t%s\t%s\n", data[i]->ID, data[i]->studentName, data[i]->homeAddress, data[i]->classId, data[i]->enrollment);
    }

    // Free memory
    free(data);
}

// Function to sort and print student information in lexicographical order
void sortnames(info **data, int n)
{
    // Sort the names using bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(data[j]->studentName, data[j + 1]->studentName) > 0)
            {
                // Swap the pointers if names are not in lexicographical order
                info *tempPtr = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tempPtr;
            }
        }
    }

    // Print the sorted student information
    printf("Student names in lexicographical order:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%s\t%s\t%s\t%s\n", data[i]->ID, data[i]->studentName, data[i]->homeAddress, data[i]->classId, data[i]->enrollment);
    }
}

// Helper function to collect nodes with a specific city into an array
void collectNodesByCity(struct Node *root, info **data, int *index, const char *city)
{
    if (root == NULL)
        return;

    collectNodesByCity(root->left, data, index, city);

    if (strcmp(root->data->homeAddress, city) == 0)
        data[(*index)++] = root->data;

    collectNodesByCity(root->right, data, index, city);
}

// Function to search for nodes with a specific city, sort the matching nodes, and print the student information in lexicographical order
void findAndSortByCity(struct Node *root, const char *city)
{
    if (root == NULL)
        return;

    info **data = malloc(countNodes(root) * sizeof(info *));
    int index = 0;
    collectNodesByCity(root, data, &index, city);

    if (index == 0)
    {
        printf("city was not found.\n");
        free(data);
        return;
    }
    sortnames(data, index);

    free(data);
}

// Helper function to collect nodes with a specific Class into an array
void collectNodesByClass(struct Node *root, info **data, int *index, const char *class)
{
    if (root == NULL)
        return;

    collectNodesByClass(root->left, data, index, class);

    if (strcmp(root->data->classId, class) == 0)
        data[(*index)++] = root->data;

    collectNodesByClass(root->right, data, index, class);
}

// Function to search for nodes with a specific Class, sort the matching nodes, and print the student information in lexicographical order
void findAndSortByClass(struct Node *root, const char *class)
{
    if (root == NULL)
        return;

    info **data = malloc(countNodes(root) * sizeof(info *));
    int index = 0;
    collectNodesByClass(root, data, &index, class);
    if (index == 0)
    {
        printf("Class was not found.\n");
        free(data);
        return;
    }
    sortnames(data, index);

    free(data);
}

void collectodesByClass(struct Node *root, info **data, int *index,
                        const char *class)
{
    if (root == NULL)
    {
        return;
    }

    collectodesByClass(root->left, data, index, class);

    if (strcmp(root->data->classId, class) == 0)
    {
        info *newNode = malloc(sizeof(info));
        memcpy(newNode, root->data, sizeof(info));
        data[(*index)++] = newNode;
    }

    collectodesByClass(root->right, data, index, class);
}
void collectUniqueClasses(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    // Collect unique classes from the left subtree
    collectUniqueClasses(root->left);

    // Check if the class already exists in the left subtree
    bool exists = false;
    struct Node *current = root->left;
    while (current != NULL)
    {
        if (strcmp(root->data->classId, current->data->classId) == 0)
        {
            exists = true;
            break;
        }
        current = current->right;
    }

    // If the class doesn't exist in the left subtree, print the class and sort the associated student names
    if (!exists)
    {
        printf("Class: %s\n", root->data->classId);

        // Collect all students with the current class
        info **data = malloc(sizeof(info *) * 100); // Assuming a maximum of 100 students per class
        int index = 0;
        collectodesByClass(root, data, &index, root->data->classId);

        // Sort and print student names
        sortnames(data, index);

        // Cleanup memory
        for (int i = 0; i < index; i++)
        {
            free(data[i]);
        }
        free(data);
    }

    // Collect unique classes from the right subtree
    collectUniqueClasses(root->right);
}

// // Function to print all classes and sort them by name
// void printClassesSortedByName(struct Node *root)
// {
//     if (root == NULL)
//         return;

//     int numClasses = countNodes(root);
//     char **classes = malloc(numClasses * sizeof(char *));
//     int index = 0;

//     collectUniqueClasses(root, classes, &index);
//     if (index == 0)
//     {
//         printf("No classes found.\n");
//         free(classes);
//         return;
//     }

//     sortnames(classes, numClasses);

//     printf("Classes sorted by name:\n");
//     for (int i = 0; i < numClasses; i++)
//     {
//         printf("%s\n", classes[i]);
//     }

//     free(classes);
// }

// main menu
void menu()
{
    printf("1.Insert a student with	all	its	associated	data.\n");
    printf("2.Find a student by	his/her student	ID,	and	support	updating	of	the	student	info	if	found.\n");
    printf("3.List all students in lexicographic order of their	names.\n");
    printf("4.Search for a city	and	list all students from that	city in	lexicographic order	of their names.\n");
    printf("5.List all students by their class in lexicographic order of their names\n");
    printf("6.Delete a student given his/her student ID.\n");
    printf("7.Save all students	in file	students.data.\n");
    printf("8.Exit\n");
}
// Helper function to save a single node's data to the file
void saveNodeToFile(FILE *file, struct Node *node)
{
    if (node == NULL)
        return;

    // Format the node's data as a comma-separated string
    char nodeData[500]; // Adjust the size as per data requirements
    snprintf(nodeData, sizeof(nodeData), "%d,%s,%s,%s,%s\n",
             node->data->ID, node->data->studentName, node->data->homeAddress,
             node->data->classId, node->data->enrollment);

    // Write the formatted data to the file
    fprintf(file, "%s", nodeData);

    // Recursively save the left and right subtrees
    saveNodeToFile(file, node->left);
    saveNodeToFile(file, node->right);
}

// Function to save the entire BST to a file
void saveBSTToFile(struct Node *root)
{
    // Open the file for writing
    FILE *file = fopen("student.data", "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    // Save the BST to the file using in-order traversal
    saveNodeToFile(file, root);

    // Close the file
    fclose(file);
}

int main()
{
    int x = -1;
    char id[MAXSIZE];
    readFile(); // read data from file automatically

    do
    {
        menu();
        printf("Please enter your operation:\n");
        scanf("%d", &x);

        switch (x)
        {
        case 1: // Insert a student with	all	its	associated	data
            insertNodeByUser();
            PrintInOrder(root);
            break;
        case 2: // find student and update data based on id
            printf("Enter Student ID: ");
            scanf("%s", id);
            struct Node *foundNode = findNode(root, atoi(id));
            if (foundNode != NULL)
            {
                printf("Student found:\n");
                printf("Student ID\tStudent Name\tHome Address\tClass ID\tEnrollment Data\n");

                printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n", foundNode->data->ID, foundNode->data->studentName, foundNode->data->homeAddress, foundNode->data->classId, foundNode->data->enrollment);
                updateNode(foundNode);
            }
            else
            {
                printf("Student not found.\n");
            }

            break;
        case 3: // sort data based on lexicographic order of their	names
            printf("Student ID\tStudent Name\tHome Address\tClass ID\tEnrollment Data\n");
            sortNames(root);
            break;
        case 4: // lexicographic order of names based on city
            const char f[MAXSIZE];
            printf("Enter Home Address: ");
            scanf("%s", f);
            findAndSortByCity(root, f);

            break;
        case 5: // lexicographic order of names based on class id
            int c;
            printf("1- Specific class. \n2- All classes.");
            scanf("%d", &c);
            if (c == 1)
            {
                printf("Enter Class ID: ");
                scanf("%s", f);
                findAndSortByClass(root, f);
            }
            else if (c == 2)
            {

                collectUniqueClasses(root);
            }
            break;
        case 6: // delete node by student id
            printf("Enter Student ID: ");
            scanf("%s", id);
            foundNode = findNode(root, atoi(id));
            if (foundNode != NULL)
            {
                root = deleteNode(root, atoi(id));
                printf("Node with ID %s is deleted.\n", id);
            }
            else
            {
                printf("Node with ID %s not found.\n", id);
            }

            break;
        case 7: // save data on fine
            saveBSTToFile(root);
            break;
        case 8:
            printf("Exiting Program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (x != 8);

    return 0;
}