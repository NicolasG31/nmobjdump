/*
** nm2.c for nm in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Mon Feb 20 11:09:55 2017 Nicolas Guillon
** Last update Sun Feb 26 15:59:25 2017 Nicolas Guillon
*/

#include "../nmobjdump.h"

int     getElfVer(Elf64_Ehdr *data)
{
  if (data->e_ident[EI_MAG0] != ELFMAG0 ||
      data->e_ident[EI_MAG1] != ELFMAG1 ||
      data->e_ident[EI_MAG2] != ELFMAG2 ||
      data->e_ident[EI_MAG3] != ELFMAG3)
    return (-1);

  return (data->e_ident[EI_CLASS]);
}

Elf64_Shdr	*secFnd(unsigned int type, void *buff, int pos)
{
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*sct;
  int		i;
  int		fnd;

  elf = buff;
  fnd = 0;
  i = 0;
  while (i < elf->e_shnum)
    {
      sct = buff + elf->e_shoff + (elf->e_shentsize * i);
      if (sct->sh_type == type)
        {
          if (fnd == pos)
            return (sct);
          fnd++;
        }
      i++;
    }
  return (0);
}

int		toNotPrint(void *buff, void *s, int nb)
{
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*sec;
  Elf64_Shdr	*sectab;
  int		type;

  elf = buff;
  sec = s;
  type = sec->sh_type;
  if (type == SHT_NULL || type == SHT_NOBITS
      || nb == elf->e_shstrndx
      || !sec->sh_size)
    return (1);
  if ((sectab = secFnd(SHT_SYMTAB, buff, 0)))
    if (sectab->sh_name == sec->sh_name)
      return (1);
  if ((sectab = secFnd(SHT_STRTAB, buff, 1)))
    if (sectab->sh_name == sec->sh_name)
      return (1);
  if ((sectab = secFnd(SHT_STRTAB, buff, 2)))
    if (sectab->sh_name == sec->sh_name)
      return (1);
  return (0);
}

void		getSecH(void *buff, Elf64_Shdr **sec, char **strtab)
{
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*s;
  int		i;
  int		size;

  i = 0;
  size = 0;
  elf = buff;
  s = buff + elf->e_shoff + (elf->e_shentsize * elf->e_shstrndx);
  *sec = s;
  *strtab = buff + s->sh_offset;
}


int		printSecs(void *buff, char *file, int ac, struct stat s)
{
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*scn;
  char		*strtab;
  int		i;

  i = 0;
  elf = buff;
  getSecH(buff, &scn, &strtab);
  if (!elf->e_shoff)
    return (0);
  printMachine(elf, file, ac);
  while (i < elf->e_shnum)
    {
      scn = buff + elf->e_shoff + (elf->e_shentsize * i);
      if (!toNotPrint(buff, scn, i))
	{
	  printf("Contents of section %s:\n", strtab + scn->sh_name);
	  printSec(buff, scn);
	}
      i++;
    }
  return (1);
}

