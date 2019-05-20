/*
** prog.c for nmobjdump in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas.guillon@epitech.eu>
** 
** Started on  Tue Feb 14 13:57:05 2017 Nicolas Guillon
** Last update Mon Feb 27 10:17:39 2017 Nicolas Guillon
*/

#include "../nmobjdump.h"

int		headerFile(void *buff, struct stat s, char *file, int ac)
{
  Elf64_Ehdr	*elf;
  int		ver;

  elf = buff;
  if (elf->e_ident[EI_VERSION] != 1 || (ver = getElfVer(elf)) == -1)
    {
      printf("nm: %s: File format not recognized\n", file);
      return (-1);
    }
  if (ver == 2)
    {
      if (!checkSize(buff, file, s))
	return (0);
      return (printSymb(buff, file, ac, 0));
    }
  else if (ver == 1)
    {
      if (!checkSize32(buff, file, s))
	return (0);
      return (printSymb32(buff, file, ac, 0));
    }
  else
    return (-1);
}

int		statMapFile(int fd, char *file, int ac)
{
  void		*buff;
  struct stat	 s;

  fstat(fd, &s);
  if ((buff = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
      (void *)-1)
    {
      printf("nm: Warning : '%s' is not an ordinary file\n", file);
      return (-1);
    }
  close(fd);
  return headerFile(buff, s, file, ac);
}

int	openFile(char *file, int ac)
{
  int	fd;

  fd = open(file, O_RDONLY);
  if (fd == -1)
    {
      printf("nm: '%s': No such file\n", file);
      return -1;
    }
  return statMapFile(fd, file, ac);
}

int	main(int ac, char **av)
{
  int	i;

  i = 1;
  if (ac < 2)
    {
      openFile("a.out", 2);
      return 0;
    }
  while (i != ac)
    {
      if (i != 1)
	printf("\n");
      openFile(av[i++], i);
    }
  return (1);
}
