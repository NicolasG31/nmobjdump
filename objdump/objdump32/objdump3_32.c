/*
** nm3.c for nm in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Wed Feb 22 10:34:31 2017 Nicolas Guillon
** Last update Sun Feb 26 14:53:08 2017 Nicolas Guillon
*/

#include "../../nmobjdump.h"

void		printMachine32(Elf32_Ehdr *elf, char *file, int ac)
{
  if (ac == 2)
    printf("\n");
  if (elf->e_ident[EI_CLASS] == 2)
    printf("%s:     file format elf64-x86-64\n", file);
  else if (elf->e_ident[EI_CLASS] == 1)
    printf("%s:     file format elf32-i386\n", file);
  if (elf->e_machine == 62)
    printf("architecture: i386:x86-64\n");
  else if (elf->e_machine == 3)
    printf("architecture: i386\n");
  else
    printf("architecture: unknown\n");
  printf("start address 0x%016x\n\n", elf->e_entry);
}

void            printString32(Elf32_Shdr *sec, unsigned char *str, int nb)
{
  unsigned int  i;

  i = 0;
  while (i < 16)
    {
      if ((nb + i) < sec->sh_size)
        {
          if (str[nb + i] >= 32 && str[nb + i] < 127)
            printf("%c", str[nb + i]);
          else
            printf(".");
        }
      else
        printf(" ");
      i++;
    }
}

void		printHexa32(Elf32_Shdr *sec, unsigned char *str, int nb)
{
  unsigned int	i;

  i = 0;
  while (i < 16)
    {
      if ((nb + i) < sec->sh_size)
        printf("%02x", str[nb + i]);
      else
        printf("  ");
      if ((i % 4) == 3)
        printf(" ");
      i++;
    }
}

void		printSec32(void *buff, Elf32_Shdr *sec)
{
  char		*str;
  unsigned int	i;

  i = 0;
  str = buff + sec->sh_offset;
  while (i < sec->sh_size)
    {
      printf(" %04x ", sec->sh_addr + i);
      printHexa32(sec, str, i);
      printf(" ");
      printString32(sec, str, i);
      printf("\n");
      i += 16;
    }
}
