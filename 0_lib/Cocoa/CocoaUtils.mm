
#include <Cocoa/Cocoa.h>
#include "CocoaUtils.h"

#import "NSString+SymlinksAndAliases.h"

const char *getActualPathFromResolvedAliases(const char *path)
{
	NSApplicationLoad();
	static char outPath[65536];
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	
	NSString *fullyResolvedPath = [[NSString stringWithFormat:@"%s", path] stringByResolvingSymlinksAndAliases];

//	NSLog(@"%@", fullyResolvedPath);
	
	sprintf(outPath, "%s/", [fullyResolvedPath UTF8String]);
	
	[pool release];
	
//	printf("path = '%s'\n", outPath);
	
//	char testStr[16384];
//	sprintf(testStr, "%s/test.txt", outPath);
//	FILE *fp = fopen(testStr, "w");
//	fclose(fp);
	
	return (const char*)outPath;
}
