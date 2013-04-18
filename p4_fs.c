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

static int p4_getattr(const char *path, struct stat *stbuf)
{
}

static int p4_access(const char *path, int mask)
{
}

static int p4_readlink(const char *path, char *buf, size_t size)
{
}


static int p4_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
}

static int p4_mknod(const char *path, mode_t mode, dev_t rdev)
{
}

static int p4_mkdir(const char *path, mode_t mode)
{
}

static int p4_unlink(const char *path)
{
}

static int p4_rmdir(const char *path)
{
}

static int p4_symlink(const char *from, const char *to)
{
}

static int p4_rename(const char *from, const char *to)
{
}

static int p4_link(const char *from, const char *to)
{
}

static int p4_chmod(const char *path, mode_t mode)
{
}

static int p4_chown(const char *path, uid_t uid, gid_t gid)
{
}

static int p4_truncate(const char *path, off_t size)
{
}

static int p4_utimens(const char *path, const struct timespec ts[2])
{
}

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

static int p4_statfs(const char *path, struct statvfs *stbuf)
{
}

static int p4_create(const char* path, mode_t mode, struct fuse_file_info* fi)
{
}


static int p4_release(const char *path, struct fuse_file_info *fi)
{
}

static int p4_fsync(const char *path, int isdatasync,
		     struct fuse_file_info *fi)
{
}

static int p4_setxattr(const char *path, const char *name, const char *value,
			size_t size, int flags)
{
}

static int p4_getxattr(const char *path, const char *name, char *value,
			size_t size)
{
}

static int p4_listxattr(const char *path, char *list, size_t size)
{
}

static int p4_removexattr(const char *path, const char *name)
{
}

static int p4_flush(const char *path, struct fuse_file_info *fi)
{
}

static int p4_opendir(const char *path, struct fuse_file_info *fi)
{
}

static int p4_releasedir(const char *path, struct fuse_file_info *fi)
{
}

static int p4_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
}

static void *p4_init(struct fuse_conn_info *conn)
{
}

static void destroy(void *private_data)
{
}

static int ftruncate(const char *path, off_t size, struct fuse_file_info *fi)
{
}

static int fgetattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi)
{
}

static int lock(const char *path, struct fuse_file_info *fi, int cmd,
		     struct flock *locks)
{
}

static int bmap(const char *path, size_t blocksize, uint64_t *idx)
{
}

static int ioctl(const char *path, int cmd, void *arg,
		      struct fuse_file_info *fi, unsigned int flags, void *data)
{
}

static int poll(const char *path, struct fuse_file_info *fi,
		     struct fuse_pollhandle *ph, unsigned *reventsp)
{
}

static int write_buf(const char *path, struct fuse_bufvec *buf, off_t off,
			  struct fuse_file_info *fi)
{
}

static int read_buf(const char *path, struct fuse_bufvec **bufp,
			 size_t size, off_t off, struct fuse_file_info *fi)
{
}

static int flock(const char *path, struct fuse_file_info *fi, int op)
{
}

static struct fuse_operations p4_oper = {
	.getattr	= p4_getattr,
	.access		= p4_access,
	.readlink	= p4_readlink,
	.readdir	= p4_readdir,
	.mknod		= p4_mknod,
	.mkdir		= p4_mkdir,
	.symlink	= p4_symlink,
	.unlink		= p4_unlink,
	.rmdir		= p4_rmdir,
	.rename		= p4_rename,
	.link		= p4_link,
	.chmod		= p4_chmod,
	.chown		= p4_chown,
	.truncate	= p4_truncate,
	.utimens	= p4_utimens,
	.open		= p4_open,
	.read		= p4_read,
	.write		= p4_write,
	.statfs		= p4_statfs,
	.create         = p4_create,
	.release	= p4_release,
	.fsync		= p4_fsync,
	.setxattr	= p4_setxattr,
	.getxattr	= p4_getxattr,
	.listxattr	= p4_listxattr,
	.removexattr	= p4_removexattr,
	.flush		= p4_flush,
	.opendir	= p4_opendir,
	.releasedir	= p4_releasedir,
	.fsyncdir	= p4_fsyncdir,
	.destroy	= p4_destroy,
	.ftruncate	= p4_ftruncate,
	.fgetattr	= p4_fgetattr,
	.lock		= p4_lock,
	.bmap		= p4_bmap,
	.ioctl		= p4_ioctl,
	.poll		= p4_poll,
	.write_buf	= p4_write_buf,
	.read_buf	= p4_read_buf,
	.flock		= p4_flock,
	.init		= *p4_init,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &p4_oper, NULL);
}
