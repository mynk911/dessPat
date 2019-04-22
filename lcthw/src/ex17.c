///
/// \file ex17.c
/// \brief ex 17 heap and stack memory
/// \author Mayank Bansal
///

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "lcthw.h"
#include "ex17_ds.h"

#define TESTING

#ifdef TESTING
void * my_malloc(size_t size);
#define malloc my_malloc
#endif


void die(const char* message)
{
    if(errno)
    {
        perror(message);
    }
    else
    {
        fprintf(stderr, "ERROR: %s\n", message);
    }
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    size_t rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die("Failed to load database.");
}

struct Connection* Database_open(const char* filename, char mode)
{
    struct Connection* conn = malloc(sizeof(struct Connection));
    if(!conn)
        die("Cannot create Connection");

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db)
        die("Cannot create Database");

    if(mode == 'c')
    {
        conn->file = fopen(filename, "wb");
    } else {
        conn->file = fopen(filename, "rb+");

        if(conn->file)
            Database_load(conn);
    }

    if(!conn->file)
        die("failed to open file");

    return conn;
}

void Database_close(struct Connection* conn)
{
    if(conn)
    {
        if(conn->file)
            fclose(conn->file);
        if(conn->db)
            free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection* conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1)
        die("Failed to write database");

    fflush(conn->file);
    if(rc == -1)
        die("Cannot flush database");
}

void Database_create(struct Connection* conn)
{
    int i = 0;

    for (i = 0; i < MAX_ROWS; ++i) {
        struct Address addr = {.id = i, .set = 0};
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char* name, 
        const char* email)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set)
        die("Already set, delete it first");

    addr->set = 1;
    char* res = strncpy(addr->name, name, MAX_DATA);
    if(!res)
        die("name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res)
        die("email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("Id not set");
    }
}

void Database_delete(struct Connection* conn, int id)
{
    struct Address addr = {.id=0 , .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection* conn)
{
    struct Database* db = conn->db;

    for(int i = 0; i < MAX_ROWS; i++)
    {
        struct Address* curr = &db->rows[i];

        if(curr->set)
            Address_print(curr);
    }
}

int ex17(int argc,const char *argv[])
{
    if(argc < 3)
        die("USAGE: dessPat <dbfile> <action> [action param]");

    const char* filename = argv[1];
    char action = argv[2][0];
    struct Connection* conn = Database_open(filename, action);
    int id = 0;

    if(argc  > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("there are not that many records");

    switch(action)
    {
        case 'c' : 
            Database_create(conn);
            Database_write(conn);
            break;
        case 'g' :
            if(argc != 4)
                die("need an id to get");
            Database_get(conn, id);
            break;
        case 's':
            if(argc != 6)
                die("need id, name and email to set");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
        case 'd':
            if(argc != 4)
                die("need id to delete");
            Database_delete(conn, id);
            Database_write(conn);
            break;
        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action c=create, g=get, s=set, d=delete, l=list");
    }
    Database_close(conn);

    return 0;
}
