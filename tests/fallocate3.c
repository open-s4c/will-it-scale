#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>

#define FILESIZE 73819750

char *testcase_description = "Some file fallocate";

void testcase(unsigned long long *iterations, unsigned long nr)
{
    char tmpfile[PATH_MAX];
    snprintf(&tmpfile[0], sizeof(tmpfile), "./willitscale.%ld", nr);
    while (1) {
        int fd = open(tmpfile, O_WRONLY|O_CREAT|O_TRUNC|O_CLOEXEC, 0644);
        assert(fd != -1);
        int ret = fallocate(fd,  FALLOC_FL_KEEP_SIZE, 0, FILESIZE);
        assert(ret == 0);
        close(fd);
        (*iterations)++;
    }
}
