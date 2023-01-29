#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int main()
{
    User *logged_in_user = (User *)malloc(sizeof(User));
    logged_in_user = NULL;

    // Usershead
    User *usersHead = (User *)malloc(sizeof(User));
    usersHead->name = (char *)malloc(2);
    usersHead->pass = (char *)malloc(2);
    strcpy(usersHead->name, "s");
    strcpy(usersHead->pass, "s");
    usersHead->nextUser = NULL;

    while (1)
    {
        // command
        char *cmdstr = (char *)malloc(1);
        cmdstr = input(cmdstr);
        int cmd = command(cmdstr);
        free(cmdstr);
        if (cmd == 0)
        {
            // signup
            char *name = (char *)malloc(1);
            char *pass = (char *)malloc(1);
            name = input(name);
            pass = input(pass);
            signup(usersHead, name, pass, logged_in_user);
            free(name);
            free(pass);

            // post head
            Post *postsHead = (Post *)malloc(sizeof(Post));
            postsHead->text = (char *)malloc(2);
            postsHead->writer = (char *)malloc(2);
            strcpy(postsHead->text, "s");
            strcpy(postsHead->writer, "s");
            postsHead->likes = 0;
            postsHead->postId = 0;
            postsHead->nextPost = NULL;
            findEnd(usersHead)->usersPosts = postsHead;

            // likedposts head
            LP *LPHead = (LP *)malloc(sizeof(LP));
            LPHead->post = NULL;
            LPHead->nextLP = NULL;
            findEnd(usersHead)->likedPosts = LPHead;
        }
        else if (cmd == 1)
        {
            // login
            char *name = (char *)malloc(1);
            char *pass = (char *)malloc(1);
            name = input(name);
            pass = input(pass);
            login(usersHead, &logged_in_user, name, pass);
            free(name);
            free(pass);
        }
        else if (cmd == 2)
        {
            // posting
            char *text = (char *)malloc(1);
            text = inputPost(text);
            submit_post(logged_in_user, text);
            free(text);
        }
        else if (cmd == 3)
        {
            // logout
            logout(&logged_in_user);
        }
        else if (cmd == 4)
        {
            show_user_info(logged_in_user);
        }
        else if (cmd == 5)
        {
            char *name = (char *)malloc(1);
            name = input(name);
            findPrintUser(usersHead, name);
            free(name);
        }
        else if (cmd == 6)
        {
            int postid;
            scanf("%d", &postid);
            delete_post(logged_in_user, postid);
        }
        else if (cmd == 7)
        {
            char *name = (char *)malloc(1);
            int postid;
            name = input(name);
            scanf("%d", &postid);
            like_post(name, postid, logged_in_user, usersHead);
            free(name);
        }
        else
            printf("unknown command.\n");
    }
}