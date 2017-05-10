//  Created by fym on 16/8/4.

#include "FileEncrypt.h"
//  参数 需要处理的文件路径
string fileSourcePath = "newfileSourcePath";
int main()
{
    FileEncrypt *fe = new FileEncrypt();
    string readPath = fileSourcePath;
    fe->FindAllFile(readPath);
    return 0;
}
