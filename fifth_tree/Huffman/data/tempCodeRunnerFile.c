void statCount()
{
	char str[500];
	int len, i;
	while (fgets(str, 500, Src) != NULL)
	{
		len = strlen(str);
		if (str[len-1]=='\n')
			str[len-1] = 0;
		for (i = 0; i < len-1; i++)
		{
			if (str[i]>0)
				Ccount[str[i]]++;
		}
	}
	Ccount[0]= 1;
}