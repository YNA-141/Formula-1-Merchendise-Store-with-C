#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#define MAX_ITEMS 100

struct Accounts{
    char name[50];
    char email[65];
    char pass[100];
    int birthyear;
};
typedef struct Accounts login;

struct item{
    int id;
    char item[100];
    char colour[50];
    char details[500];
    int stock;
    float price;
};
typedef struct item shopitems;


int loadItems(shopitems list[])
{
FILE *fp= fopen("shopitems.txt", "r");
int count= 0;


    while(fscanf(fp, "%d\n", &list[count].id) != EOF)
    {

        fscanf(fp, "%s\n", &list[count].item);
        fscanf(fp, "%s\n", &list[count].colour);
        fscanf(fp, "%s\n", &list[count].details);
        fscanf(fp, "%d\n", &list[count].stock);
        fscanf(fp, "%f\n", &list[count].price);
        count++;
        if(count>=MAX_ITEMS)
        {
            break;
        }
    }
fclose(fp);


return count;
}

void save(shopitems list[], int count)
{
FILE *fp= fopen("shopitems.txt", "w");
    for(int i= 0; i<count; i++)
        {
            fprintf(fp, "%d\n", list[i].id);
            fprintf(fp, "%s\n", list[i].item);
            fprintf(fp, "%s\n", list[i].colour);
            fprintf(fp, "%s\n", list[i].details);
            fprintf(fp, "%d\n", list[i].stock);
            fprintf(fp, "%.2f\n", list[i].price);

        }
fclose(fp);
}


void viewITEMS(void)
{
shopitems list[MAX_ITEMS];
int count= loadItems(list);

    printf("\n---Current Inventory has %d Items---\n", count);
    printf("%-5s %-20s %-10s %-10s %-8s\n", "ID", "Name", "Color", "Stock", "Price");
    printf("____________________________________________________________\n");

    for(int i=0; i<count; i++)
        {
            printf("%-5d %-20s %-10s %-10d Tk.%-8.2f \n", list[i].id, list[i].item, list[i].colour, list[i].stock, list[i].price);
        }
    printf("____________________________________________________________\n");
}

void addITEM(void)
{
shopitems list[MAX_ITEMS];
int count= loadItems(list);

    if(count>=MAX_ITEMS)
        {
            printf("!!Inventory is full!!\n");
            return;
        }

shopitems newItem;

    printf("\n---Add New Item---\n");
    printf("Enter Item ID: ");
    scanf("%d", &newItem.id);
    getchar();


    for(int i=0; i<count; i++)
        {
            if(list[i].id == newItem.id)
            {
                printf("Error! Pick a different ID :(\n");
                return;
            }
        }

    printf("\nEnter Item Name: ");
    scanf("%s", &newItem.item);

    printf("\nEnter Colour: ");
    scanf("%s", &newItem.colour);

    printf("\nEnter Details: ");
    scanf("%s", &newItem.details);

    printf("\nEnter Stock: ");
    scanf("%d", &newItem.stock);

    printf("\nEnter Price: ");
    scanf("%f", &newItem.price);

    list[count] = newItem;
    count++;

    save(list, count);
    printf("!!Item added successfully!!\n");
}

void editITEM(void)
{
shopitems list[MAX_ITEMS];
int count= loadItems(list);
int id, flag= -1;

    viewITEMS();
    printf("\nEnter ID of item to edit: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++)
    {
        if(list[i].id == id)
        {
            flag= i;
            break;
        }
    }

    if(flag != -1)
    {
        printf("Editing Item %s-\n", list[flag].item);
        printf("New Stock: ");
        scanf("%d", &list[flag].stock);
        printf("New Price: ");
        scanf("%f", &list[flag].price);

        save(list, count);
        printf("!!Item updated successfully!!\n");
    }
    else
        {
            printf("Item ID not found :(\n");
        }
}


void deleteITEM(void)
{
shopitems list[MAX_ITEMS];
int count=loadItems(list);
int id, flag= -1;

    viewITEMS();
    printf("\nEnter ID of item to DELETE: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++)
    {
        if(list[i].id == id)
        {
            flag= i;
            break;
        }
    }

    if(flag !=-1)
        {

            for(int i= flag; i<(count-1); i++)
            {
                list[i]= list[i+1];
            }
            count--;
            save(list, count);
            printf("!!Item deleted successfully!! :))\n");
        }
    else
        {
            printf("Item ID not found.\n");
        }
}

void viewBilledCustomers(void) {
FILE *fp= fopen("billedCustomers.txt", "r");
int c;

    printf("\n---Billed Customer History---\n");
    if (fp == NULL)
        {
            printf("No sales history found.\n");
            return;
        }
    while((c=fgetc(fp))!= EOF)
    {
        printf("%c", c);
    }
fclose(fp);
}

void sellerlogin(void)
{
char sellerMAIL[65], sellerPASS[100];
login temp;
FILE *sellerID;
int loggedIn= 0;

    while(loggedIn==0)
        {
            sellerID= fopen("sellerID.dat", "rb");


            printf("\n---Seller Login---\n");
            printf("Enter Email: ");
            scanf("%s", &sellerMAIL);
            printf("Enter Password: ");
            scanf("%s", &sellerPASS);

            int flag= 0;
            while(fread(&temp, sizeof(login), 1, sellerID))
                {
                    if (strcmp(sellerMAIL, temp.email) == 0 && strcmp(sellerPASS, temp.pass) == 0)
                    {
                        flag=1;
                        break;
                    }
                }
            fclose(sellerID);

            if(flag==1)
            {
                printf("\nWelcome Boss <3\n");
                loggedIn= 1;
                int n= -1;
                while(n!= 0)
                {
                    printf("\n---Seller Dashboard---\n");
                    printf("1. View Items\n");
                    printf("2. Add Item\n");
                    printf("3. Edit Item\n");
                    printf("4. Delete Item\n");
                    printf("5. View Sales History\n");
                    printf("0. Logout\n");
                    printf("Enter Your Choice Boss ;): ");
                    scanf("%d", &n);
                    if(n ==1)
                    {
                        viewITEMS();
                    }
                    else if(n == 2)
                    {
                        addITEM();
                    }
                    else if(n== 3)
                    {
                        editITEM();
                    }
                    else if(n==4)
                    {
                        deleteITEM();
                    }
                    else if(n==5)
                    {
                        viewBilledCustomers();
                    }
                }
            }
            else
                {
                    printf("\nInvalid Email or Password! You are not my BOSS! I miss my Boss T^T\n");
                    return;
                }
        }
}


void billDetail(shopitems item, int qty, char *custName)
{
float total= item.price * qty;
float discount= 0.05;

    if(qty>5)
        {
            discount = 0.15;
        }

float discountAmt= total*discount;
float finalAmt= total-discountAmt;

    printf("\n---INVOICE---\n");
    printf("Customer: %s\n", custName);
    printf("Item: %s (%s)\n", item.item, item.colour);
    printf("Quantity: %d\n", qty);
    printf("Price Per Unit: $%.2f\n", item.price);
    printf("Total: Tk.%.2f\n", total);
    printf("Discount (%.2f%%): -Tk.%.2f\n", discount*100, discountAmt);
    printf("Grand Total: Tk.%.2f\n", finalAmt);

FILE *fp= fopen("billedCustomers.txt", "a");
    fprintf(fp, "Customer: %s  Item: %s  Qty: %d  Paid: $%.2f\n", custName, item.item, qty, finalAmt);

fclose(fp);

shopitems list[MAX_ITEMS];
int count= loadItems(list);

    for(int i=0; i<count; i++)
    {
        if(list[i].id == item.id)
        {
            list[i].stock =list[i].stock-qty;
            break;
        }
    }

save(list, count);
}

void cart(char *custName)
{
int id, qty;
shopitems list[MAX_ITEMS];
int count= loadItems(list);
int flag2= -1;

    printf("\nEnter Item ID to buy: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++)
    {
        if(list[i].id == id)
        {
            flag2= i;
            break;
        }
    }

    if(flag2 != -1)
        {
        printf("Selected: %s (Stock: %d)\n", list[flag2].item, list[flag2].stock);
        printf("Enter Quantity: ");
        scanf("%d", &qty);

        if(qty<=list[flag2].stock && qty>0)
            {
                billDetail(list[flag2], qty, custName);
            }
        else
            {
                printf("Error! Insufficient stock Sowwy :( \n");
            }
        }
    else
        {
            printf("Item ID not found\n");
        }
}


void search(char *custName) {
shopitems list[MAX_ITEMS];
int count= loadItems(list);
char khoj[50];

    printf("Search for an Item: ");
    scanf("%s", &khoj);

    printf("\nSearch Results:\n");
    int flag= 0;
    for(int i=0; i<count; i++) {

        if(strstr(list[i].item, khoj) != NULL)
        {
            printf("ID: %d | %s | %s | Tk.%.2f | Stock: %d\n", list[i].id, list[i].item, list[i].colour, list[i].price, list[i].stock);
            flag= 1;
        }
    }
    if(flag==0)
    {
        printf("No items found\n");
    }

    printf("\n1. Buy Item\n");
    printf("\n0. Back");
    printf("\nEnter Your Choice: ");
int choice;

    scanf("%d", &choice);
    if(choice == 1)
    {
        cart(custName);
    }
}

void sorting(int mode, char *custName)
{
    shopitems list[MAX_ITEMS];
    int count= loadItems(list);
    shopitems temp;

    for(int i= 0; i < count-1; i++)
        {
            for(int j= 0; j < count-(i+1); j++)
                {

                if(mode == 1)
                    {
                        if(list[j].price < list[j+1].price)
                            {
                                temp = list[j];
                                list[j] = list[j+1];
                                list[j+1] = temp;
                            }
                    }

                else
                    {
                        if(list[j].price > list[j+1].price)
                            {
                                temp = list[j];
                                list[j] = list[j+1];
                                list[j+1] = temp;
                            }
                    }
            }
    }

    printf("\n---Items Sorted by Price---\n");

    for(int i=0; i<count; i++)
        {
            printf("ID: %d | %s | Tk.%.2f\n", list[i].id, list[i].item, list[i].price);
        }

    printf("\n1. Buy an Item");
    printf("\n0. Back");
    printf("\nEnter Your Choice: ");

int choice;

    scanf("%d", &choice);
    if(choice== 1)
    {
        cart(custName);
    }
}

void createacc()
{
FILE *fp= fopen("customerID.dat", "ab");
login newCust;

    printf("\n---Create Account---\n");
    printf("Name: ");
    scanf("%s", &newCust.name);
    printf("Email: ");
    scanf("%s", &newCust.email);
    printf("Password: ");
    scanf("%s", &newCust.pass);
    printf("Birth Year: ");
    scanf("%d", &newCust.birthyear);

    fwrite(&newCust, sizeof(login), 1, fp);
    fclose(fp);
    printf("Account created! Please login\n");
}

void customerlogin(void)
{
char customerMAIL[65], customerPASS[100];
login temp;
FILE *customerID;
int choice;

    printf("\n1. Login");
    printf("\n2. Create New Account");
    printf("\nEnter Your Choice: ");
    scanf("%d", &choice);

    if(choice== 2)
        {
            createacc();
            return;
        }

    customerID= fopen("customerID.dat", "rb");
    if(customerID==NULL)
        {
            printf("No customers found, register first\n");
            return;
        }

    printf("\n---Customer Login---\n");
    printf("Enter Email: ");
    scanf("%s", &customerMAIL);
    printf("Enter Password: ");
    scanf("%s", &customerPASS);

int flag= -1;
    while(fread(&temp, sizeof(login), 1, customerID))    //
        {
            if(strcmp(customerMAIL, temp.email) == 0 && strcmp(customerPASS, temp.pass) == 0)
            {
                flag= 1;
                break;
            }
        }
fclose(customerID);

    if(flag==1)
        {
            printf("\nWelcome %s!\n", temp.name);
            int n2= -1;
            while(n2!= 0)
                {
                    printf("\n---Shop Menu---\n");
                    printf("1. View All Items");
                    printf("\n2. Search Item");
                    printf("\n3. Sort High to Low");
                    printf("\n4. Sort Low to High");
                    printf("\n0. Logout");
                    printf("\nEnter: ");
                    scanf("%d", &n2);

                    if(n2== 1)
                        {
                            viewITEMS();
                            cart(temp.name);
                        }
                    else if(n2 == 2)
                        {
                            search(temp.name);
                        }
                    else if(n2 == 3)
                        {
                            sorting(1, temp.name);
                        }
                    else if(n2 == 4)
                        {
                            sorting(0, temp.name);
                        }
                }
        }
    else
        {
            printf("Login Error\n");
        }
}

int main() {
    int n = -1;

    do
        {
            printf("\n---Formula-1 Merchandise Store---\n");
            printf("1. Seller Login\n");
            printf("2. Customer Login\n");
            printf("0. Exit\n");
            printf("Choice: ");
            scanf("%d", &n);

            switch(n)
                {
                    case 1: sellerlogin();
                            break;
                    case 2: customerlogin();
                            break;
                    case 0: printf("Exiting...\n");
                            break;
                    default: printf("You dumb bro? Invalid choice!\n");
                }
        }
    while(n!= 0);

    return 0;
}

