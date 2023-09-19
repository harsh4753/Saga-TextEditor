#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define max_line 10
#define line_char 150
int access_the_line;
FILE *ptr;
FILE *top;
FILE *bottom;
FILE *temp;
struct buffer *array[max_line];
int move_up_count = 0;

char str_top[line_char];
char str_bottom[line_char];
int current = 0;

struct node
{
    char data;
    struct node *next;
};
struct buffer
{
    struct node *head;
};
int count(struct node *p)
{
    int l = 0;
    while (p != NULL)
    {
        l++;
        p = p->next;
    }
    return l;
}
int delete (struct node *p, int index)
{
    struct node *q = NULL;
    int x = -1, i;
    if (index < 1 || index > count(p))
        return -1;
    if (index == 1)
    {
        q = array[access_the_line]->head;
        x = array[access_the_line]->head->data;
        array[access_the_line]->head = array[access_the_line]->head->next;
        free(q);
        return x;
    }
    else
    {
        for (i = 0; i < index - 1; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        free(p);
        return x;
    }
}
void insert(struct node *p, int index, char x)
{
    struct node *t;
    int i;
    if (index < 0 || index > count(p))
        return;
    t = (struct node *)malloc(sizeof(struct node));
    t->data = x;
    if (index == 0)
    {
        t->next = array[access_the_line]->head;
        array[access_the_line]->head = t;
    }
    else
    {
        for (i = 0; i < index - 1; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}

void init_buffer()
{
    for (int i = 0; i < max_line; i++)
    {
        array[i] = (struct buffer *)malloc(sizeof(struct buffer));
        array[i]->head = NULL;
    }
}

void load_line_to_array(int line_number, char line[])
{
    if (line[0] == '\n')
    {
        return;
    }
    struct node *first = array[line_number]->head;
    struct node *t, *last;
    array[line_number]->head = (struct node *)malloc(sizeof(struct node));
    array[line_number]->head->data = line[0];
    array[line_number]->head->next = NULL;
    last = array[line_number]->head;
    int n = strlen(line);
    int w = 0;
    while (w < n)
    {
        if (line[w] == '\n')
        {
            n = n - 1;
            break;
        }
        w++;
    }
    for (int i = 1; i < n; i++)
    {
        t = (struct node *)malloc(sizeof(struct node));
        t->data = line[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}
void append_line(FILE *fp, char *c)
{
    fputs(c, fp);
}
char *list_to_string(struct node *p)
{
    char *empty = (char *)malloc(sizeof(char));
    empty[0] = '\n';

    if (p == NULL)
    {
        return empty;
    }
    struct node *countNode = p;
    int count = 0; // Counts number of nodes
    while (countNode != NULL)
    {
        count++;
        countNode = countNode->next;
    }
    char *result = (char *)malloc(sizeof(char) * (count + 1));
    struct node *temp = p;
    int i = 0;
    while (temp != NULL)
    {
        result[i] = temp->data;
        i++;
        temp = temp->next;
    }
    result[i] = '\n';
    return result;
}

void full_the_buffer()
{
    char s[line_char];
    for (int i = 0; i < max_line; i++)
    {
        if (fgetc(ptr) != EOF)
        {
            fseek(ptr, -1, SEEK_CUR);

            fgets(s, line_char, ptr);
            load_line_to_array(i, s);
        }
    }
}

void print_buffer()
{
    printf("\n........................................SAGA_TEXT_EDITOR......................................................\n");
    int a = current;
    for (int i = 0; i < max_line; i++)
    {
        a = a % max_line;
        struct node *p = array[a]->head;
        if (!p)
        {
            printf("\n");
        }
        else
        {
            while (p != NULL)
            {
                printf("%c", p->data);
                p = p->next;
            }
            printf("\n");
        }

        a++;
    }
    printf("\n............................................................................................................\n");
}
void getlastlinetop(FILE *fp)

{
    if (fseek(fp, -1, SEEK_CUR) == 0)
        fseek(fp, 1, SEEK_CUR);
    else
    {
        return;
    }
    // fseek(fp, -1, SEEK_CUR);
    int current_position;
    char ch;
    current_position = ftell(fp);
    do6
    {
        if (fseek(fp, -2, SEEK_CUR) != 0)
        {
            fseek(fp, 0, SEEK_SET);
            break;
        }
        // fseek(fp, -2, SEEK_CUR);
        ch = fgetc(fp);
    } while (ch != '\n');
    // while (ch != '\n'){

    //     if (fseek(fp, -2, SEEK_CUR) !=0){
    //         fseek(fp, 0, SEEK_SET);  //if file has only 1 line
    //     }
    //     ch = fgetc(fp);
    // }
    int line_starting_position = ftell(fp);
    int line_lenght = current_position - line_starting_position;
    fgets(str_top, line_lenght + 1, fp);
    fseek(fp, line_starting_position - current_position - 1, SEEK_CUR);

    return;
}

void getlastlinefrombottom(FILE *fp)
{

    // if (!ftell(fp))
    // {
    //     return  ;
    // }
    // fseek(fp, -1, SEEK_CUR);
    if (fseek(fp, -1, SEEK_CUR) == 0)
        fseek(fp, 1, SEEK_CUR);
    else
    {

        fgets(str_bottom, line_char, ptr);
        return;
    }

    int current_position;
    char ch;
    current_position = ftell(fp);
    do
    {
        if (fseek(fp, -2, SEEK_CUR) != 0)
        {
            fseek(fp, 0, SEEK_SET);
            break;
        }
        // fseek(fp, -2, SEEK_CUR);
        ch = fgetc(fp);
    } while (ch != '\n');
    // while (ch != '\n'){
    //     if (fseek(fp, -2, SEEK_CUR) != 0){
    //         fseek(fp, 0, SEEK_SET);  //if file has only 1 line
    //         break;
    //     }
    //     ch = fgetc(fp);
    // }
    int line_starting_position = ftell(fp);
    int line_lenght = current_position - line_starting_position;
    fgets(str_bottom, line_lenght, fp);
    fseek(fp, line_starting_position - current_position + 1, SEEK_CUR);

    return;
}
void move_up()
{
    current = (current) % max_line;
    char *string = list_to_string(array[current]->head);
    append_line(top, string);
    getlastlinefrombottom(bottom);
    load_line_to_array(current, str_bottom);
    current++;
    print_buffer();
    move_up_count++;
}
void move_down()
{
    if (ftell(top) && move_up_count)
    {
        current--;
        current = current % max_line;
        char *string = list_to_string(array[current]->head);
        append_line(bottom, string);
        getlastlinetop(top);
        load_line_to_array(current, str_top);
        print_buffer();
        move_up_count--;
    }
}

int main()
{
    char str[20];
    printf("Enter the name of file");
    scanf("%s", str);
    ptr = fopen(str, "r+");
    if (ptr == NULL)
    {
        printf("FILE DOESNOT EXIST");
        exit(1);
    }
    top = fopen("top.txt", "w+");
    bottom = fopen("bottom.txt", "w+");
    temp = fopen("temp.txt", "w+");
    fseek(ptr, 0, SEEK_END);

    long lastofthefile = ftell(ptr);
    long starting_position_of_bottom = ftell(bottom);
    long starting_position_of_top = ftell(top);
    rewind(ptr);
    init_buffer();
    full_the_buffer();
    print_buffer();
    int i;
    printf("press 1 and enter to go up\n");
    printf("press 2 and enter to go down\n");
    printf("press 3 and enter to insert\n");
    printf("press 4 and enter to delete\n");
    printf("press 5 to save the file\n");
    printf("press 6 to quit\n");
    long v;
    int line_number;
    int line_number1;
    while (1)
    {
        printf("Enter the key");
        scanf("%d", &i);
        switch (i)
        {
        case 1:

            v = ftell(ptr);
            if (v != lastofthefile || ftell(bottom))
            {

                move_up();
            }

            break;
        case 2:

            if (ftell(top))
            {
                move_down();
            }
            break;
        case 4:

            printf("enter the line number from which you want to delete");
            scanf("%d", &line_number);
            int position;
            printf("Enter the node number you want want to delete");
            scanf("%d", &position);
            access_the_line = (current + line_number - 1) % max_line;
            int xyz = delete (array[access_the_line]->head, position);
            print_buffer();
            break;

        case 3:

            printf("enter the line number from which you want to insert");
            scanf("%d", &line_number1);
            int position1;
            printf("Enter the node number you want want to insert");
            scanf("%d", &position1);
            access_the_line = (current + line_number1 - 1) % max_line;
            char d;
            printf("Enter the character you want to insert");
            scanf("\n%c", &d);
            insert(array[access_the_line]->head, position1, d);
            print_buffer();
            break;
        case 5:
            // to save the file
            while (move_up_count && ftell(bottom))
            {
                move_up();
                move_up_count--;
            }
            char copy[line_char];
            long last_position_of_top = ftell(top);
            rewind(top);
            // to copy the content top
            while (last_position_of_top != ftell(top))
            {
                fgets(copy, line_char, top);
                fputs(copy, temp);
            }
            // to copy the content of buffer
            for (int i = 0; i < max_line; i++)
            {
                current = current % max_line;
                char *copy1 = list_to_string(array[current]->head);
                fputs(copy1, temp);
                current++;
            }
            // top copy the content of main file
            while (lastofthefile != ftell(ptr))
            {
                char copy2[line_char];
                fgets(copy2, line_char, ptr);
                fputs(copy2, temp);
            }
            int result2 = remove("main.txt");
            if (result2 != 0)
                printf("Unable to delete the file");
            int result = rename("temp.txt", "main.txt");
            if (result != 0)
            {
                printf("The file could not be renamed.");
            }

            return 0;

        case 6:
            printf("changes in the file is not saved");
            return 0;
        }
    }
    fclose(ptr);
    fclose(bottom);
    fclose(top);
    fclose(temp);
    return 0;
}