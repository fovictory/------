/******************************************************************************

Copyright (C), 2001-2013, Huawei Tech. Co., Ltd.

******************************************************************************
File Name     :
Version       :
Author        :
Created       : 2013/9
Last Modified :
Description   :
Function List :

History       :
1.Date        : 2013/9
Author      :
Modification: Created file

******************************************************************************/
#include "FileManager.h"
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct File {
	char* parentname;
	char* filename;
	int type; //0 dir 1 file 
} FileInfo;

typedef std::vector<FileInfo*> VecFileInfo;
VecFileInfo vecfileinfo;
bool bInit = false;
int removedircnt = 0;
int temp = 0;

int CreateDir(const char * ParentDirName, const char * DirName)
{
	if(bInit == false){
		FileInfo* m_f = (FileInfo*)malloc(sizeof(FileInfo));
		m_f->filename = (char*)malloc(1000*sizeof(char));
		m_f->parentname = (char*)malloc(10000*sizeof(char));
		strcpy(m_f->filename,"root");
		strcpy(m_f->parentname,"");
		m_f->type = 0;
		vecfileinfo.push_back(m_f);
		bInit = true;
	}

	bool findparent = false;
	bool finddir = false;
	for(int j=0;j<(vecfileinfo).size();j++){
		if((strcmp(vecfileinfo[j]->filename,ParentDirName) == 0)&&(vecfileinfo[j]->type == 0)){
			findparent = true;
		}
	}
	if(findparent == false){
		return -1;
	}
	for(int j=0;j<(vecfileinfo).size();j++){

		if((strcmp(vecfileinfo[j]->filename,DirName) == 0)&&(vecfileinfo[j]->type == 0)){
			finddir = true;
		}
	}
	if(finddir == true){
		return -1;
	}
	FileInfo* fi = (FileInfo*)malloc(sizeof(FileInfo));
	fi->filename = (char*)malloc(1000*sizeof(char));
	fi->parentname = (char*)malloc(10000*sizeof(char));
	strcpy(fi->filename,DirName);
	strcpy(fi->parentname,ParentDirName);
	fi->type = 0;
	vecfileinfo.push_back(fi);
    return 0;
}

void DeleteDir(const char * DirName)
{
	int cnt = 0;
	int cnt_firsrrem = 0;
	if(removedircnt == 0){
		for(VecFileInfo::iterator it = vecfileinfo.begin();it != vecfileinfo.end();){
			if((strcmp(vecfileinfo[cnt_firsrrem]->filename,DirName) == 0)&&(vecfileinfo[cnt_firsrrem]->type == 0)){
				it = vecfileinfo.erase(it);
			}else{
				it++;
				cnt_firsrrem++;
			}
		}
	}
	removedircnt++;
	for(VecFileInfo::iterator it = vecfileinfo.begin();it != vecfileinfo.end();){
		if((strcmp(vecfileinfo[cnt]->parentname,DirName) == 0)&&(vecfileinfo[cnt]->type == 0)){
			DeleteDir(vecfileinfo[cnt]->filename);
			removedircnt--;
			it = vecfileinfo.erase(it);
		}else if((strcmp(vecfileinfo[cnt]->parentname,DirName) == 0)&&(vecfileinfo[cnt]->type == 1)){
			it = vecfileinfo.erase(it);
		}else{
			it++;
			cnt++;
		}
	}
	removedircnt = 0;
    return;
}
int MoveDir(const char * SrcDirName, const char * DestDirName)
{
	bool bsrcdir = false;
	bool bdestdir = false;
	for(int j=0;j<(vecfileinfo).size();j++){
		if((strcmp(vecfileinfo[j]->filename,DestDirName) == 0)&&(vecfileinfo[j]->type == 0)){
			bdestdir = true;
		}
	}
	if(bdestdir == false){
		return -1;
	}

	for(int j=0;j<(vecfileinfo).size();j++){
		if((strcmp(vecfileinfo[j]->filename,SrcDirName) == 0)&&(vecfileinfo[j]->type == 0)){
			strcpy(vecfileinfo[j]->parentname,DestDirName);
			bsrcdir = true;
		}
	}
	if(bsrcdir == false){
		return -1;
	}

    return 0;
}

int CreateFile(const char * DirName, const char * FileName)
{
	if(bInit == false){
		FileInfo* m_f = (FileInfo*)malloc(sizeof(FileInfo));
		m_f->filename = (char*)malloc(1000*sizeof(char));
		m_f->parentname = (char*)malloc(10000*sizeof(char));
		strcpy(m_f->filename,"root");
		strcpy(m_f->parentname,"");
		m_f->type = 0;
		vecfileinfo.push_back(m_f);
		bInit = true;
	}

	bool findparent = false;
	bool finddir = false;
	for(int j=0;j<(vecfileinfo).size();j++){
		if((strcmp(vecfileinfo[j]->filename,DirName) == 0)&&(vecfileinfo[j]->type == 0)){
			findparent = true;
		}
	}
	if(findparent == false){
		return -1;
	}
	for(int j=0;j<(vecfileinfo).size();j++){

		if((strcmp(vecfileinfo[j]->filename,FileName) == 0)&&(vecfileinfo[j]->type == 1)){
			finddir = true;
		}
	}
	if(finddir == true){
		return -1;
	}
	FileInfo* fi = (FileInfo*)malloc(sizeof(FileInfo));
	fi->filename = (char*)malloc(1000*sizeof(char));
	fi->parentname = (char*)malloc(10000*sizeof(char));
	strcpy(fi->filename,FileName);
	strcpy(fi->parentname,DirName);
	fi->type = 1;
	vecfileinfo.push_back(fi);
	return 0;
}

void DeleteFile(const char * FileName)
{
	int cnt = 0;

	for(VecFileInfo::iterator it = vecfileinfo.begin();it != vecfileinfo.end();){
		if((strcmp(vecfileinfo[cnt]->filename,FileName) == 0)&&(vecfileinfo[cnt]->type == 1)){
			it = vecfileinfo.erase(it);
		}else{
			it++;
			cnt++;
		}


	}
    return;
}

unsigned int GetFileNum(const char * DirName)
{
	int cnt = 0;
	for(int j=0;j<(vecfileinfo).size();j++){

		if((strcmp(vecfileinfo[j]->parentname,DirName) == 0)&&(vecfileinfo[j]->type == 1)){
			cnt++;
		}else if((strcmp(vecfileinfo[j]->parentname,DirName) == 0)&&(vecfileinfo[j]->type == 0)){
			cnt = cnt+GetFileNum(vecfileinfo[j]->filename);
		}
	}
	//printf("%d\n",cnt);
    return cnt;
}

void Clear(void)
{
	bInit = false;
	VecFileInfo().swap(vecfileinfo);
	//vecfileinfo = NULL;
	removedircnt = 0;
    return;
}
