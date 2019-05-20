/*
** nm2.c for nm in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Mon Feb 20 11:09:55 2017 Nicolas Guillon
** Last update Sun Feb 26 23:29:04 2017 Nicolas Guillon
*/

#include "../../nmobjdump.h"

Elf32_Sym	**sortSymtab32(Elf32_Sym **tab, char *strtab)
{
  Elf32_Sym	*tmp;
  int		i;

  i = 0;
  while (tab[i])
    {
      if (tab[i] && tab[i + 1])
        {
          if (strcmp(remUnder32(strtab + tab[i]->st_name),
                     remUnder32(strtab + tab[i + 1]->st_name)) > 0)
            {
              tmp = tab[i];
              tab[i] = tab[i + 1];
              tab[i + 1] = tmp;
              i = -1;
            }
        }
      i++;
    }
  return (tab);
}


Elf32_Sym	**fillSymtab32(void *buff, Elf32_Shdr *sym, char *strtab)
{
  Elf32_Ehdr	*elf;
  Elf32_Sym	**tab;
  Elf32_Sym	*symtab;
  int		size;
  int		i;
  int		j;

  elf = buff;
  symtab = buff + sym->sh_offset;
  size = sym->sh_size / sym->sh_entsize;
  tab = malloc(sizeof(Elf32_Sym *) * (size + 1));
  i = 0;
  j = 0;
  while (i != size)
    {
      if (strlen(strtab + (symtab + i)->st_name) != 0)
      	{
	  tab[j] = symtab + i;
	  j++;
	}
      i++;
    }
  return (tab);
}

Elf32_Shdr	*shGet32(unsigned int type, void *buff)
{
  Elf32_Ehdr	*elf;
  Elf32_Shdr	*sh;
  int		i;
  int		pos;
  int		nb;

  i = 0;
  pos = 0;
  elf = buff;
  nb = 0;
  pos = howManyTables32(type, buff);
  if (pos == -1)
    return 0;
  while (i != elf->e_shnum)
    {
      sh = buff + elf->e_shoff + (elf->e_shentsize * i);
      if (sh->sh_type == type)
	{
	  if (nb == pos)
	    return (sh);
	  nb++;
	}
      i++;
    }
  return (0);
}

int		getSymb32(void *buff, Elf32_Shdr **sym, char **strtab, char *file)
{
  Elf32_Shdr	*sh;

  if ((*sym = shGet32(SHT_SYMTAB, buff)) == 0 || \
      (sh = shGet32(SHT_STRTAB, buff)) == 0)
    {
      printf("nm: %s: no symbols\n", file);
      return (0);
    }
  *strtab = buff + sh->sh_offset;
  return (1);
}

int		printSymb32(void *buff, char *file, int ac, int i)
{
  Elf32_Shdr	*sym;
  Elf32_Sym	**tab;
  char		*strtab;

  if (ac >= 3)
    printf("%s\n", file);
  if (getSymb32(buff, &sym, &strtab, file) == 0)
    return (0);
  tab = fillSymtab32(buff, sym, strtab);
  tab = sortSymtab32(tab, strtab);
  while (tab[i])
    {
      if (ELF32_ST_TYPE(tab[i]->st_info) != STT_FILE)
  	{
          if (tab[i]->st_value)
            printf("%016x ", tab[i]->st_value);
          else
            printf("\t\t ");
          printf("%c %s\n", getTypeSymb32(tab[i], sym, strtab),\
		 strtab + tab[i]->st_name);
  	}
      i++;
    }
  free(tab);
  return (1);
}
