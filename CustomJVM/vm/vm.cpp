#include "vm.hpp"

typedef jint(JNICALL* JNI_CreateJavaVM_func)(JavaVM** pvm, void** penv, void* args);
JNI_CreateJavaVM_func JNI_CreateJavaVM_ptr;

void vm::add_to_path(JNIEnv* env, std::string path)
{
	const std::string urlPath = "file:/" + path;
	jclass class_loader = env->FindClass("java/lang/ClassLoader");
	jmethodID system_class_loader = env->GetStaticMethodID(class_loader, "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
	jobject class_loader_instance = env->CallStaticObjectMethod(class_loader, system_class_loader);

	jclass url_class_loader = env->FindClass("java/net/URLClassLoader");
	jmethodID add_url = env->GetMethodID(url_class_loader, "addURL", "(Ljava/net/URL;)V");
	jclass url_class = env->FindClass("java/net/URL");
	jmethodID url_constructor = env->GetMethodID(url_class, "<init>", "(Ljava/lang/String;)V");
	jobject url_instance = env->NewObject(url_class, url_constructor, env->NewStringUTF(urlPath.c_str()));
	env->CallVoidMethod(class_loader_instance, add_url, url_instance);
}

JNIEnv* vm::create_vm(JavaVM** jvm, std::string natives)
{
	JNIEnv* env;
	JavaVMInitArgs vm_args;

	//set vm arguments
	JavaVMOption* options = new JavaVMOption[1];
	options[0].optionString = (char*) natives.c_str();
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 1;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;

	char* javaHome = getenv("JAVA_HOME");

	if (!javaHome) {
		printf("Could not find %JAVA_HOME%! it must be set in Path! \n");
		return NULL;
	}

	std::string jvmDLL;

	//find proper jvm.dll
	if (std::string(javaHome).find("jdk") != std::string::npos) {
		jvmDLL = std::string(javaHome) + SEP + "jre" + SEP + "bin" + SEP + "server" + SEP + "jvm.dll";
	}
	else {
		jvmDLL = std::string(javaHome) + SEP + "bin" + SEP + "server" + SEP + "jvm.dll";
	}

	// Load jvm.dll
	HMODULE jvmLib = LoadLibraryA(jvmDLL.c_str());
	if (!jvmLib) {
		printf("ERROR: Could not load jvm.dll \n");
		return NULL;
	}
	JNI_CreateJavaVM_ptr = (JNI_CreateJavaVM_func)GetProcAddress(jvmLib, "JNI_CreateJavaVM");

	jint rc = JNI_CreateJavaVM_ptr(jvm, (void**)&env, &vm_args);

	delete options;

	if (rc != JNI_OK) {
		return NULL;
	}

	return env;
}