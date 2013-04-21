/*
  Borrow the frame from:  
  Big Brother File System
  Copyright (C) 2012 Joseph J. Pfeiffer, Jr., Ph.D. <pfeiffer@cs.nmsu.edu>

  Add encryption and decryption, and change stroage path to hidden folder

  Shan Liang and Kaitlin Powell
*/

#include "params.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>

#include "log.h"



// Report errors to logfile and give -errno to caller
static int p4_error(char *str)
{
    int ret = -errno;
    
    log_msg("    ERROR %s: %s\n", str, strerror(errno));
    
    return ret;
}

//  Get Back-end Storage file path

static void p4_bkend_path(char fpath[PATH_MAX], const char *path)
{
    strcpy(fpath, P4_DATA->bkend_dir);
    strncat(fpath, path, PATH_MAX); // ridiculously long paths will
				    // break here

    log_msg("    p4_bkend_path:  bkend_dir = \"%s\", path = \"%s\", fpath = \"%s\"\n",
	    P4_DATA->bkend_dir, path, fpath);
}

int p4_getattr(const char *path, struct stat *statbuf)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_getattr(path=\"%s\", statbuf=0x%08x)\n",
	  path, statbuf);
    p4_bkend_path(fpath, path);
    
    retstat = lstat(fpath, statbuf);
    if (retstat != 0)
	retstat = p4_error("p4_getattr lstat");
    
    log_stat(statbuf);
    
    return retstat;
}

int p4_readlink(const char *path, char *link, size_t size)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("p4_readlink(path=\"%s\", link=\"%s\", size=%d)\n",
	  path, link, size);
    p4_bkend_path(fpath, path);
    
    retstat = readlink(fpath, link, size - 1);
    if (retstat < 0)
	retstat = p4_error("p4_readlink readlink");
    else  {
	link[retstat] = '\0';
	retstat = 0;
    }
    
    return retstat;
}

int p4_mknod(const char *path, mode_t mode, dev_t dev)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_mknod(path=\"%s\", mode=0%3o, dev=%lld)\n",
	  path, mode, dev);
    p4_bkend_path(fpath, path);
    
    if (S_ISREG(mode)) {
        retstat = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
	if (retstat < 0)
	    retstat = p4_error("p4_mknod open");
        else {
            retstat = close(retstat);
	    if (retstat < 0)
		retstat = p4_error("p4_mknod close");
	}
    } else
	if (S_ISFIFO(mode)) {
	    retstat = mkfifo(fpath, mode);
	    if (retstat < 0)
		retstat = p4_error("p4_mknod mkfifo");
	} else {
	    retstat = mknod(fpath, mode, dev);
	    if (retstat < 0)
		retstat = p4_error("p4_mknod mknod");
	}
    
    return retstat;
}

int p4_mkdir(const char *path, mode_t mode)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_mkdir(path=\"%s\", mode=0%3o)\n",
	    path, mode);
    p4_bkend_path(fpath, path);
    
    retstat = mkdir(fpath, mode);
    if (retstat < 0)
	retstat = p4_error("p4_mkdir mkdir");
    
    return retstat;
}

int p4_unlink(const char *path)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("p4_unlink(path=\"%s\")\n",
	    path);
    p4_bkend_path(fpath, path);
    
    retstat = unlink(fpath);
    if (retstat < 0)
	retstat = p4_error("p4_unlink unlink");
    
    return retstat;
}

int p4_rmdir(const char *path)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("p4_rmdir(path=\"%s\")\n",
	    path);
    p4_bkend_path(fpath, path);
    
    retstat = rmdir(fpath);
    if (retstat < 0)
	retstat = p4_error("p4_rmdir rmdir");
    
    return retstat;
}

int p4_symlink(const char *path, const char *link)
{
    int retstat = 0;
    char flink[PATH_MAX];
    
    log_msg("\np4_symlink(path=\"%s\", link=\"%s\")\n",
	    path, link);
    p4_bkend_path(flink, link);
    
    retstat = symlink(path, flink);
    if (retstat < 0)
	retstat = p4_error("p4_symlink symlink");
    
    return retstat;
}

int p4_rename(const char *path, const char *newpath)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    char fnewpath[PATH_MAX];
    
    log_msg("\np4_rename(fpath=\"%s\", newpath=\"%s\")\n",
	    path, newpath);
    p4_bkend_path(fpath, path);
    p4_bkend_path(fnewpath, newpath);
    
    retstat = rename(fpath, fnewpath);
    if (retstat < 0)
	retstat = p4_error("p4_rename rename");
    
    return retstat;
}

int p4_link(const char *path, const char *newpath)
{
    int retstat = 0;
    char fpath[PATH_MAX], fnewpath[PATH_MAX];
    
    log_msg("\np4_link(path=\"%s\", newpath=\"%s\")\n",
	    path, newpath);
    p4_bkend_path(fpath, path);
    p4_bkend_path(fnewpath, newpath);
    
    retstat = link(fpath, fnewpath);
    if (retstat < 0)
	retstat = p4_error("p4_link link");
    
    return retstat;
}

int p4_chmod(const char *path, mode_t mode)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_chmod(fpath=\"%s\", mode=0%03o)\n",
	    path, mode);
    p4_bkend_path(fpath, path);
    
    retstat = chmod(fpath, mode);
    if (retstat < 0)
	retstat = p4_error("p4_chmod chmod");
    
    return retstat;
}

int p4_chown(const char *path, uid_t uid, gid_t gid)
  
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_chown(path=\"%s\", uid=%d, gid=%d)\n",
	    path, uid, gid);
    p4_bkend_path(fpath, path);
    
    retstat = chown(fpath, uid, gid);
    if (retstat < 0)
	retstat = p4_error("p4_chown chown");
    
    return retstat;
}

int p4_truncate(const char *path, off_t newsize)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_truncate(path=\"%s\", newsize=%lld)\n",
	    path, newsize);
    p4_bkend_path(fpath, path);
    
    retstat = truncate(fpath, newsize);
    if (retstat < 0)
	p4_error("p4_truncate truncate");
    
    return retstat;
}

int p4_utime(const char *path, struct utimbuf *ubuf)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_utime(path=\"%s\", ubuf=0x%08x)\n",
	    path, ubuf);
    p4_bkend_path(fpath, path);
    
    retstat = utime(fpath, ubuf);
    if (retstat < 0)
	retstat = p4_error("p4_utime utime");
    
    return retstat;
}

int p4_open(const char *path, struct fuse_file_info *fi)
{
    int retstat = 0;
    int fd;
    char fpath[PATH_MAX];
    
    log_msg("\np4_open(path\"%s\", fi=0x%08x)\n",
	    path, fi);
    p4_bkend_path(fpath, path);
    
    fd = open(fpath, fi->flags);
    if (fd < 0)
	retstat = p4_error("p4_open open");
    
    fi->fh = fd;
    log_fi(fi);
    
    return retstat;
}

int p4_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_read(path=\"%s\", buf=0x%08x, size=%d, offset=%lld, fi=0x%08x)\n",
	    path, buf, size, offset, fi);
    // no need to get fpath on this one, since I work from fi->fh not the path
    log_fi(fi);
    
    retstat = pread(fi->fh, buf, size, offset);
    if (retstat < 0)
	retstat = p4_error("p4_read read");
    
    return retstat;
}

int p4_write(const char *path, const char *buf, size_t size, off_t offset,
	     struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_write(path=\"%s\", buf=0x%08x, size=%d, offset=%lld, fi=0x%08x)\n",
	    path, buf, size, offset, fi
	    );
    // no need to get fpath on this one, since I work from fi->fh not the path
    log_fi(fi);
	
    retstat = pwrite(fi->fh, buf, size, offset);
    if (retstat < 0)
	retstat = p4_error("p4_write pwrite");
    
    return retstat;
}

int p4_statfs(const char *path, struct statvfs *statv)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_statfs(path=\"%s\", statv=0x%08x)\n",
	    path, statv);
    p4_bkend_path(fpath, path);
    
    // get stats for underlying filesystem
    retstat = statvfs(fpath, statv);
    if (retstat < 0)
	retstat = p4_error("p4_statfs statvfs");
    
    log_statvfs(statv);
    
    return retstat;
}

int p4_flush(const char *path, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_flush(path=\"%s\", fi=0x%08x)\n", path, fi);
    log_fi(fi);
	
    return retstat;
}

int p4_release(const char *path, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_release(path=\"%s\", fi=0x%08x)\n",
	  path, fi);
    log_fi(fi);

    retstat = close(fi->fh);
    
    return retstat;
}

int p4_fsync(const char *path, int datasync, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_fsync(path=\"%s\", datasync=%d, fi=0x%08x)\n",
	    path, datasync, fi);
    log_fi(fi);
    
    if (datasync)
	retstat = fdatasync(fi->fh);
    else
	retstat = fsync(fi->fh);
    
    if (retstat < 0)
	p4_error("p4_fsync fsync");
    
    return retstat;
}

int p4_setxattr(const char *path, const char *name, const char *value, size_t size, int flags)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_setxattr(path=\"%s\", name=\"%s\", value=\"%s\", size=%d, flags=0x%08x)\n",
	    path, name, value, size, flags);
    p4_bkend_path(fpath, path);
    
    retstat = lsetxattr(fpath, name, value, size, flags);
    if (retstat < 0)
	retstat = p4_error("p4_setxattr lsetxattr");
    
    return retstat;
}

int p4_getxattr(const char *path, const char *name, char *value, size_t size)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_getxattr(path = \"%s\", name = \"%s\", value = 0x%08x, size = %d)\n",
	    path, name, value, size);
    p4_bkend_path(fpath, path);
    
    retstat = lgetxattr(fpath, name, value, size);
    if (retstat < 0)
	retstat = p4_error("p4_getxattr lgetxattr");
    else
	log_msg("    value = \"%s\"\n", value);
    
    return retstat;
}

int p4_listxattr(const char *path, char *list, size_t size)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    char *ptr;
    
    log_msg("p4_listxattr(path=\"%s\", list=0x%08x, size=%d)\n",
	    path, list, size
	    );
    p4_bkend_path(fpath, path);
    
    retstat = llistxattr(fpath, list, size);
    if (retstat < 0)
	retstat = p4_error("p4_listxattr llistxattr");
    
    log_msg("    returned attributes (length %d):\n", retstat);
    for (ptr = list; ptr < list + retstat; ptr += strlen(ptr)+1)
	log_msg("    \"%s\"\n", ptr);
    
    return retstat;
}

int p4_removexattr(const char *path, const char *name)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_removexattr(path=\"%s\", name=\"%s\")\n",
	    path, name);
    p4_bkend_path(fpath, path);
    
    retstat = lremovexattr(fpath, name);
    if (retstat < 0)
	retstat = p4_error("p4_removexattr lrmovexattr");
    
    return retstat;
}

int p4_opendir(const char *path, struct fuse_file_info *fi)
{
    DIR *dp;
    int retstat = 0;
    char fpath[PATH_MAX];
    
    log_msg("\np4_opendir(path=\"%s\", fi=0x%08x)\n",
	  path, fi);
    p4_bkend_path(fpath, path);
    
    dp = opendir(fpath);
    if (dp == NULL)
	retstat = p4_error("p4_opendir opendir");
    
    fi->fh = (intptr_t) dp;
    
    log_fi(fi);
    
    return retstat;
}

int p4_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
	       struct fuse_file_info *fi)
{
    int retstat = 0;
    DIR *dp;
    struct dirent *de;
    
    log_msg("\np4_readdir(path=\"%s\", buf=0x%08x, filler=0x%08x, offset=%lld, fi=0x%08x)\n",
	    path, buf, filler, offset, fi);
    dp = (DIR *) (uintptr_t) fi->fh;

    de = readdir(dp);
    if (de == 0) {
	retstat = p4_error("p4_readdir readdir");
	return retstat;
    }

    do {
	log_msg("calling filler with name %s\n", de->d_name);
	if (filler(buf, de->d_name, NULL, 0) != 0) {
	    log_msg("    ERROR p4_readdir filler:  buffer full");
	    return -ENOMEM;
	}
    } while ((de = readdir(dp)) != NULL);
    
    log_fi(fi);
    
    return retstat;
}

int p4_releasedir(const char *path, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_releasedir(path=\"%s\", fi=0x%08x)\n",
	    path, fi);
    log_fi(fi);
    
    closedir((DIR *) (uintptr_t) fi->fh);
    
    return retstat;
}

int p4_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_fsyncdir(path=\"%s\", datasync=%d, fi=0x%08x)\n",
	    path, datasync, fi);
    log_fi(fi);
    
    return retstat;
}

void *p4_init(struct fuse_conn_info *conn)
{
    
    log_msg("\np4_init()\n");
    
    return P4_DATA;
}

/**
 * Clean up filesystem
 *
 * Called on filesystem exit.
 *
 * Introduced in version 2.3
 */
void p4_destroy(void *userdata)
{
    log_msg("\np4_destroy(userdata=0x%08x)\n", userdata);
}

int p4_access(const char *path, int mask)
{
    int retstat = 0;
    char fpath[PATH_MAX];
   
    log_msg("\np4_access(path=\"%s\", mask=0%o)\n",
	    path, mask);
    p4_bkend_path(fpath, path);
    
    retstat = access(fpath, mask);
    
    if (retstat < 0)
	retstat = p4_error("p4_access access");
    
    return retstat;
}

int p4_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    int retstat = 0;
    char fpath[PATH_MAX];
    int fd;
    
    log_msg("\np4_create(path=\"%s\", mode=0%03o, fi=0x%08x)\n",
	    path, mode, fi);
    p4_bkend_path(fpath, path);
    
    fd = creat(fpath, mode);
    if (fd < 0)
	retstat = p4_error("p4_create creat");
    
    fi->fh = fd;
    
    log_fi(fi);
    
    return retstat;
}

int p4_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_ftruncate(path=\"%s\", offset=%lld, fi=0x%08x)\n",
	    path, offset, fi);
    log_fi(fi);
    
    retstat = ftruncate(fi->fh, offset);
    if (retstat < 0)
	retstat = p4_error("p4_ftruncate ftruncate");
    
    return retstat;
}

int p4_fgetattr(const char *path, struct stat *statbuf, struct fuse_file_info *fi)
{
    int retstat = 0;
    
    log_msg("\np4_fgetattr(path=\"%s\", statbuf=0x%08x, fi=0x%08x)\n",
	    path, statbuf, fi);
    log_fi(fi);
    
    retstat = fstat(fi->fh, statbuf);
    if (retstat < 0)
	retstat = p4_error("p4_fgetattr fstat");
    
    log_stat(statbuf);
    
    return retstat;
}

struct fuse_operations p4_oper = {
  .getattr = p4_getattr,
  .readlink = p4_readlink,
  .getdir = NULL,
  .mknod = p4_mknod,
  .mkdir = p4_mkdir,
  .unlink = p4_unlink,
  .rmdir = p4_rmdir,
  .symlink = p4_symlink,
  .rename = p4_rename,
  .link = p4_link,
  .chmod = p4_chmod,
  .chown = p4_chown,
  .truncate = p4_truncate,
  .utime = p4_utime,
  .open = p4_open,
  .read = p4_read,
  .write = p4_write,
  .statfs = p4_statfs,
  .flush = p4_flush,
  .release = p4_release,
  .fsync = p4_fsync,
  .setxattr = p4_setxattr,
  .getxattr = p4_getxattr,
  .listxattr = p4_listxattr,
  .removexattr = p4_removexattr,
  .opendir = p4_opendir,
  .readdir = p4_readdir,
  .releasedir = p4_releasedir,
  .fsyncdir = p4_fsyncdir,
  .init = p4_init,
  .destroy = p4_destroy,
  .access = p4_access,
  .create = p4_create,
  .ftruncate = p4_ftruncate,
  .fgetattr = p4_fgetattr
};

void p4_usage()
{
    fprintf(stderr, "usage:  p4fs [FUSE and mount options] rootDir mountPoint\n");
    abort();
}

int main(int argc, char *argv[])
{
    int fuse_stat;
    struct p4_state *p4_data;

    if ((getuid() == 0) || (geteuid() == 0)) {
	fprintf(stderr, "Running BBFS as root opens unnacceptable security holes\n");
	return 1;
    }
    
    if ((argc < 3) || (argv[argc-2][0] == '-') || (argv[argc-1][0] == '-'))
	p4_usage();

    p4_data = malloc(sizeof(struct p4_state));
    if (p4_data == NULL) {
	perror("main calloc");
	abort();
    }

    p4_data->rootdir = realpath(argv[argc-2], NULL);
    argv[argc-2] = argv[argc-1];
    argv[argc-1] = NULL;
    argc--;

    p4_data->bkend_dir = malloc(sizeof(char) * PATH_MAX);
    strcpy(p4_data->bkend_dir, p4_data->rootdir);
    strncat(p4_data->bkend_dir, "/.p4_bckend/", PATH_MAX);
    
    p4_data->logfile = log_open();
    
    fprintf(stderr, "about to call fuse_main\n");
    fuse_stat = fuse_main(argc, argv, &p4_oper, p4_data);
    fprintf(stderr, "fuse_main returned %d\n", fuse_stat);
    
    return fuse_stat;
}
