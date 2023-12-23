// Final Project
// Members:
// 65070503402 Korawit Sritotum
// 65070503406 Gunn Wangwichit
// 65070503439 Sikares Nuntipatsakul
// 65070503464 Ratchanon Tarawan
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Hilly.h"

// Inventory System
typedef struct product1
{
    char product_name[50];
    int product_quantity;
    float product_cost;
    float product_price;
    int product_minimum;
} Inventory;
// Accounting struct product
typedef struct product2
{
    char product_name[50];
    int product_quantity;
    double product_price;
    float product_cost;
    float product_profit;
    char product_time_stamp[50];
    char timestamp_keep[100];
    unsigned long long timestamp_sec_keep;
} Accounting;
typedef struct product3
{
    char product_name[50];
    int product_quantity;
    float product_amount;
    float product_price;
    char product_timestamp[100];
    unsigned long long product_timestamp_sec;
    float product_profit;
} Showing;
typedef struct user
{
    char username[50];
    char password[50];
} User;

int item[1000];
int count;
int menu_inventory();
int menu_accounting();
int menu_Pos();
int login();
const char *count_item = "C %d";
const char *save_record = "Item name : %s | Quality : %d | Cost : %.2f | Price : %.2f\n";
const char *import_record = "Item name : %s | Quality : %d | Cost : %f | Price : %f\n";

int main()
{
    FILE *file_inventory;
    FILE *file_inventory_backup;
    FILE *file_accounting;
    FILE *file_accounting_backup;
    FILE *file_pos;
    FILE *file_pos2;
    FILE *file_pos_backup;
    FILE *file_timestamp;
    FILE *file_timestamp_backup;
    FILE *file_user;

    file_inventory = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Inventory.txt", "r+");
    file_accounting = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Accounting.txt", "r+");
    file_pos = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS.txt", "a+");
    file_pos2 = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS2.txt", "a+");
    file_timestamp = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestamp.txt", "r+");
    file_pos_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoSbackup.txt", "w+");
    file_inventory_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Inventorybackup.txt", "w+");
    file_accounting_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Accountingbackup.txt", "w+");
    file_timestamp_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestampbackup.txt", "w+");
    file_user = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Username.txt", "r+");

    int input, count_user = 0, register_user = 0, select_login = 0;
    Inventory iny[1000];
    Accounting acc[1000];
    Showing acc1[1000];
    User list[1000];
    char username[100], password[100];
    for (int i = 0; i < 1000; i++)
    {
        fscanf(file_user, "Username : %s Password : %s\n", &list[i].username, &list[i].password);
        if ((int)list[i].username[0] < 65)
        {
            count_user = i;
            break;
        }
    }
    while (register_user == 0)
    {
        system("clear");
        printf("--------------------------------------\n");
        printf("|\t     \U0001F510 Login Page\t     |\n");
        printf("--------------------------------------");
        printf("\nUsername : ");
        scanf("%s", &username);
        printf("Password : ");
        scanf("%s", &password);
        // printf("Count user = %d", count_user);
        for (int i = 0; i <= count_user; i++)
        {
            printf("Username : %s Password : %s\n", list[i].username, list[i].password);
            if (strcmp(username, list[i].username) == 0 && strcmp(password, list[i].password) == 0)
            {
                printf("\t \U00002705 Login success\n");
                register_user = 1;
                break;
            }
            register_user = 2;
        }
        while (register_user == 2)
        {
            printf("\n\t  \U000026D4 Login Failed\n\U0001F514 Enter again [0] or register [1] : ");
            scanf("%d", &select_login);
            if (select_login == 0)
            {
                register_user = 0;
                break;
            }
            else if (select_login == 1)
            {
                while (register_user != 0)
                {
                    printf("--------------------------------------\n");
                    printf("|\t   \U0001F4DD Register Page\t     |\n");
                    printf("--------------------------------------\n");
                    printf("Username : ");
                    scanf("%s", &list[count_user].username);
                    printf("Password : ");
                    scanf("%s", &list[count_user].password);
                    file_user = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Username.txt", "a+");
                    fprintf(file_user, "Username : %s Password : %s\n", list[count_user].username, list[count_user].password);
                    count_user++;
                    register_user = 0;
                    fclose(file_user);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 1000; i++)
    {
        fscanf(file_inventory, "Item name : %s | Quality : %d | Cost : %f | Price : %f | Minimum item : %d\n", &iny[i].product_name, &iny[i].product_quantity, &iny[i].product_cost, &iny[i].product_price, &iny[i].product_minimum);
        // printf("%s\n", iny[i].product_name);
        if ((int)iny[i].product_name[0] < 65)
        {
            count = i;
            break;
        }
    }
    // printf("%d", count);

    while (input != 4)
    {
        system("clear");
        // printf("Countttt %d\n", count);
        printf("\n|--------------------------------------------------------|\n");
        printf("|\t\U0001F4B8 Welcome To Online Shop Management System\t |\n");
        printf("|--------------------------------------------------------|\n\n");
        printf("|-- Please Select Menu \U0001F447 --|\n");
        printf("\U0001F449 [1] Inventory System\n");
        printf("\U0001F449 [2] Accounting System\n");
        printf("\U0001F449 [3] Point of Sales\n");
        printf("\U0001F449 [4] End The Program\n");
        printf("\n\U000025B6 Select : ");
        scanf("%d", &input);
        if (input == 1)
        {
            // file_count = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/count.txt", "w+");
            count = menu_inventory(iny, count, file_inventory, save_record, import_record);
            fclose(file_inventory);
            // fclose(file_count);
            //  menu_inventory(iny, count);
            //  printf("\nCount --> %d", count);
        }
        else if (input == 2)
        {
            menu_accounting(acc, iny, acc1, count, file_accounting, file_timestamp, file_pos2, file_pos);
            fclose(file_timestamp);
            fclose(file_pos);
            fclose(file_pos2);
        }
        else if (input == 3)
        {
            menu_pos(iny, count, file_pos, file_pos2, file_accounting, file_timestamp, file_inventory, file_pos_backup, file_inventory_backup, file_accounting_backup, file_timestamp_backup);
            fclose(file_pos);
            fclose(file_pos2);
        }
        else if (input == 4)
        {
            printf("Save Program & Exit...\U0001F601\n");
            break;
        }
        else
        {
            printf("\U0001F6AB Please Try Again, Input Correct Menu\n");
        }
        printf("\n");
    }
    return 0;
}
int login(User list[], int count_user, int register_user, int select_login)
{
    char username[20];
    char password[20];
    FILE *file_user;
    while (register_user == 0)
    {
        system("clear");
        printf("--------------------------------------\n");
        printf("|\t     \U0001F510 Login Page\t     |\n");
        printf("--------------------------------------");
        printf("\nUsername : ");
        scanf("%s", &username);
        printf("Password : ");
        scanf("%s", &password);
        for (int i = 0; i < count_user; i++)
        {
            if (strcmp(username, list[i].username) == 0 && strcmp(password, list[i].password) == 0)
            {
                printf("\t \U00002705 Login success\n");
                register_user = 1;
                break;
            }
            register_user = 2;
        }
        while (register_user == 2)
        {
            printf("\n\t  \U000026D4 Login Failed\n\U0001F514 Enter again [0] or register [1] : ");
            scanf("%d", &select_login);
            if (select_login == 0)
            {
                register_user = 0;
                break;
            }
            else if (select_login == 1)
            {
                while (register_user != 0)
                {
                    printf("--------------------------------------\n");
                    printf("|\t   \U0001F4DD Register Page\t     |\n");
                    printf("--------------------------------------\n");
                    printf("Username : ");
                    scanf("%s", &list[count_user].username);
                    printf("Password : ");
                    scanf("%s", &list[count_user].password);
                    file_user = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Username.txt", "a+");
                    fprintf(file_user, "Username : %s Password : %s\n", list[count_user].username, list[count_user].password);
                    count_user++;
                    register_user = 0;
                    fclose(file_user);
                    break;
                }
            }
        }
    }
    return count_user;
}
int menu_inventory(Inventory inventory[], int count, FILE *file_inventory, const char *save_record, const char *import_record) // Bill
{
    int num = 0;
    char select = '0';
    char out;
    // printf("COUNT UP %d", count);
    for (int i = 0; i < 1000; i++)
    {
        fscanf(file_inventory, "Item name : %s | Quality : %d | Cost : %f | Price : %f | Minimum item : %d\n", &inventory[i].product_name, &inventory[i].product_quantity, &inventory[i].product_cost, &inventory[i].product_price, &inventory[i].product_minimum);
        // printf("%s\n", inventory[i].product_name);

        if ((int)inventory[i].product_name[0] < 65)
        {
            count = i;
            break;
        }
    }
    // แก้รับค่าจาก File
    // for (int i = 0; i < count; i++)
    // {
    //     // fseek(file_inventory, 0, SEEK_SET);
    //     fscanf(file_inventory, "%s %d %f %f\n", &inventory[i].product_name, &inventory[i].product_quantity, &inventory[i].product_cost, &inventory[i].product_price);
    //     // printf("%s", inventory[i].product_name);
    // }
    //
    // printf("Can u hear me?\n");
    while (select != '5')
    {
        system("clear");
        select = '0';
        // printf("Hi\n");
        printf("\n|---------------------------------|\n");
        printf("|\t\U0001F4E6 Inventory System \t  |\n");
        printf("|---------------------------------|\n\n");
        printf("\U0001F50D [1] Search Item by Name\n");
        printf("\U0001F50D [2] Show All of Items\n");
        printf("\U0001F50D [3] Add New Item\n");
        printf("\U0001F50D [4] Show List of Nearly Out of Stock Items\n");
        printf("\U0001F50D [5] Back & Save\n");
        printf("\n\U000025B6 Select : ");
        scanf("%s", &select);
        if (select == '1')
        {
            system("clear");
            int flag;
            char search_name[1000];
            printf("|---------------------------------|\n");
            printf("|\t  \U0001F4E6 Search Item \t  |\n");
            printf("|---------------------------------|\n");
            printf("\n\U0001F50D Please Input Item Name : ");
            scanf("%s", &search_name);
            for (int i = 0; i < count; i++)
            {
                flag = 0;
                if (strcmp(search_name, inventory[i].product_name) == 0)
                {
                    flag = 1;
                    int quantity, price;
                    char select_1;
                    printf("\U0001F449 [1] Add an Item Stock\n");
                    printf("\U0001F449 [2] Remove an Item Stock\n");
                    printf("\U0001F449 [3] Details & Stock of Item\n");
                    printf("\U000025B6 Select : ");
                    scanf("%s", &select_1);

                    if (select_1 == '1')
                    {

                        printf("\U00002795 Enter Quantity To Add More : ");
                        scanf("%d", &quantity);
                        inventory[i].product_quantity += quantity;
                        break;
                    }
                    else if (select_1 == '2')
                    {

                        printf("\U00002795 Enter Quantity To Be Remove: ");
                        scanf("%d", &quantity);
                        inventory[i].product_quantity -= quantity;
                        break;
                    }
                    if (select_1 == '3')
                    {
                        // system("clear");
                        char choose = 'n';
                        while (choose != 'y')
                        {
                            system("clear");
                            printf("\n\U0001F50D Please Input Item Name : \n");
                            system("clear");
                            printf("|---------------------------------|\n");
                            printf("|\t  \U0001F4DD Item Details \t  |\n");
                            printf("|---------------------------------|\n\n");
                            printf(" \U0001F538 Item Name : %s\n", inventory[i].product_name);
                            printf(" \U0001F4A1 Item Quantity : %d\n", inventory[i].product_quantity);
                            printf(" \U0001F4A1 Item Minimum quantity : %d\n", inventory[i].product_minimum);
                            printf(" \U0001F4B8 Item Cost price : %.2f\n", inventory[i].product_cost);
                            printf(" \U0001F4B8 Item Sell price : %.2f\n", inventory[i].product_price);
                            printf("  \n|---------------------------------|\n");
                            printf("Done? [Y/N] : ");
                            scanf("%s", &choose);
                            if (choose == 'y')
                            {
                                break;
                            }
                            else
                            {
                                printf("Wrong Input, Please Try Again");
                            }
                        }
                    }
                    else
                    {
                        printf("Wrong Input, Please Try Again");
                    }
                }
            }
            if (flag == 0)
            {
                char choose1 = 'n';
                printf("\U0001F6AB We Don't Have This Item in Inventory");
                while (tolower(choose1) != 'y')
                {
                    printf("\n\nGo Back? [Y] : ");
                    scanf("%s", &choose1);
                    if (tolower(choose1) == 'y')
                    {
                        break;
                    }
                    else
                    {
                        printf("\U000026D4 Wrong Input, Please Try Again");
                    }
                }
            }
        }
        else if (select == '2')
        {
            system("clear");
            char out = 'n';
            while (tolower(out) == 'n')
            {
                // printf("%c", tolower(out));
                system("clear");
                printf("------------------------------------------\n");
                printf("\t      \U0001F4C7 List of Item\t \n");
                printf("------------------------------------------\n\n");
                for (int i = 0; i < count; i++)
                {
                    printf("%d. %s\b\t\t", i + 1, inventory[i].product_name);
                    if ((i + 1) % 3 == 0)
                    {
                        printf("\n");
                    }
                }
                if ((count) % 3 != 0)
                {
                    printf("\n");
                }
                printf("\n------------------------------------------\n");

                int com = 0;
                while (com == 0)
                {
                    printf("Done? [Y/N] : ");
                    scanf("%s", &out);
                    if (tolower(out) == 'y' || tolower(out) == 'n')
                    {
                        com++;
                    }
                    else
                    {
                        printf("\nWrong Input, Please Try Again\n");
                    }
                }
            }
        }
        if (select == '3')
        {
            system("clear");
            printf("\U00002795 Enter Item Name : ");
            scanf("%s", &inventory[count].product_name);
            printf("\U00002795 Enter Item Quanlity : ");
            scanf("%d", &inventory[count].product_quantity);
            printf("\U00002795 Enter Item Cost Price : ");
            scanf("%f", &inventory[count].product_cost);
            printf("\U00002795 Enter Item Sell Price : ");
            scanf("%f", &inventory[count].product_price);
            printf("\U00002795 Enter Item Minimum Quanlity : ");
            scanf("%d", &inventory[count].product_minimum);
            fprintf(file_inventory, "Item name : %s | Quality : %d | Cost : %.2f | Price : %.2f | Minimum item : %d\n", inventory[count].product_name, inventory[count].product_quantity, inventory[count].product_cost, inventory[count].product_price, inventory[count].product_minimum);
            printf("------ \U00002705 Done ------\n");
            count++;
            // fprintf(file_count, "%d", count);
        }
        if (select == '4')
        {
            system("clear");
            char out = 'n';
            while (tolower(out) == 'n')
            {
                system("clear");
                int flag = 0;
                printf("---------------------------------------------\n");
                printf("    \U0001F5C2  List of Nearly Out of Stock Items    \n");
                printf("---------------------------------------------\n\n");
                for (int i = 0; i < count; i++)
                {
                    if (inventory[i].product_quantity <= inventory[i].product_minimum)
                    {
                        printf(" \U0001F3F7  Item name : %s\t\b    \U0001F4CB Quantity : %d\n", inventory[i].product_name, inventory[i].product_quantity);
                        flag++;
                        if (flag % 3 == 0)
                        {
                            // printf("\n\n");
                        }
                    }
                }
                if (flag == 0)
                {
                    printf("There is No Item That Nearly Out of Stock...\n");
                }
                printf("\n---------------------------------------------\n");

                int com = 0;
                while (com == 0)
                {
                    printf("Done? [Y/N] : ");
                    scanf("%s", &out);
                    if (tolower(out) == 'y' || tolower(out) == 'n')
                    {
                        com++;
                    }
                    else
                    {
                        printf("\nWrong Input, Please Try Again\n");
                    }
                }
            }
        }
        if (select == '5')
        {
            system("clear");
            break;
        }
        else
        {
            printf("Wrong Input, Please Try Again\n");
        }
    }
    file_inventory = fopen("inventory.txt", "w+");
    for (int i = 0; i < count; i++)
    {
        // printf("Item name : %s | Quality : %d | Cost : %.2f | Price : %.2f | Minimum item : %d\n", inventory[i].product_name, inventory[i].product_quantity, inventory[i].product_cost, inventory[i].product_price, inventory[i].product_minimum);
        fprintf(file_inventory, "Item name : %s | Quality : %d | Cost : %.2f | Price : %.2f | Minimum item : %d\n", inventory[i].product_name, inventory[i].product_quantity, inventory[i].product_cost, inventory[i].product_price, inventory[i].product_minimum);
    }
    fclose(file_inventory);
    // printf("COUNT IN LOOP %d", count);
    return count;
}

// char *timestamp()
// {
//     time_t t = time(NULL);
//     // printf("\nDate : %s", ctime(&t));
//     return ctime(&t);
// }

int menu_accounting(Accounting accounting[], Inventory inventory[], Showing acc1[], int count, FILE *file_accounting, FILE *file_timestamp, FILE *file_pos2, FILE *file_pos) // Time
{
    int count_time, count_txn;
    float balance;
    file_accounting = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Accounting.txt", "r+");
    file_pos2 = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS2.txt", "r+");
    file_pos = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS.txt", "r+");
    file_timestamp = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestamp.txt", "r+");
    // cash, total, change, cost;
    fscanf(file_accounting, "%f", &balance);
    // fscanf(file_pos, "Cash : %f | Total : %f | Change : %f | Cost : %f", &cash, &total, &change, &cost);
    // printf("Balance = %.2f\n", balance);
    for (int i = 0; i < 1000; i++)
    {
        fscanf(file_timestamp, "Millisecond : %llu | Timestamp : %[^\n]\n", &accounting[i].timestamp_sec_keep, &accounting[i].timestamp_keep);
        if ((int)accounting[i].timestamp_keep[0] < 65)
        {
            count_time = i;
            break;
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        fscanf(file_pos, "Timestamp (Millisecond) : %llu | Item name : %s | Quality : %d | Amount : %f | Profit : %f | Timestamp : %[^\n]\n", &acc1[i].product_timestamp_sec, &acc1[i].product_name, &acc1[i].product_quantity, &acc1[i].product_amount, &acc1[i].product_profit, &acc1[i].product_timestamp);
        //  printf("Timestamp sec : %llu", acc1[i].prodcut_timestamp_sec);
        if ((int)acc1[i].product_name[0] < 65)
        {
            count_txn = i;
            break;
        }
        // printf("Timestamp (Millisecond) : %llu | Item name : %s | Quality : %d | Amount : %.2f | Profit : %.2f | Timestamp : %s\n", acc1[i].product_timestamp_sec, acc1[i].product_name, acc1[i].product_quantity, acc1[i].product_amount, acc1[i].product_profit, acc1[i].product_timestamp);
        //  printf("Item name : %s | Quality : %d | Amount : %.2f | Timestamp : %s\n", acc1[i].product_name, acc1[i].product_quantity, acc1[i].product_amount, acc1[i].product_timestamp);
    }

    int total, select = 0, sub_select = -1, sub_sub_select = -1;
    float profit;

    while (select != 6)
    {
        system("clear");
        sub_select = -1;
        printf("\n|-------------------------------|\n");
        printf("|\t\U0001F4B8 Account System  \t|\n");
        printf("|-------------------------------|\n\n");
        printf(" \U0001F50D [1] Show Timestamp\n");
        printf(" \U0001F50D [2] Show Financial Status\n");
        printf(" \U0001F50D [3] Show Daily Summary\n");
        printf(" \U0001F50D [4] Show Weekly Summary\n");
        printf(" \U0001F50D [5] Show Monthly Summary\n");
        printf(" \U0001F50D [6] Back\n");
        printf("\n\U000025B6 Select : ");
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            while (sub_select != 0)
            {
                printf("\n|----------------------------------|\n");
                printf("|\t    \U0001F9FE Timestamp\t   |\n");
                printf("|----------------------------------|\n\n");
                printf("--------------------------------------\n");
                for (int i = 0; i < count_time; i++)
                {

                    // fscanf(file_timestamp, "%[^\n]\n", &accounting[i].timestamp_keep);
                    if (i >= 10)
                    {
                        printf("| \U0001F552 [%d] : %s  |\n", i + 1, accounting[i].timestamp_keep);
                    }
                    else
                    {
                        printf("| \U0001F552 [%d] : %s  |\n", i + 1, accounting[i].timestamp_keep);
                    }

                    printf("--------------------------------------\n");
                }

                printf("\nPress 0 To Go Back\n");
                printf("\U000025B6 Select : ");
                scanf("%d", &sub_select);

                float temp = 0;
                if (sub_select > 0 && sub_select <= count_time)
                {
                    system("clear");
                    printf("\n|----------------------------------|\n");
                    if (sub_select >= 10)
                    {
                        printf("|     \U0001F9FE Timestamp #%d: Details    |\n", sub_select);
                    }
                    else
                    {
                        printf("|     \U0001F9FE Timestamp #%d: Details     |\n", sub_select);
                    }
                    printf("|----------------------------------|\n\n");
                    for (int i = 0; i <= count_txn; i++)
                    {
                        // printf("%d\n", i);
                        if (strcmp(accounting[sub_select - 1].timestamp_keep, acc1[i].product_timestamp) == 0)
                        {
                            // printf("%d---\n", i);
                            printf(" \t\U0001F31F Name : %s     \n", acc1[i].product_name);
                            printf(" \t\U0001F3F7  Quantity : %d \n", acc1[i].product_quantity);
                            printf(" \t\U0001F4B0 Amount : %.2f \n", acc1[i].product_amount);
                            printf("\n");
                            temp += acc1[i].product_amount;
                        }
                    }
                    printf(" \U0001F4B5 Total Transaction : %.2f ฿\n", temp);
                    printf("-----------------------------------\n");
                    printf("Press Any Number to Go Back\n");
                    printf("\U000025B6 Select : ");
                    scanf("%d", &sub_select);
                }

                else if (sub_select != 0)
                {
                    printf("Wrong Input, Please Try Again");
                }
            }
        }
        else if (select == 2)
        {
            system("clear");
            float temp = balance;
            float temp_2 = balance - 10000;
            float temp_satang = balance - temp;
            float temp_2_satang = balance - temp_2;
            // cost = find_cost();
            // float profit, thousand, five_hund, hundred, fifty, ten, five, one, two, point_five, point_twofive, thousand_2, five_hund_2, hundred_2, fifty_2, ten_2, five_2, two_2, one_2, point_five_2, point_twofive_2;
            // profit = total_cost - total_sale;
            while (sub_select != 0)
            {
                const float money_types[11] = {1000, 500, 100, 50, 20, 10, 5, 2, 1, 0.5, 0.25};
                const char money_types_str[11][6] = {"1000", "500", "100", "50", "20", "10", "5", "2", "1", "0.5", "0.25"}; // [จำนวน Array][ความยาว Array]
                // float money = 12345.25, profit = money - 10000;
                printf("\n|-----------------------------------------------|\n");
                printf("|    \U0001F3DB  Financial Status (Banknotes & Coins)    |\n");
                printf("|-----------------------------------------------|\n");
                printf("| Banknote/Coin |    Balance    |     Profit    |\n");
                printf("|-----------------------------------------------|\n");
                int i, m, p;
                for (i = 0; i < 11; ++i)
                {
                    {
                        p = floor(temp_2 / money_types[i]);
                        m = floor(temp / money_types[i]);
                        printf("|%10s   \t|%8d\t|%8d\t|\n", money_types_str[i], m, p);
                        temp_2 -= (p * money_types[i]);
                        temp -= (m * money_types[i]);
                    }
                }
                printf("|-----------------------------------------------|\n");
                printf("|     Total\t|   %.2f ฿  |   %.2f ฿\t|\n", balance, balance - 10000);
                printf("|-----------------------------------------------|\n");
                printf("\nPress 0 To Go Back\n");
                printf("\U000025B6 Select : ");
                scanf("%d", &sub_select);
                if (sub_select != 0)
                {
                    printf("Wrong Input, Please Try Again");
                }
            }
        }
        else if (select == 3)
        {
            system("clear");
            char select_sub_3 = NULL;
            int count_daily = 0;
            while (select_sub_3 != '0')
            {
                float daily_profit = 0;
                unsigned long long temp = timestamp_sec() - (timestamp_sec() % 86400000); // 864000000 = 1 day
                unsigned long long temp2 = temp + 86400000;
                printf("\n|------------------------------------|\n");
                printf("|\t   \U0001F4B0 Daily Summary \t     |\n");
                printf("|------------------------------------|\n");
                // printf("%llu", temp);
                printf(" \U0001F4C5 Date : %s\n", timestamp_msec(temp));
                for (int i = 0; i < count_txn; i++)
                {
                    // printf("%llu\n", acc1[i].product_timestamp_sec);
                    if (acc1[i].product_timestamp_sec >= temp && acc1[i].product_timestamp_sec <= temp2)
                    {
                        count_daily++;
                        printf(" \U0001F538 Item name : %s\tProfit %.2f\n", acc1[i].product_name, acc1[i].product_profit);
                        daily_profit += acc1[i].product_profit;
                    }
                }
                printf("\n \U0001F4B5 Total Daily Profit : %.2f", daily_profit);
                printf("\n \U0001F381 Total Items : %d\n", count_daily);
                printf("|------------------------------------|\n");
                printf("Press 0 To Go Back\n");
                printf("\U000025B6 Select : ");
                scanf("%s", &select_sub_3);
                if (select_sub_3 != '0')
                {
                    printf("Wrong Input, Please Try Again");
                }
            }
        }
        if (select == 4)
        {
            system("clear");
            char select_sub_4 = NULL;
            int count_week = 0;
            while (select_sub_4 != '0')
            {
                float week_profit = 0;
                unsigned long long temp = timestamp_sec() - (timestamp_sec() % (86400000 * 7)); // 864000000 = 1 day
                unsigned long long temp2 = temp + (86400000 * 7);
                printf("\n|------------------------------------|\n");
                printf("|\t   \U0001F4B0 Weekly Summary \t     |\n");
                printf("|------------------------------------|\n");
                printf(" \U0001F4C5 Date : %s", timestamp_msec(temp));
                printf("\t          \U00002B07      \n");
                printf(" \U0001F4C5 Date : %s\n", timestamp_msec(temp2));
                for (int i = 0; i < count_txn; i++)
                {
                    // printf("%llu\n", acc1[i].product_timestamp_sec);
                    if (acc1[i].product_timestamp_sec >= temp && acc1[i].product_timestamp_sec <= temp2)
                    {
                        count_week++;
                        printf(" \U0001F538 [%d] Item : %s\tProfit %.2f\n", count_week, acc1[i].product_name, acc1[i].product_profit);
                        week_profit += acc1[i].product_profit;
                    }
                }
                printf("\n \U0001F4B5 Total Weekly Profit : %.2f", week_profit);
                printf("\n \U0001F381 Total Items : %d\n", count_week);
                printf("|------------------------------------|\n");
                printf("Press 0 To Go Back\n");
                printf("\U000025B6 Select : ");
                scanf("%s", &select_sub_4);
                if (select_sub_4 != '0')
                {
                    printf("Wrong Input, Please Try Again");
                }
            }
        }
        if (select == 5)
        {
            system("clear");
            char select_sub_5 = NULL;
            int count_month = 0;
            while (select_sub_5 != '0')
            {
                float month_profit = 0;
                unsigned long long temp = timestamp_sec() - (timestamp_sec() % (2629743000)); // 864000000 = 1 day
                unsigned long long temp2 = temp + (2629743000);
                printf("\n|------------------------------------|\n");
                printf("|\t   \U0001F4B0 Monthly Summary \t     |\n");
                printf("|------------------------------------|\n\n");
                printf(" \U0001F4C5 Date : %s", timestamp_msec(temp));
                printf("\t          \U00002B07      \n");
                printf(" \U0001F4C5 Date : %s\n", timestamp_msec(temp2));
                for (int i = 0; i < count_txn; i++)
                {
                    // printf("%llu\n", acc1[i].product_timestamp_sec);
                    if (acc1[i].product_timestamp_sec >= temp && acc1[i].product_timestamp_sec <= temp2)
                    {
                        count_month++;
                        printf(" \U0001F538[%d] Item : %s\tProfit %.2f\n", count_month, acc1[i].product_name, acc1[i].product_profit);
                        month_profit += acc1[i].product_profit;
                    }
                }
                printf("\n \U0001F4B5 Total Monthly Profit : %.2f", month_profit);
                printf("\n \U0001F381 Total Items : %d\n", count_month);
                printf("|------------------------------------|\n");
                printf("Press 0 To Go Back\n");
                printf("\U000025B6 Select : ");
                scanf("%s", &select_sub_5);
                if (select_sub_5 != '0')
                {
                    printf("Wrong Input, Please Try Again");
                }
            }
        }
        else if (select == 6)
        {
            break;
        }
        else
        {
            printf("Wrong Input, Please Try Again\n");
        }
    }
}

int menu_pos(Inventory inventory[], int count, FILE *file_pos, FILE *file_pos2, FILE *file_accounting, FILE *file_timestamp, FILE *file_inventory, FILE *file_pos_backup, FILE *file_inventory_backup, FILE *file_accounting_backup, FILE *file_timestamp_backup) // Hill
{
    int pro, qty, count_item = 0, flag = 0, flags = 0;
    float price, amount, cost, profit, balance, cash = 0, change = 0, total = 0;
    char check, ans;
    system("clear");
    printf("\n------------------------------\n");
    printf("|\t\U0001F4B8 PoS System  \t     |\n");
    printf("------------------------------\n");
    char time[1000];
    char time_sec[1000];
    do
    {
        file_inventory = fopen("inventory.txt", "r+");
        for (int i = 0; i < count; i++)
        {
            fscanf(file_inventory, "Item name : %s | Quality : %d | Cost : %f | Price : %f | Minimum item : %d\n", &inventory[i].product_name, &inventory[i].product_quantity, &inventory[i].product_cost, &inventory[i].product_price, &inventory[i].product_minimum);
            // printf("%s\n", inventory[i].product_name);
        }
        fclose(file_inventory);
        file_accounting = fopen("accounting.txt", "r+");
        fscanf(file_accounting, "%f", &balance);
        system("clear");
        printf("\n------------------------------------------------\n");
        printf("\t\t\U0001F516  List of Items\t     \n");
        printf("------------------------------------------------\n");
        for (int i = 0; i < count; i++) // count = total items
        {
            if (strlen(inventory[i].product_name) <= 3)
            {
                printf("[%d] %s\t\t\tx %d\t\tPrice %8.2f ฿\b\n", i + 1, inventory[i].product_name, inventory[i].product_quantity, inventory[i].product_price);
            }
            else
            {
                printf("[%d] %s\t\tx %d\tPrice %8.2f ฿\b\n", i + 1, inventory[i].product_name, inventory[i].product_quantity, inventory[i].product_price);
            }
        }

        file_pos = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS.txt", "r");
        file_pos_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoSbackup.txt", "w");
        char ch1;
        while ((ch1 = fgetc(file_pos)) != EOF)
        {
            fputc(ch1, file_pos_backup);
        }
        fclose(file_pos_backup);
        fclose(file_pos);

        file_inventory = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Inventory.txt", "r");
        file_inventory_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Inventorybackup.txt", "w");
        char ch2;
        while ((ch2 = fgetc(file_inventory)) != EOF)
        {
            fputc(ch2, file_inventory_backup);
        }
        fclose(file_inventory_backup);
        fclose(file_inventory);

        file_timestamp = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestamp.txt", "r");
        file_timestamp_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestampbackup.txt", "w");
        char ch3;
        while ((ch3 = fgetc(file_timestamp)) != EOF)
        {
            fputc(ch3, file_timestamp_backup);
        }
        fclose(file_timestamp_backup);
        fclose(file_timestamp);
        // printf("------------------------------------------------\n");
        strcpy(time, timestamp());
        unsigned long long time_sec = timestamp_sec();
        // strcpy(time_sec, timestamp_sec());
        file_timestamp = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestamp.txt", "a+");
        fprintf(file_timestamp, "Millisecond : %llu | Timestamp : %s", time_sec, time);
        //  fclose(file_timestamp);
        do
        {
            int q_count = 0;
            while (q_count == 0)
            {
                printf("------------------------------------------------");
                printf("\n\U0001F4CD Product \t  : ");
                scanf("%d", &pro);
                printf("\U0001F4E5 Quantity \t  : ");
                scanf("%d", &qty);
                q_count++;
                if (qty > inventory[pro - 1].product_quantity)
                {
                    printf("\n\nNot Enough Item Quantity, Please Try Again...\n\n");
                    q_count = 0;
                }
            }

            amount = inventory[pro - 1].product_price * qty;
            inventory[pro - 1].product_quantity -= qty;
            printf("\U0001F4B0 Amount\t  : %.2f ฿", amount);
            total = total + amount;

            for (int i = pro - 1; i <= pro; i++)
            {
                profit = 0;
                profit = (inventory[i].product_price - inventory[i].product_cost) * qty;
                balance += profit;
                // printf("-->%.2f\n", profit);
                // printf("----->%.2f\n", balance);
                break;
            }

            count_item = count_item + qty;
            printf("\n------------------------------------------------");
            printf("\n\U0001F6D2 Item in Cart   : %d", count_item);
            printf("\n\U0001F4B8 Current Total  : %.2f ฿", total);
            printf("\n------------------------------------------------");

            if (pro != 0)
            {
                file_pos = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS.txt", "a+");
                fprintf(file_pos, "Timestamp (Millisecond) : %llu | Item name : %s | Quality : %d | Amount : %.2f | Profit : %.2f | Timestamp : %s", time_sec, inventory[pro - 1].product_name, qty, amount, amount - (inventory[pro - 1].product_cost * qty), time);
                // printf("Quantity -> %d", inventory[i].product_quantity);
                fclose(file_pos);
                // break;
                //  qty = 0;
            }
            int flag = 0;
            while (flag == 0)
            {
                printf("\nAdd more items? [Y/N] : ");
                scanf("%s", &check);
                if ((int)tolower(check) == 121 || (int)tolower(check) == 110)
                {
                    flag++;
                }
                else
                {
                    printf("\nWrong Input, Please Try Again");
                }
            }

        } while (tolower(check) == 'y');

        do
        {
            printf("Cash\t\t: ");
            scanf("%f", &cash);
            if (cash < total)
            {
                fclose(file_timestamp);
                file_pos = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS.txt", "w");
                file_pos_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoSbackup.txt", "r");
                char cpy1;
                while ((cpy1 = fgetc(file_pos_backup)) != EOF)
                {
                    fputc(cpy1, file_pos);
                }
                fclose(file_pos_backup);
                fclose(file_pos);

                char cpy2;
                file_inventory = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Inventory.txt", "w");
                file_inventory_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Inventorybackup.txt", "r");
                while ((cpy2 = fgetc(file_inventory_backup)) != EOF)
                {
                    fputc(cpy2, file_inventory);
                }
                fclose(file_inventory_backup);
                fclose(file_inventory);

                char cpy3;
                file_timestamp = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestamp.txt", "w");
                file_timestamp_backup = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Timestampbackup.txt", "r");
                while ((cpy3 = fgetc(file_timestamp_backup)) != EOF)
                {
                    fputc(cpy3, file_timestamp);
                }
                fclose(file_timestamp_backup);
                fclose(file_timestamp);
                printf("\nInsufficient Funds\n");
                break;
            }
            change = cash - total;
        } while (cash < total);
        if (cash >= total)
        {
            system("clear");
            printf("\n-------------------------------------------");
            printf("\n\t\t\U0001F9FE Receipt\t\n");
            printf("-------------------------------------------\n");
            // timestamp();
            printf("Date\t\t: %s", time);
            printf("Items\t\t: %d\n", count_item);
            printf("Total\t\t: %.2f ฿\n", total);
            printf("Cash\t\t: %.2f ฿\n", cash);
            printf("Change\t\t: %.2f ฿", change);
            printf("\n-------------------------------------------");

            int flags = 0;
            while (flags == 0)
            {
                printf("\n\nClose? [Y/N]: ");
                scanf("%s", &ans);
                if ((int)tolower(ans) == 121 || (int)tolower(ans) == 110)
                {
                    flags++;
                }
                else
                {
                    printf("Wrong Input, Please Try Again\n");
                }
            }
            if (cash != 0)
            {
                file_pos2 = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/PoS2.txt", "a+");
                fprintf(file_pos2, "Timestamp (Millisec) : %llu | Cash : %.2f | Total : %.2f | Change : %.2f | Timestamp : %s", time_sec, cash, total, change, time);
                fclose(file_pos2);
                fclose(file_timestamp);
            }
            if (tolower(ans) == 'y')
            {
                // system("clear"); // clear screen
                printf("\nThank you for Purchasing \U0001F64F\n");
                // printf("BALANCECCECECECE %.2f\n", balance);
                file_accounting = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Accounting.txt", "r+");
                fprintf(file_accounting, "%.2f", balance);
                fclose(file_accounting);
                file_inventory = fopen("/Users/sikar/Desktop/ALL WORK CLASS/CPE100/C/Final Project/Inventory.txt", "w+");
                for (int i = 0; i < count; i++)
                {
                    // printf("Item name : %s | Quality : %d | Cost : %.2f | Price : %.2f | Minimum item : %d\n", inventory[i].product_name, inventory[i].product_quantity, inventory[i].product_cost, inventory[i].product_price, inventory[i].product_minimum);
                    fprintf(file_inventory, "Item name : %s | Quality : %d | Cost : %.2f | Price : %.2f | Minimum item : %d\n", inventory[i].product_name, inventory[i].product_quantity, inventory[i].product_cost, inventory[i].product_price, inventory[i].product_minimum);
                }
                fclose(file_inventory);
                break;
            }
        }
    } while (tolower(ans) == 'n');
    return 0;
}