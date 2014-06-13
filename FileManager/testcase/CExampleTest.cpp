
#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include "FileManager.h"

// 注册测试套到CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION( CExampleTest );

// 测试用例实现示例

// SetUp: 在每个用例前执行一次
void CExampleTest::setUp()
{

}

// tearDown: 在每个用例后执行一次
void CExampleTest::tearDown()
{
    Clear();
}

void CExampleTest::TestCase01()
{
	int result = 0;
    result = CreateDir("root", "DirA");
	result = CreateDir("DirA", "DirB");
	result = CreateDir("root", "DirC");
	result = CreateDir("un", "test");
	result = CreateFile("DirA", "File2");
    result = CreateFile("DirA", "File1");
	result = CreateFile("DirB", "File3");
	result = CreateFile("DirC", "File4");
	result = CreateDir("DirC", "DirD");
	result = CreateFile("DirD", "File5");
	result = CreateFile("DirB", "DirE");
	result = CreateFile("DirE", "DirF");
	result = CreateFile("DirB", "DirG");
	result = CreateFile("DirG", "DirH");

	
	//MoveDir("DirD", "DirB");
	//DeleteFile("File4");
	//DeleteDir("DirA");
    CPPUNIT_ASSERT(0 == GetFileNum("DirK"));
}
void CExampleTest::TestCase02()
{
	int result = 0;
	result = CreateDir("root", "DirY");


	//MoveDir("DirD", "DirB");
	//DeleteFile("File4");
	DeleteDir("DirY");
	CPPUNIT_ASSERT(2 == GetFileNum("DirC"));
}
