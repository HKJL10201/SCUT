#include "u_fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
	char *disk = "/home/ender/OS/diskimg";
	FILE * f = NULL;
	f = fopen(disk, "r+");
	if (f == NULL) {
		printf("open disk failed\n");
		return 0;
	}//dd bs=1K count=5K if=/dev/zero of=diskimg
	struct sb *s_b = malloc(sizeof(struct sb));
	/*init super_block*/
	fseek(f, 0, SEEK_END);
	s_b->fs_size = ftell(f) / BLOCK_SIZE;
	s_b->first_blk = 1 + BITMAP_BLOCK;
	s_b->bitmap = BITMAP_BLOCK;
	if (fseek(f, 0, SEEK_SET) != 0)
		fprintf(stderr, "failed!\n");
	fwrite(s_b, sizeof(struct sb), 1, f);
	/*init Bitmap_block*/
	if (fseek(f, BLOCK_SIZE, SEEK_SET) != 0)
		fprintf(stderr, "failed!\n");
	int blk[40];
	memset(blk, -1, sizeof(blk));    //32*40=1280
	fwrite(blk, sizeof(blk), 1, f);
	int n=(1<<30)|(1<<31);
	fwrite(&n, sizeof(int), 1, f);
	int em[87];
	memset(em, 0, sizeof(em));
	fwrite(em, sizeof(em), 1, f);
	int sum = (BITMAP_BLOCK - 1) * BLOCK_SIZE;
	char rest[sum];
	memset(rest, 0, sizeof(rest));
	fwrite(rest, sizeof(rest), 1, f);
	/* init root */
	fseek(f, BLOCK_SIZE * (BITMAP_BLOCK + 1), SEEK_SET);
	struct u_fs_disk_block *root = malloc(sizeof(struct u_fs_disk_block));
	root->size = 0;
	root->nNextBlock = -1;
	root->data[0] = '\0';
	fwrite(root, sizeof(struct u_fs_disk_block), 1, f);
	if (fclose(f) != 0)
		printf("close failed !\n");
	else
		printf("success!\n");
	return 0;
}