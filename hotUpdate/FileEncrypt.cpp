//
//  encrypt.cpp
//  FileEncrypt
//
//  Created by 李伟光 on 13-9-2.
//
//

#include "FileEncrypt.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
/*****************
 找出所有文件
*****************/
string fileOutPath = "newfileOutPath";
void FileEncrypt::FindAllFile(string folderPath)
{
//    if(folderPath.find(".jpg")!=folderPath.npos||folderPath.find(".png")!=folderPath.npos||folderPath.find(".ccz")!=folderPath.npos)
//    {
//        encryptFileByName(folderPath);
//    }
    
    if(folderPath.find(".")!=folderPath.npos)
    {
        encryptFileByName(folderPath);
    }
    DIR *dp;
    struct dirent* dirp;
    
    if((dp = opendir(folderPath.c_str())) == NULL)
    {
        //CCLog("can not match the folder path");
        std::cout<<folderPath.c_str()<<std::endl;

        return;
    }
    while ((dirp=readdir(dp))!=NULL)
    {
        struct stat buf;
        stat(folderPath.c_str(), &buf);
        
        // 如果是目录
        if (S_ISDIR(buf.st_mode))
        {
            string path;
            if( (strcmp(dirp->d_name,".") != 0 ) &&(strcmp(dirp->d_name,"..") != 0))
            {
                path =  folderPath + "/" + dirp->d_name;
            }
            // std::cout<<"文件夹路径:"<<dirp->d_name<<std::endl;
            //如果是目录，递归调用
            FindAllFile(path);
        }
        else
        {
            // 如果是文件直接打印
            //CCLog("%s/%s\n",folderPath.c_str(),dirp->d_name);
        }
    }
    closedir(dp);

}
/*****************
 文件加密
 *****************/
void FileEncrypt::encryptFileByName(string pFileName)
{
    //第一先获取文件的路径
    string path =pFileName;  //CCFileUtils::sharedFileUtils()->getWriteablePath() + pFileName;
    //CCLOG("path = %s",path.c_str());
    // std::cout<<"ddddddeeeee"<< std::endl;
    // std::cout<<path.c_str()<< std::endl;
    // std::cout<<"eeeeee"<< std::endl;
    if(pFileName.find("startGame")!=path.npos)
    {
        std::cout<<"加密的文件输出路径为:";
    }
    //    lua文件
    if(pFileName.find(".lua")!=pFileName.npos)
    {
        FILE* file = fopen(path.c_str(), "rb");
        saveFile2(pFileName,file);
    }
    //    图片资源
    else
    {
      unsigned long nSize = 0;
      unsigned char* pBuffer = getFileData(pFileName.c_str(),"rb",&nSize);
      int newblen = nSize;

      if(pBuffer!=NULL&&nSize>0)
      {
         if(pFileName.find(".jpg")!=pFileName.npos||pFileName.find(".png")!=pFileName.npos||pFileName.find(".ccz")!=pFileName.npos)
         {
             for (int i = 0; i<nSize; i++)
             {
                 if(i==0)
                 {
                     pBuffer[i]=pBuffer[i]+1;
                 }
                 if(i==2)
                 {
                     pBuffer[i]=pBuffer[i]-1;
                 }
                 if(i>=2)
                 {
                     break;
                 }
              }
          }
           
           
          string path =  _outputPath;
          mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
          //创建一个文件指针
          //路径、模式
          string::size_type position=pFileName.find("willZipResAndSrcFile");
          
          string namePath=pFileName.substr(position+21,pFileName.npos);
          string namePath2=namePath;
          while (namePath.find("/")!=namePath.npos)
          {
          
              mkdir((path+namePath.substr(0,namePath.find("/"))).c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
              path+=namePath.substr(0,namePath.find("/"))+"/";
              namePath=namePath.substr(namePath.find("/")+1,namePath.npos);
          }
        
          path=path+namePath;

        
          FILE *fp = fopen(path.c_str(), "wb+");
          fwrite(pBuffer, 1, newblen, fp);
          fclose(fp);
      }
        
    }
    
}

bool FileEncrypt::saveFile2(string pFileName,FILE *file)
{
    string path = _outputPath;
    mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
    //创建一个文件指针
    //路径、模式
    string::size_type position=pFileName.find("willZipResAndSrcFile");
    // std::cout<<"位置1111111"<<pFileName<<position<<std::endl;

    string namePath= pFileName.substr(position+21,pFileName.npos);
    string namePath2=namePath;

    // std::cout<<"这个是什么"<<pFileName<<std::endl;

    while (namePath.find("/")!=namePath.npos) 
    {
        mkdir((path+namePath.substr(0,namePath.find("/"))).c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
        path+=namePath.substr(0,namePath.find("/"))+"/";
        namePath=namePath.substr(namePath.find("/")+1,namePath.npos);
    }
    
    path=path+namePath;
    
    std::cout<<"path"<<path<<std::endl;
    FILE* file2 = fopen(path.c_str(), "wb");
    int i = 0;
    char c;
    while ( (c = fgetc(file)) != EOF) 
    {
        if ( i%2 == 0) 
        {
            c = c + 10;
        }
        else 
        {
            c = c + 20;
        }
        i++;
        fputc(c, file2);
    }
    
    fclose(file);
    fclose(file2);
}


unsigned char* FileEncrypt::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;

    *pSize = 0;
    do
    {
        FILE *fp = fopen(pszFileName, pszMode);
        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new (std::nothrow) unsigned char[*pSize];
        if (pBuffer == 0) {
            printf("[std::bad_alloc] %s:%d\n", pszFileName, *pSize);
        }
        
        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);
    

    return pBuffer;
}
void FileEncrypt::setOutputPath(const char* outputpath)
{
    // fileOutPath=outputpath;
    _outputPath = outputpath;

    printf("[-FileEncrypt output:  %s]\n", _outputPath.c_str());
}
