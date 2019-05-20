/*
** nm3.c for nm in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Wed Feb 22 10:34:31 2017 Nicolas Guillon
** Last update Sun Feb 26 23:30:46 2017 Nicolas Guillon
*/

#include "../../nmobjdump.h"

int	getElfVer32(Elf32_Ehdr *data)
{
  if (data->e_ident[EI_MAG0] != ELFMAG0 ||
      data->e_ident[EI_MAG1] != ELFMAG1 ||
      data->e_ident[EI_MAG2] != ELFMAG2 ||
      data->e_ident[EI_MAG3] != ELFMAG3)
    return (-1);

  return (data->e_ident[EI_CLASS]);
}

int	isFromSec32(Elf32_Sym *symtab, char *shstrtab,
		    Elf32_Shdr *sec, const char *name)
{
  return (!strcmp(&(shstrtab)[sec[symtab->st_shndx].sh_name], name));
}

char	getTypeSymb32(Elf32_Sym *sym, Elf32_Shdr *shdr, char *strtab)
{
  char	c;

  if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym->st_shndx == SHN_UNDEF)
        c = 'w';
    }
  else if (sym->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (sym->st_shndx == SHN_ABS)
    c = 'A';
  else if (sym->st_shndx == SHN_COMMON)
    c = 'C';
  else if (isFromSec32(sym, strtab, shdr, ".text")
	   || ELF32_ST_TYPE(sym->st_info) == STT_FUNC)
    c = 'T';
  else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  else
    c = '?';
  if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
    c += 32;
  return c;
}

char	*remUnder32(char *str)
{
  int	i;
  char	*nstr;

  i = 0;
  if (str[i] == '_')
    while (str[i] == '_')
      i++;
  nstr = strdup(&str[i]);
  return nstr;
}

int		howManyTables32(unsigned int type, void *buff)
{
  Elf32_Ehdr    *elf;
  Elf32_Shdr    *sh;
  int           i;
  int           pos;

  i = 0;
  pos = 0;
  elf = buff;
  while (i != elf->e_shnum)
    {
      sh = buff + elf->e_shoff + (elf->e_shentsize * i);
      if (sh->sh_type == type)
        pos++;
      i++;
    }
  return (pos - 1);
}
