#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>

#include "dessPatConfig.h"
#include "dbg.h"
#include "c_utils.h"

#include "lcthw.h"
#include "ex17_ds.h"

#ifdef C_SERVICE_MOCK_TESTS
#include "FakeServices.h"

#define malloc my_malloc
#define fopen my_fopen

#endif // C_SERVICE_MOCK_TESTS

int ex1(FILE* out)
{
    int distance = 100;

    fprintf(out, "You are %d miles away.\n", distance);

    return 0;
}


int ex3(FILE* out)
{
    int age = 23;
    int height = 74;

    fprintf(out, "I am %d years old.\n", age);
    fprintf(out, "I am %d inches tall.\n", height);

    return 0;
}

int ex7(FILE* out)
{
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";

    fprintf(out, "You are %d miles away.\n", distance);
    fprintf(out, "You have %f levels of power.\n", power);
    fprintf(out, "You have %f awesome super powers.\n", super_power);
    fprintf(out, "I have an initial %c.\n", initial);
    fprintf(out, "I have a first name %s.\n", first_name);
    fprintf(out, "I have a last name %s.\n", last_name);
    fprintf(out, "My whole name is %s %c %s.\n",
	    first_name, initial, last_name);

    int bugs = 100;
    double bug_rate = 1.2;

    fprintf(out, "You have %d bugs at the imaginary rate of %f.\n",
	    bugs, bug_rate);

    unsigned long universe_of_defects = 1UL * 1024L * 1024L * 1024L;
    fprintf(out, "The entire universe has %lu bugs.\n", universe_of_defects);

    double expected_bugs = bugs * bug_rate;
    fprintf(out, "You are expected to have %f bugs.\n", expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    fprintf(out, "That is only a %e portion of the universe.\n",
						part_of_universe);

    //this makes no sense, just a demo of something weird
    char nul_byte = '\0';
    int care_percentage = bugs * nul_byte;
    fprintf(out, "Which means you should care %d%%.\n", care_percentage);
    return 0;
}

int ex8(int argc,const char *argv[], FILE* out)
{
    int i = 0;

    // since executable is at index 0, argc > 1 if arguments given
    if (argc == 1)
    {
	fprintf(out, "You only have one argument. You suck.\n");
    }
    else if (argc > 1 && argc < 4)
    {
	fprintf(out, "Here's your arguments:\n");

	for (i = 0; i < argc; i++)
	{
	    fprintf(out, "%s ", argv[i]);
	}
    }
    else
    {
	fprintf(out, "You have too many arguments. You suck.\n");
    }

    return 0;
}

int ex9(FILE* out)
{
    int i = 0;

    while (i < 25) {
	fprintf(out, "%d ", i);
	i++;
    }
    fprintf(out, "\n");

    return 0;
}

int ex10(int argc,const char *argv[], FILE* out)
{
    if (argc != 2) {
	fprintf(out, "ERROR: You need one argument.\n");
	return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
	char letter = argv[1][i];

	switch (letter) {
	case 'a':
	case 'A':
	    fprintf(out, "%d: 'A'\n", i);
	    break;

	case 'e':
	case 'E':
	    fprintf(out, "%d: 'E'\n", i);
	    break;

	case 'i':
	case 'I':
	    fprintf(out, "%d: 'I'\n", i);
	    break;

	case 'o':
	case 'O':
	    fprintf(out, "%d: 'O'\n", i);
	    break;

	case 'u':
	case 'U':
	    fprintf(out, "%d: 'U'\n", i);
	    break;

	case 'y':
	case 'Y':
	    if (i > 2) {
		// it's only sometimes Y
		fprintf(out, "%d: 'Y'\n", i);
	    }
	    break;

	default:
	    fprintf(out, "%d: %c is not a vowel\n", i, letter);
	}
    }

    return 0;
}

int ex11(FILE* out)
{
    int numbers[4] = { 0 };
    char name[4] = { 'a'};
    unsigned int x = (97 << 24) + (68 << 16) + (90 << 8) + 121;
    char y[4];
    memcpy(y,&x,4);
    // first, print them out raw
    fprintf(out, "numbers: %d %d %d %d\n",
	   numbers[0], numbers[1], numbers[2], numbers[3]);

    fprintf(out, "name each: %d %d %d %d\n",
	   name[0], name[1], name[2], name[3]);

    fprintf(out, "name each: %c %c %c %c\n",
	   y[0], y[1], y[2], y[3]);

    x = UINT_MAX;
    memcpy(y,&x,4);
    fprintf(out, "name each: %c %c %c %c\n",
	   y[0], y[1], y[2], y[3]);

    fprintf(out, "name: %s\n", name);

    // setup the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    // setup the name
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    // then print them out initialized
    fprintf(out, "numbers: %d %d %d %d\n",
	   numbers[0], numbers[1], numbers[2], numbers[3]);

    fprintf(out, "name each: %c %c %c %c\n",
	   name[0], name[1], name[2], name[3]);

    // print the name like a string
    fprintf(out, "name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    fprintf(out, "another: %s\n", another);

    fprintf(out, "another each: %c %c %c %c\n",
	   another[0], another[1], another[2], another[3]);

    return 0;
}

int ex12(FILE *out)
{
    char full_name[] = {
	'Z', 'e', 'd',
	' ', 'A', '.', ' ',
	'S', 'h', 'a', 'w' , '\0'
    };
    int areas[] = { 10, 12, 13, 14, 20 };
    char name[] = "Zed";


    // WARNING: On some systems you may have to change the
    // %ld in this code to a %u since it will use unsigned ints
    fprintf(out, "The size of an int: %zu\n", sizeof(int));
    fprintf(out, "The size of areas (int[]): %zu\n" , sizeof(areas));
    fprintf(out, "The number of ints in areas: %zu\n",
	    sizeof(areas) / sizeof(int));
    fprintf(out, "The first area is %u, the 2nd %u.\n", areas[0], areas[1]);

    fprintf(out, "The size of a char: %zu\n", sizeof(char));
    fprintf(out, "The size of name (char[]): %zu\n", sizeof(name));
    fprintf(out,"The number of chars: %zu\n", sizeof(name) / sizeof(char));

    fprintf(out,"The size of full_name (char[]): %zu\n", sizeof(full_name));
    fprintf(out, "The number of chars: %zu\n",
	    sizeof(full_name) / sizeof(char));

    //full_name[12] = 'X';

    fprintf(out, "name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}

int ex13(int argc,const char *argv[], FILE* out)
{
    int i = 0;
    // let's make our own array of strings
    char *states[] = {
	"California", "Oregon",
	"Washington", "Texas"
    };

    int num_states = 4;

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1; i < argc; i++) {
	fprintf(out, "arg %d: %s\n", i, argv[i]);
    }


    for (i = 0; i < num_states; i++) {
	fprintf(out, "state %d: %s\n", i, states[i]);
    }

    return 0;
}

//forward declarations
int can_print_it(char ch);
void print_letters(const char arg[],size_t n, FILE* out);

void print_arguments(int argc,const char *argv[], FILE* out)
{
    int i = 0;

    for (i = 0; i < argc; i++) {
	print_letters(argv[i],strlen(argv[i]), out);
    }
}

void print_letters(const char arg[], size_t n, FILE* out)
{
    size_t i = 0;

    for (i = 0; i<n; i++) {
	char ch = arg[i];

	if (can_print_it(ch)) {
	    fprintf(out, "%c", ch);
	}
    }
	fprintf(out, "\n");
}

int can_print_it(char ch)
{
    return isalpha((unsigned char)ch) ||
	   isblank((unsigned char)ch);
}

int ex14(int argc,const char *argv[], FILE* out)
{
    print_arguments(argc, argv, out);
    return 0;
}

int ex15(FILE* out)
{
	// create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
	"Alan", "Frank",
	"Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
	fprintf(out, "%s has %d years alive.\n", names[i], ages[i]);
    }

    fprintf(out, "---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < count; i++) {
	fprintf(out, "%s has %d years alive.\n",
		*(cur_name + i), *(cur_age + i));
    }

    fprintf(out, "---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
	fprintf(out, "%s has %d years alive.\n", cur_name[i], cur_age[i]);
    }

    fprintf(out, "---\n");

    // fourth way with pointers in a stupid complex way
    for (cur_name = names, cur_age = ages;
	    (cur_age - ages) < count; cur_name++, cur_age++) {
	fprintf(out, "%s has %d years alive.\n", *cur_name, *cur_age);
    }

    return 0;
}

struct Person {
    char* name;
    int age;
    int height;
    int weight;
};

struct Person* CreatePerson(const char* n, int a, int h, int w)
{
    struct Person* who = (struct Person*) malloc(sizeof(struct Person));
    assert(who != NULL);

    size_t length = strlen(n) + 1;
    who->name = (char *) malloc(length);
    strcpy(who->name, n);

    who->age = a;
    who->height = h;
    who->weight = w;

    return who;
}

void DestroyPerson(struct Person** p)
{
    assert(*p != NULL);
    free((*p)->name);
    free(*p);
    *p = NULL;
}

void PrintPerson(FILE* out, struct Person* p)
{
    fprintf(out, "Name : %s\n", p->name);
    fprintf(out, "Age : %d\n", p->age);
    fprintf(out, "Height : %d\n", p->height);
    fprintf(out, "Weight : %d\n", p->weight);
}

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

int Address_print(char* buf, struct Address *addr)
{
    return sprintf(buf, "%d %s %s\n", addr->id, addr->name, addr->email);
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

void Database_get(struct Connection *conn,char* buf, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
	Address_print(buf, addr);
    } else {
	die("Id not set");
    }
}

void Database_delete(struct Connection* conn, int id)
{
    struct Address addr = {.id=0 , .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection* conn, char* buf)
{
    struct Database* db = conn->db;

    size_t length = 0;
    for(int i = 0; i < MAX_ROWS; i++)
    {
	struct Address* curr = &db->rows[i];

	if(curr->set)
	    length += Address_print(buf + length, curr);
    }
}

int ex17(int argc,const char *argv[], char* buf)
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
	    Database_get(conn, buf, id);
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
	    Database_list(conn, buf);
	    break;
	default:
	    die("Invalid action c=create, g=get, s=set, d=delete, l=list");
    }
    Database_close(conn);

    return 0;
}

int* bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0, i = 0, j = 0;

    int *target = malloc(count * sizeof(int));
    if (!target) die("Memory Error!");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            if (cmp(target[j], target[j + 1]) > 0)
                swap(target+j,target+j+1);
        }
    }
    return target;
}

int* selection_sort(int* numbers, int count, compare_cb cmp)
{
    int temp = 0, i = 0, j = 0, mindex = 0;

    int* target = malloc(count * sizeof(int));
    if (!target) die("Memory Error!");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count - 1; i++)
    {
        mindex = i;
        for (j = i + 1; j < count; j++)
        {
            if (cmp(target[mindex], target[j]) > 0)
                mindex = j;
        }
        swap(target+i,target+mindex);
    }
    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reversed_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if (a == 0 || b == 0)
	return 0;
    else
	return a % b;
}

int ex18(int argc,const char** argv, char* buf, sort_cb sort, compare_cb cmp)
{
    if (argc < 2) die("USAGE: dessPat 1 2 4 3 5 ..");

    int count = argc - 1;
    const char** inputs = argv + 1;

    int* numbers = malloc(sizeof(int) * count);
    if (!numbers) die("Memory Error");

    for (int i = 0; i < count; i++)
	numbers[i] = atoi(inputs[i]);

    int *sorted = sort(numbers, count, cmp);
    if (!sorted) die("Failed to sort");

    int length  = 0;
    for (int i = 0; i < count; i++)
        length += sprintf(buf + length, "%d ", sorted[i]);
    length += sprintf(buf + length, "\n");

    free(sorted);

// Prints out cmp function from read only memory
//    unsigned char* data = (unsigned char*) cmp;

//    for (int i = 0; i < 25; i++)
//    {
//    printf("%02x:", data[i]);
//    }
//    printf("\n");
    free(numbers);

    return 0;
}

int test_check(char* file_name)
{
    FILE* input = NULL;
    char* block = NULL;

    block = malloc(100);
    check_mem(block);

    input = fopen(file_name, "r");
    check(input, "Failed to open %s.", file_name);

    free(block);
    fclose(input);
    return 0;

error:
    if (block) free(block);
    if (input) fclose(input);
    return -1;
}

int test_sentinel(int code)
{
    char* temp = malloc(100);
    check_mem(temp);

    switch (code)
    {
    case 1 :
	log_info("it worked.");
	break;
    default:
	sentinel("I shouldn't run.");
    }

    free(temp);
    return 0;

error:
    if (temp)
	free(temp);
    return -1;
}

int test_check_mem()
{
    char* test = NULL;
    check_mem(test);

    free(test);
    return 0;
error:
    return -1;
}

int test_check_debug()
{
    int i = 0;
    check_debug(i != 0, "Oops I was zero.");
    return 0;
error:
    return -1;
}

int ex19(int argc, const char *argv[])
{
    check(argc > 2, "Need an argument.");

    debug("I have brown hair.");
    debug("I am %d years old.", 24);
    log_err("I believe everything is broken");
    log_err("There are %d problems im %s", 0, "space");
    log_warn("You can safely ignore this");
    log_warn("Maybe Consider looking at %s.", "/etc/passwd");
    log_info("Well I did something mundane");
    log_info("It happened %f times today", 1.3f);

    check(test_check("CMakeCache.txt") == 0, "failed with ex19.c");
    check(test_check(argv[1]) == -1, "failed with argv");
    check(test_sentinel(1) == 0, "test_sentinel failed");
    check(test_sentinel(100) == -1, "test_sentinel failed");
    check(test_check_mem() == -1, "test_check_mem failed");
    check(test_check_debug() == -1, "test_check_debug failed");

    return 0;
error:
    return 1;
}

#include "ex22.h"

const char* MY_NAME = "Mayank Bansal";

void scope_demo(int count)
{
    log_info("count is %d", count);
    if (count > 10) {
	int count = 100;
	log_info("count in this scope is %d", count);
    }
    log_info("count is at exit : %d", count);
    count = 3000;
    log_info("count after assign: %d", count);
}

int ex22()
{
    //extra
    int* x = age();
    *x = 25000;
    log_info("My name: %s age: %d", MY_NAME, get_age());
    set_age(100);
    log_info("My age is now: %d", get_age());
    log_info("The size is now: %d", THE_SIZE);
    print_size();
    THE_SIZE = 9;
    log_info("The size is now: %d", THE_SIZE);
    print_size();
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);
    log_info("count after calling scope_demo: %d", count);

    return 0;
}

int normal_copy(char* from, char* to, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
	to[i] = from[i];
    }
    return i;
}

int duffs_device(char* from, char* to, int count)
{
    int n = (count + 7) / 8;
    switch (count % 8) {
    case 0:
	do {
	    *to++ = *from++;
    case 7:
	*to++ = *from++;
    case 6:
	*to++ = *from++;
    case 5:
	*to++ = *from++;
    case 4:
	*to++ = *from++;
    case 3:
	*to++ = *from++;
    case 2:
	*to++ = *from++;
    case 1:
	*to++ = *from++;
	}  while (--n > 0);
    }
    return count;
}

int valid_copy(char* data, int count, int expects)
{
    int i = 0;
    for(i = 0; i < count; i++)
    {
	if (data[i] != expects) {
	    log_err("[%d] %c != %c", i, data[i], expects);
	    return 0;
	}
    }
    return 1;
}

int ex23(int argc, char* argv[])
{
    char from[1000] = { 'a' };
    char to[1000] = { 'c' };
    int rc = 0;

    memset(from, 'x', 1000);
    memset(to, 'y', 1000);
    check(valid_copy(to, 1000, 'y'), "Not initialized correctly.");
    rc = normal_copy(from, to, 1000);
    check(rc == 1000, "Normal copy failed.");
    check(valid_copy(to, 1000, 'x'), "Normal copy failed");
    memset(to, 'y', 1000);
    rc = duffs_device(from, to, 1000);
    check(rc == 1000, "Duffs device failed");
    check(valid_copy(to, 1000, 'x'), "Duffs Device failed");

    return 0;

error:
    return 1;
}


typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES, BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue","Green","Brown", "Black", "Other"
};

typedef struct Person2 {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person2;

int ex24(int argc, char* argv[])
{
    Person2 you;
    int i = 0;
    char* in = NULL; int rc;
    printf("fn");
    in = fgets(you.first_name, MAX_DATA - 1, stdin);
    //in = gets(you.first_name);
    check(in != NULL, "fn failed");
    //rc = fscanf(stdin, "%s", &you.first_name);
    //check(rc > 0, "fn failed : enter string");

    printf("ln");
    in = fgets(you.last_name, MAX_DATA - 1, stdin);
    check(in != NULL, "ln failed");
    //rc = fscanf(stdin, "%50s", &you.last_name);
    //check(rc > 0, "ln failed : enter string");

    printf("age");
    rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "age failed : enter number");

    printf("eye color");
    for (i = 0; i <= OTHER_EYES; i++) {
	printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "eye colr failed : enter number");
    you.eyes = eyes - 1;
    check(you.eyes >= 0 && you.eyes <= OTHER_EYES, "eye color failed : invalid eye color");

    printf("income");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "income failed : enter floating point number");

    printf("you : %s %s %d %s %f\n", you.first_name, you.last_name, you.age, EYE_COLOR_NAMES[you.eyes], you.income);

    return 0;
error:
    return -1;
}


int read_string(char** out_string, int max_buffer)
{
    *out_string = calloc(1, max_buffer - 1);
    check_mem(*out_string);
    char* result = fgets(*out_string, max_buffer, stdin);
    check(result != NULL, "input error");
    return 0;
error:
    if (*out_string)
	free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(int* out_int)
{
    char* input = NULL;
    int rc = read_string(&input, MAX_DATA);
    check(rc == 0, "failed to read number");
    *out_int = atoi(input);
    free(input);
    return 0;
error:
    if (input)
	free(input);
    return -1;
}

int read_scan(const char* fmt, ...)
{
    int i = 0;
    int rc = 0;
    int* out_int = NULL;
    char* out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    va_list argp;
    va_start(argp, fmt);
    for (i = 0; fmt[i] != '\0'; i++)
    {
	if (fmt[i] == '%')
	{
	    i++;
	    switch (fmt[i])
	    {
	    case '\0':sentinel("Invalid format. you ended with %%");
		break;
	    case 'd': out_int = va_arg(argp, int*);
		rc = read_int(out_int);
		check(rc == 0, "Failed to read int");
		break;
	    case 'c': out_char = va_arg(argp, char*);
		*out_char = fgetc(stdin);
		break;
	    case's': max_buffer = va_arg(argp, int);
		out_string = va_arg(argp, char**);
		rc = read_string(out_string, max_buffer);
		check(rc == 0, "failed to read string");
		break;
	    default: sentinel("Invalid format");
	    }
	}
	else {
	    fgetc(stdin);
	}
	check(!feof(stdin) && !ferror(stdin), "Input error");
    }
    va_end(argp);
    return 0;
error:
    va_end(argp);
    return -1;
}

int ex25(int argc, char* argv[])
{
    char* first_name = NULL;
    char initial = ' ';
    char* last_name = NULL;
    int age = 0;

    int rc = read_scan("%s", MAX_DATA, &first_name);
    check(rc == 0, "failed fn");
    rc = read_scan("%c\n", &initial);
    check(rc == 0, "failed initial");
    rc = read_scan("%s", MAX_DATA, &last_name);
    check(rc == 0, "failed ln");
    rc = read_scan("%d", &age);
    check(rc == 0, "failed age");

    printf("guy : %s %c %s %d", first_name, initial, last_name, age);
    free(first_name);
    free(last_name);
    return 0;
error:
    return -1;
}
