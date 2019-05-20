/*
** nmobjectdump.h for nmobjectdump in /home/nicolas/nmobjdump
** 
** Made by Nicolas Guillon
** Login   <nicolas.guillon@epitech.eu>
** 
** Started on  Mon Feb 13 17:05:04 2017 Nicolas Guillon
** Last update Mon Feb 27 10:19:27 2017 Nicolas Guillon
*/

#ifndef NMOBJDUMP_H_
#define NMOBJDUMP_H_

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>

int		openFile(char *file, int ac);
int		statMapFile(int fd, char *file, int ac);
int		headerFile(void *buff, struct stat s, char *file, int ac);
char		*remUnder(char *str);
int		howManyTables(unsigned int type, void *buff);
char		print_type(Elf64_Sym *sym, Elf64_Shdr *shdr);
int		getElfVer(Elf64_Ehdr *data);
Elf64_Sym	**sortSymtab(Elf64_Sym **tab, char *strtab);
Elf64_Sym	**fillSymtab(void *buff, Elf64_Shdr *sym, char *strtab);
Elf64_Shdr	*shGet(unsigned int type, void *buff);
int		getSymb(void *buff, Elf64_Shdr **sym, char **strtab, char *file);
int		printSymb(void *buff, char *file, int ac, int i);
char		getTypeSymb(Elf64_Sym *sym, Elf64_Shdr *shdr, char *strtab);
int		isFromSec(Elf64_Sym *symtab, char *shstrtab, Elf64_Shdr *sec, const char *name);
int		printSecs(void *buff, char *file, int ac, struct stat s);
void		getSecH(void *buff, Elf64_Shdr **sec, char **strtab);
int		toNotPrint(void *buff, void *s, int nb);
Elf64_Shdr	*secFnd(unsigned int type, void *buff, int pos);
void		printSec(void *buff, Elf64_Shdr *sec);
void		printHexa(Elf64_Shdr *sec, unsigned char *str, int nb);
void		printString(Elf64_Shdr *sec, unsigned char *str, int nb );
void		printMachine(Elf64_Ehdr *elf, char *file, int ac);
int		checkSize(void *buff, char *file, struct stat s);
int		checkSize32(void *buff, char *file, struct stat s);
Elf32_Sym	**sortSymtab32(Elf32_Sym **tab, char *strtab);
Elf32_Sym	**fillSymtab32(void *buff, Elf32_Shdr *sym, char *strtab);
Elf32_Shdr	*shGet32(unsigned int type, void *buff);
int		getSymb32(void *buff, Elf32_Shdr **sym, char **strtab, char *file);
int		printSymb32(void *buff, char *file, int ac, int i);
int		getElfVer32(Elf32_Ehdr *data);
int		isFromSec32(Elf32_Sym *symtab, char *shstrtab, Elf32_Shdr *sec, const char *name);
char		getTypeSymb32(Elf32_Sym *sym, Elf32_Shdr *shdr, char *strtab);
char		*remUnder32(char *str);
int		howManyTables32(unsigned int type, void *buff);
Elf32_Shdr	*secFnd32(unsigned int type, void *buff, int pos);
int		toNotPrint32(void *buff, void *s, int nb);
void		getSecH32(void *buff, Elf32_Shdr **sec, char **strtab);
int		printSecs32(void *buff, char *file, int ac, struct stat s);
void		printMachine32(Elf32_Ehdr *elf, char *file, int ac);
void		printString32(Elf32_Shdr *sec, unsigned char *str, int nb);
void		printHexa32(Elf32_Shdr *sec, unsigned char *str, int nb);
void		printSec32(void *buff, Elf32_Shdr *sec);
#endif
