#include "main.h"
/**
 * _code - changes directory buildin
 * @av: arg to work with
 * Return: integer
 */

int _cd(char *av[])
{
	char *oldpwd = NULL, *newpath, *pathbit, *newptr;
	char *homestr = "HOME", *oldpwdstr = "OLDPWD";
	int ret, printpath = 0;

	oldpwd = getcwd(oldpwd, 0);
	if (oldpwd == NULL)
		return (1);
	if (av[1] == NULL || av[1][0] == 0)
	{
		newpath = _getenv(homestr);
		if (newpath == homestr)
			newpath = _strdup(" ");
		av[1] = newpath;
		av[2] = NULL;
	}
	else if (av[1][0] == '-' && av[1][1] == 0)
	{
		newpath = _getenv(oldpwdstr);
		if (newpath == oldpwdstr)
			newpath = _strdup(" ");
		printpath = 1;
		free(av[1]);
		av[1] = newpath;
	}
#ifdef DUBUGCD
	printf("Making new path %s: %c\n", av[1], av[1][0]);
#endif
	newpath = malloc(sizeof(char) * (_strlen(oldpwd) + _strlen(av[1] + 2)));
	if (newpath == NULL)
		return (-1);
	newptr = newpath;
	pathbit = oldpwd;
	if (av[1][0] != '/' && pathbit[1] != 0)
		while (*pathbit)
			*newptr++ = *pathbit++;
	*newptr++ = '/';
	pathbit = _strtok(av[1], "/");
#ifdef DUBUGCD
	printf("Starting newpath: %s Pathbit got: %s \n", newpath, pathbit);
	printf("newpath/ptr diff: %p \n", newptr - newpath);
#endif
	while (pathbit != NULL)
	{
		if (pathbit[0] == '.' && pathbit[1] == '.' && pathbit[2] == 0)
		{
#ifdef DUBUGCD
			printf("going back a directory %s: %s\n", newpath, newpath);
#endif
			newptr--;
			if(newptr != newpath)
				newptr--;
			while (*newptr != '/')
				newptr--;
			*newptr++ = '/';
		}
		else if (!(pathbit[0] == '.' && pathbit[1] == 0))
		{
			while (*pathbit)
				*newptr++ = *pathbit++;
			*newptr++ = '/';
		}
		pathbit = _strtok(NULL, "/");
#ifdef DUBUGCD
		printf("Got pathbit: %s \n", pathbit);
#endif
	}
	if (newptr != newpath && newptr != newpath + 1)
		newptr--;
	*newptr = 0;
#ifdef DUBUGCD
	printf("New path: %s\n", newpath);
#endif
	ret = chdir(newpath);
	if (ret == 0)
	{
		_setenv("OLDPWD", oldpwd);
		free(oldpwd);
		_setenv("PWD", newpath);
		if (printpath)
			fprintstrs(1, newpath, "\n", NULL);
		free(newpath);
		return (0);
	}
	printerr(": cd: can't cd tp ");
	fprintstrs(STDERR_FILENO, av[1], "\n", NULL);
	free(oldpwd);
	free(newpath);
	return (ret);
}
