/*
** nm2.c for nm in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Mon Feb 20 11:09:55 2017 Nicolas Guillon
** Last update Sun Feb 26 15:08:57 2017 Nicolas Guillon
*/

#include "../nmobjdump.h"

int		checkSize(void *buff, char *file, struct stat s)
{
  Elf64_Ehdr	*ehdr;
  Elf64_Shdr	*shdr;
  unsigned int	sizesec;

  sizesec = 0;
  ehdr = buff;
  shdr = buff + ehdr->e_shoff;
  sizesec += ehdr->e_shoff;
  sizesec += ehdr->e_shnum * sizeof(Elf64_Shdr);
  if (s.st_size < sizesec)
    {
      printf("nm: %s: File truncated\n", file);
      return (0);
    }
  return (1);

}
