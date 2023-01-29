#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LP
{
    struct Post *post;
    struct LP *nextLP;
} LP;

typedef struct User
{
    char *name;
    char *pass;
    struct Post *usersPosts;
    struct LP *likedPosts;
    struct User *nextUser;
} User;

typedef struct Post
{
    char *writer;
    int postId;
    int likes;
    char *text;
    struct Post *nextPost;
} Post;

Post *findPostEnd(User *logged_in_user)
{
    Post *curr = logged_in_user->usersPosts;
    while (curr->nextPost != NULL)
    {
        curr = curr->nextPost;
    }
    return curr;
}

Post *findPreviousPost(Post *head, int postId)
{
    Post *prev;
    Post *curr = head;
    while (curr != NULL)
    {
        if (curr->postId == postId)
            return prev;
        prev = curr;
        curr = curr->nextPost;
    }
    return NULL;
}

Post *findPost(Post *head, int postId)
{
    Post *curr = head;
    while (curr != NULL)
    {
        if (curr->postId == postId)
            return curr;
        curr = curr->nextPost;
    }
    return NULL;
}

LP *findLikedEnd(User *user)
{
    LP *curr = user->likedPosts;
    while (curr->nextLP != NULL)
    {
        curr = curr->nextLP;
    }
    return curr;
}

User *find(User *head, char *name)
{
    User *curr = head;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->nextUser;
    }
    return NULL;
}

User *findEnd(User *usersHead)
{
    User *curr = usersHead;
    while (curr->nextUser != NULL)
        curr = curr->nextUser;
    return curr;
}

int signup(User *usersHead, char *name, char *pass, User *logged_in_user)
{
    if (logged_in_user != NULL)
    {
        printf("someone is already logged in.\n");
        return 1;
    }
    if (find(usersHead, name) != NULL)
    {
        printf("username exists bro. \n");
        return 2;
    }
    User *newUser = (User *)malloc(sizeof(User));
    newUser->name = (char *)malloc(300);
    newUser->pass = (char *)malloc(300);
    newUser->nextUser = NULL;
    strcpy(newUser->name, name);
    strcpy(newUser->pass, pass);
    User *curr = findEnd(usersHead);
    curr->nextUser = newUser;
    printf("signup was done with %s as name and %s as pass.\n", newUser->name , newUser->pass);
    return 0;
}

int login(User *usersHead, User **logged_in_user, char *name, char *pass)
{
    if (*logged_in_user != NULL)
    {
        printf("someone is already logged in.\n");
        return 1;
    }
    if (find(usersHead, name) == NULL)
    {
        printf("username does not exist.\n");
        return 2;
    }
    if (strcmp(find(usersHead, name)->pass, pass) == 0)
    {
        *logged_in_user = find(usersHead, name);
        printf("login successful.\n");
        return 0;
    }
    printf("wrong password.\n");
    return 3;
}

int submit_post(User *logged_in_user, char *text)
{
    if (logged_in_user == NULL)
    {
        printf("no one is logged in.\n");
        return 1;
    }
    Post *newPost = (Post *)malloc(sizeof(Post));
    newPost->text = (char *)malloc(300);
    newPost->writer = (char *)malloc(300);
    Post *curr = findPostEnd(logged_in_user);
    strcpy(newPost->text, text);
    strcpy(newPost->writer, logged_in_user->name);
    newPost->likes = 0;
    newPost->postId = curr->postId + 1;
    newPost->nextPost = NULL;
    curr->nextPost = newPost;
    printf("posted succsesfully. \n");
    return 0;
}

int logout(User **logged_in_user)
{
    if (*logged_in_user == NULL)
    {
        printf("no one is logged in.\n");
        return 1;
    }
    *logged_in_user = NULL;
    printf("logout succsefull\n");
    return 0;
}

int postPrint(Post *somePost)
{
    printf("user: %s \n", somePost->writer);
    printf("post id: %d \n", somePost->postId);
    printf("likes: %d \n", somePost->likes);
    printf("post: %s \n", somePost->text);
}

int show_user_info(User *logged_in_user)
{
    if (logged_in_user == NULL)
    {
        printf("aint nobody logged in bro.\n");
        return 1;
    }
    printf("name: %s \n", logged_in_user->name);
    printf("pass: %s \n", logged_in_user->pass);
    Post *curr = logged_in_user->usersPosts->nextPost;
    if (curr == NULL)
        printf("user has no posts\n");
    while (curr != NULL)
    {
        printf("--\n");
        postPrint(curr);
        curr = curr->nextPost;
    }
}

int findPrintUser(User *head, char *name)
{
    User *curr = head;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
        {
            Post *currPost = curr->usersPosts->nextPost;
            if (currPost == NULL)
                printf("user has no posts\n");
            while (currPost != NULL)
            {
                printf("---\n");
                postPrint(currPost);
                currPost = currPost->nextPost;
            }
            return 0;
        }
        curr = curr->nextUser;
    }
    printf("user was not found bro\n");
    return 1;
}

int delete_post(User *logged_in_user, int postId)
{
    if (logged_in_user == NULL)
    {
        printf("no one is logged in.\n");
        return 1;
    }
    Post *previous_post = findPreviousPost(logged_in_user->usersPosts, postId);
    Post *deleting_post = findPost(logged_in_user->usersPosts, postId);
    previous_post->nextPost = deleting_post->nextPost;
    free(deleting_post);
    printf("deleted succsesfully.\n");
    return 0;
}

int is_liked(User *logged_in_user, Post *likedPost)
{
    LP *curr = logged_in_user->likedPosts->nextLP;
    while (curr != NULL)
    {
        if ((curr->post) == likedPost)
            return 1;
        curr = curr->nextLP;
    }
    return 0;
}

int like_post(char *name, int postId, User *logged_in_user, User *head)
{
    if (logged_in_user == NULL)
    {
        printf("no one is logged in.\n");
        return 1;
    }
    User *likedUser = find(head, name);
    if (likedUser == NULL)
    {
        printf("username does not exist.\n");
        return 2;
    }
    Post *likedPost = findPost(likedUser->usersPosts, postId);
    if (likedPost == NULL)
    {
        printf("post does not exist.\n");
        return 3;
    }
    if (is_liked(logged_in_user, likedPost) == 1)
    {
        printf("youve already liked that post before!\n");
        return 4;
    }
    LP *newLikedPost = (LP *)malloc(sizeof(LP));
    newLikedPost->nextLP = NULL;
    newLikedPost->post = likedPost;
    likedPost->likes++;
    findLikedEnd(likedUser)->nextLP = newLikedPost;
    printf("post liked suucsesfully.\n");
    return 0;
}

int command(char *cmd)
{
    if (!strcmp(cmd, "signup"))
        return 0;
    if (!strcmp(cmd, "login"))
        return 1;
    if (!strcmp(cmd, "logout"))
        return 3;
    if (!strcmp(cmd, "post"))
        return 2;
    if (!strcmp(cmd, "delete"))
        return 6;
    if (!strcmp(cmd, "info"))
        return 4;
    if (!strcmp(cmd, "find_user"))
        return 5;
    if (!strcmp(cmd, "like"))
        return 7;
    return -1;
}

char *input(char *cmdstr)
{
    char inp_tmp = 's';
    int i = 0;
    while (1)
    {
        inp_tmp = getchar();
        if (inp_tmp == ' ' || inp_tmp == '\n')
            break;
        *(cmdstr + i) = inp_tmp;
        i++;
        cmdstr = (char *)realloc(cmdstr, i + 1);
    }
    // add null car
    cmdstr[i] = '\0';
    return cmdstr;
}

char *inputPost(char *cmdstr)
{
    char inp_tmp = 's';
    int i = 0;
    while (1)
    {
        inp_tmp = getchar();
        if (inp_tmp == '\n')
            break;
        *(cmdstr + i) = inp_tmp;
        i++;
        cmdstr = (char *)realloc(cmdstr, i + 1);
    }
    // add null car
    cmdstr[i] = '\0';
    return cmdstr;
}
