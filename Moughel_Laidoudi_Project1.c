/*
Project Done by :

Moughel Mohamed Souhail 105672
El Mehdi Laidoudi 102320

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char name[30];
    char percentage[30];
    char plateform[30];
    double number_of_users;
}social_media_info;
// Final Version//
void menu()
{
    printf("\n\n\t\t------------------- Menu to Use-----------------------\n");
    printf("\n\t\t1. View The file content\n");
    printf("\n\t\t2. Load the file content to an array\n");
    printf(
        "\n\t\t3. Get the country with the highest number of social media "
        "users\n");
    printf("\n\t\t4. Sort data by number of social media users\n");
    printf("\n\t\t5. Get a countrys social media data\n");
    printf("\n\t\t6. To Quit ");
    printf("\n\t\t-------------------------------------------------------\n");
    printf("\n\t\tYour choice please:");
}

double array_to_double(char arr[], FILE *infp, int n)
{
    int i, ch;
    char *endptr;
    for (i = 0; ((i < n - 1) && ((ch = fgetc(infp)) != '\n')); i++)
    {
        if (ch != ',')
        {
            arr[i] = ch;
        }
        else
        {
            i--;
        }
    }
    arr[i] = '\0';
    return strtod(arr, &endptr);
}
void remove_endline(char arr[])
{
    int len;
    len = strlen(arr);
    arr[len - 1] = '\0';
}

int Load_The_File(FILE *infp, social_media_info *arr)
{
    int i = 0;
    char *endptr;
    char temp, Line[50];
    char user_num[20];
    char number_of_users[30];
    fseek(infp, 0, 0);
    while (!feof(infp))
    {
        fgets(arr[i].name, 30, infp);
        remove_endline(arr[i].name);
        fgets(arr[i].percentage, 30, infp);
        fgets(arr[i].plateform, 30, infp);
        arr[i].number_of_users = (array_to_double(number_of_users, infp, 9));
        fgets(Line, 50, infp);
        i++;
    }
    return (i);
}
void View_The_file_content(FILE *infp)
{
    fseek(infp, 0, 0);
    char content[50];
    while (!feof(infp))
    {
        fgets(content, 50, infp);
        printf("\n\t\t%s", content);
    }
}

void highest_users(social_media_info *arr, int x, int *i)
{
    double max = 0;
    for (int j = 0; j < x; j++)
    {
        if (arr[j].number_of_users > max)
        {
            max = arr[j].number_of_users;
            *i = j;
        }
    }
}

void sorting_array(social_media_info *arr, int n)
{
    social_media_info container;
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].number_of_users > arr[min_idx].number_of_users)
                min_idx = j;

        if (min_idx != i)
            container = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = container;
    }
}
/* This function works on some computers and others not , after testing it on Replit its works perfectly*/
void search_data_country(social_media_info *arr, char *country_search, int len,
                         int *index)
{
    int value,
        flag = 0;
    int i;
    for (i = 0; i < len; i++)
    {
        value = strcmp(country_search, arr[i].name);
        if (value == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        *index = i;
    }
    else
    {
        *index = -1;
    }
}

int main()
{

    FILE *infp;
    infp = fopen("social_media.txt", "r");
    social_media_info arr[50];
    int choice, arr_len, i, b, z, flag2 = 0;
    char country_search[30], ch;
    do
    {
        menu();
        scanf("%d", &choice);
        printf(
            "\n\t\t--------------------------------------------------------"
            "\n");
        if (choice == 1)
            View_The_file_content(
                infp);
        else if (choice == 2)
        {
            arr_len = Load_The_File(infp, arr);
            printf("\n\t\tLoading Successfull with the data of %d countries ",
                   arr_len);
            flag2 = 1;
        }
        else if (choice == 3 && flag2 != 0)

        {
            highest_users(arr, arr_len, &i);
            printf(
                "\n\t\tThe country that has the highest number of active "
                "social "
                "media users is :%s \n\t\t\t\twith %.2lf millions of "
                "users\n",
                arr[i].name, arr[i].number_of_users);
        }
        else if (choice == 4 &&
                 flag2 != 0)
        {
            sorting_array(arr, arr_len);
            printf("\n\t\tSorted Successful");
        }
        else if (choice == 5 &&
                 flag2 != 0)
        {
            // choice 5 begin
            printf(
                "\n\t\tPlease enter the name of the country that you want the data "
                "from:");
            ch = getchar();
            gets(country_search);
            search_data_country(arr, country_search, z, &b);
            if (b >= 0)
            {
                printf(
                    "\n\t\tCountry Data\n\t\t------------------------------------ "
                    "\n\t\t%s\n\t\t%s\t\t%s\t\t%.2lf",
                    arr[b].name, arr[b].percentage, arr[b].plateform,
                    arr[b].number_of_users);
            }
            else
            {
                printf("\n\t\tCountry not found\n");
            }
        }
        else if (choice == 6)
        {
            printf("\n\t\t You decided to QUIT,...Bye!\n\n\t\t");
        }
        else
        {
            printf(
                "\n\t\t You cannot execute this menus unless you select first "
                "the second menu ,or this number is not available \n");
        }
    } while (choice != 6);
    return 0;
}
