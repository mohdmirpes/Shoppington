#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_PRODUCTS 100
#define MAX_HISTORY 100

// User structure
typedef struct history{
    int id;
    struct history *next;
}hist;
typedef struct {
    int userID;
    char name[100];
    hist *browsehist;
    hist *purhist;
} User;

// Product structure
typedef struct {
    int productID;
    char productName[100];
    float price;
} Product;

// Function to add a new user
void addUser(User users[], int *userCount, char *name) {
    if (*userCount < MAX_USERS) {
        users[*userCount].userID=(*userCount+1);
        strcpy(users[*userCount].name, name);
        users[*userCount].purhist = NULL;
        users[*userCount].browsehist = NULL;
        (*userCount)++;
    } else {
        printf("User limit reached!\n");
    }
}

// Function to add a new product
void addProduct(Product products[], int *productCount, char *productName, float price) {
    if (*productCount < MAX_PRODUCTS) {
        products[*productCount].productID = (*productCount)+1;
        strcpy(products[*productCount].productName, productName);
        products[*productCount].price = price;
        (*productCount)++;
    } else {
        printf("Product limit reached!\n");
    }
}

// Function to track browsing history
void trackBrowsingHistory(User *users, int productID) {
    if(users->browsehist==NULL)
    {
        hist *nn=(hist*)malloc(sizeof(hist));
        users->browsehist=nn;
        nn->id=productID;
        nn->next=NULL;
        return;
    }
    hist *temp;
    temp=users->browsehist;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    hist *nn=(hist*)malloc(sizeof(hist));
    temp->next=nn;
    nn->id=productID;
    nn->next=NULL;
}

// Function to track purchase history
void trackPurchaseHistory(User *user, int productID) {
    if(user->purhist==NULL)
    {
        hist *nn=(hist*)malloc(sizeof(hist));
        user->purhist=nn;
        nn->id=productID;
        nn->next=NULL;
        return;
    }
    hist *temp;
    temp=user->purhist;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    hist *nn=(hist*)malloc(sizeof(hist));
    temp->next=nn;
    nn->id=productID;
    nn->next=NULL;
}

int max(int arr[])
{
    int pos=0;
    int max=0;
    for(int i=0;i<MAX_PRODUCTS;i++)
    {
        if(arr[i]>max)
        {
            pos=i;
            max=arr[i];
        }
    }
    arr[pos]=0;
    return pos;
}

int isEmpty(int arr[])
{
    for(int i=0;i<MAX_PRODUCTS;i++)
    {
        if(arr[i]!=0)
        {
            return 0;
        }
    }
    return 1;
}

// Function to generate recommendations based on browsing history
void generateRecommendations(User *user, Product products[], int productCount) {
    printf("Recommendations for %s:\n", user->name);
    int rec[MAX_PRODUCTS];
    for(int i=0;i<MAX_PRODUCTS;i++)
    {
        rec[i]=0;
    }
    hist *temp1,*temp2;
    temp1=user->browsehist;
    temp2=user->purhist;
    // each time a product is browsed, its recommendation likelyhood increases by 1
    while(temp1!=NULL)
    {
        int productID = temp1->id;
        for (int j = 0; j < productCount; j++) {
            if (products[j].productID == productID) {
                rec[j]+=1;
                break;
            }
        }
        temp1=temp1->next;
    }
    // each time a product is purchased, its recommendation likelyhood increases by 1
    while(temp2!=NULL)
    {
        int productID = temp2->id;
        for (int j = 0; j < productCount; j++) {
            if (products[j].productID == productID) {
                rec[j]+=1;
                break;
            }
        }
        temp2=temp2->next;
    }
    //arranging the final recommendation list based on likelyhood
    // Arranging the final recommendation list based on likelihood
    int count = 0; // Counter to limit to 3 recommendations
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (count >= 3) { // Stop after 3 recommendations
            break;
        }
    
    int x = max(rec);
    printf("%d, %s\n", products[x].productID, products[x].productName);

    count++; // Increment the counter

    if (isEmpty(rec)) { // Break if no more recommendations are available
        break;
    }
}

}
// Function to display user data
void displayUserData(User *user) {
    printf("User ID: %d\n", user->userID);  // Corrected from %s to %d for userID
    printf("Name: %s\n", user->name);
    printf("Purchase History: ");
    
    hist *temp2 = user->purhist;
    if (temp2 == NULL) {
        printf("No purchases yet.\n");
    } else {
        while (temp2 != NULL) {
            printf("%d ", temp2->id);
            temp2 = temp2->next;
        }
    }
    printf("\n");

    printf("Browse History: ");
    hist *temp1 = user->browsehist;
    if (temp1 == NULL) {
        printf("No browsing history yet.\n");
    } else {
        while (temp1 != NULL) {
            printf("%d ", temp1->id);
            temp1 = temp1->next;
        }
    }
    printf("\n");
}


// Main function
int main() {
    // Initialize the arrays for users and products
    User users[MAX_USERS];
    Product products[MAX_PRODUCTS];
    
    int userCount = 0;
    int productCount = 0;
    int m;
    char name[50];
    int userID;
    int productID;
    while(1)
    {
        printf("enter choice:\n1.add user\n2.add product\n3.browse product\n4.purchase product\n5.display user details\n6.generate recommendations for user\n7.exit: ");
        scanf("%d",&m);
        switch(m)
        {
            case(1):
            {
                printf("enter username:");
                scanf("%s",&name);
                addUser(users,&userCount,&name);
                break;
            }
            case 2:
            {
                printf("enter product name:");
                scanf("%s",&name);
                addUser(products,&productCount,&name);
                break;
            }
            case(3):
            {
                printf("enter userID: ");
                scanf("%d",&userID);
                printf("enter productID: ");
                scanf("%d",&productID);
                trackBrowsingHistory(&(users[userID]),productID);
                break;
            }
            case(4):
            {
                printf("enter userID: ");
                scanf("%d",&userID);
                printf("enter productID: ");
                scanf("%d",&productID);
                trackPurchaseHistory(&(users[userID]),productID);
                break;
            }
            case(5):
            {
                printf("enter userID: ");
                scanf("%d",&userID);
                displayUserData(&(users[userID]));
                break;
            }
            case(6):
            {
                printf("enter userID: ");
                scanf("%d",&userID);
                generateRecommendations(&(users[userID]),products,productCount);
                break;
            }
            case(7):
            {
                exit(0);
                break;
            }
            default:
            {
                printf("incorrect input");
                exit(1);
            }
        }
    }
    return 0;
}