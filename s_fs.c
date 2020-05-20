#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//typedef int (*fuse_filler_dir_t) (void *buf, const char *name, const struct stat *stbuf, off_t off);


static int do_getattr( const char *path, struct stat *st )
{
	printf( "[getattr] called\n" );
	printf( "\tAttributes of %s requested\n", path );	
	st->st_uid = getuid();	// Owner of the file, is the user who mounted the file system.
	st->st_gid = getgid();	// Group owner of the file, group to which the user who mounted the fs belong to.
	st->st_atime = time( NULL );	// The last access time.
	st->st_mtime = time( NULL );	// The last modification time.

	if ( strcmp ( path, "/" ) == 0 )
	{
		st->st_mode = S_IFDIR | 0755;
		st->st_nlink = 2;
	}
	else
	{
		st->st_mode = S_IFREG | 0644;
		st->st_nlink = 1;
		st->st_size = 1024;
	}

	return 0;
}

static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)

{
	printf( "[readdir] called\n" );
	printf("--> Getting the list of files of %s\n", path);

	filler( buffer, ".", NULL, 0);
	filler( buffer, "..", NULL, 0);
	if( strcmp( path, "/" ) == 0 )
	{
		filler( buffer, "file54", NULL, 0 );
		filler( buffer, "file349", NULL, 0 );
	}
	return 0;
}



static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi)
{
	printf( "[read] called\n" );
	printf( "\t for the path %s\n" );
	
	char file54Text[] = "Hello World from file54!";
	char file349Text[] = "Hello World from file349!";
	char *selectedText = NULL;

	if ( strcmp( path, "/file54" ) == 0 )
	{
		selectedText = file54Text;
	}
	else if ( strcmp( path, "/file349" ) == 0 )
	{
		selectedText = file349Text;
	}
	else
	{
		return -1;
	}

	memcpy( buffer, selectedText + offset, size );

	return strlen( selectedText ) - offset;
}

static struct fuse_operations operations = {
	.getattr = do_getattr,
	.readdir = do_readdir,
	.read = do_read,
};

int main( int argc, char *argv[] )
{
	return fuse_main( argc, argv, &operations, NULL );
}
