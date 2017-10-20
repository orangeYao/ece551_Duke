#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

void myStat(char * filename)
{
   struct stat sb;

   if (lstat(filename, &sb) == -1) {
       fprintf(stderr, "stat: cannot stat '%s': ", filename);
       perror ("");
       exit(EXIT_FAILURE);
   }
   
   if (S_ISLNK(sb.st_mode))
   {
       char buf[256];
       buf[readlink(filename, buf, 256)] = '\0';
       printf("  File: '%s' -> '%s'\n", filename, buf);
   }
   else 
       printf("  File: '%s'\n", filename);


   const char * file_type;
   char fst;

   switch (sb.st_mode & S_IFMT) {
   case S_IFBLK:  {file_type = "block special file";        fst = 'b';} break;
   case S_IFCHR:  {file_type = "character special file";    fst = 'c';} break;
   case S_IFDIR:  {file_type = "directory";                 fst = 'd';} break;
   case S_IFIFO:  {file_type = "fifo";                      fst = 'p';} break;
   case S_IFLNK:  {file_type = "symbolic link";             fst = 'l';} break;
   case S_IFREG:  {file_type = "regular file";              fst = '-';} break;
   case S_IFSOCK: {file_type = "socket";                    fst = 's';} break;
   default:       {file_type = "unknown?";                  fst = '@';} break;
   }

   printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n", 
            (long) sb.st_size,
            (long) sb.st_blocks,
            (long) sb.st_blksize,
            file_type);


   if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode))
   {
       printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %x,%x\n",
            sb.st_dev, sb.st_dev, (long) sb.st_ino, (long) sb.st_nlink, 
            major(sb.st_rdev), minor(sb.st_rdev));

   }
   else
       printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
            sb.st_dev, sb.st_dev, (long) sb.st_ino, (long) sb.st_nlink);



   char hum[11];
   for (int i=0; i<11; i++)
       hum[i] = '-';
   hum[0] = fst; 
   hum[10] = '\0';

   if ((sb.st_mode & S_IRUSR) != 0)
       hum[1] = 'r';
   if ((sb.st_mode & S_IWUSR) != 0)
       hum[2] = 'w';
   if ((sb.st_mode & S_IXUSR) != 0)
       hum[3] = 'x';
   if ((sb.st_mode & S_IRGRP) != 0)
       hum[4] = 'r';
   if ((sb.st_mode & S_IWGRP) != 0)
       hum[5] = 'w';
   if ((sb.st_mode & S_IXGRP) != 0)
       hum[6] = 'x';
   if ((sb.st_mode & S_IROTH) != 0)
       hum[7] = 'r';
   if ((sb.st_mode & S_IWOTH) != 0)
       hum[8] = 'w';
   if ((sb.st_mode & S_IXOTH) != 0)
       hum[9] = 'x';

   struct passwd *uu =  getpwuid(sb.st_uid);
   struct group *gg = getgrgid(sb.st_gid);

   printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n", 
           (unsigned int) (sb.st_mode & ~S_IFMT), hum,
           sb.st_uid, uu->pw_name,
           sb.st_gid, gg->gr_name);

   char *tmp = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
   printf("Access: %s\n", tmp);
   free(tmp);
   tmp = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
   printf("Modify: %s\n", tmp);
   free(tmp);
   tmp = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
   printf("Change: %s\n", tmp);
   free(tmp);
   printf(" Birth: -\n");

}


int main(int argc, char ** argv)
{
  for (int i=1; i<argc; i++)
      myStat(argv[i]);

  return EXIT_SUCCESS;
}
