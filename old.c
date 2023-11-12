
char *getstr(const char* src);
//my strdup implementation
char *getstr(const char* src){
int l; for (l=0;src[l];l++);
char *dst=(char*)malloc(l+1);
for (;l>=0;l--) dst[l]=src[l];
return dst;}
