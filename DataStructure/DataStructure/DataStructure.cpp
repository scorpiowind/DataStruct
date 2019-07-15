// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "tree.h"
#include <iostream>

template<typename T>
const string  BinaryTree::tree<T>::visualFile = "visualFile.md";

int main()
{
	auto test = BinaryTree::treeTest();
	test.testMain();
}

