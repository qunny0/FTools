//  Created by fym on 16/8/4.

#include "FileEncrypt.h"

//  参数 需要处理的文件路径
// string fileSourcePath = "newfileSourcePath";

int main(int argc, char* argv[])
{
	printf("--[main]-- %d input: %s output: %s\n", argc, argv[1], argv[2]);
	if (argc < 3) {
		printf("!!! please input file path\n");
		return 1;
	}

    FileEncrypt *fe = new FileEncrypt(argv[2]);
    string readPath = argv[1];
    // fe->setOutputPath(argv[2]);
    fe->FindAllFile(readPath);

    return 0;
}
