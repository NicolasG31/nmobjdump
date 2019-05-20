/*
** nm2.c for nm in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Mon Feb 20 11:09:55 2017 Nicolas Guillon
** Last update Sun Feb 26 14:53:00 2017 Nicolas Guillon
*/

#include "../../nmobjdump.h"

Elf32_Shdr	*secFnd32(unsigned int type, void *buff, int pos)
{
  Elf32_Ehdr	*elf;
  Elf32_Shdr	*sct;
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

int		toNotPrint32(void *buff, void *s, int nb)
{
  Elf32_Ehdr	*elf;
  Elf32_Shdr	*sec;
  Elf32_Shdr	*sectab;
  int		type;

  elf = buff;
  sec = s;
  type = sec->sh_type;
  if (type == SHT_NULL || type == SHT_NOBITS
      || nb == elf->e_shstrndx
      || !sec->sh_size)
    return (1);
  if ((sectab = secFnd32(SHT_SYMTAB, buff, 0)))
    if (sectab->sh_name == sec->sh_name)
      return (1);
  if ((sectab = secFnd32(SHT_STRTAB, buff, 1)))
    if (sectab->sh_name == sec->sh_name)
      return (1);
  if ((sectab = secFnd32(SHT_STRTAB, buff, 2)))
    if (sectab->sh_name == sec->sh_name)
      return (1);
  return (0);
}

void		getSecH32(void *buff, Elf32_Shdr **sec, char **strtab)
{
  Elf32_Ehdr	*elf;
  Elf32_Shdr	*s;
  int		i;
  int		size;

  i = 0;
  size = 0;
  elf = buff;
  s = buff + elf->e_shoff + (elf->e_shentsize * elf->e_shstrndx);
  *sec = s;
  *strtab = buff + s->sh_offset;
}


int		printSecs32(void *buff, char *file, int ac, struct stat s)
{
  Elf32_Ehdr	*elf;
  Elf32_Shdr	*scn;
  char		*strtab;
  int		i;

  i = 0;
  elf = buff;
  getSecH32(buff, &scn, &strtab);
  if (!elf->e_shoff)
    return (0);
  printMachine32(elf, file, ac);
  while (i < elf->e_shnum)
    {
      scn = buff + elf->e_shoff + (elf->e_shentsize * i);
      if (!toNotPrint32(buff, scn, i))
	{
	  printf("Content of section %s:\n", strtab + scn->sh_name);
	  printSec32(buff, scn);
	}
      i++;
    }
  return (1);
}

