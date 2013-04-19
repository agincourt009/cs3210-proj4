#include <config.h>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/xattr.h>

#include "encryption.h"

static int p4_open(const char *path, struct fuse_file_info *fi)
{
}

static int p4_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
}

static int p4_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
}

static int p4_release(const char *path, struct fuse_file_info *fi)
{
}

static struct fuse_operations p4_oper = {
	.open		= p4_open,
	.read		= p4_read,
	.write		= p4_write,
	.release	= p4_release,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &p4_oper, NULL);
}
