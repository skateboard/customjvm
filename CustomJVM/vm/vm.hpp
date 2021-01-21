#pragma once
#include <jni.h>
#include <Windows.h>
#include <string>

#ifdef _WIN32
#define SEP  '\\';
#else
#define SEP '/';
#endif

namespace vm {
	void add_to_path(JNIEnv* env, std::string path);
	JNIEnv* create_vm(JavaVM** jvm, std::string natives);
}