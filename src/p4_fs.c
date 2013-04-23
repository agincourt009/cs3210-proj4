/*
  Borrow the frame from:  
  Big Brother File System
  Copyright (C) 2012 Joseph J. Pfeiffer, Jr., Ph.D. <pfeiffer@cs.nmsu.edu>

  Add encryption and decryption, and change stroage path to a hidden folder

  Shan Liang and Kaitlin Powell
*/
#define _GNU_SOURCE
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
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/xattr.h>

#define ENCRYPT_KEY	0x96

//  Get Back-end Storage file path
static void p4_bkend_path(char fpath[PATH_MAX], const char *path)
{
	strcpy(fpath, P4_DATA->bkend_dir);
	strncat(fpath, path, PATH_MAX);
}

int p4_getattr(const char *path, struct stat *statbuf)
{
	int retstat = 0;
	char fpath[PATH_MAX];
 
	if(syscall(290)){   	
		p4_bkend_path(fpath, path);
    		retstat = lstat(fpath, statbuf);
		if (retstat != 0)
			return -errno;
	}
	return retstat;
}

int p4_readlink(const char *path, char *link, size_t size)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		retstat = readlink(fpath, link, size - 1);
		if (retstat < 0)
			return -errno;
		else{
			link[retstat] = '\0';
			retstat = 0;
		}
	}	
    	return retstat;
}

int p4_mknod(const char *path, mode_t mode, dev_t dev)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    	
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		if(S_ISREG(mode)){
        		retstat = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
			if (retstat < 0)
				return -errno;
        		else {
				retstat = close(retstat);
	    			if (retstat < 0)
					return -errno;
			}
		}else if(S_ISFIFO(mode)){
			retstat = mkfifo(fpath, mode);
			if(retstat < 0)
				return -errno;
		}else{	
	   		retstat = mknod(fpath, mode, dev);
	    		if(retstat < 0)
				return -errno;
    		}
	}
	return retstat;
}

int p4_mkdir(const char *path, mode_t mode)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		retstat = mkdir(fpath, mode);
		if(retstat < 0)
			return -errno;
    	}
	return retstat;
}

int p4_unlink(const char *path)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		retstat = unlink(fpath);
		if(retstat < 0)
			return -errno;
	}	
	return retstat;
}	

int p4_rmdir(const char *path)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		retstat = rmdir(fpath);
		if (retstat < 0)
			return -errno;
    	}
	return retstat;
}

int p4_symlink(const char *path, const char *link)
{
	int retstat = 0;
	char flink[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(flink, link);
    		retstat = symlink(path, flink);
		if(retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_rename(const char *path, const char *newpath)
{
	int retstat = 0;
	char fpath[PATH_MAX];
	char fnewpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		p4_bkend_path(fnewpath, newpath);
    		retstat = rename(fpath, fnewpath);
		if(retstat < 0)
			return -errno;
	}	
	return retstat;
}

int p4_link(const char *path, const char *newpath)
{
	int retstat = 0;
	char fpath[PATH_MAX], fnewpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		p4_bkend_path(fnewpath, newpath);
		retstat = link(fpath, fnewpath);
		if(retstat < 0)
    			return -errno;
	}
    	return retstat;
}

int p4_chmod(const char *path, mode_t mode)
{	
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		retstat = chmod(fpath, mode);
		if(retstat < 0)
    			return -errno;
	}
    	return retstat;
}

int p4_chown(const char *path, uid_t uid, gid_t gid)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		retstat = chown(fpath, uid, gid);
		if(retstat < 0)
    			return -errno;
	}
    	return retstat;
}

int p4_truncate(const char *path, off_t newsize)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		retstat = truncate(fpath, newsize);
		if(retstat < 0)
    			return -errno;
	}
	return retstat;
}

int p4_utime(const char *path, struct utimbuf *ubuf)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		retstat = utime(fpath, ubuf);
		if(retstat < 0)
    			return -errno;
	}
	return retstat;
}

int p4_open(const char *path, struct fuse_file_info *fi)
{
	int retstat = 0;
	int fd;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
    		fd = open(fpath, fi->flags);
		if(fd < 0)
			return -errno;
		fi->fh = fd;
	}
    	return retstat;
}

int p4_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	int retstat = 0;
	char* enc_buf = malloc(sizeof(char) * size);
	char temp_char;
	int index;
    
	if((syscall(290))){   	
		retstat = pread(fi->fh, enc_buf, size, offset);
		if(retstat < 0)
			return -errno;
		for(index = 0; index < size; index++){
			temp_char = enc_buf[index] ^ ENCRYPT_KEY;
			buf[index] = temp_char;
		}
	}
	return retstat;
}

int p4_write(const char *path, const char *buf, size_t size, off_t offset,
	     struct fuse_file_info *fi)
{
	int retstat = 0;
	char* dec_buf = malloc(sizeof(char) * size);
	char temp_char;
	int index;
	
	if((syscall(290))){   	
		for(index = 0; index < size; index++){
			temp_char = buf[index] ^ ENCRYPT_KEY;
			dec_buf[index] = temp_char;
		}
		retstat = pwrite(fi->fh, dec_buf, size, offset);
		if(retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_statfs(const char *path, struct statvfs *statv)
{
	int retstat = 0;
	char fpath[PATH_MAX];
	
	if((syscall(290))){   	
    		p4_bkend_path(fpath, path);
    		retstat = statvfs(fpath, statv);
		if(retstat < 0)
			return -errno;
    	}
	return retstat;
}

int p4_flush(const char *path, struct fuse_file_info *fi)
{
	int retstat = 0;
	return retstat;
}

int p4_release(const char *path, struct fuse_file_info *fi)
{
	int retstat = 0;
	if((syscall(290))){   	
		retstat = close(fi->fh);
	}
	return retstat;
}

int p4_fsync(const char *path, int datasync, struct fuse_file_info *fi)
{
	int retstat = 0;
	if((syscall(290))){   	
		if(datasync)
			retstat = fdatasync(fi->fh);
		else
			retstat = fsync(fi->fh);
    		if(retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_setxattr(const char *path, const char *name, const char *value, size_t size, int flags)
{
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		retstat = lsetxattr(fpath, name, value, size, flags);
		if (retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_getxattr(const char *path, const char *name, char *value, size_t size)
{	
	int retstat = 0;
	char fpath[PATH_MAX];
    
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		retstat = lgetxattr(fpath, name, value, size);
		if (retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_listxattr(const char *path, char *list, size_t size)
{
	int retstat = 0;
	char fpath[PATH_MAX];
	
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		retstat = llistxattr(fpath, list, size);
		if(retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_removexattr(const char *path, const char *name)
{
	int retstat = 0;
	char fpath[PATH_MAX];

	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		retstat = lremovexattr(fpath, name);
		if (retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_opendir(const char *path, struct fuse_file_info *fi)
{
	DIR *dp;
	int retstat = 0;
	char fpath[PATH_MAX];
	
	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		dp = opendir(fpath);
		if(dp == NULL)
			return -errno;
		fi->fh = (intptr_t) dp;
	}
	return retstat;
}

int p4_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
	       struct fuse_file_info *fi)
{
	int retstat = 0;
	DIR *dp;
	struct dirent *de;

	if((syscall(290))){   	
		dp = (DIR *) (uintptr_t) fi->fh;
		de = readdir(dp);
		if(de == 0) {
			return -errno;
		}

		do{
			if(filler(buf, de->d_name, NULL, 0) != 0) {
        			return -ENOMEM;
    			}
		}while((de = readdir(dp)) != NULL);
	}
	return retstat;
}

int p4_releasedir(const char *path, struct fuse_file_info *fi)
{
	int retstat = 0;
	if((syscall(290))){   	
		closedir((DIR *) (uintptr_t) fi->fh);
	}
	return retstat;
}

int p4_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
	int retstat = 0;
	return retstat;
}

void *p4_init(struct fuse_conn_info *conn)
{
	
	return P4_DATA;
}

void p4_destroy(void *userdata)
{
}

int p4_access(const char *path, int mask)
{
	int retstat = 0;
	char fpath[PATH_MAX];

	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		retstat = access(fpath, mask);

		if(retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	int retstat = 0;
	char fpath[PATH_MAX];
	int fd;

	if((syscall(290))){   	
		p4_bkend_path(fpath, path);
		fd = creat(fpath, mode);
		if(fd < 0)	
			return -errno;
		fi->fh = fd;
	}
	return retstat;
}

int p4_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi)
{
	int retstat = 0;
	if((syscall(290))){   	
		retstat = ftruncate(fi->fh, offset);
		if(retstat < 0)
			return -errno;
	}
	return retstat;
}

int p4_fgetattr(const char *path, struct stat *statbuf, struct fuse_file_info *fi)
{
	int retstat = 0;
	if((syscall(290))){   	
		retstat = fstat(fi->fh, statbuf);
		if(retstat < 0)
			return -errno;
	}
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

int main(int argc, char *argv[])
{
	int fuse_stat;
	struct p4_state *p4_data;

	if((getuid() == 0) || (geteuid() == 0)){
		fprintf(stderr, "Running BBFS as root opens unnacceptable security holes\n");
		return 1;
	}

	if((argc < 3) || (argv[argc-2][0] == '-') || (argv[argc-1][0] == '-')){
		fprintf(stderr, "usage:  p4fs [FUSE and mount options] rootDir mountPoint\n");
		abort();
    	}

	p4_data = malloc(sizeof(struct p4_state));
	if(p4_data == NULL) {
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
	
	fprintf(stderr, "about to call fuse_main, %ld\n", syscall(290));
	fuse_stat = fuse_main(argc, argv, &p4_oper, p4_data);
	fprintf(stderr, "fuse_main returned %d\n", fuse_stat);

	return fuse_stat;
}
