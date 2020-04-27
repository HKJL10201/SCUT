#define FUSE_USE_VERSION 26

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include "u_fs.h"
char *disk = "/home/ender/OS/diskimg";

int write_blk(long blk, struct u_fs_disk_block * blk_info) 
{
	FILE* f;
	f = fopen(disk, "r+");
	if (f == NULL)
		return -1;
	if (fseek(f, blk * BLOCK_SIZE, SEEK_SET) != 0) {
		fclose(f);
		return -1;
	}
	fwrite(blk_info, sizeof(struct u_fs_disk_block), 1, f);
	if (ferror(f) || feof(f)) {
		fclose(f);
		return -1;
	}
	fclose(f);
	return 0;
}

int is_exist(struct u_fs_file_directory *file_dir, char *p, char *q, int* offset, int* pos, int size, int mode) 
{
	while (*offset < size) {
		if (mode == 0)
			*pos = *offset;
		else if (mode == 1 && file_dir->flag == 1
				&& strcmp(p, file_dir->fname) == 0
				&& ((*q == '\0' && strlen(file_dir->fext) == 0)
						|| (*q != '\0' && strcmp(q, file_dir->fext) == 0)))
			return -EEXIST;
		else if (mode == 2 && file_dir->flag == 2
				&& strcmp(p, file_dir->fname) == 0)
			return -EEXIST;
		file_dir++;
		*offset += sizeof(struct u_fs_file_directory);
	}
	return 0;
}

void del_p(void*ptr, ...) 
{
	va_list ptrs;
	int n = 0;
	char *pars;
	va_start(ptrs, ptr);
	free(ptr);
	while (1) {
		pars = va_arg(ptrs, void *);
		if (pars == NULL)
			break;
		free(pars);
		n++;
	}
	va_end(ptrs);
}

int set_bitmap(long start_blk, int mode) 
{
	if (start_blk == -1)
		return -1;
	int start = start_blk / 8;
	int left = start_blk % 8;
	int f;

	int mask = 1;
	mask <<= left;

	FILE* fp = NULL;
	fp = fopen(disk, "r+");
	if (fp == NULL)
		return -1;
	fseek(fp, BLOCK_SIZE + start, SEEK_SET);
	int *tmp = malloc(sizeof(int));
	fread(tmp, sizeof(int), 1, fp);
	f = *tmp;
	if (mode)
		f |= mask;
	else
		f &= ~mask;

	*tmp = f;
	fseek(fp, BLOCK_SIZE + start, SEEK_SET);
	fwrite(tmp, sizeof(int), 1, fp);
	fclose(fp);
	free(tmp);
	return 0;
}

int read_blk(long blk, struct u_fs_disk_block * blk_info) 
{
	FILE* fp;
	fp = fopen(disk, "r+");
	if (fp == NULL)
		return -1;
	fseek(fp, blk * BLOCK_SIZE, SEEK_SET);
	fread(blk_info, sizeof(struct u_fs_disk_block), 1, fp);
	if (ferror(fp) || feof(fp)) {
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}

int read_path(const char * path, struct u_fs_file_directory *attr) 
{
	struct u_fs_disk_block *blk;
	blk = malloc(sizeof(struct u_fs_disk_block));
	/* read the super block*/
	if (read_blk(0, blk) == -1) 
	{
		free(blk);
		return -1;
	}
	struct sb* sb_record;
	sb_record = (struct sb*) blk;
	long start_blk;
	start_blk = sb_record->first_blk;

	char *p, *q, *tmp_path;
	tmp_path = strdup(path);
	p = tmp_path;
	if (strcmp(path, "/") == 0) 
	{
		attr->flag = 2;
		attr->nStartBlock = start_blk;
		free(blk);
		return 0;
	}
	if (!p) 
	{
		free(blk);
		return -1;
	}
	p++;
	q = strchr(p, '/');
	if (q != NULL) 
	{
		tmp_path++;
		*q = '\0';
		q++;
		p = q;
	}
	q = strchr(p, '.');
	if (q != NULL) 
	{
		*q = '\0';
		q++;
	}
	if (read_blk(start_blk, blk) == -1) 
	{
		free(blk);
		return -1;
	}
	struct u_fs_file_directory *file_dir = (struct u_fs_file_directory*) blk->data;
	int offset = 0;
	if (*tmp_path != '/') 
	{ 
		while (offset < blk->size) 
		{
			if (strcmp(file_dir->fname, tmp_path) == 0 && file_dir->flag == 2) 
			{
				start_blk = file_dir->nStartBlock;
				break;
			}
			file_dir++;
			offset += sizeof(struct u_fs_file_directory);
		}
		if (offset == blk->size) 
		{
			free(blk);
			return -1;
		}
		if (read_blk(start_blk, blk) == -1) 
		{
			free(blk);
			return -1;
		}
		file_dir = (struct u_fs_file_directory*) blk->data;
	}
	offset = 0;
	while (offset < blk->size) 
	{
		if (file_dir->flag != 0 && strcmp(file_dir->fname, p) == 0 && (q == NULL || strcmp(file_dir->fext, q) == 0)) 
		{
			start_blk = file_dir->nStartBlock;
			strcpy(attr->fname, file_dir->fname);
			strcpy(attr->fext, file_dir->fext);
			attr->fsize = file_dir->fsize;
			attr->nStartBlock = file_dir->nStartBlock;
			attr->flag = file_dir->flag;
			free(blk);
			return 0;
		}
		file_dir++;
		offset += sizeof(struct u_fs_file_directory);
	}
	free(blk);
	return -1;
}

int srh_emp(int num, long* start_blk) 
{
	*start_blk = 1 + BITMAP_BLOCK + 1;
	int tmp = 0;
	FILE* fp = NULL;
	fp = fopen(disk, "r+");
	if (fp == NULL)
		return 0;
	int start, left;
	unsigned int mask, f;
	int *flag;

	int max = 0;
	long max_start = -1;

	while (*start_blk < TOTAL_BLOCKS - 1) 
	{
		start = *start_blk / 8;
		left = *start_blk % 8;
		mask = 1;
		mask <<= left;
		fseek(fp, BLOCK_SIZE + start, SEEK_SET);
		flag = malloc(sizeof(int));
		fread(flag, sizeof(int), 1, fp);
		f = *flag;
		for (tmp = 0; tmp < num; tmp++) 
		{
			if ((f & mask) == mask)	
				break;
			if ((mask & 0x80000000) == 0x80000000) 
			{
				fread(flag, sizeof(int), 1, fp);
				f = *flag;
				mask = 1;
			} else
				mask <<= 1;
		}
		if (tmp > max) 
		{
			max_start = *start_blk;
			max = tmp;
		}
		if (tmp == num)
			break;
		*start_blk = (tmp + 1) + *start_blk;
		tmp = 0;
	}
	*start_blk = max_start;
	fclose(fp);
	int j = max_start;
	int i;
	for (i = 0; i < max; ++i) 
	{
		if (set_bitmap(j++, 1) == -1) 
		{
			free(flag);
			return -1;
		}
	}
	free(flag);
	return max;
}

int lar_blk(long p_dir_blk, struct u_fs_file_directory *file_dir, struct u_fs_disk_block *blk_info, long *tmp, char*p, char*q, int mode) 
{
	long blk;
	tmp = malloc(sizeof(long));
	if (srh_emp(1, tmp) == 1)
		blk = *tmp;
	else 
	{
		del_p(p, q, blk_info, NULL);
		return -errno;
	}
	free(tmp);
	blk_info->nNextBlock = blk;
	write_blk(p_dir_blk, blk_info);

	blk_info->size = sizeof(struct u_fs_file_directory);
	blk_info->nNextBlock = -1;
	file_dir = (struct u_fs_file_directory*) blk_info->data;
	strcpy(file_dir->fname, p);
	if (mode == 1 && *q != '\0')
		strcpy(file_dir->fext, q);
	file_dir->fsize = 0;
	file_dir->flag = mode;

	tmp = malloc(sizeof(long));
	if (srh_emp(1, tmp) == 1)
		file_dir->nStartBlock = *tmp;
	else {
		return -errno;
	}
	free(tmp);
	write_blk(blk, blk_info);

	blk_info->size = 0;
	blk_info->nNextBlock = -1;
	strcpy(blk_info->data, "\0");
	write_blk(file_dir->nStartBlock, blk_info);
	return 0;
}

int is_emp(const char* path) 
{

	struct u_fs_disk_block *blk = malloc(sizeof(struct u_fs_disk_block));
	struct u_fs_file_directory *attr = malloc(sizeof(struct u_fs_file_directory));
	if (read_path(path, attr) == -1) 
	{
		del_p(blk, attr, NULL);
		return 0;
	}
	long sta;
	sta = attr->nStartBlock;
	if (attr->flag == 1) 
	{
		del_p(blk, attr, NULL);
		return 0;
	}
	if (read_blk(sta, blk) == -1) 
	{
		del_p(blk, attr, NULL);
		return 0;
	}
	struct u_fs_file_directory *file_dir = (struct u_fs_file_directory*) blk->data;
	int pos = 0;
	while (pos < blk->size) 
	{
		if (file_dir->flag != 0) 
		{
			del_p(blk, attr, NULL);
			return 0;
		}
		file_dir++;
		pos += sizeof(struct u_fs_file_directory);
	}
	del_p(blk, attr, NULL);
	return 1;
}

int devide(char*name, char*ext, const char*path, long*p_dir_blk, int mode) 
{
	char*tmp_p, *p, *q;
	tmp_p = strdup(path);
	struct u_fs_file_directory* attr = malloc(sizeof(struct u_fs_file_directory));
	p = tmp_p;
	if (!p)
		return -errno;
	p++;
	q = strchr(p, '/');
	if (mode == 2 && q != NULL)
		return -EPERM;
	else if (q != NULL) 
	{
		*q = '\0';
		q++;
		p = q;
		if (read_path(tmp_p, attr) == -1) 
		{
			free(attr);
			return -ENOENT;
		}
	}
	if (q == NULL) 
	{
		if (read_path("/", attr) == -1) 
		{
			free(attr);
			return -ENOENT;
		}
	}
	if (mode == 1) 
	{
		q = strchr(p, '.');
		if (q != NULL) 
		{
			*q = '\0';
			q++;
		}
	}
	if (mode == 1) 
	{
		if (strlen(p) > MAX_FILENAME + 1) 
		{
			free(attr);
			return -ENAMETOOLONG;
		} 
		else if (strlen(p) > MAX_FILENAME) 
		{
			if (*(p + MAX_FILENAME) != '~') 
			{
				free(attr);
				return -ENAMETOOLONG;
			}
		} 
		else if (q != NULL) 
		{
			if (strlen(q) > MAX_EXTENSION + 1) 
			{
				free(attr);
				return -ENAMETOOLONG;
			} 
			else if (strlen(q) > MAX_EXTENSION) 
			{
				if (*(q + MAX_EXTENSION) != '~') 
				{
					free(attr);
					return -ENAMETOOLONG;
				}
			}
		}
	} 
	else if (mode == 2) 
	{
		if (strlen(p) > MAX_FILENAME) 
		{
			free(attr);
			return -ENAMETOOLONG;
		}
	}
	*name = *ext = '\0';
	if (p != NULL)
		strcpy(name, p);
	if (q != NULL)
		strcpy(ext, q);
	free(tmp_p);
	*p_dir_blk = attr->nStartBlock;
	free(attr);
	if (*p_dir_blk == -1) 
		return -ENOENT;
	return 0;
}

int create(const char* path, int mode) 
{
	int res;
	long p_dir_blk;
	char *p = malloc(15 * sizeof(char)), *q = malloc(15 * sizeof(char));
	if ((res = devide(p, q, path, &p_dir_blk, mode))) 
	{
		del_p(p, q, NULL);
		return res;
	}
	struct u_fs_disk_block *blk = malloc(sizeof(struct u_fs_disk_block));
	if (read_blk(p_dir_blk, blk) == -1) 
	{
		del_p(blk, p, q, NULL);
		return -ENOENT;
	}
	struct u_fs_file_directory *file_dir = (struct u_fs_file_directory*) blk->data;
	int offset = 0;
	int pos = blk->size;
	if ((res = is_exist(file_dir, p, q, &offset, &pos, blk->size, mode))) 
	{
		del_p(blk, p, q, NULL);
		return res;
	}
	file_dir += offset / sizeof(struct u_fs_file_directory);
	long *tmp = malloc(sizeof(long));
	if (pos == blk->size) 
	{
		if (blk->size > MAX_DATA_IN_BLOCK) 
		{
			if ((res = lar_blk(p_dir_blk, file_dir, blk, tmp, p, q, mode))) 
			{
				del_p(p, q, blk, NULL);
				return res;
			}
			del_p(p, q, blk, NULL);
			return 0;
		} 
		else
			blk->size += sizeof(struct u_fs_file_directory);
	} 
	else 
	{
		offset = 0;
		file_dir = (struct u_fs_file_directory*) blk->data;
		while (offset < pos)
			file_dir++;
	}
	strcpy(file_dir->fname, p);
	if (mode == 1 && *q != '\0')
		strcpy(file_dir->fext, q);
	file_dir->fsize = 0;
	file_dir->flag = mode;
	tmp = malloc(sizeof(long));
	if ((res = srh_emp(1, tmp)) == 1) 
		file_dir->nStartBlock = *tmp;
	else 
	{
		del_p(blk, p, q, NULL);
		return -errno;
	}
	free(tmp);

	write_blk(p_dir_blk, blk);
	blk->size = 0;
	blk->nNextBlock = -1;
	strcpy(blk->data, "\0");
	write_blk(file_dir->nStartBlock, blk);
	del_p(p, q, blk, NULL);
	return 0;
}

int set_attr(const char* path, struct u_fs_file_directory* attr) 
{
	int res;
	struct u_fs_disk_block* blk_info = malloc(sizeof(struct u_fs_disk_block));
	char *p = malloc(15 * sizeof(char)), *q = malloc(15 * sizeof(char));
	long start_blk;
	if ((res = devide(p, q, path, &start_blk, 1))) 
	{
		del_p(p, q, NULL);
		return res;
	}
	if (read_blk(start_blk, blk_info) == -1) 
	{
		res = -1;
		del_p(blk_info, NULL);
		return res;
	}
	struct u_fs_file_directory *file_dir = (struct u_fs_file_directory*) blk_info->data;
	int offset = 0;
	while (offset < blk_info->size) 
	{
		if (file_dir->flag != 0 && strcmp(p, file_dir->fname) == 0 && (*q == '\0' || strcmp(q, file_dir->fext) == 0)) 
		{
			strcpy(file_dir->fname, attr->fname);
			strcpy(file_dir->fext, attr->fext);
			file_dir->fsize = attr->fsize;
			file_dir->nStartBlock = attr->nStartBlock;
			file_dir->flag = attr->flag;
			res = 0;
			break;
		}
		file_dir++;
		offset += sizeof(struct u_fs_file_directory);
	}
	del_p(p, q, NULL);
	if (write_blk(start_blk, blk_info) == -1) 
		res = -1;
	del_p(blk_info, NULL);
	return res;
}

int rmv_file(const char *path, int mode) 
{
	struct u_fs_file_directory *attr = malloc(sizeof(struct u_fs_file_directory));
	if (read_path(path, attr) == -1) 
	{
		free(attr);
		return -ENOENT;
	}
	if (mode == 1 && attr->flag == 2) 
	{
		free(attr);
		return -EISDIR;
	} else if (mode == 2 && attr->flag == 1) 
	{
		free(attr);
		return -ENOTDIR;
	}
	struct u_fs_disk_block* blk_info = malloc(sizeof(struct u_fs_disk_block));
	if (mode == 1) 
	{
		long next_blk = attr->nStartBlock;
		while (next_blk != -1) 
		{
		set_bitmap(next_blk, 0);
		read_blk(next_blk, blk_info);
		next_blk = blk_info->nNextBlock;
		}
	} 
	else if (!is_emp(path)) 
	{
		del_p(blk_info, attr, NULL);
		return -ENOTEMPTY;
	}
	attr->flag = 0;
	if (set_attr(path, attr) == -1) 
	{
		del_p(blk_info, attr, NULL);
		return -1;
	}
	del_p(blk_info, attr, NULL);
	return 0;
}

////////////////////////////////////////////////////////////////

void * u_fs_init(struct fuse_conn_info *conn) 
{
	FILE * fp = NULL;
	fp = fopen(disk, "r+");
	if (fp == NULL) {
		fprintf(stderr, "unsuccessful!\n");
		return;
	}
	struct sb *sb_record = malloc(sizeof(struct sb));
	fread(sb_record, sizeof(struct sb), 1, fp);
	TOTAL_BLOCKS = sb_record->fs_size;
	fclose(fp);
	return (long*) TOTAL_BLOCKS;
}

static int u_fs_getattr(const char *path, struct stat *stbuf) 
{
	struct u_fs_file_directory *attr = malloc(sizeof(struct u_fs_file_directory));
	if (read_path(path, attr) == -1) 
	{
		free(attr);
		return -ENOENT;
	}
	memset(stbuf, 0, sizeof(struct stat));
	// All files will be full access (i.e., chmod 0666), with permissions to be mainly ignored
	if (attr->flag == 2) {   //directory
		stbuf->st_mode = S_IFDIR | 0666;
	} else if (attr->flag == 1) {   //regular file
		stbuf->st_mode = S_IFREG | 0666;
		stbuf->st_size = attr->fsize;
	}
	free(attr);
	return 0;
}

static int u_fs_readdir(const char*path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info*fi) 
{
	struct u_fs_disk_block *blk;
	struct u_fs_file_directory *attr;
	blk = malloc(sizeof(struct u_fs_disk_block));
	attr = malloc(sizeof(struct u_fs_file_directory));
	if (read_path(path, attr) == -1) 
	{
		del_p(attr, blk, NULL);
		return -ENOENT;
	}
	long start_blk = attr->nStartBlock;
	if (attr->flag == 1) 
	{
		del_p(attr, blk, NULL);
		return -ENOENT;
	}
	if (read_blk(start_blk, blk)) 
	{
		del_p(attr, blk, NULL);
		return -ENOENT;
	}
	//all directory had . and .. child_directory
	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	struct u_fs_file_directory *file_dir = (struct u_fs_file_directory*) blk->data;
	int pos = 0;
	char name[MAX_FILENAME + MAX_EXTENSION + 2];
	while (pos < blk->size) 
	{
		strcpy(name, file_dir->fname);
		if (strlen(file_dir->fext) != 0) 
		{
			strcat(name, ".");
			strcat(name, file_dir->fext);
		}
		if (file_dir->flag != 0 && name[strlen(name) - 1] != '~' && filler(buf, name, NULL, 0))
			break;
		file_dir++;
		pos += sizeof(struct u_fs_file_directory);
	}
	del_p(attr, blk, NULL);
	return 0;
}

static int u_fs_mkdir(const char *path, mode_t mode) 
{
	int res = create(path, 2);
	return res;
}

static int u_fs_rmdir(const char *path) 
{
	int res = rmv_file(path, 2);
	return res;
}

static int u_fs_mknod(const char *path, mode_t mode, dev_t rdev) 
{
	int res = create(path, 1);
	return res;
}

static int u_fs_unlink(const char *path) 
{
	int res = rmv_file(path, 1);
	return res;
}

static int u_fs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) 
{
	struct u_fs_file_directory *attr = malloc(sizeof(struct u_fs_file_directory));
	read_path(path, attr);
	if (offset > attr->fsize) 
	{
		free(attr);
		return -EFBIG;
	}
	long start_blk = attr->nStartBlock;
	if (start_blk == -1) 
	{
		free(attr);
		return -errno;
	}
	struct u_fs_disk_block *blk_info = malloc(sizeof(struct u_fs_disk_block));
	int para_offset = offset;
	int num;
	while (1) 
	{
		if (read_blk(start_blk, blk_info) == -1) 
			return -errno;
		if (offset <= blk_info->size)
			break;
		offset -= blk_info->size;
		start_blk = blk_info->nNextBlock;
	}
	char* pt = blk_info->data;
	pt += offset;
	int towrite = 0;
	int writen = 0;
	towrite = (MAX_DATA_IN_BLOCK - offset < size ? MAX_DATA_IN_BLOCK - offset : size);
	strncpy(pt, buf, towrite);
	buf += towrite;
	blk_info->size += towrite;
	writen += towrite;
	size -= towrite;
	long* next_blk = malloc(sizeof(long));
	if (size > 0) 
	{
		num = srh_emp(size / MAX_DATA_IN_BLOCK + 1, next_blk);
		if (num == -1) 
		{
			del_p(attr, blk_info, next_blk, NULL);
			return -errno;
		}
		blk_info->nNextBlock = *next_blk;
		write_blk(start_blk, blk_info);
		int i;
		while (1) 
		{
			for (i = 0; i < num; ++i) 
			{
				towrite = (MAX_DATA_IN_BLOCK < size ? MAX_DATA_IN_BLOCK : size);
				blk_info->size = towrite;
				strncpy(blk_info->data, buf, towrite);
				buf += towrite;
				size -= towrite;
				writen += towrite;
				if (size == 0)
					blk_info->nNextBlock = -1;
				else
					blk_info->nNextBlock = *next_blk + 1;
				write_blk(*next_blk, blk_info);
				*next_blk = *next_blk + 1;
			}
			if (size == 0)
				break;
			num = srh_emp(size / MAX_DATA_IN_BLOCK + 1, next_blk);
			if (num == -1) 
			{
				del_p(attr, blk_info, next_blk, NULL);
				return -errno;
			}
		}
	} 
	else if (size == 0) 
	{
		long next_blk;
		next_blk = blk_info->nNextBlock;
		blk_info->nNextBlock = -1;
		write_blk(start_blk, blk_info);
		while (next_blk != -1) 
		{
			set_bitmap(next_blk, 0);
			read_blk(next_blk, blk_info);
			next_blk = blk_info->nNextBlock;
		}
	}
	size = writen;
	attr->fsize = para_offset + size;
	if (set_attr(path, attr) == -1) 
		size = -errno;
	del_p(attr, blk_info, next_blk, NULL);
	return size;
}

static int u_fs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) 
{
	struct u_fs_file_directory *attr = malloc(sizeof(struct u_fs_file_directory));
	//get the file's attribute with path
	if (read_path(path, attr) == -1) 
	{
		free(attr);
		return -ENOENT;
	}
	//directory can't be read ,it must be a file
	if (attr->flag == 2) 
	{
		free(attr);
		return -EISDIR;
	}
	struct u_fs_disk_block *blk_info;		//the file content's block
	blk_info = malloc(sizeof(struct u_fs_disk_block));

	if (read_blk(attr->nStartBlock, blk_info) == -1) {
		del_p(attr, blk_info, NULL);
		return -1;
	}

	if (offset < attr->fsize) 
	{
		if (offset + size > attr->fsize)
			size = attr->fsize - offset;
	} 
	else
		size = 0;
	int real_offset, blk_num, i, ret = 0;
	long start_blk = blk_info->nNextBlock;
	blk_num = offset / MAX_DATA_IN_BLOCK;
	real_offset = offset % MAX_DATA_IN_BLOCK;
	for (i = 0; i < blk_num; i++) 
	{
		if (read_blk(blk_info->nNextBlock, blk_info) == -1|| start_blk == -1) 
		{
			printf("read_block_from_pos failed!\n");
			del_p(attr, blk_info, NULL);
			return -1;
		}
	}
	int temp = size;
	char *pt = blk_info->data;
	pt += real_offset;
	ret = (MAX_DATA_IN_BLOCK - real_offset < size ? MAX_DATA_IN_BLOCK - real_offset : size);
	memcpy(buf, pt, ret);
	temp -= ret;
	while (temp > 0) 
	{
		if (read_blk(blk_info->nNextBlock, blk_info) == -1) 
		{
			printf("read_block_from_pos failed!\n");
			break;
		}
		if (temp > MAX_DATA_IN_BLOCK) 
		{
			memcpy(buf + size - temp, blk_info->data, MAX_DATA_IN_BLOCK);
			temp -= MAX_DATA_IN_BLOCK;
		} 
		else 
		{
			memcpy(buf + size - temp, blk_info->data, temp);
			break;
		}
	}
	del_p(attr, blk_info, NULL);
	return size;
}

static int u_fs_truncate(const char *path, off_t size) 
{return 0;}
static int u_fs_flush(const char*path, struct fuse_file_info *fi) 
{return 0;}
static int u_fs_open(const char*path, struct fuse_file_info *fi) 
{return 0;}

///////////////////////////////////////////////////////////////////////////////////

static struct fuse_operations ufs_op = 
{ 
	.getattr = u_fs_getattr, 
	.open = u_fs_open, 
	.readdir = u_fs_readdir, 
	.mkdir = u_fs_mkdir,
	.rmdir = u_fs_rmdir, 
	.mknod = u_fs_mknod, 
	.write = u_fs_write, 
	.read = u_fs_read, 
	.unlink = u_fs_unlink, 
	.truncate = u_fs_truncate,
	.flush = u_fs_flush, 
	.init = u_fs_init 
};

/////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) 
{
	return fuse_main(argc, argv, &ufs_op, NULL);
}