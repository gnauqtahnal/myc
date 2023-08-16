#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void (*version)(void);
    void (*plan)(unsigned int, unsigned int, const char*);
    void (*ok)(unsigned int, unsigned int, const char*, const char*);
    void (*not_ok)(unsigned int, unsigned int, const char*, const char*);
    void (*skip)(unsigned int, unsigned int, const char*, const char*);
    struct {
        void (*open)(void);
        void (*close)(void);
        void (*string)(unsigned int, unsigned int, const char*);
    } comment;
} tap_t;

static void tap_comment_indent(unsigned int lvl);
static void tap_version(void);
static void tap_plan(unsigned int lvl, unsigned int nb, const char* cmt);

tap_t tap = {
    .version = tap_version,
    .plan = tap_plan,
};

static void tap_subtest_indent(unsigned int lvl)
{
    for (unsigned int i = 0; i < lvl; i++) {
        fprintf(stdout, "    ");
    }
}

static void tap_comment_indent(unsigned int lvl)
{
    for (unsigned int i = 0; i < lvl; i++) {
        fprintf(stdout, "  ");
    }
}

static void tap_version(void)
{
    fprintf(stdout, "TAP version 14\n");
    fflush(stdout);
}

static void tap_plan(unsigned int lvl, unsigned int nb, const char* cmt)
{
    /* Start a line */
    tap_subtest_indent(lvl);
    fprintf(stdout, "1..%u", nb);
    if (cmt) {
        fprintf(stdout, " # %s", cmt);
    }
    fprintf(stdout, "\n");
    /* End a line */
    fflush(stdout);
}

void tap_prd_ok(unsigned int nb, const char* desc, const char* cmt)
{
    fprintf(stdout, "ok %u", nb);
    if (desc) {
        fprintf(stdout, " - %s", desc);
    }
    if (cmt) {
        fprintf(stdout, " # %s", cmt);
    }
    fprintf(stdout, "\n");
    fflush(stdout);
}

void tap_prd_not_ok(unsigned int nb, const char* desc, const char* cmt)
{
    fprintf(stdout, "not ok %u", nb);
    if (desc) {
        fprintf(stdout, " - %s", desc);
    }
    if (cmt) {
        fprintf(stdout, " # %s", cmt);
    }
    fprintf(stdout, "\n");
    fflush(stdout);
}

void tap_prd_skip(unsigned int nb, const char* desc, const char* cmt)
{
    fprintf(stdout, "ok %u", nb);
    if (desc) {
        fprintf(stdout, " - %s", desc);
    }
    fprintf(stdout, " # SKIP");
    if (cmt) {
        fprintf(stdout, " %s", cmt);
    }
    fprintf(stdout, "\n");
    fflush(stdout);
}

void tap_prd_cmt_open(void)
{
    fprintf(stdout, "  ---\n");
    fflush(stdout);
}

void tap_prd_cmt_close(void)
{
    fprintf(stdout, "  ...\n");
    fflush(stdout);
}

void tap_prd_cmt_content(unsigned int indent, const char* cmt)
{
    for (unsigned int i = 0; i <= indent; i++) {
        fprintf(stdout, "  ");
    }
    fprintf(stdout, "%s\n", cmt);
    fflush(stdout);
}

int main(void)
{
    tap.version();

    tap.plan(0, 123, NULL);
    tap.plan(0, 123, "with comment");

    tap.plan(1, 123, NULL);
    tap.plan(1, 123, "level 2");

    return 0;
}
