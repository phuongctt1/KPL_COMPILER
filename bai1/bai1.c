#include <stdio.h>
#include<string.h>
void docfile()
{
	FILE * file,*f,*f1,*f2;
	char a[50]="\0",b[50]="\0";
	char i,m;
	int j=0,k,n=0,p=0,l=1;
	file = fopen ("vanban.txt" , "rt");
	
		do{	
		f = fopen ("stopw.txt" , "rt");
			i=getc(file);			
			while(i>='A'&&i<='Z')
			{
				while(i>='A'&&i<='z')
				i=getc(file);
				if(i=='.')
				{  do{i=getc(file);if(i=='\n') l=l+1;i=getc(file);if(i=='\n') l=l+1;}
					while(i<'A'||i>'z');

					a[0]=i;j=1;i=getc(file);
				}
				if(i=='\n') l=l+1;
			}
				while(i>='a'&&i<='z')
					{
						a[j]=i;
						j++;
						a[j]='\0';
						i= getc(file);
					}
				 if(a[0]!=NULL)
				 {
 					for(k=0;k<j;k++)
 					if(a[k]>='A'&&a[k]<='Z')
 						a[k]=a[k]+32;
 					do
					 {m=getc(f);
			 			while(m>='A'&&m<='z')
 						{				 	
					 		b[n]=m;
					 		n++;
					 		b[n]='\0';
						 	m=getc(f);
						 }
						 if(strcmp(b,a)==0)
 							p=1;			
 							
						b[0]='\0';
						n=0;
					 }while(m!=EOF);
				if(p!=1)
						{
							f1 = fopen ("file1" , "a+");
							fprintf(f1,"%s\n",a);
							fclose (f1);
							f2 = fopen ("file2" , "a+");
							fprintf(f2,"%s %d\n",a,l);
							fclose (f2);
																							
						}
				 p=0;					
 				}
						 a[0]='\0';
						 j=0;
				if(i=='.')
				{  
					do{i=getc(file);if(i=='\n') l=l+1;}
					while((i<'A'||i>'z')&&i!=EOF);
					a[0]=i;j=1;					
				}
				if(i=='\n') l=l+1;
				fclose (f);				
		}while(i!= EOF);
		fclose (file);
			
		
}
void tachfile()
{
	FILE *f,*f1,*f2,*f3;
	char a[50]="\0",b[50]="\0",m,n;
	f= fopen("file1","rt");
	int p=0,i=0,u=0,k,j,z=0;
	
	while(fgets(a,100,f)!=NULL)
		{
			f1= fopen("file3","a+");
			while(fgets(b,100,f1)!=NULL)
				{				
					if(strcmp(b,a)==0)
					p=1;
				}
			if(p!=1)
				{
					fprintf(f1,"%s",a);
				}
			p=0;
			fclose (f1);
		}
		
	f1= fopen("file3","rt");
	while(fgets(a,100,f1)!=NULL)
	{
		f= fopen("file1","rt");
		f2= fopen("file4","a+");
		while(fgets(b,100,f)!=NULL)
		{
			if(strcmp(b,a)==0)
					u=u+1;
		}
		i=0;
			while(a[i]!='\0')
			{
				if(a[i]=='\n')
					a[i]='\0';				
				i++;
			}	
			fprintf(f2,"%d\n",u);
		u=0;
	}
	fclose (f);
	fclose (f2);
	f1=fopen("file3","rt");
	m=getc(f1);
	while(m!=EOF)
		{
			i=0;			
			while(m>='a'&&m<='z')
			{
				a[i]=m;
				a[i+1]='\0';
				i++;
				m=getc(f1);
			}
			f2=fopen("file2","rt");
			n=getc(f2);
			while(n!=EOF)
				{	
					j=0;
					while(n>='a'&&n<='z')
					{
						b[j]=n;
						b[j+1]='\0';
						j++;
						n=getc(f2);
					}
					if(strcmp(b,a)==0)
					{
						n=getc(f2);
						f3=fopen("file5","a+");
						fprintf(f3,",%c",n);
						fclose(f3);
					}
					b[0]='\0';
					n=getc(f2);
				}
				f3=fopen("file5","a+");
				fprintf(f3,"\n");
				fclose(f3);
				a[0]='\0';
				m=getc(f1);
		}
		fclose (f1);
	fclose (f2);
}
void ghepfile()
{
	FILE *f,*f1,*f2;
	char a[50]="\0",b[50]="\0",c[50]="\0";
	int i;
	f=fopen("file3","rt");
	f1=fopen("file4","rt");
	f2=fopen("file5","rt");
	while(fgets(a,100,f)!=NULL)
	{
		fgets(b,100,f1);
		fgets(c,100,f2);
		i=0;
		while(a[i]!='\0')
			{
				if(a[i]=='\n')
					a[i]='\0';				
				i++;
			}
		i=0;
		while(b[i]!='\0')
			{
				if(b[i]=='\n')
					b[i]='\0';				
				i++;
			}
		i=0;
		while(c[i]!='\0')
			{
				if(c[i]=='\n')
					c[i]='\0';				
				i++;
			}
		
		printf("%s %s%s\n",a,b,c);
		
				
	}
	fclose(f);
	fclose(f1);
	fclose(f2);
}
main()
{
	docfile();
	tachfile();
	ghepfile();
	

	return 0;
}
