#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

#include "dessPatConfig.h"
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
    int i = 0, j = 0;

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
    int i = 0, j = 0, mindex = 0;

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

int test_check(const char* file_name)
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

int THE_SIZE = 1000;

static int THE_AGE = 24;

int get_age()
{
    return THE_AGE;
}

int * age()
{
    return &THE_AGE;
}

void set_age(int age)
{
    THE_AGE = age;
}

double update_ratio(double new_ratio)
{
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

int get_size()
{
    return THE_SIZE;
}

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


typedef enum EyeColor {
    BLUE_EYES,
    GREEN_EYES,
    BROWN_EYES,
    BLACK_EYES,
    OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue",
    "Green",
    "Brown",
    "Black",
    "Other"
};

typedef struct Person2 {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person2;

int ex24(FILE* inp, FILE* out)
{
    Person2 you;
    int i = 0;
    char* in = NULL; int rc;
    printf("fn");
    in = fgets(you.first_name, MAX_DATA - 1, inp);
    check(in != NULL, "fn failed");

    printf("ln");
    in = fgets(you.last_name, MAX_DATA - 1, inp);
    check(in != NULL, "ln failed");

    printf("age");
    rc = fscanf(inp, "%d", &you.age);
    check(rc > 0, "age failed : enter number");

    printf("eye color");
    for (i = 0; i <= OTHER_EYES; i++) {
	printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    int eyes = -1;
    rc = fscanf(inp, "%d", &eyes);
    check(rc > 0, "eye colr failed : enter number");
    you.eyes = eyes - 1;
    check(you.eyes >= 0 && you.eyes <= OTHER_EYES, "eye color failed : invalid eye color");

    printf("income");
    rc = fscanf(inp, "%f", &you.income);
    check(rc > 0, "income failed : enter floating point number");

    fprintf(out, "you : %s %s %d %s %f\n", you.first_name, you.last_name, you.age,
	    EYE_COLOR_NAMES[you.eyes], you.income);

    return 0;
error:
    return -1;
}


int read_string(FILE* in, char** out_string, int max_buffer)
{
    *out_string = calloc(1, max_buffer - 1);
    check_mem(*out_string)
    char* result = fgets(*out_string, max_buffer, in);
    check(result != NULL, "input error")
    return 0;
error:
    if (*out_string)
	free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(FILE* in, int* out_int)
{
    char* input = NULL;
    int rc = read_string(in, &input, MAX_DATA);
    check(rc == 0, "failed to read number");
    *out_int = atoi(input);
    free(input);
    return 0;
error:
    if (input)
	free(input);
    return -1;
}

int read_scan(FILE* in, const char* fmt, ...)
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
        case '\0':sentinel("Invalid format. you ended with %%")
		break;
	    case 'd': out_int = va_arg(argp, int*);
		rc = read_int(in, out_int);
        check(rc == 0, "Failed to read int")
		break;
	    case 'c': out_char = va_arg(argp, char*);
		*out_char = fgetc(in);
		break;
	    case's': max_buffer = va_arg(argp, int);
		out_string = va_arg(argp, char**);
		rc = read_string(in, out_string, max_buffer);
        check(rc == 0, "failed to read string")
		break;
        default: sentinel("Invalid format")
	    }
	}
	else {
	    fgetc(in);
	}
    check(!feof(in) && !ferror(in), "Input error")
    }
    va_end(argp);
    return 0;
error:
    va_end(argp);
    return -1;
}

List *List_create()
{
    return calloc(1, sizeof (List));
}

void List_destroy(List* list)
{
    LIST_FOREACH(list,first,next,cur)
	if(cur->prev)
	    free(cur->prev);
    free(list->last);
    free(list);
}

void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur)
	    free(cur->value);
}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, const void* value)
{
    ListNode* node = calloc(1, sizeof(ListNode));
    check_mem(node)

    node->value = value;

    if(list->last == NULL)
    {
	list->first = node;
	list->last = node;
    } else {
	list->last->next = node;
	node->prev = list->last;
	list->last = node;
    }
    list->count++;
error:
    return;
}

const void* List_pop(List* list)
{
    ListNode* node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void  List_unshift(List* list, const void* value)
{
    ListNode* node = calloc(1, sizeof(ListNode));
    check_mem(node)
    node->value = value;

    if(list->first == NULL)
    {
	list->first = node;
	list->last = node;
    } else {
	list->first->prev = node;
	node->next = list->first;
	list->first = node;
    }
    list->count++;
error:
    return;
}

const void* List_shift(List* list)
{
    ListNode* node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

const void* List_remove(List* list, ListNode* node)
{
    const void* result = NULL;

    check(list->first && list->last, "list is empty")
    check(node, "node can't be null")

    if(node == list->first)
    {
	if(node == list->last)
	{
	    list->first = NULL;
	    list->last = NULL;
	} else {
	    list->first = node->next;
        check(list->first != NULL, "invalid list")
	    list->first->prev = NULL;
	}
    } else if(node == list->last)
    {
	list->last = node->prev;
    check(list->last != NULL , "invalid list")
	list->last->next = NULL;
    } else {
	node->next->prev = node->prev;
	node->prev->next = node->next;
    }
    list->count--;
    result = node->value;
    free(node);
error:
    return result;
}

int List_bubble_sort(List *list, ListCompare cmp)
{
    for(ListNode* s = list->last; s != list->first; s = s->prev)
        for(ListNode* t = list->first; t != s; t = t->next )
            if(cmp(t->value, t->next->value) > 0)
            {
                const void* temp = t->next->value;
                t->next->value = t->value;
                t->value = temp;
            }

    return 0;
}

List* List_merge(List* left, List* right, ListCompare cmp)
{
    List* result = List_create();
    while(left->count > 0 && right->count > 0)
    {
        if(cmp(left->first->value, right->first->value) < 0)
            List_push(result, List_shift(left));
        else
            List_push(result, List_shift(right));
    }

    while(left->count > 9)
        List_push(result, List_shift(left));

    while(right->count > 0)
        List_push(result, List_shift(right));

    return result;
}

List* List_merge_sort(List *list, ListCompare cmp)
{
    // basic case
    if(list->count <= 1) return list;

    size_t middle = list->count / 2;
    List* left = List_create();
    List* right = List_create();

    ListNode* curr = list->first;
    for(size_t i = 0; i < list->count; i++)
    {
        if(i < middle)
            List_push(left, curr->value);
        else
            List_push(right, curr->value);

        curr = curr->next;
    }

    List *sorted_left = List_merge_sort(left, cmp);
    List *sorted_right = List_merge_sort(right, cmp);

    if(left != sorted_left) List_destroy(left);
    if(right != sorted_right) List_destroy(list);

    return List_merge(sorted_left, sorted_right, cmp);
}

DArray *DArray_create(size_t element_size, size_t initial_max)
{
    DArray* array = malloc(sizeof (DArray));
    check_mem(array)
    array->max = initial_max;
    check(array->max > 0, "initial max must be greater than 0.")

    array->contents = calloc(initial_max, sizeof (void *));
    check_mem(array->contents)

    array->end = 0;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;
error:
    if(array)
      free(array);
    return NULL;
}


void DArray_clear(DArray *array)
{
    if(array->element_size > 0)
    {
        for(size_t i = 0; i < array->max; i++)
            if(array->contents[i] != NULL)
                free(array->contents[i]);
    }
}

static inline int DArray_resize(DArray* array, size_t new_size)
{
    array->max = new_size;
    check(array->max > 0, "new_size must be greater than 0.")

    void* contents = realloc(array->contents, (unsigned)array->max * sizeof (void *));
    check_mem(contents)

    array->contents = contents;
    return 0;
error:
    return -1;
}

int DArray_expand(DArray *array)
{
    size_t old_max = array->max;
    check(DArray_resize(array, array->max + array->expand_rate) == 0,
          "failed to expand to new size %zu", array->max + array->expand_rate)
    memset(array->contents + old_max, 0, array->expand_rate + 1);
    return 0;
error:
    return -1;
}

int DArray_contract(DArray *array)
{
    size_t new_size = array->end < array->expand_rate
            ? array->expand_rate
            : array->end;
    return DArray_resize(array, new_size + 1);
}

void DArray_destroy(DArray* array)
{
    if(array)
    {
        if(array->contents)
            free(array->contents);
        free(array);
    }
}

void DArray_clear_destroy(DArray* array)
{
    DArray_clear(array);
    DArray_destroy(array);
}


int DArray_push(DArray *array,const void *el)
{
    array->contents[array->end] = el;
    array->end++;

    if(DArray_end(array) >= DArray_max(array))
    {
        return DArray_expand(array);
    }
    else
    {
        return 0;
    }
}

const void* DArray_pop(DArray* array)
{
    check(array->end >= 1, "Attempt to pop from empty array.")
    const void* el = DArray_remove(array, array->end -1);
    array->end--;
    if(DArray_end(array) > array->expand_rate && DArray_end(array) % array->expand_rate)
    {
        DArray_contract(array);
    }

    return el;
error:
    return NULL;
}

size_t DArray_qsort_partition(DArray *array, size_t lo, size_t hi, DArray_compare cmp)
{
    const void* pivot = DArray_get(array, (lo + hi)/2);
    size_t i = lo -1; size_t j = hi + 1;
    while(1)
    {
        do {i++;} while(cmp(DArray_get(array, i), pivot) < 0);
        do {j--;} while(cmp(DArray_get(array, j), pivot) > 0);
        if(i >= j) return j;
        const void* temp = DArray_get(array, i);
        DArray_set(array, i, DArray_get(array, j));
        DArray_set(array, j, temp);
    }
}

void DArray_qsort_imp(DArray *array, size_t lo, size_t hi, DArray_compare cmp)
{
    if(lo < hi)
    {
        size_t p = DArray_qsort_partition(array, lo, hi, cmp);
        DArray_qsort_imp(array, lo , p, cmp);
        DArray_qsort_imp(array, p+1, hi, cmp);
    }
}

int DArray_qsort(DArray *array, DArray_compare cmp)
{
    //qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    DArray_qsort_imp(array, 0, DArray_count(array)-1, cmp);
    return 0;
}

void heapifyDown(DArray* array, size_t start, size_t end, DArray_compare cmp)
{
    size_t root = start;
    while(root * 2 + 1 <= end)
    {
        size_t left = root * 2 + 1;
        size_t swap = root;
        if(cmp(DArray_get(array, left), DArray_get(array, swap)) > 0)
            swap = left;

        if(left + 1 <= end && cmp(DArray_get(array, left+1), DArray_get(array, swap)) > 0)
            swap = left + 1;

        if(swap == root) return;

        const void* temp = DArray_get(array, root);
        DArray_set(array, root, DArray_get(array, swap));
        DArray_set(array, swap, temp);

        root = swap;
    }
}

void buildHeap(DArray* array, DArray_compare cmp)
{
    size_t start = (DArray_count(array) - 2)/2 + 1;
    while(start > 0)
    {
        heapifyDown(array, start-1, DArray_count(array)-1, cmp);
        start--;
    }
}

int DArray_hsort(DArray *array, DArray_compare cmp)
{
    buildHeap(array, cmp);
    size_t s = DArray_count(array)-1;
    while(s > 0)
    {
        const void* temp = DArray_get(array, s);
        DArray_set(array, s, DArray_get(array, 0));
        DArray_set(array, 0, temp);
        s--;
        heapifyDown(array, 0, s, cmp);
    }
    return 0;
}

void DArray_msort_merge(DArray* src, DArray* dst, size_t lo, size_t mid, size_t hi, DArray_compare cmp)
{
    size_t i = lo;
    size_t j = mid+1;

    for(size_t k = lo; k <= hi; k++)
    {
        if(i <= mid && (j > hi || cmp(DArray_get(src, i), DArray_get(src, j)) < 0))
        {
            DArray_set(dst, k, DArray_get(src, i));
            i++;
        }
        else
        {
            DArray_set(dst, k, DArray_get(src, j));
            j++;
        }
    }
}

void DArray_msort_imp(DArray* src, DArray* dst, size_t lo, size_t hi, DArray_compare cmp)
{
    if(hi - lo > 1)
    {
        size_t mid = (lo + hi)/2;
        DArray_msort_imp(dst, src, lo, mid, cmp);
        DArray_msort_imp(dst, src, mid+1, hi, cmp);
        DArray_msort_merge(src, dst, lo, mid, hi,  cmp);
    }
}
int DArray_msort(DArray *array, DArray_compare cmp)
{
    DArray *copy = DArray_create(sizeof (int), DArray_count(array));
    for(int i = 0; i < DArray_count(array); i++)
    {
        DArray_set(copy, i, DArray_get(array, i));
    }
    DArray_msort_imp(copy, array, 0, DArray_count(array)-1, cmp);
    return 0;
}

void Variant_print(Variant *var)
{
    switch(var->type)
    {
    case TYPE_INT:
        printf("INT: %d\n", var->data.as_integer);
        break;
    case TYPE_FLOAT:
        printf("FLOAT: %f\n", var->data.as_float);
        break;
    case TYPE_STRING:
        printf("STRING: %s\n", var->data.as_string);
        break;
    default :
        printf("UNKNOWN_TYPE: %d\n", var->type);
    }
}

RadixMap *RadixMap_create(size_t max)
{
    RadixMap* map = calloc(sizeof (RadixMap), 1);
    check_mem(map)
    map->contents = calloc(sizeof (RMElement), max + 1);
    check_mem(map->contents)
    map->temp = calloc(sizeof (RMElement), max + 1);
    check_mem(map->temp)
    map->max = max;
    map->end = 0;
    return map;
error:
    return NULL;
}

void RadixMap_destroy(RadixMap *map)
{
    if(map) {
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

#define ByteOf(x, y) (((uint8_t*)x)[(y)])

static inline void radix_sort(short offset, uint64_t max, uint64_t* source, uint64_t* dest)
{
    uint64_t count[256] = {0}, s = 0, c = 0,* cp = NULL, *sp = NULL, *end = NULL;

    // count occurence of every byte value
    for(sp = source, end = source+max; sp < end; sp++)
    {
        count[ByteOf(sp,offset)]++;
    }
    // transform count into index by summing
    // elements and storing into same array
    for(s = 0, cp = count, end = count + 256; cp < end; cp++)
    {
        c = *cp;
        *cp = s;
        s += c;
    }

    // fill dest with right value in right place
    for(sp = source, end = source + max; sp < end; sp++)
    {
        cp = count + ByteOf(sp, offset);
        dest[*cp] = *sp;
        ++(*cp);
    }
}
void RadixMap_sort(RadixMap *map)
{
    uint64_t* source = &map->contents[0].raw;
    uint64_t* temp = &map->temp[0].raw;

    radix_sort(0, map->max, source, temp);
    radix_sort(1, map->max, temp, source);
    radix_sort(2, map->max, source, temp);
    radix_sort(3, map->max, temp, source);
}

RMElement *
RadixMap_find(RadixMap *map,
                         uint32_t to_find,
                         size_t* lb)
{
    int low = 0, high = map->end - 1;
    RMElement* data = map->contents;

    while(low <= high)
    {
        int middle = low + (high - low)/2;
        uint32_t key = data[middle].data.key;

        if(to_find < key) high = middle - 1;
        else if(to_find > key) low = middle + 1;
        else return &data[middle];
    }
    *lb = low;
    return NULL;
}

int
RadixMap_add(RadixMap *map,
             uint32_t key,
             uint32_t value)
{
    check(key < UINT32_MAX, "key can't be equal to UINT32_MAX")
    RMElement element = {.data = {.key = key, .value = value}};

    check(map->end + 1 < map->max, "Radix map is full")
    map->contents[map->end++] = element;

    size_t lb;
    RadixMap_find(map, key, &lb);

    uint64_t* source = &map->contents[0].raw + lb;
    uint64_t* temp = &map->temp[0].raw + lb;

    radix_sort(0, map->max - lb, source, temp);
    radix_sort(1, map->max - lb, temp, source);
    radix_sort(2, map->max - lb, source, temp);
    radix_sort(3, map->max - lb, temp, source);
    return 0;
error:
    return -1;
}

int
RadixMap_delete(RadixMap *map,
                RMElement *el)
{
    check(map->end > 0, "There is nothing to delete")
    check(el != NULL, "can't delete a NULL element")

    el->data.key = UINT32_MAX;

    if(map->end > 1) RadixMap_sort(map);

    map->end--;

    return 0;
error:
    return -1;
}

static int default_compare(void* a, void* b)
{
    return bstrcmp((bstring) a, (bstring) b);
}

/** Bob Jenkin's hash algorithm
 */
static uint32_t
default_hash(void* a)
{
    size_t len = blength((bstring) a);
    char* key = bdata((bstring) a);
    uint32_t hash = 0, i = 0;

    for(hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

Hashmap*
Hashmap_create(Hashmap_compare compare,
               Hashmap_hash hash)
{
    Hashmap* map = calloc(1, sizeof (Hashmap));
    check_mem(map)

    map->compare = compare == NULL ? default_compare : compare;
    map->hash = hash == NULL ? default_hash : hash;
    map->buckets = DArray_create(sizeof(DArray *), DEFAULT_NUMBER_OF_BUCKETS);
    map->buckets->end = map->buckets->end = map->buckets->max;
    check_mem(map->buckets)

    return  map;
error:
    if(map) Hashmap_destroy(map);
    return NULL;
}

void
Hashmap_destroy(Hashmap* map)
{
    size_t i = 0, j = 0;

    if(map) {
        if(map->buckets) {
            for(i = 0; i < DArray_count(map->buckets); i++) {
                DArray *bucket = DArray_get(map->buckets, i);
                if(bucket) {
                    for(j = 0; j < DArray_count(bucket); j++) {
                        free(DArray_get(bucket, j));
                    }
                }
                DArray_destroy(bucket);
            }
            DArray_destroy(map->buckets);
        }
        free(map);
    }
}

static inline HashmapNode*
Hashmap_node_create(uint32_t hash,
                    void* key,
                    void* data)
{
    HashmapNode* node = calloc(1, sizeof (HashmapNode));
    check_mem(node)

    node->key = key;
    node->data = data;
    node->hash = hash;

    return node;

    error:
    return NULL;
}

static inline DArray*
Hashmap_find_bucket(Hashmap* map,
                    void* key,
                    int create,
                    uint32_t* hash_out)
{
    uint32_t hash = map->hash(key);
    size_t bucket_n = hash % DEFAULT_NUMBER_OF_BUCKETS;
    check(bucket_n >= 0, "invalid bucket found %lu", bucket_n)
    *hash_out = hash;
    DArray* bucket = DArray_get(map->buckets, bucket_n);

    if(!bucket && create) {
        //setup new bucket
        bucket = DArray_create(sizeof(void *), DEFAULT_NUMBER_OF_BUCKETS);
        check_mem(bucket)
        DArray_set(map->buckets, bucket_n, bucket);
    }

    return bucket;

    error:
    return NULL;
}

int Hashmap_set(Hashmap* map, void* key, void* data)
{
    uint32_t hash = 0;
    DArray* bucket = Hashmap_find_bucket(map, key, 1, &hash);
    check(bucket, "error can't create bucket")

    HashmapNode* node = Hashmap_node_create(hash, key, data);
    check_mem(node)

    DArray_push(bucket, node);

    return  0;
error:
    return -1;
}

static inline int Hashmap_get_node(Hashmap* map, uint32_t hash, DArray* bucket, void* key)
{
    size_t i = 0;

    for(i = 0; i < DArray_end(bucket); i++) {
        debug("TRY %lu", i);
        const HashmapNode* node = DArray_get(bucket, i);
        if(node->hash == hash && map->compare(node->key, key) == 0) return (int)i;
    }

    return -1;
}

void *
Hashmap_get(Hashmap* map,
                  void* key)
{
    uint32_t hash = 0;
    DArray* bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if(!bucket) return NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if(i == -1) return NULL;

    const HashmapNode* node = DArray_get(bucket, (size_t)i);
    check(node != NULL, "failed to get node from bucket when it should exist")

    return node->data;
error:
    return NULL;
}

int
Hashmap_traverse(Hashmap* map,
                 Hashmap_traverse_cb traverse_cb)
{
    size_t i, j;
    int rc;
    for(i = 0; i < DArray_count(map->buckets); i++) {
        DArray* bucket = (DArray *) DArray_get(map->buckets, i);
        if(bucket) {
            for(j = 0; j < DArray_count(bucket); j++) {
                HashmapNode* node = (HashmapNode* ) DArray_get(bucket, j);
                rc = traverse_cb(node);
                if(rc != 0) return  rc;
            }
        }
    }
    return 0;
}

void*
Hashmap_delete(Hashmap* map,
               void* key)
{
    uint32_t hash = 0;
    DArray* bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if(!bucket) return  NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if(i == -1) return  NULL;

    HashmapNode* node = DArray_get(bucket, (size_t)i);

    void* data = node->data;
    free(node);

    HashmapNode* ending = DArray_pop(bucket);

    if(ending != node) {
        DArray_set(bucket, (size_t)i, ending);
    }

    return data;
}

uint32_t
Hashmap_fnv1a_hash(void* data)
{
    const uint32_t FNV_PRIME = 16777619;
    const uint32_t FNV_OFFSET_BASIS = 2166136261;

    bstring s = (bstring) data;
    uint32_t hash = FNV_OFFSET_BASIS;

    for(int i = 0; i < blength(s); i++)
    {
        hash ^= bchare(s, i , 0);
        hash *= FNV_PRIME;
    }

    return hash;
}

uint32_t
Hashmap_adler32_hash(void* data)
{
    const int MOD_ADLER = 65521;
    bstring s = (bstring)data;
    uint32_t a=1,b=0;

    for(int i = 0; i < blength(s); i++)
    {
        a = (a + bchare(s, i, 0)) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
}

uint32_t
Hashmap_djb_hash(void* data)
{
    bstring s = (bstring)data;
    uint32_t hash = 538;
    int i = 0;

    for(int i = 0; i < blength(s); i++)
    {
        hash = ((hash << 5) + hash) + bchare(s, i , 0);
    }

    return hash;
}

void
Hashmap_generate_distribution(Hashmap_hash hash_func,
                              uint32_t* stats,
                              int buckets)
{
    int BUCKETS = buckets;
    const int BUFFER_LEN = 20;
    const int NUM_KEYS = (BUCKETS)*1000;

    DArray* keys = DArray_create(0, NUM_KEYS);
    FILE* urand = fopen("/dev/urandom", "r");
    check(urand != NULL, "failed to open /dev/urandom")

    struct bStream* stream = bsopen((bNread)fread, urand);
    check(stream != NULL, "failed to create bstream")

    bstring key = bfromcstr("");
    int rc = 0;
    for(int i = 0; i < NUM_KEYS; i++)
    {
        rc = bsread(key, stream, BUFFER_LEN);
        check(rc >= 0, "Failed to read from /dev/urandom")
        DArray_push(keys, bstrcpy(key));
    }

    bsclose(stream);
    fclose(urand);

    uint32_t hash = 0;
    for(int i = 0; i < DArray_count(keys); i++) {
        hash = hash_func(DArray_get(keys, i));
        stats[hash % BUCKETS]++;
    }
error:
    for(size_t i = 0; i < DArray_count(keys); i++) {
        bdestroy(DArray_get(keys, i));
    }
    DArray_destroy(keys);
}

static inline void
String_setup_skip_chars(size_t* skip_chars,
                        const unsigned char* needle,
                        size_t nlen)
{
    size_t last = nlen - 1;
    for(size_t i = 0; i < UCHAR_MAX + 1; i++) skip_chars[i] = nlen;
    for(size_t i = 0; i < last; i++) skip_chars[needle[i]] = last - i;
}

static inline const unsigned char*
String_base_search(const unsigned char* haystack,
                   size_t hlen,
                   const unsigned char* needle,
                   size_t nlen,
                   size_t* skip_chars)
{
    size_t last = nlen - 1;

    assert(haystack != NULL && "bad haystack to search");
    assert(needle != NULL && "bad needler to search for");

    check(nlen > 0, "nlen can't be <= 0")
    check(hlen > 0, "hlen can't be <= 0")

    while(hlen >= nlen) {
        for(size_t i = last; haystack[i] == needle[i];i--)
            if(i == 0) return  haystack;

        hlen -= skip_chars[haystack[last]];
        haystack += skip_chars[haystack[last]];
    }
error:  // fallthrough
    return NULL;
}

int
String_find(bstring in,
            bstring what)
{
    const unsigned char* found = NULL;
    const unsigned char* haystack = (const unsigned char *)bdata(in);
    size_t hlen = (size_t)blength(in);
    const unsigned char* needle = (const unsigned char *)bdata(what);
    size_t nlen = (size_t)blength(what);
    size_t skip_chars[UCHAR_MAX + 1] = { 0 };

    String_setup_skip_chars(skip_chars, needle, nlen);
    found = String_base_search(haystack, hlen, needle, nlen, skip_chars);

    return found != NULL ? (int)(found - haystack):-1;
}

StringScanner*
StringScanner_create(bstring in)
{
    StringScanner* scan = calloc(1, sizeof (StringScanner));
    check_mem(scan)

    scan->in = in;
    scan->haystack = (const unsigned char* )bdata(in);
    scan->hlen = (size_t)blength(in);

    assert(scan != NULL);
    return  scan;
error:
    free(scan);
    return NULL;
}

static inline void
StringScanner_set_needle(StringScanner* scan,
                          bstring tofind)
{
    scan->needle = (const unsigned char*)bdata(tofind);
    scan->nlen = (size_t)blength(tofind);
    String_setup_skip_chars(scan->skip_chars, scan->needle, scan->nlen);
}

static inline void StringScanner_reset(StringScanner* scan)
{
    scan->haystack = (const unsigned char*)bdata(scan->in);
    scan->hlen = (size_t)blength(scan->in);
}

int StringScanner_scan(StringScanner* scan, bstring tofind)
{
    const unsigned char* found = NULL;
    size_t found_at = 0;

    if(scan->hlen <= 0) {
        StringScanner_reset(scan);
        return -1;
    }

    if((const unsigned char* )bdata(tofind)!=scan->needle)
        StringScanner_set_needle(scan, tofind);

    found = String_base_search(scan->haystack, scan->hlen, scan->needle,
                               scan->nlen, scan->skip_chars);

    if(found) {
        found_at = found - (const unsigned char*)bdata(scan->in);
        scan->haystack = found + scan->nlen;
        scan->hlen -= found_at - scan->nlen;
    } else {
        StringScanner_reset(scan);
        found_at = 0;
    }

    return found_at;
}

void StringScanner_destroy(StringScanner* scan)
{
    if(scan) free(scan);
}

BSTree* BSTree_create(BSTree_compare compare)
{
    BSTree* map = calloc(1, sizeof (BSTree));
    check_mem(map)

    map->compare = compare == NULL ? default_compare : compare;

    return map;
error:
    if(map) {
        BSTree_destroy(map);
    }
    return  NULL;
}

static int BSTree_destroy_cb(BSTreeNode* node)
{
    free(node);
    return 0;
}

void BSTree_destroy(BSTree* map)
{
    if(map) {
        BSTree_traverse(map, BSTree_destroy_cb);
        free(map);
    }
}

static inline BSTreeNode*
BSTreeNode_create(BSTreeNode* parent,
                  void* key,
                  void* data)
{
    BSTreeNode* node = calloc(1, sizeof (BSTreeNode));
    check_mem(node)

    node->key = key;
    node->data = data;
    node->parent = parent;
    return node;
error:
    return NULL;
}

static inline void
BSTree_setnode(BSTree* map,
               BSTreeNode* node,
               void* key,
               void* data)
{
    int cmp = map->compare(node->key, key);

    if(cmp <= 0) {
        if(node->left)
            BSTree_setnode(map, node->left, key, data);
        else
            node->left = BSTreeNode_create(node, key, data);
    } else {
        if(node->right)
            BSTree_setnode(map, node->right, key, data);
        else
            node->right = BSTreeNode_create(node, key, data);
    }
}

int BSTree_set(BSTree* map, void* key, void* data)
{
    if(map->root == NULL) {
        map->root = BSTreeNode_create(NULL, key, data);
        check_mem(map->root)
    } else
        BSTree_setnode(map, map->root, key, data);
    return 0;
error:
    return -1;
}

static inline BSTreeNode*
BSTree_getnode(BSTree* map, BSTreeNode* node, void* key)
{
    int cmp = map->compare(node->key, key);

    if(cmp == 0) return node;
    else if(cmp < 0) {
        if(node->left)
            return BSTree_getnode(map, node->left, key);
        else
            return NULL;
    } else {
        if(node->right)
            return BSTree_getnode(map, node->right, key);
        else
            return NULL;
    }
}

void* BSTree_get(BSTree* map, void* key)
{
    if(map->root == NULL) return NULL;
    else {
        BSTreeNode* node = BSTree_getnode(map, map->root, key);
        return node == NULL ? NULL : node->data;
    }
}

static inline int
BSTree_traverse_nodes(BSTreeNode* node,
                      BSTree_traverse_cb traverse_cb)
{
    int rc = 0;

    if(node->left) {
        rc = BSTree_traverse_nodes(node->left, traverse_cb);
        if(rc != 0) return rc;
    }

    if(node->right) {
        rc = BSTree_traverse_nodes(node->right, traverse_cb);
        if(rc!=0) return rc;
    }

    return traverse_cb(node);
}

int BSTree_traverse(BSTree* map, BSTree_traverse_cb traverse_cb)
{
    if(map->root)
        return BSTree_traverse_nodes(map->root, traverse_cb);
    return 0;
}

static inline BSTreeNode*
BSTree_find_min(BSTreeNode* node)
{
    while(node->left)
        node = node->left;
    return node;
}

static inline void
BSTree_replace_node_in_parent(BSTree* map,
                              BSTreeNode* node,
                              BSTreeNode* new_value)
{
    if(node->parent) {
        if(node == node->parent->left)
            node->parent->left = new_value;
        else
            node->parent->right = new_value;
    } else {
        map->root = new_value;
    }

    if(new_value) {
        new_value->parent = node->parent;
    }
}

static inline void
BSTree_swap(BSTreeNode* a, BSTreeNode* b)
{
    void* temp = NULL;
    temp = b->key;
    b->key = a->key;
    a->key = temp;
    temp = b->data;
    b->data = a->data;
    a->data = temp;
}

static inline BSTreeNode*
BSTree_node_delete(BSTree* map,
                   BSTreeNode* node,
                   void* key)
{
    int cmp = map->compare(node->key, key);

    if(cmp < 0) {
        if(node->left)
            return BSTree_node_delete(map, node->left, key);
        else
            return NULL;
    } else if(cmp > 0) {
        if(node->right)
            return  BSTree_node_delete(map, node->right, key);
        else
            return NULL;
    } else {
        if(node->left && node->right) {
            BSTreeNode* successor = BSTree_find_min(node->right);
            BSTree_swap(successor, node);
            BSTree_replace_node_in_parent(map, successor, successor->right);
            return successor;
        }
        else if (node->left)
            BSTree_replace_node_in_parent(map, node, node->left);
        else if(node->right)
            BSTree_replace_node_in_parent(map, node, node->right);
        else
            BSTree_replace_node_in_parent(map, node, NULL);
        return node;
    }
}

void* BSTree_delete(BSTree* map, void* key)
{
    void* data = NULL;
    if(map->root) {
        BSTreeNode* node = BSTree_node_delete(map, map->root, key);

        if(node) {
            data = node->data;
            free(node);
        }
    }

    return data;
}

Stats *Stats_recreate(double sum, double sumsq, unsigned long n,
                     double min, double max)
{
    Stats* st = malloc(sizeof (Stats));
    check_mem(st)

    st->sum = sum;
    st->sumsq = sumsq;
    st->n = n;
    st->min = min;
    st->max = max;

    return  st;

    error:
    return NULL;
}

Stats* Stats_create()
{
    return Stats_recreate(0,0,0,0,0);
}

double Stats_mean(Stats* st)
{
    return st->sum / st->n;
}

double Stats_stddev(Stats* st)
{
    return sqrt((st->sumsq - (st->sum * st->sum / st->n)) / (st->n -1));
}

void Stats_sample(Stats* st, double s)
{
    st->sum += s;
    st->sumsq += s*s;

    if(st->n == 0) {
        st->min = s;
        st->max = s;
    } else {
        if(st->min > s) st->min = s;
        if(st->max < s) st->max = s;
    }

    st->n += 1;
}

void Stats_dump(Stats* st)
{
    fprintf(stderr, "sum: %f sumsq: %f, n:%ld, "
            "min: %f, max: %f, mean: %f, stddev: %f",
            st->sum, st->sumsq, st->n, st->min, st->max, Stats_mean(st),
            Stats_stddev(st));
}

RingBuffer* RingBuffer_create(int length)
{
    RingBuffer *buffer = calloc(1, sizeof (RingBuffer));
    buffer->length = length + 1;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = calloc(buffer->length, 1);

    return buffer;
}


void RingBuffer_destroy(RingBuffer* buffer)
{
    if(buffer)
        free(buffer->buffer);
    free(buffer);
}

int RingBuffer_write(RingBuffer *buffer, char* data, int length)
{
    if(RingBuffer_available_data(buffer) == 0)
        buffer->start = buffer->end = 0;

    check(length <= RingBuffer_available_space(buffer),
          "Not enough space: %d request, %d  available",
          length, RingBuffer_available_space(buffer));

    void* result = memcpy(RingBuffer_ends_at(buffer), data, length);
    check(result != NULL, "failed to write data into buffer");

    RingBuffer_commit_write(buffer, length);

    return length;
    error:
    return -1;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
    check_debug(amount <= RingBuffer_available_data(buffer),
                "Not enough in the buffer has %d needs %d",
                RingBuffer_available_data(buffer), amount);
    void *result = memcpy(target, RingBuffer_starts_at(buffer), amount);

    check(result != NULL, "Failed to write buffer into data");

    RingBuffer_commit_read(buffer, amount);

    if(buffer->end == buffer->start) {
        buffer->start = buffer->end = 0;
    }

    return amount;
    error:
    return -1;
}

bstring RingBuffer_gets(RingBuffer* buffer, int amount)
{
    check(amount > 0, "Need more than 0 for gets you gave %d", amount);
    check_debug(amount <= RingBuffer_available_data(buffer),
                "Not enough in the buffer");

    bstring result = blk2bstr(RingBuffer_starts_at(buffer), amount);
    check(result != NULL, "Failed to create get result");
    check(blength(result) == amount, "wrong result length");

    RingBuffer_commit_read(buffer, amount);
    assert(RingBuffer_available_data(buffer) > 0 && "Error in read commit");

    return result;
    error:
    return NULL;
}
